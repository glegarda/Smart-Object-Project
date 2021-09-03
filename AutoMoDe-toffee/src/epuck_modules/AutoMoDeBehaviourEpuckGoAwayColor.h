/**
  * @file <src/modules/AutoMoDeBehaviourRepulsionColor.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef AUTOMODE_BEHAVIOUR_EPUCK_GOAWAY_COLOR_H
#define AUTOMODE_BEHAVIOUR_EPUCK_GOAWAY_COLOR_H

#include "AutoMoDeBehaviourEpuck.h"

namespace argos {
    class AutoMoDeBehaviourEpuckGoAwayColor: public AutoMoDeBehaviourEpuck {
		public:
            AutoMoDeBehaviourEpuckGoAwayColor();
            AutoMoDeBehaviourEpuckGoAwayColor(AutoMoDeBehaviourEpuckGoAwayColor* pc_behaviour);
            virtual ~AutoMoDeBehaviourEpuckGoAwayColor();

			virtual void ControlStep();
			virtual void Reset();
			virtual void ResumeStep();
			virtual void Init();

            virtual AutoMoDeBehaviourEpuckGoAwayColor* Clone();

		private:
            CColor m_cColorEmiterParameter;
            CColor m_cColorReceiverParameter;
            Real m_unRepulsionParameter;
	};
}


#endif
