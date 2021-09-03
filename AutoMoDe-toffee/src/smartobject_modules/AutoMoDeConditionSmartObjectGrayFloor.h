/**
  * @file <src/modules/AutoMoDeConditionInvertedWhiteFloor.h>
  */
	
#ifndef AUTOMODE_CONDITION_SMART_OBJECT_GRAY_FLOOR_H
#define AUTOMODE_CONDITION_SMART_OBJECT_GRAY_FLOOR_H

#include "AutoMoDeConditionSmartObject.h"

namespace argos {
	class AutoMoDeConditionSmartObjectGrayFloor: public AutoMoDeConditionSmartObject {
		public:
			AutoMoDeConditionSmartObjectGrayFloor();
			virtual ~AutoMoDeConditionSmartObjectGrayFloor();

			AutoMoDeConditionSmartObjectGrayFloor(AutoMoDeConditionSmartObjectGrayFloor* pc_condition);
			virtual AutoMoDeConditionSmartObjectGrayFloor* Clone();

			virtual bool Verify();
			virtual void Reset();
			virtual void Init();

		private:
			CRange<Real> m_fGroundThresholdRange;
			Real m_fProbability;
	};
}

#endif
