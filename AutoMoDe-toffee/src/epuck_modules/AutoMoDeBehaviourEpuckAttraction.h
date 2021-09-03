/**
  * @file <src/modules/AutoMoDeBehaviourAttraction.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef AUTOMODE_BEHAVIOUR_EPUCK_ATTRACTION_H
#define AUTOMODE_BEHAVIOUR_EPUCK_ATTRACTION_H

#include "AutoMoDeBehaviourEpuck.h"

namespace argos {
	class AutoMoDeBehaviourEpuckAttraction: public AutoMoDeBehaviourEpuck {
		public:
			AutoMoDeBehaviourEpuckAttraction();
			AutoMoDeBehaviourEpuckAttraction(AutoMoDeBehaviourEpuckAttraction* pc_behaviour);
			virtual ~AutoMoDeBehaviourEpuckAttraction();

			virtual void ControlStep();
			virtual void Reset();
			virtual void ResumeStep();
			virtual void Init();

			virtual AutoMoDeBehaviourEpuckAttraction* Clone();

		private:
			UInt8 m_unAttractionParameter;
            CColor m_cColorEmiterParameter;
	};
}

#endif
