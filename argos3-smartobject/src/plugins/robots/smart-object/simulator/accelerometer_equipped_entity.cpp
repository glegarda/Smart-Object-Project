/**
 * @file <argos3/plugins/robots/object/simulator/accelerometer_equipped_entity.cpp>
 * @author Piotr Rochala
 */

#include "accelerometer_equipped_entity.h"
#include <argos3/core/simulator/space/space.h>
#include <argos3/core/simulator/entity/composable_entity.h>

namespace argos {

   /****************************************/
   /****************************************/

	CAccelerometerEquippedEntity::CAccelerometerEquippedEntity(CComposableEntity* pc_parent) : 
		CEntity(pc_parent) {
			Disable();
		}

   /****************************************/
   /****************************************/

	CAccelerometerEquippedEntity::CAccelerometerEquippedEntity(CComposableEntity* pc_parent,
									const std::string& str_id) : 
		CEntity(pc_parent, str_id) {
			Disable();
		}

   
   /****************************************/
   /****************************************/

	CAccelerometerEquippedEntity::~CAccelerometerEquippedEntity() {
		while(! m_tSensors.empty()) {
			delete m_tSensors.back();
			m_tSensors.pop_back();
		}
   }

   /****************************************/
   /****************************************/

	void CAccelerometerEquippedEntity::Init(TConfigurationNode& t_tree) {
	    try {
		 /*
		  * Parse basic entity stuff
		  */
		 CEntity::Init(t_tree);
		 /*
		  * Parse accelerometer sensors
		  */
		 /* Not adding any sensor is a fatal error */
		 if(t_tree.NoChildren()) {
			THROW_ARGOSEXCEPTION("No sensors defined");
		 }
		 /* Go through children */
		 TConfigurationNodeIterator it;
		 for(it = it.begin(&t_tree); it != it.end(); ++it) {
			std::string strAnchorId;
			GetNodeAttribute(*it, "anchor", strAnchorId);
			/*
			 * NOTE: here we get a reference to the embodied entity
			 * This line works under the assumption that:
			 * 1. the entity has a parent;
			 * 2. the parent has a child whose id is "body"
			 * 3. the "body" is an embodied entity
			 * If any of the above is false, this line will bomb out.
			 */
			CEmbodiedEntity& cBody = GetParent().GetComponent<CEmbodiedEntity>("body");
			if(it->Value() == "sensor") {
			   CVector3 cPos;
			   GetNodeAttribute(*it, "position", cPos);
			   AddSensor(cPos, cBody.GetAnchor(strAnchorId));
			} else {
			   THROW_ARGOSEXCEPTION("Unrecognized tag \"" << it->Value() << "\"");
			}
		  }
		  }catch(CARGoSException& ex) {
		 	THROW_ARGOSEXCEPTION_NESTED("Initialization error in accelerometer equipped entity", ex);
		  }
	}


   /****************************************/
   /****************************************/

   void CAccelerometerEquippedEntity::AddSensor(const CVector3& c_offset,
                                               SAnchor& s_anchor) {
      m_tSensors.push_back(new SSensor(c_offset, s_anchor));
   }

   
   /****************************************/
   /****************************************/
   
   void CAccelerometerEquippedEntity::Enable() {
	 CEntity::Enable();
		  for(size_t i = 0; i < m_tSensors.size(); ++i) {
		     m_tSensors[i]->Anchor.Enable();
		  }

   }
   /****************************************/
   /****************************************/
   
   void CAccelerometerEquippedEntity::Disable() {
	 CEntity::Disable();
		  for(size_t i = 0; i < m_tSensors.size(); ++i) {
		     m_tSensors[i]->Anchor.Disable();
		  }

   }
   
   /****************************************/
   /****************************************/


   REGISTER_STANDARD_SPACE_OPERATIONS_ON_ENTITY(CAccelerometerEquippedEntity);

   /****************************************/
   /****************************************/

}
