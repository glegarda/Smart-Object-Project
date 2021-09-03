/**
  * @file <src/modules/AutoMoDeConditionGrayFloor.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef AUTOMODE_CONDITION_GRAY_FLOOR_H
#define AUTOMODE_CONDITION_GRAY_FLOOR_H

#include "AutoMoDeConditionEpuck.h"

namespace argos {
	class AutoMoDeConditionEpuckGrayFloor: public AutoMoDeConditionEpuck {
		public:
			AutoMoDeConditionEpuckGrayFloor();
			virtual ~AutoMoDeConditionEpuckGrayFloor();

			AutoMoDeConditionEpuckGrayFloor(AutoMoDeConditionEpuckGrayFloor* pc_condition);
			virtual AutoMoDeConditionEpuckGrayFloor* Clone();

			virtual bool Verify();
			virtual void Reset();
			virtual void Init();

		private:
			CRange<Real> m_fGroundThresholdRange;
			Real m_fProbability;
	};
}

#endif
