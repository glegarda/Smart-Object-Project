/**
 * @file <argos3/plugins/simulator/actuators/smart_object_leds_default_actuator.cpp>
 */

#include "smartobject_leds_default_actuator.h"
#include <argos3/core/simulator/simulator.h>
#include <argos3/core/utility/logging/argos_log.h>
#include <argos3/plugins/simulator/media/led_medium.h>

namespace argos {

   /****************************************/
   /****************************************/

   CSmartObjectLEDsDefaultActuator::CSmartObjectLEDsDefaultActuator() :
      m_pcLEDEquippedEntity(NULL) {}

   /****************************************/
   /****************************************/

   void CSmartObjectLEDsDefaultActuator::SetRobot(CComposableEntity& c_entity) {
      m_pcLEDEquippedEntity = &(c_entity.GetComponent<CLEDEquippedEntity>("leds"));
      m_tSettings.resize(m_pcLEDEquippedEntity->GetLEDs().size());
   }

   /****************************************/
   /****************************************/

   void CSmartObjectLEDsDefaultActuator::Init(TConfigurationNode& t_tree) {
      try {
         CCI_SmartObjectLEDsActuator::Init(t_tree);
         std::string strMedium;
         GetNodeAttribute(t_tree, "medium", strMedium);
         m_pcLEDMedium = &CSimulator::GetInstance().GetMedium<CLEDMedium>(strMedium);
            //m_pcLEDEquippedEntity->SetMedium(*m_pcLEDMedium);
            m_pcLEDEquippedEntity->AddToMedium(*m_pcLEDMedium);
            m_pcLEDEquippedEntity->Enable();
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Error initializing the Smart Object LEDs default actuator", ex);
      }
   }

   /****************************************/
   /****************************************/

   void CSmartObjectLEDsDefaultActuator::Update() {
      m_pcLEDEquippedEntity->SetAllLEDsColors(m_tSettings);
   }

   /****************************************/
   /****************************************/

   void CSmartObjectLEDsDefaultActuator::Reset() {
      SetAllColors(CColor::BLACK);
   }

   /****************************************/
   /****************************************/

   void CSmartObjectLEDsDefaultActuator::Destroy() {
      m_pcLEDEquippedEntity->Disable();
   }

   /****************************************/
   /****************************************/

}

REGISTER_ACTUATOR(CSmartObjectLEDsDefaultActuator,
                  "smart_object_leds", "default",
                  "",
                  "1.0",
                  "The Smart Object LEDs actuator.",

                  "This actuator controls a group of LEDs. For a complete description of its\n"
                  "usage, refer to the ci_leds_actuator.h file.\n\n"

                  "REQUIRED XML CONFIGURATION\n\n"

                  "  <controllers>\n"
                  "    ...\n"
                  "    <my_controller ...>\n"
                  "      ...\n"
                  "      <actuators>\n"
                  "        ...\n"
                  "        <smart_object_leds implementation=\"default\"\n"
                  "              medium=\"leds\" />\n"
                  "        ...\n"
                  "      </actuators>\n"
                  "      ...\n"
                  "    </my_controller>\n"
                  "    ...\n"
                  "  </controllers>\n\n"

                  "The 'medium' attribute sets the id of the LED medium declared in the <media>\n"
                  "XML section.\n\n"

                  "OPTIONAL XML CONFIGURATION\n\n"

                  "None.\n",

                  "Usable"
   );

