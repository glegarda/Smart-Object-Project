/**
 * @file <argos3/plugins/robots/object/simulator/accelerometer_equipped_entity.cpp>
 * @author Piotr Rochala
 */

#ifndef ACCELEROMETER_EQUIPPED_ENTITY_H
#define ACCELEROMETER_EQUIPPED_ENTITY_H

#include <argos3/core/simulator/entity/entity.h>
#include <argos3/core/utility/math/vector3.h>
#include <argos3/core/simulator/entity/embodied_entity.h>
#include <map>

namespace argos {

   class CAccelerometerEquippedEntity : public CEntity {

   public:

      ENABLE_VTABLE();

     struct SSensor {
         typedef std::vector<SSensor*> TList;

         CVector3 Offset;
         SAnchor& Anchor;
 
         SSensor(const CVector3& c_offset,
                 SAnchor& s_anchor) :
            Offset(c_offset),
            Anchor(s_anchor) {}
      };

   public:
      CAccelerometerEquippedEntity(CComposableEntity* pc_parent);
      CAccelerometerEquippedEntity(CComposableEntity* pc_parent, const std::string& str_id);

      virtual ~CAccelerometerEquippedEntity();

      virtual void Init(TConfigurationNode& t_tree);

      virtual void Enable();

      virtual void Disable();
      

      inline size_t GetNumSensors() const {
         return m_tSensors.size();
      }

      inline SSensor& GetSensor(size_t un_idx) {
         return *m_tSensors[un_idx];
      }

      inline SSensor::TList& GetSensors() {
         return m_tSensors;
      }

      void AddSensor(const CVector3& c_offset,
                     SAnchor& s_anchor);

      virtual std::string GetTypeDescription() const {
         return "accelerometer";
      }

   protected:

      /** The list of sensors */
      SSensor::TList m_tSensors;
   };

}

#endif
