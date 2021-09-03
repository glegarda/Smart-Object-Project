/**
  * @file <src/modules/AutoMoDeBehaviourAttractionColor.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef AUTOMODE_BEHAVIOUR_EPUCK_PUSH_COLOR_H
#define AUTOMODE_BEHAVIOUR_EPUCK_PUSH_COLOR_H

#include "AutoMoDeBehaviourEpuck.h"

namespace argos {
    class AutoMoDeBehaviourEpuckPushColor: public AutoMoDeBehaviourEpuck{
		public:
            AutoMoDeBehaviourEpuckPushColor();
            AutoMoDeBehaviourEpuckPushColor(AutoMoDeBehaviourEpuckPushColor* pc_behaviour);
            virtual ~AutoMoDeBehaviourEpuckPushColor();

			virtual void ControlStep();
			virtual void Reset();
			virtual void ResumeStep();
			virtual void Init();

            virtual AutoMoDeBehaviourEpuckPushColor* Clone();

        private:
            enum GoDirection {
				        LEFT,
				        RIGHT,
                STRAIGHT,
                AVOID
			      };


            GoDirection m_eGoDirection;
            Real m_fDistanceWeightParameter;
            CColor m_cColorEmiterParameter;
            CColor m_cColorReceiverParameter;
            Real m_unAttractionParameter;
	};
}

#endif
