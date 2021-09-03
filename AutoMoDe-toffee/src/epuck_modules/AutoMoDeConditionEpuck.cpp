/**
  * @file <src/modules/AutoMoDeCondition.cpp>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#include "AutoMoDeConditionEpuck.h"

namespace argos {

	/****************************************/
	/****************************************/

  void AutoMoDeConditionEpuck::SetRobotDAO(void* pc_robot_dao) {
      m_pcRobotDAO = (EpuckDAO*) pc_robot_dao;
  }

	/****************************************/
	/****************************************/

  bool AutoMoDeConditionEpuck::EvaluateBernoulliProbability(const Real& f_probability) const {
		return m_pcRobotDAO->GetRandomNumberGenerator()->Bernoulli(f_probability);
	}

  /****************************************/
  /****************************************/
  // Return the color parameter
  CColor AutoMoDeConditionEpuck::GetColorParameter(const UInt32& un_value) {
      CColor cColorParameter;
      switch(un_value){
      case 0:
          cColorParameter = CColor::BLACK;
          break;
      case 1:
          cColorParameter = CColor::GREEN;
          break;
      case 2:
          cColorParameter = CColor::BLUE;
          break;
      case 3:
          cColorParameter = CColor::RED;
          break;
      case 4:
          cColorParameter = CColor::YELLOW;
          break;
      case 5:
          cColorParameter = CColor::MAGENTA;
          break;
      case 6:
          cColorParameter = CColor::CYAN;
          break;
      default:
          cColorParameter = CColor::BLACK;
      }
      return cColorParameter;
  }

}
