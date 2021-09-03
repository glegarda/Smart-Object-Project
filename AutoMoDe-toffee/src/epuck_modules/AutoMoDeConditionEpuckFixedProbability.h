/**
  * @file <src/modules/AutoMoDeConditionFixedProbability.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef AUTOMODE_CONDITION_EPUCK_FIXED_PROBABILITY_H
#define AUTOMODE_CONDITION_EPUCK_FIXED_PROBABILITY_H

#include "AutoMoDeConditionEpuck.h"

namespace argos {
	class AutoMoDeConditionEpuckFixedProbability: public AutoMoDeConditionEpuck {
		public:
			AutoMoDeConditionEpuckFixedProbability();
			virtual ~AutoMoDeConditionEpuckFixedProbability();

			AutoMoDeConditionEpuckFixedProbability(AutoMoDeConditionEpuckFixedProbability* pc_condition);
			virtual AutoMoDeConditionEpuckFixedProbability* Clone();

			virtual bool Verify();
			virtual void Reset();
			virtual void Init();

		private:
			Real m_fProbability;
	};
}

#endif
