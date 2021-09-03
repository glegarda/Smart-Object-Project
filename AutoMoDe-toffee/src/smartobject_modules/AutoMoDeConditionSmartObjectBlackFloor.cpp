/**
  * @file <src/modules/AutoMoDeConditionBlackFloor.cpp>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

 #include "AutoMoDeConditionSmartObjectBlackFloor.h"

 namespace argos {

  /****************************************/
  /****************************************/

	AutoMoDeConditionSmartObjectBlackFloor::AutoMoDeConditionSmartObjectBlackFloor() {
		m_strLabel = "BlackFloor";
	}

  /****************************************/
  /****************************************/

	AutoMoDeConditionSmartObjectBlackFloor::~AutoMoDeConditionSmartObjectBlackFloor() {}

  /****************************************/
  /****************************************/

	AutoMoDeConditionSmartObjectBlackFloor::AutoMoDeConditionSmartObjectBlackFloor(AutoMoDeConditionSmartObjectBlackFloor* pc_condition) {
		m_strLabel = pc_condition->GetLabel();
		m_unIndex = pc_condition->GetIndex();
		m_unIdentifier = pc_condition->GetIndex();
		m_unFromBehaviourIndex = pc_condition->GetOrigin();
		m_unToBehaviourIndex = pc_condition->GetExtremity();
		m_mapParameters = pc_condition->GetParameters();
    Init();
	}

  /****************************************/
  /****************************************/

  void AutoMoDeConditionSmartObjectBlackFloor::Init() {
    m_fGroundThreshold = 0.1;
	  std::map<std::string, Real>::iterator it = m_mapParameters.find("p");
    if (it != m_mapParameters.end()) {
      m_fProbability = it->second;
    } else {
      LOGERR << "[FATAL] Missing parameter for the following condition:" << m_strLabel << std::endl;
      THROW_ARGOSEXCEPTION("Missing Parameter");
	  }
  }

  /****************************************/
  /****************************************/

	AutoMoDeConditionSmartObjectBlackFloor* AutoMoDeConditionSmartObjectBlackFloor::Clone() {
		return new AutoMoDeConditionSmartObjectBlackFloor(this);
	}

  /****************************************/
  /****************************************/

	bool AutoMoDeConditionSmartObjectBlackFloor::Verify() {
		if (m_pcRobotDAO->GetGroundReading() <= m_fGroundThreshold) {
      return EvaluateBernoulliProbability(m_fProbability);
    }
    else {
      return false;
    }
	}

  /****************************************/
  /****************************************/

	void AutoMoDeConditionSmartObjectBlackFloor::Reset() {
    Init();
  }

 }
