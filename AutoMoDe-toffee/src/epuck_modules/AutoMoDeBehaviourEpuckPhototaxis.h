/**
  * @file <src/modules/AutoMoDeBehaviourPhototaxis.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef AUTOMODE_BEHAVIOUR_EPUCK_PHOTOTAXIS_H
#define AUTOMODE_BEHAVIOUR_EPUCK_PHOTOTAXIS_H

#include "AutoMoDeBehaviourEpuck.h"

namespace argos {
	class AutoMoDeBehaviourEpuckPhototaxis: public AutoMoDeBehaviourEpuck {
		public:
			AutoMoDeBehaviourEpuckPhototaxis();
			AutoMoDeBehaviourEpuckPhototaxis(AutoMoDeBehaviourEpuckPhototaxis* pc_behaviour);
			virtual ~AutoMoDeBehaviourEpuckPhototaxis();

			virtual void ControlStep();
			virtual void Reset();
			virtual void ResumeStep();
			virtual void Init();

			virtual AutoMoDeBehaviourEpuckPhototaxis* Clone();
	};
}

#endif
