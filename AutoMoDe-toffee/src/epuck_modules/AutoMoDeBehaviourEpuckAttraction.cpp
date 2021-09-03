/**
  * @file <src/modules/AutoMoDeBehaviourAttraction.cpp>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#include "AutoMoDeBehaviourEpuckAttraction.h"


namespace argos {

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourEpuckAttraction::AutoMoDeBehaviourEpuckAttraction() {
		m_strLabel = "Attraction";
	}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourEpuckAttraction::AutoMoDeBehaviourEpuckAttraction(AutoMoDeBehaviourEpuckAttraction* pc_behaviour) {
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

	AutoMoDeBehaviourEpuckAttraction::~AutoMoDeBehaviourEpuckAttraction() {}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourEpuckAttraction* AutoMoDeBehaviourEpuckAttraction::Clone() {
		return new AutoMoDeBehaviourEpuckAttraction(this);   // todo: check without *
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourEpuckAttraction::ControlStep() {
		CVector2 sRabVector(0,CRadians::ZERO);
		CVector2 sProxVector(0,CRadians::ZERO);
		CVector2 sResultVector(0,CRadians::ZERO);
		CCI_EPuckRangeAndBearingSensor::SReceivedPacket cRabReading = m_pcRobotDAO->GetAttractionVectorToNeighbors(m_unAttractionParameter);

		if (cRabReading.Range > 0.0f) {
			sRabVector = CVector2(cRabReading.Range, cRabReading.Bearing);
		}

		sProxVector = CVector2(m_pcRobotDAO->GetProximityReading().Value, m_pcRobotDAO->GetProximityReading().Angle);
		sResultVector = sRabVector - 6*sProxVector;

		if (sResultVector.Length() < 0.1) {
			sResultVector = CVector2(1, CRadians::ZERO);
		}

		m_pcRobotDAO->SetWheelsVelocity(ComputeWheelsVelocityFromVector(sResultVector));
       // m_pcRobotDAO->SetLEDsColor(m_cColorEmiterParameter);

		m_bLocked = false;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourEpuckAttraction::Init() {
		std::map<std::string, Real>::iterator it = m_mapParameters.find("att");
		if (it != m_mapParameters.end()) {
			m_unAttractionParameter = it->second;
		} else {
			LOGERR << "[FATAL] Missing parameter for the following behaviour:" << m_strLabel << std::endl;
			THROW_ARGOSEXCEPTION("Missing Parameter");
		}
        /*it = m_mapParameters.find("cle");
        if (it != m_mapParameters.end()) {
            m_cColorEmiterParameter = GetColorParameter(it->second, true);
        } else {
            LOGERR << "[FATAL] Missing parameter for the following behaviour:" << m_strLabel << std::endl;
            THROW_ARGOSEXCEPTION("Missing Parameter");
        }*/
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourEpuckAttraction::Reset() {
		m_bOperational = false;
		ResumeStep();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourEpuckAttraction::ResumeStep() {
		m_bOperational = true;
	}
}
