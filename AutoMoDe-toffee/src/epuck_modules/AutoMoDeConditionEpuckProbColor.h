/**
  * @file <src/modules/AutoMoDeConditionColor.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef AUTOMODE_CONDITION_EPUCK_PROB_COLOR_H
#define AUTOMODE_CONDITION_EPUCK_PROB_COLOR_H

#include "AutoMoDeConditionEpuck.h"

namespace argos {
    class AutoMoDeConditionEpuckProbColor: public AutoMoDeConditionEpuck {
		public:
            AutoMoDeConditionEpuckProbColor();
            virtual ~AutoMoDeConditionEpuckProbColor();

            AutoMoDeConditionEpuckProbColor(AutoMoDeConditionEpuckProbColor* pc_condition);
            virtual AutoMoDeConditionEpuckProbColor* Clone();

			virtual bool Verify();
			virtual void Reset();
			virtual void Init();

		private:
            CColor m_cColorParameter;
			Real m_fProbability;
            Real m_fDistance;
	};
}

#endif
