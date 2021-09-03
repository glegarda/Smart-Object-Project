/**
  * @file <src/modules/AutoMoDeConditionFixedProbability.cpp>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

 #include "AutoMoDeConditionEpuckFixedProbability.h"

 namespace argos {

  /****************************************/
  /****************************************/

	AutoMoDeConditionEpuckFixedProbability::AutoMoDeConditionEpuckFixedProbability() {
		m_strLabel = "FixedProbability";
	}

  /****************************************/
  /****************************************/

	AutoMoDeConditionEpuckFixedProbability::~AutoMoDeConditionEpuckFixedProbability() {}

  /****************************************/
  /****************************************/

	AutoMoDeConditionEpuckFixedProbability::AutoMoDeConditionEpuckFixedProbability(AutoMoDeConditionEpuckFixedProbability* pc_condition) {
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

	AutoMoDeConditionEpuckFixedProbability* AutoMoDeConditionEpuckFixedProbability::Clone() {
		return new AutoMoDeConditionEpuckFixedProbability(this);
	}

  /****************************************/
  /****************************************/

	void AutoMoDeConditionEpuckFixedProbability::Init() {
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

	bool AutoMoDeConditionEpuckFixedProbability::Verify() {
		return EvaluateBernoulliProbability(m_fProbability);
	}

  /****************************************/
  /****************************************/

	void AutoMoDeConditionEpuckFixedProbability::Reset() {
    	Init();
  	}

 }
