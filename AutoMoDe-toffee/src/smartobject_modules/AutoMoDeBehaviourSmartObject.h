/*
 * @file <src/modules/AutoMoDeBehaviour.h>
 *
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 *
 * @package ARGoS3-AutoMoDe
 *
 * @license MIT License
 */

#ifndef AUTOMODEBEHAVIOURSMARTOBJECT_H
#define AUTOMODEBEHAVIOURSMARTOBJECT_H

#include "../modules_general/AutoMoDeBehaviour.h"

#include <argos3/demiurge/smartobject-dao/SmartObjectDAO.h>

#include <map>

namespace argos {
	class AutoMoDeBehaviourSmartObject : public  AutoMoDeBehaviour {
		protected:
			/*
			 * Pointer to the state of the robot. Shared with the controller AutoMoDeController
			 * and the finite state machine AutoMoDeFiniteStateMachine.
			 */
      		SmartObjectDAO* m_pcRobotDAO;

		public:
			AutoMoDeBehaviourSmartObject();
			~AutoMoDeBehaviourSmartObject();

			/*
			 * Setter for the shared pointer to the representation of the robot state.
			 */
			void SetRobotDAO(void* pc_robot_dao);

            CColor GetColorParameter(const UInt32& un_value, const bool& b_emiter);

		private:

			CColor RandomColor();
			CColor NextColor();
			CColor CurrentColor();

			CColor c_CurrentColor;
			UInt16 color_index;
			std::vector<CColor> color_cycle;


      
	};
}

#endif
