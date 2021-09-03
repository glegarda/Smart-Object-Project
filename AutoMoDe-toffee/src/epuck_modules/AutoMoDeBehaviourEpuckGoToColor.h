/**
  * @file <src/modules/AutoMoDeBehaviourAttractionColor.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef AUTOMODE_BEHAVIOUR_EPUCK_GOTO_COLOR_H
#define AUTOMODE_BEHAVIOUR_EPUCK_GOTO_COLOR_H

#include "AutoMoDeBehaviourEpuck.h"

namespace argos {
    class AutoMoDeBehaviourEpuckGoToColor: public AutoMoDeBehaviourEpuck{
		public:
            AutoMoDeBehaviourEpuckGoToColor();
            AutoMoDeBehaviourEpuckGoToColor(AutoMoDeBehaviourEpuckGoToColor* pc_behaviour);
            virtual ~AutoMoDeBehaviourEpuckGoToColor();

			virtual void ControlStep();
			virtual void Reset();
			virtual void ResumeStep();
			virtual void Init();

            virtual AutoMoDeBehaviourEpuckGoToColor* Clone();

        private:
            Real m_fDistanceWeightParameter;
            CColor m_cColorEmiterParameter;
            CColor m_cColorReceiverParameter;
            Real m_unAttractionParameter;
	};
}

#endif
