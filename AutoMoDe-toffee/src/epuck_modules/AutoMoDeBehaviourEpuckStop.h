/**
  * @file <src/modules/AutoMoDeBehaviourStop.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */


#ifndef AUTOMODE_BEHAVIOUR_EPUCK_STOP_H
#define AUTOMODE_BEHAVIOUR_EPUCK_STOP_H

#include "AutoMoDeBehaviourEpuck.h"

namespace argos {
	class AutoMoDeBehaviourEpuckStop: public AutoMoDeBehaviourEpuck {
		public:
			AutoMoDeBehaviourEpuckStop();
			AutoMoDeBehaviourEpuckStop(AutoMoDeBehaviourEpuckStop* pc_behaviour);
			virtual ~AutoMoDeBehaviourEpuckStop();

			virtual void ControlStep();
			virtual void Reset();
			virtual void ResumeStep();
			virtual void Init();


			virtual AutoMoDeBehaviourEpuckStop* Clone();

        private:
            CColor m_cColorEmiterParameter;
	};
}


#endif
