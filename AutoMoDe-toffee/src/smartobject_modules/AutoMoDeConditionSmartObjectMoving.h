/**
  * @file <src/modules/AutoMoDeConditionMoving.h>
  */

#ifndef AUTOMODE_CONDITION_SMART_OBJECT_MOVING_H
#define AUTOMODE_CONDITION_SMART_OBJECT_MOVING_H

#include "AutoMoDeConditionSmartObject.h"

namespace argos {
	class AutoMoDeConditionSmartObjectMoving: public AutoMoDeConditionSmartObject {
		public:
			AutoMoDeConditionSmartObjectMoving();
			virtual ~AutoMoDeConditionSmartObjectMoving();

			AutoMoDeConditionSmartObjectMoving(AutoMoDeConditionSmartObjectMoving* pc_condition);
			virtual AutoMoDeConditionSmartObjectMoving* Clone();

			virtual bool Verify();
			virtual void Reset();
			virtual void Init();

		private:
			Real m_fMovingThreshold;
			int timer;
	};
}

#endif
