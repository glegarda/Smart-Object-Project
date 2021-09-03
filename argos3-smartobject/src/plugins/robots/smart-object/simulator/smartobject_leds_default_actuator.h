/**
 * @file <argos3/plugins/simulator/actuators/leds_default_actuator.h>
 */

#ifndef SMART_OBJECT_LEDS_DEFAULT_ACTUATOR_H
#define SMART_OBJECT_LEDS_DEFAULT_ACTUATOR_H

#include <string>
#include <map>

namespace argos {
   class CSmartObjectLEDsDefaultActuator;
   class CLEDMedium;
}
#include <argos3/plugins/robots/smart-object/control_interface/ci_smartobject_leds_actuator.h>
#include <argos3/plugins/simulator/entities/led_equipped_entity.h>
#include <argos3/core/simulator/actuator.h>

namespace argos {

   class CSmartObjectLEDsDefaultActuator : public CSimulatedActuator,
                                	   public CCI_SmartObjectLEDsActuator {

   public:

      CSmartObjectLEDsDefaultActuator();

      virtual ~CSmartObjectLEDsDefaultActuator() {}

      virtual void SetRobot(CComposableEntity& c_entity);

      virtual void Init(TConfigurationNode& t_tree);
      virtual void Update();
      virtual void Reset();
      virtual void Destroy();

   private:

      CLEDEquippedEntity* m_pcLEDEquippedEntity;
      CLEDMedium*         m_pcLEDMedium;

   };

}

#endif
