/**
 * @file <argos3/plugins/robots/object/simulator/object_accelerometer_sensor.cpp>
 * @author Piotr Rochala
 */

#include "smartobject_accelerometer_sensor.h"

#include <argos3/core/simulator/simulator.h>
#include <argos3/core/simulator/entity/embodied_entity.h>
#include <argos3/core/simulator/entity/composable_entity.h>
#include <argos3/plugins/robots/smart-object/simulator/accelerometer_equipped_entity.h>

namespace argos {
   CSmartObjectAccelerometerSensor::CSmartObjectAccelerometerSensor() : 
	  m_pcEmbodiedEntity(NULL),
          m_pcAcceleratorEntity(NULL),
          m_pcControllableEntity(NULL),
	  oldVelX(0.0f),
	  oldVelY(0.0f),
	  oldVelZ(0.0f) {}


   void CSmartObjectAccelerometerSensor::SetRobot(CComposableEntity& c_entity) {
      try {
         m_pcEmbodiedEntity = &(c_entity.GetComponent<CEmbodiedEntity>("body"));
         m_pcControllableEntity = &(c_entity.GetComponent<CControllableEntity>("controller"));
         m_pcAcceleratorEntity = &(c_entity.GetComponent<CAccelerometerEquippedEntity>("accelerometer"));
         m_pcAcceleratorEntity->Enable();
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Can't set robot for the smart object accelerometer sensor", ex);
      }
   }

   void CSmartObjectAccelerometerSensor::Init(TConfigurationNode& t_tree) {
	try {
        CCI_SmartObjectAccelerometerSensor::Init(t_tree);
        /* Parse noise level */
        Real fNoiseLevel = 0.0f;
        GetNodeAttributeOrDefault(t_tree, "noise_level", fNoiseLevel, fNoiseLevel);
        if(fNoiseLevel < 0.0f) {
            THROW_ARGOSEXCEPTION("Can't specify a negative value for the noise level"
                                 << " of the e-puck proximity sensor");
        }
        else if(fNoiseLevel > 0.0f) {
            m_bAddNoise = true;
            m_cNoiseRange.Set(-fNoiseLevel, fNoiseLevel);
            m_pcRNG = CRandom::CreateRNG("argos");
        }
         
	 	const CVector3& cEntityPos = m_pcEmbodiedEntity->GetOriginAnchor().Position;
	 /* We need to set initial values for older position, equal to the current because of the fact when the reset button is pressed, the robots go
	back to the initial position but the old position still indicates the last one, and therefore the object thinks it's moving.*/
         oldPosX = cEntityPos.GetX();
         oldPosY = cEntityPos.GetY();
         oldPosZ = cEntityPos.GetZ();
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Initialization error in smart object accelerometer sensor", ex);
      }
   }

   void CSmartObjectAccelerometerSensor::Update() {
		const CVector3& cEntityPos = m_pcEmbodiedEntity->GetOriginAnchor().Position;

		/* current position */		
		const Real currentPosX = cEntityPos.GetX();
		const Real currentPosY = cEntityPos.GetY();
		const Real currentPosZ = cEntityPos.GetZ();
		const Real clockTick = CPhysicsEngine::GetSimulationClockTick();

		/* current velocity */
		Real currentVelX = (currentPosX - oldPosX) / clockTick;
		Real currentVelY = (currentPosY - oldPosY) / clockTick;
		Real currentVelZ = (currentPosZ - oldPosZ) / clockTick;
		
      	/* Apply noise to the sensor */
        if(m_bAddNoise) {
        	currentVelX += m_pcRNG->Uniform(m_cNoiseRange);
        	currentVelY += m_pcRNG->Uniform(m_cNoiseRange)*currentVelY;
        	currentVelZ += m_pcRNG->Uniform(m_cNoiseRange)*currentVelZ;
    	}

		m_sReading.vel.v_X = currentVelX;
		m_sReading.vel.v_Y = currentVelY;
		m_sReading.vel.v_Z = currentVelZ;

		/* current acceleration */		
		m_sReading.acc.a_X = (currentVelX - oldVelX) / clockTick;
		m_sReading.acc.a_Y = (currentVelY - oldVelY) / clockTick;
		m_sReading.acc.a_Z = (currentVelZ - oldVelZ) / clockTick;
		
		oldPosX = currentPosX;
		oldPosY = currentPosY;
		oldPosZ = currentPosZ;

		oldVelX = currentVelX;
		oldVelY = currentVelY;
		oldVelZ = currentVelZ; 

   }

   void CSmartObjectAccelerometerSensor::Reset() {
	const CVector3& cEntityPos = m_pcEmbodiedEntity->GetOriginAnchor().Position;
	oldPosX = cEntityPos.GetX();
	oldPosY = cEntityPos.GetY();
	oldPosZ = cEntityPos.GetZ();
	m_sReading.vel.v_X = 0.0f;
	m_sReading.vel.v_Y = 0.0f;
	m_sReading.vel.v_Z = 0.0f;
	m_sReading.acc.a_X = 0.0f;
	m_sReading.acc.a_Y = 0.0f;
	m_sReading.acc.a_Z = 0.0f;
	
   }

   REGISTER_SENSOR(CSmartObjectAccelerometerSensor,
                   "smart_object_accelerometer", "default",
                   "Piotr Rochala [piotr.rochala@ulb.ac.be]",
                   "1.0",
                   "The smart object accelerometer sensor",
                   "This sensor can provide 2 possible values. 1. The velocity of the object, 2. The acceleration of the object. \n"
		   "In controllers, you must include the ci_object_accelerometer_sensor.h header.\n\n"
		   "REQUIRED XML CONFIGURATION\n\n"
                   "  <controllers>\n"
                   "    ...\n"
                   "    <my_controller ...>\n"
                   "      ...\n"
                   "      <sensors>\n"
                   "        ...\n"
                   "        <smart_object_accelerometer implementation=\"default\" />\n"
                   "        ...\n"
                   "      </sensors>\n"
                   "      ...\n"
                   "    </my_controller>\n"
                   "    ...\n"
                   "  </controllers>\n\n",
                   "Usable"
                   );


}
