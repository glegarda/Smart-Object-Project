/**
  * @file <src/modules/AutoMoDeConditionInvertedWhiteFloor.h>
  */
	
#ifndef AUTOMODE_CONDITION_SMART_OBJECT_WHITE_FLOOR_H
#define AUTOMODE_CONDITION_SMART_OBJECT_WHITE_FLOOR_H

#include "AutoMoDeConditionSmartObject.h"

namespace argos {
	class AutoMoDeConditionSmartObjectWhiteFloor: public AutoMoDeConditionSmartObject {
		public:
			AutoMoDeConditionSmartObjectWhiteFloor();
			virtual ~AutoMoDeConditionSmartObjectWhiteFloor();

			AutoMoDeConditionSmartObjectWhiteFloor(AutoMoDeConditionSmartObjectWhiteFloor* pc_condition);
			virtual AutoMoDeConditionSmartObjectWhiteFloor* Clone();

			virtual bool Verify();
			virtual void Reset();
			virtual void Init();

		private:
			Real m_fGroundThreshold;
			Real m_fProbability;
	};
}

#endif
