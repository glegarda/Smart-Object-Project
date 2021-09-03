/**
  * @file <src/modules/AutoMoDeCondition.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef AUTOMODECONDITIONEPUCK_H
#define AUTOMODECONDITIONEPUCK_H

#include "../modules_general/AutoMoDeCondition.h"

#include <argos3/core/utility/math/vector2.h>
#include <argos3/core/utility/logging/argos_log.h>

#include <argos3/demiurge/epuck-dao/EpuckDAO.h>

#include <map>

namespace argos {
	class AutoMoDeConditionEpuck : public AutoMoDeCondition {
		protected:
			/*
			 * Shared pointer to the state of the robot.
			 */
			EpuckDAO* m_pcRobotDAO;

		public:

			~AutoMoDeConditionEpuck(){};

			/*
			 * Setter for the pointer to the robot state.
			 */
			void SetRobotDAO(void* pc_robot_dao);

			/*
			 * Returns a random value from a Bernoulli distribution.
			 */
			bool EvaluateBernoulliProbability(const Real& f_probability) const;

            /*
             * Data transform for color of the LEDs.
             */
            CColor GetColorParameter(const UInt32 &un_value);
	};
}

#endif
