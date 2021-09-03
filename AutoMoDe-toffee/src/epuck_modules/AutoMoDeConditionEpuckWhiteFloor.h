/**
  * @file <src/modules/AutoMoDeConditionInvertedWhiteFloor.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */
	
#ifndef AUTOMODE_CONDITION_EPUCK_WHITE_FLOOR_H
#define AUTOMODE_CONDITION_EPUCK_WHITE_FLOOR_H

#include "AutoMoDeConditionEpuck.h"

namespace argos {
	class AutoMoDeConditionEpuckWhiteFloor: public AutoMoDeConditionEpuck {
		public:
			AutoMoDeConditionEpuckWhiteFloor();
			virtual ~AutoMoDeConditionEpuckWhiteFloor();

			AutoMoDeConditionEpuckWhiteFloor(AutoMoDeConditionEpuckWhiteFloor* pc_condition);
			virtual AutoMoDeConditionEpuckWhiteFloor* Clone();

			virtual bool Verify();
			virtual void Reset();
			virtual void Init();

		private:
			Real m_fGroundThreshold;
			Real m_fProbability;
	};
}

#endif
