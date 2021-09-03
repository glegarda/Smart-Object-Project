/*
 * @file <src/core/AutoMoDeController.cpp>
 *
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 *
 * @package ARGoS3-AutoMoDe
 *
 * @license MIT License
 */

#include "AutoMoDeController.h"

namespace argos {

	/****************************************/
	/****************************************/

	AutoMoDeController::AutoMoDeController() {}

	/****************************************/
	/****************************************/

	AutoMoDeController::~AutoMoDeController() {}



	/****************************************/
	/****************************************/

	void AutoMoDeController::SetHistoryFlag(bool b_history_flag) {
		if (b_history_flag) {
			m_pcFiniteStateMachine->MaintainHistory();
		}
	}
}
