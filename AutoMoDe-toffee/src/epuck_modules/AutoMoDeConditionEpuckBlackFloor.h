/**
  * @file <src/modules/AutoMoDeConditionBlackFloor.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef AUTOMODE_CONDITION_EPUCK_BLACK_FLOOR_H
#define AUTOMODE_CONDITION_EPUCK_BLACK_FLOOR_H

#include "AutoMoDeConditionEpuck.h"

namespace argos {
	class AutoMoDeConditionEpuckBlackFloor: public AutoMoDeConditionEpuck {
		public:
			AutoMoDeConditionEpuckBlackFloor();
			virtual ~AutoMoDeConditionEpuckBlackFloor();

			AutoMoDeConditionEpuckBlackFloor(AutoMoDeConditionEpuckBlackFloor* pc_condition);
			virtual AutoMoDeConditionEpuckBlackFloor* Clone();

			virtual bool Verify();
			virtual void Reset();
			virtual void Init();

		private:
			Real m_fGroundThreshold;
			Real m_fProbability;
	};
}

#endif
