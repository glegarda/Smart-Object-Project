/**
 * @file <argos3/plugins/robots/object/simulator/smartobject_entity.cpp>
 */

#include "smartobject_entity.h"
#include "accelerometer_equipped_entity.h"

#include <argos3/core/utility/math/matrix/rotationmatrix3.h>
#include <argos3/core/simulator/space/space.h>
#include <argos3/core/simulator/entity/controllable_entity.h>
#include <argos3/core/simulator/entity/embodied_entity.h>
#include <argos3/plugins/simulator/entities/ground_sensor_equipped_entity.h> 
#include <argos3/plugins/simulator/entities/led_equipped_entity.h>
namespace argos {

   /****************************************/
   /****************************************/

   static const Real BODY_RADIUS                = 0.065f;
   static const Real BODY_HEIGHT                = 0.115f;  //0.08
   static const Real BODY_MASS 		  = 2.0f;
   static const UInt32 LED_COUNT		  = 256;  //256

  // static const CRadians LED_RING_START_ANGLE   = CRadians((ARGOS_PI / 8.0f) * 0.5f);
   //static const CRadians LED_RING_START_ANGLE   = CRadians(ARGOS_PI / 8.0f);
    static const CRadians LED_RING_START_ANGLE   = CRadians(ARGOS_PI / (Real) LED_COUNT);
   static const Real LED_RING_RADIUS            = BODY_RADIUS;
   //static const Real LED_RING_ELEVATION         = 0.14 - 0.035/2; // BODY_HEIGHT
    static const Real LED_RING_ELEVATION         = 0.115 - 0.035/2; // BODY_HEIGHT


   /****************************************/
   /****************************************/

   CSmartObjectEntity::CSmartObjectEntity() :
      CComposableEntity(NULL),
      m_pcControllableEntity(NULL),
      m_pcEmbodiedEntity(NULL),
      m_pcLEDEquippedEntity(NULL),
      m_pcGroundSensorEquippedEntity(NULL),
      m_pcAccelerometerEquippedEntity(NULL) {
   }

   /****************************************/
   /****************************************/

