/*
 * @file <src/core/AutoMoDeController.h>
 *
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 *
 * @package ARGoS3-AutoMoDe
 *
 * @license MIT License
 */

#ifndef AUTOMODE_CONTROLLER_SMART_OBJECT_H
#define AUTOMODE_CONTROLLER_SMART_OBJECT_H

#include <argos3/core/utility/logging/argos_log.h>
#include <argos3/core/control_interface/ci_controller.h>

#include <argos3/demiurge/smartobject-dao/SmartObjectDAO.h>
#include <argos3/demiurge/smartobject-dao/SOReferenceModel1Dot1.h>

#include "../AutoMoDeController.h"

#include "../AutoMoDeFiniteStateMachine.h"
#include "../AutoMoDeFsmBuilder.h"

#include <argos3/plugins/robots/smart-object/control_interface/ci_smartobject_accelerometer_sensor.h>
#include <argos3/plugins/robots/smart-object/control_interface/ci_smartobject_ground_sensor.h>
#include <argos3/plugins/robots/smart-object/control_interface/ci_smartobject_leds_actuator.h>

namespace argos{
	class AutoMoDeControllerSmartObject: public AutoMoDeController {
		public:
			/*
			 * Class constructor.
			 */
			AutoMoDeControllerSmartObject();

			/*
			 * Class desctructor.
			 */
			virtual ~AutoMoDeControllerSmartObject();

			/*
			 * Controller initializer.
			 */
			virtual void Init(TConfigurationNode& t_node);

			/*
			 * Core of the controller.
			 */
			virtual void ControlStep();

			/*
			 *
			 */
			virtual void Reset();

			/*
			 *
			 */
			virtual void Destroy();

			/*
			 * Setter for the AutoMoDeFiniteStateMachine.
			 */
			void SetFiniteStateMachine(AutoMoDeFiniteStateMachine* pc_fine_state_machine);

			void SetHistoryFlag(bool b_history_flag);

		private:
			/*
			 * Function that contains all actuations required at the start of an experiment or during the entire experiment.
			 * Example of what you might add in the future: display LED colors, start omnidirectional camera, etc.
			 * This function needs to be called by Reset() in order for the experiment to properly restart.
			 */
			void InitializeActuation();

			/*
			 * Pointer to the finite state machine object that represents the behaviour
			 * of the robot.
			 */
			AutoMoDeFiniteStateMachine* m_pcFiniteStateMachine;

			/*
			 * Pointer to the object representing the state of the robot. This object is
			 * shared with the finite state object AutoMoDeFiniteStateMachine.
			 */
			SmartObjectDAO* m_pcRobotState;

			/*
			 * Time step variable.
			 */
			UInt32 m_unTimeStep;

			/*
			 * Integer part of the robot identifier.
			 */
			UInt32 m_unRobotID;

			/*
			 * String that contains the configuration of the finite state machine.
			 */
			std::string m_strFsmConfiguration;

			/*
			 * Flag that tells whether an history is maintained or not.
			 */
			bool m_bMaintainHistory;

			/*
			 * Flag that tells whether an URL containing a DOT description of the
			 * finite state machine is to be displayed or not.
			 */
			bool m_bPrintReadableFsm;

			/*
			 * The path to where the history shall be stored.
			 */
			std::string m_strHistoryFolder;

			/*
			 * Pointer to the object in charge of creating the AutoMoDeFiniteStateMachine.
			 */
			AutoMoDeFsmBuilder* m_pcFsmBuilder;


			/*
			 * Pointer to the robot RGB LEDs actuator.
			 */
			CCI_SmartObjectLEDsActuator* m_pcLEDsActuator;


			/*
			 * Pointer to the robot ground sensor.
			 */
			CCI_SmartObject_GroundSensor* m_pcGroundSensor;

			/*
			 * Pointer to the robot accelerometer sensor.
			 */
			CCI_SmartObjectAccelerometerSensor* m_pcAccelerometerSensor;

			bool m_bFiniteStateMachineGiven;

			/* Flat that tells if the smart object should display the color on all leds or only
				partially.
			*/
			bool m_bPartialLighting;
			
			bool init;
	};
}

#endif
