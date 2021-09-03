/**
 * @file <argos3/plugins/robots/object/simulator/smartobject_entity.h>
 * @author Piotr Rochala
 */

#ifndef SMARTOBJECT_ENTITY_H
#define SMARTOBJECT_ENTITY_H

namespace argos {
   class CControllableEntity;
   class CEmbodiedEntity;
   class CObjectEntity;
   class CGroundSensorEquippedEntity;
   class CLEDEquippedEntity;
   class CLightSensorEquippedEntity;
   class CAccelerometerEquippedEntity;
}

#include <argos3/core/simulator/entity/composable_entity.h>
#include <argos3/plugins/robots/smart-object/simulator/accelerometer_equipped_entity.h>

namespace argos {

   class CSmartObjectEntity : public CComposableEntity {

   public:

      ENABLE_VTABLE();

   public:

      CSmartObjectEntity();

      CSmartObjectEntity(const std::string& str_id,
                   const std::string& str_controller_id,
                   const CVector3& c_position = CVector3(),
                   const CQuaternion& c_orientation = CQuaternion());
      
      virtual void Init(TConfigurationNode& t_tree);
      virtual void Reset();
      virtual void Destroy();

      virtual void UpdateComponents();
      
      inline CControllableEntity& GetControllableEntity() {
         return *m_pcControllableEntity;
      }

      inline CEmbodiedEntity& GetEmbodiedEntity() {
         return *m_pcEmbodiedEntity;
      }

      inline CLEDEquippedEntity& GetLEDEquippedEntity() {
         return *m_pcLEDEquippedEntity;
      }

      inline CGroundSensorEquippedEntity& GetGroundSensorEquippedEntity() {
         return *m_pcGroundSensorEquippedEntity;
      }

      inline CAccelerometerEquippedEntity& GetAccelerometerEquippedEntity() {
         return *m_pcAccelerometerEquippedEntity;
      }


      virtual std::string GetTypeDescription() const {
         return "smart_object";
      }

   private:

      void SetLEDPosition();

   private:

      CControllableEntity*                   m_pcControllableEntity;
      CEmbodiedEntity*                       m_pcEmbodiedEntity;
      CLEDEquippedEntity*                    m_pcLEDEquippedEntity;
      CGroundSensorEquippedEntity*           m_pcGroundSensorEquippedEntity;
      CLightSensorEquippedEntity*            m_pcLightSensorEquippedEntity;
      CAccelerometerEquippedEntity*	     m_pcAccelerometerEquippedEntity;
   };

}

#endif
