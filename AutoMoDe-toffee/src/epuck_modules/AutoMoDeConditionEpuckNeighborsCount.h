/**
  * @file <src/modules/AutoMoDeConditionNeighborsCount.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef AUTOMODE_CONDITION_EPUCK_NEIGHBORS_COUNT_H
#define AUTOMODE_CONDITION_EPUCK_NEIGHBORS_COUNT_H

#include "AutoMoDeConditionEpuck.h"

namespace argos {
	class AutoMoDeConditionEpuckNeighborsCount: public AutoMoDeConditionEpuck {
		public:
			AutoMoDeConditionEpuckNeighborsCount();
			virtual ~AutoMoDeConditionEpuckNeighborsCount();

			AutoMoDeConditionEpuckNeighborsCount(AutoMoDeConditionEpuckNeighborsCount* pc_condition);
			virtual AutoMoDeConditionEpuckNeighborsCount* Clone();

			virtual bool Verify();
			virtual void Reset();
			virtual void Init();

		private:
			Real m_fParameterEta;
			UInt8 m_unParameterXi;
	};
}

#endif
