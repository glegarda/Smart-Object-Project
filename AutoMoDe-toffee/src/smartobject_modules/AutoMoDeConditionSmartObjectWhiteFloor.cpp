/**
  * @file <src/modules/AutoMoDeConditionInvertedWhiteFloor.cpp>
  */

 #include "AutoMoDeConditionSmartObjectWhiteFloor.h"

 namespace argos {

	/****************************************/
	/****************************************/

	AutoMoDeConditionSmartObjectWhiteFloor::AutoMoDeConditionSmartObjectWhiteFloor() {
		m_strLabel = "WhiteFloor";
	}

	/****************************************/
	/****************************************/

	AutoMoDeConditionSmartObjectWhiteFloor::~AutoMoDeConditionSmartObjectWhiteFloor() {}

	/****************************************/
	/****************************************/

	bool AutoMoDeConditionSmartObjectWhiteFloor::Verify() {
    if (m_pcRobotDAO->GetGroundReading() >= m_fGroundThreshold) {
      return EvaluateBernoulliProbability(m_fProbability);
    }
    else {
      return false;
    }
	}

	/****************************************/
	/****************************************/

	AutoMoDeConditionSmartObjectWhiteFloor::AutoMoDeConditionSmartObjectWhiteFloor(AutoMoDeConditionSmartObjectWhiteFloor* pc_condition) {
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

	AutoMoDeConditionSmartObjectWhiteFloor* AutoMoDeConditionSmartObjectWhiteFloor::Clone() {
		return new AutoMoDeConditionSmartObjectWhiteFloor(this);
	}

	/****************************************/
	/****************************************/

	void AutoMoDeConditionSmartObjectWhiteFloor::Init() {
		m_fGroundThreshold = 0.95;
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

	void AutoMoDeConditionSmartObjectWhiteFloor::Reset() {}

 }
