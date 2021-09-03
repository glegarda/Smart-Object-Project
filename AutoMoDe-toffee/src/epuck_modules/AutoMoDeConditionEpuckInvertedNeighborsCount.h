/**
  * @file <src/modules/AutoMoDeConditionInvertedNeighborsCount.h>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#ifndef AUTOMODE_CONDITION_INVERTED_NEIGHBORS_COUNT_H
#define AUTOMODE_CONDITION_INVERTED_NEIGHBORS_COUNT_H

#include "AutoMoDeConditionEpuck.h"

namespace argos {
	class AutoMoDeConditionEpuckInvertedNeighborsCount: public AutoMoDeConditionEpuck {
		public:
			AutoMoDeConditionEpuckInvertedNeighborsCount();
			virtual ~AutoMoDeConditionEpuckInvertedNeighborsCount();

			AutoMoDeConditionEpuckInvertedNeighborsCount(AutoMoDeConditionEpuckInvertedNeighborsCount* pc_condition);
			virtual AutoMoDeConditionEpuckInvertedNeighborsCount* Clone();

			virtual bool Verify();
			virtual void Reset();
			virtual void Init();

		private:
			Real m_fParameterEta;
			UInt8 m_unParameterXi;
	};
}

#endif
