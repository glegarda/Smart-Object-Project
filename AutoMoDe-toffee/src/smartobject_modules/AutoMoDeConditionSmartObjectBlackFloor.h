/**
  * @file <src/modules/AutoMoDeConditionBlackFloor.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef AUTOMODE_CONDITION_SMART_OBJECT_BLACK_FLOOR_H
#define AUTOMODE_CONDITION_SMART_OBJECT_BLACK_FLOOR_H

#include "AutoMoDeConditionSmartObject.h"

namespace argos {
	class AutoMoDeConditionSmartObjectBlackFloor: public AutoMoDeConditionSmartObject {
		public:
			AutoMoDeConditionSmartObjectBlackFloor();
			virtual ~AutoMoDeConditionSmartObjectBlackFloor();

			AutoMoDeConditionSmartObjectBlackFloor(AutoMoDeConditionSmartObjectBlackFloor* pc_condition);
			virtual AutoMoDeConditionSmartObjectBlackFloor* Clone();

			virtual bool Verify();
			virtual void Reset();
			virtual void Init();

		private:
			Real m_fGroundThreshold;
			Real m_fProbability;
	};
}

#endif
