/**
  * @file <src/modules/AutoMoDeBehaviourRepulsion.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef AUTOMODE_BEHAVIOUR_EPUCK_REPULSION_H
#define AUTOMODE_BEHAVIOUR_EPUCK_REPULSION_H

#include "AutoMoDeBehaviourEpuck.h"

namespace argos {
	class AutoMoDeBehaviourEpuckRepulsion: public AutoMoDeBehaviourEpuck {
		public:
			AutoMoDeBehaviourEpuckRepulsion();
			AutoMoDeBehaviourEpuckRepulsion(AutoMoDeBehaviourEpuckRepulsion* pc_behaviour);
			virtual ~AutoMoDeBehaviourEpuckRepulsion();

			virtual void ControlStep();
			virtual void Reset();
			virtual void ResumeStep();
			virtual void Init();

			virtual AutoMoDeBehaviourEpuckRepulsion* Clone();

		private:
			UInt8 m_unRepulsionParameter;
            CColor m_cColorEmiterParameter;
	};
}


#endif
