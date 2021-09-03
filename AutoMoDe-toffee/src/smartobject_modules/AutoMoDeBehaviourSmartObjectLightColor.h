/**
  * @file <src/modules/AutoMoDeBehaviourLightColor.h>
  */


#ifndef AUTOMODE_BEHAVIOUR_SMART_OBJECT_LIGHT_COLOR_H
#define AUTOMODE_BEHAVIOUR_SMART_OBJECT_LIGHT_COLOR_H

#include "AutoMoDeBehaviourSmartObject.h"

namespace argos {
	class AutoMoDeBehaviourSmartObjectLightColor: public AutoMoDeBehaviourSmartObject {
		public:
			AutoMoDeBehaviourSmartObjectLightColor();
			AutoMoDeBehaviourSmartObjectLightColor(AutoMoDeBehaviourSmartObjectLightColor* pc_behaviour);
			virtual ~AutoMoDeBehaviourSmartObjectLightColor();

			virtual void ControlStep();
			virtual void Reset();
			virtual void ResumeStep();
			virtual void Init();


			virtual AutoMoDeBehaviourSmartObjectLightColor* Clone();

        private:
            CColor m_cColorEmiterParameter;
			bool next;
			UInt16 index;
	};
}


#endif
