/*
 * @file <src/modules/AutoMoDeBehaviour.h>
 *
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 *
 * @package ARGoS3-AutoMoDe
 *
 * @license MIT License
 */

#ifndef AUTOMODEBEHAVIOUREPUCK_H
#define AUTOMODEBEHAVIOUREPUCK_H

#include "../modules_general/AutoMoDeBehaviour.h"

#include <argos3/plugins/robots/e-puck/control_interface/ci_epuck_proximity_sensor.h>
#include <argos3/plugins/robots/e-puck/control_interface/ci_epuck_range_and_bearing_sensor.h>

#include <argos3/demiurge/epuck-dao/EpuckDAO.h>

#include <map>

namespace argos {
	class AutoMoDeBehaviourEpuck : public  AutoMoDeBehaviour {
		protected:
			/*
			 * Pointer to the state of the robot. Shared with the controller AutoMoDeController
			 * and the finite state machine AutoMoDeFiniteStateMachine.
			 */
      		EpuckDAO* m_pcRobotDAO;

		public:
			~AutoMoDeBehaviourEpuck();

			CVector2 ComputeWheelsVelocity(Real fLeftVelocity, Real fRightVelocity);

			CVector2 ComputeWheelsVelocityFromVector1(CVector2 c_vector_to_follow);

			/*
			 * Utility function. Returns a vector containing the wheels velocity
			 * needed for the robot to follow the vector passed as parameter of the method.
			 */
			CVector2 ComputeWheelsVelocityFromVector(CVector2 c_vector_to_follow);

			/*
			 * Utility function. Returns a vector containing the sum of the
			 * proximity readings passed as parameter of the method.
			 */
			CVector2 SumProximityReadings(CCI_EPuckProximitySensor::TReadings s_prox);

			/*
			 * Setter for the shared pointer to the representation of the robot state.
			 */
			void SetRobotDAO(void* pc_robot_dao);

			/*
			* Data transform for color of the omnidirectional camera and LEDs.
			*/
			CColor GetColorParameter(const UInt32& un_value, const bool& b_emiter);
      
	};
}

#endif
