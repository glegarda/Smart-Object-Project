/**
  * @file <src/modules/AutoMoDeBehaviourAntiPhototaxis.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef AUTOMODE_BEHAVIOUR_EPUCK_ANTI_PHOTOTAXIS_H
#define AUTOMODE_BEHAVIOUR_EPUCK_ANTI_PHOTOTAXIS_H

#include "AutoMoDeBehaviourEpuck.h"

namespace argos {
	class AutoMoDeBehaviourEpuckAntiPhototaxis: public AutoMoDeBehaviourEpuck {
		public:
			AutoMoDeBehaviourEpuckAntiPhototaxis();
			AutoMoDeBehaviourEpuckAntiPhototaxis(AutoMoDeBehaviourEpuckAntiPhototaxis* pc_behaviour);
			virtual ~AutoMoDeBehaviourEpuckAntiPhototaxis();

			virtual void ControlStep();
			virtual void Reset();
			virtual void ResumeStep();
			virtual void Init();

			virtual AutoMoDeBehaviourEpuckAntiPhototaxis* Clone();
	};
}

#endif