   CSmartObjectEntity::CSmartObjectEntity(const std::string& str_id,
                              const std::string& str_controller_id,
                              const CVector3& c_position,
                              const CQuaternion& c_orientation) :
      CComposableEntity(NULL, str_id),
      m_pcControllableEntity(NULL),
      m_pcEmbodiedEntity(NULL),
      m_pcLEDEquippedEntity(NULL),
      m_pcGroundSensorEquippedEntity(NULL),
      m_pcLightSensorEquippedEntity(NULL),
      m_pcAccelerometerEquippedEntity(NULL){
      try {
         m_pcEmbodiedEntity = new CEmbodiedEntity(this, "body_0", c_position, c_orientation);
         AddComponent(*m_pcEmbodiedEntity);

	/* LED equipped entity */
         m_pcLEDEquippedEntity = new CLEDEquippedEntity(this, "leds_0");
         AddComponent(*m_pcLEDEquippedEntity);
         m_pcLEDEquippedEntity->AddLEDRing(
            CVector3(0.0f, 0.0f, LED_RING_ELEVATION),
            LED_RING_RADIUS,
            LED_RING_START_ANGLE,
            LED_COUNT,
            m_pcEmbodiedEntity->GetOriginAnchor());
       
         /* Ground sensor equipped entity */
         m_pcGroundSensorEquippedEntity =
            new CGroundSensorEquippedEntity(this,
                                            "ground_0");
         AddComponent(*m_pcGroundSensorEquippedEntity);
         m_pcGroundSensorEquippedEntity->AddSensor(CVector2(0.03f, 0.0f),
                                                   CGroundSensorEquippedEntity::TYPE_GRAYSCALE, //TYPE_GRAYSCALE TYPE_BLACK_WHITE
         m_pcEmbodiedEntity->GetOriginAnchor());

	/* Accelerometer equipped entity */
    	m_pcAccelerometerEquippedEntity =
            new CAccelerometerEquippedEntity(this,
                                            "acc_0");
         AddComponent(*m_pcAccelerometerEquippedEntity);
         m_pcAccelerometerEquippedEntity->AddSensor(CVector3(0.03f, 0.0f, 0.05f),
         m_pcEmbodiedEntity->GetOriginAnchor());
       
         /* Controllable entity
            It must be the last one, for actuators/sensors to link to composing entities correctly */
         m_pcControllableEntity = new CControllableEntity(this);
         AddComponent(*m_pcControllableEntity);
         m_pcControllableEntity->SetController(str_controller_id);
         /* Update components */
         UpdateComponents();
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Failed to initialize entity \"" << GetId() << "\".", ex);
      }
   }

   /****************************************/
   /****************************************/

   void CSmartObjectEntity::Init(TConfigurationNode& t_tree) {
      try {
         /*
          * Init parent
          */
         CComposableEntity::Init(t_tree);
         /*
          * Create and init components
          */
         /* Embodied entity */
         m_pcEmbodiedEntity = new CEmbodiedEntity(this);
         AddComponent(*m_pcEmbodiedEntity);
         m_pcEmbodiedEntity->Init(GetNode(t_tree, "body"));

	/* LED equipped entity */
         m_pcLEDEquippedEntity = new CLEDEquippedEntity(this, "leds_0");
         AddComponent(*m_pcLEDEquippedEntity);
         m_pcLEDEquippedEntity->AddLEDRing(
            CVector3(0.0f, 0.0f, LED_RING_ELEVATION),
            LED_RING_RADIUS,
            LED_RING_START_ANGLE,
            LED_COUNT,
            m_pcEmbodiedEntity->GetOriginAnchor());

         /* Ground sensor equipped entity */
         m_pcGroundSensorEquippedEntity =
            new CGroundSensorEquippedEntity(this,
                                            "ground_0");
         AddComponent(*m_pcGroundSensorEquippedEntity);
         m_pcGroundSensorEquippedEntity->AddSensor(CVector2(0.03f, 0.0f),
                                                   CGroundSensorEquippedEntity::TYPE_GRAYSCALE,
                                                   m_pcEmbodiedEntity->GetOriginAnchor());

	/* Accelerometer equipped entity */
    	m_pcAccelerometerEquippedEntity =
            new CAccelerometerEquippedEntity(this,
                                            "acc_0");
         AddComponent(*m_pcAccelerometerEquippedEntity);
         m_pcAccelerometerEquippedEntity->AddSensor(CVector3(0.03f, 0.0f, 0.05f),
                                                   m_pcEmbodiedEntity->GetOriginAnchor());
       
         /* Controllable entity
            It must be the last one, for actuators/sensors to link to composing entities correctly */
         m_pcControllableEntity = new CControllableEntity(this);
         AddComponent(*m_pcControllableEntity);
         m_pcControllableEntity->Init(GetNode(t_tree, "controller"));
         /* Update components */
         UpdateComponents();
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Failed to initialize entity \"" << GetId() << "\".", ex);
      }
   }

   /****************************************/
   /****************************************/

   void CSmartObjectEntity::Reset() {
      /* Reset all components */
      CComposableEntity::Reset();
      /* Update components */
      UpdateComponents();
   }

   /****************************************/
   /****************************************/

   void CSmartObjectEntity::Destroy() {
      CComposableEntity::Destroy();
   }

   /****************************************/
   /****************************************/

#define UPDATE(COMPONENT) if(COMPONENT->IsEnabled()) COMPONENT->Update();

   void CSmartObjectEntity::UpdateComponents() {
      UPDATE(m_pcLEDEquippedEntity);
   }

   /****************************************/
   /****************************************/
   
   REGISTER_ENTITY(CSmartObjectEntity, "smart_object", "Piotr Rochala [piotr.rochala@ulb.ac.be]", "1.0", "The smart object", 
			"The object is a device which main feature is lighting the LEDs according to its movement and floor color."
			"REQUIRED XML CONFIGURATION\n\n"
			"  <arena ...>\n"
                   	"    ...\n"
                   	"    <smart_object id=\"ob0\">\n"
                   	"      <body position=\"0.4,2.3,0.25\" orientation=\"45,90,0\" />\n"
                   	"      <controller config=\"mycntrl\" />\n"
                   	"    </smart_object>\n"
                   	"    ...\n"
                   	"  </arena>\n\n", 
			"Under development");


   /****************************************/
   /****************************************/

   REGISTER_STANDARD_SPACE_OPERATIONS_ON_COMPOSABLE(CSmartObjectEntity);

   /****************************************/
   /****************************************/

}
