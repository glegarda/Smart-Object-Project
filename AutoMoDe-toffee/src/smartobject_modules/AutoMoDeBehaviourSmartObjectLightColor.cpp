/**
  * @file <src/modules/AutoMoDeBehaviourLightColor.cpp>
  */

#include "AutoMoDeBehaviourSmartObjectLightColor.h"


namespace argos {

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourSmartObjectLightColor::AutoMoDeBehaviourSmartObjectLightColor() {
		m_strLabel = "LightColor";
		next = false;
		index = 0;
	}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourSmartObjectLightColor::AutoMoDeBehaviourSmartObjectLightColor(AutoMoDeBehaviourSmartObjectLightColor* pc_behaviour) {
		m_strLabel = pc_behaviour->GetLabel();
		m_bLocked = pc_behaviour->IsLocked();
		m_bOperational = pc_behaviour->IsOperational();
		m_unIndex = pc_behaviour->GetIndex();
		m_unIdentifier = pc_behaviour->GetIdentifier();
		m_mapParameters = pc_behaviour->GetParameters();

		Init();
	}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourSmartObjectLightColor::~AutoMoDeBehaviourSmartObjectLightColor() {}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourSmartObjectLightColor* AutoMoDeBehaviourSmartObjectLightColor::Clone() {
		return new AutoMoDeBehaviourSmartObjectLightColor(this);
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourSmartObjectLightColor::ControlStep() {
		if (next){
			m_cColorEmiterParameter = GetColorParameter(index, true);			
			next = false;
		}
   		m_pcRobotDAO->SetLEDsColor(m_cColorEmiterParameter);
		m_bLocked = false;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourSmartObjectLightColor::Init() {
		next = false;
        std::map<std::string, Real>::iterator it = m_mapParameters.find("cle");
        if (it != m_mapParameters.end()) {
			if (it->second != 5 && it->second != 6) {
            	m_cColorEmiterParameter = GetColorParameter(it->second, true);
			}else{
				index = it->second;
				next = true;
			}
        } else {
            LOGERR << "[FATAL] Missing parameter for the following behaviour:" << m_strLabel << std::endl;
            THROW_ARGOSEXCEPTION("Missing Parameter");
        }
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourSmartObjectLightColor::Reset() {
		m_bOperational = false;
		ResumeStep();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourSmartObjectLightColor::ResumeStep() {
		m_bOperational = true;
	}
}
