/*
 * @file <src/core/AutoMoDeController.h>
 *
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 *
 * @package ARGoS3-AutoMoDe
 *
 * @license MIT License
 */

#ifndef AUTOMODE_CONTROLLER_H
#define AUTOMODE_CONTROLLER_H

#include <argos3/core/utility/logging/argos_log.h>
#include <argos3/core/control_interface/ci_controller.h>


#include "./AutoMoDeFiniteStateMachine.h"
#include "./AutoMoDeFsmBuilder.h"

namespace argos{
	class AutoMoDeController: public CCI_Controller {
		public:
			/*
			 * Class constructor.
			 */
			AutoMoDeController();

			/*
			 * Class desctructor.
			 */
			virtual ~AutoMoDeController();

			/*
			 * Controller initializer.
			 */
			virtual void Init(TConfigurationNode& t_node) = 0;

			/*
			 * Core of the controller.
			 */
			virtual void ControlStep() = 0;

			/*
			 *
			 */
			virtual void Reset() = 0;

			/*
			 *
			 */
			virtual void Destroy() = 0;

			/*
			 * Setter for the AutoMoDeFiniteStateMachine.
			 */
			virtual void SetFiniteStateMachine(AutoMoDeFiniteStateMachine* pc_fine_state_machine) = 0;

			void SetHistoryFlag(bool b_history_flag);
			
			/*
			 * Function that contains all actuations required at the start of an experiment or during the entire experiment.
			 * Example of what you might add in the future: display LED colors, start omnidirectional camera, etc.
			 * This function needs to be called by Reset() in order for the experiment to properly restart.
			 */
			virtual void InitializeActuation() = 0;

		private:
	
			/*
			 * Pointer to the finite state machine object that represents the behaviour
			 * of the robot.
			 */
			AutoMoDeFiniteStateMachine* m_pcFiniteStateMachine;

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

			bool m_bFiniteStateMachineGiven;
	};
}

#endif
