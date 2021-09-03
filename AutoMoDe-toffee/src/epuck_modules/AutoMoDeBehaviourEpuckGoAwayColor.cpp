/**
  * @file <src/modules/AutoMoDeBehaviourRepulsion.cpp>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#include "AutoMoDeBehaviourEpuckGoAwayColor.h"


namespace argos {

	/****************************************/
	/****************************************/

    AutoMoDeBehaviourEpuckGoAwayColor::AutoMoDeBehaviourEpuckGoAwayColor() {
        m_strLabel = "GoAwayColor";
	}

	/****************************************/
	/****************************************/

    AutoMoDeBehaviourEpuckGoAwayColor::AutoMoDeBehaviourEpuckGoAwayColor(AutoMoDeBehaviourEpuckGoAwayColor* pc_behaviour) {
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

    AutoMoDeBehaviourEpuckGoAwayColor::~AutoMoDeBehaviourEpuckGoAwayColor() {}

	/****************************************/
	/****************************************/

    AutoMoDeBehaviourEpuckGoAwayColor* AutoMoDeBehaviourEpuckGoAwayColor::Clone() {
        return new AutoMoDeBehaviourEpuckGoAwayColor(this);
	}

	/****************************************/
	/****************************************/

    void AutoMoDeBehaviourEpuckGoAwayColor::ControlStep() {
        CCI_EPuckOmnidirectionalCameraSensor::SReadings sReadings = m_pcRobotDAO->GetCameraInput();
        CCI_EPuckOmnidirectionalCameraSensor::TBlobList::iterator it;
        CVector2 sColVectorSum(0,CRadians::ZERO);
		CVector2 sProxVectorSum(0,CRadians::ZERO);
		CVector2 sResultVector(0,CRadians::ZERO);

        for (it = sReadings.BlobList.begin(); it != sReadings.BlobList.end(); it++) {
            if ((*it)->Color == m_cColorReceiverParameter  && (*it)->Distance >= 6.0 && (*it)->Distance <= 17.0f) {
                sColVectorSum += CVector2(1 / (((*it)->Distance) + 1), (*it)->Angle);
            }
		}

        sProxVectorSum = CVector2(m_pcRobotDAO->GetProximityReading().Value, m_pcRobotDAO->GetProximityReading().Angle);

        if (sColVectorSum.Length() != 0)
            sResultVector = -CVector2(m_unRepulsionParameter, sColVectorSum.Angle().SignedNormalize()) - 5*sProxVectorSum;
        else
            sResultVector = CVector2(m_unRepulsionParameter, sColVectorSum.Angle().SignedNormalize()) - 5*sProxVectorSum;

		m_pcRobotDAO->SetWheelsVelocity(ComputeWheelsVelocityFromVector(sResultVector));

		m_bLocked = false;
	}

	/****************************************/
	/****************************************/

    void AutoMoDeBehaviourEpuckGoAwayColor::Init() {
        std::map<std::string, Real>::iterator it = m_mapParameters.find("vel");
		if (it != m_mapParameters.end()) {
			m_unRepulsionParameter = it->second;
		} else {
			LOGERR << "[FATAL] Missing parameter for the following behaviour:" << m_strLabel << std::endl;
			THROW_ARGOSEXCEPTION("Missing Parameter");
		}
      /*  it = m_mapParameters.find("cle");
        if (it != m_mapParameters.end()) {
            m_cColorEmiterParameter = GetColorParameter(it->second, true);
        } else {
            LOGERR << "[FATAL] Missing parameter for the following behaviour:" << m_strLabel << std::endl;
            THROW_ARGOSEXCEPTION("Missing Parameter");
        }*/
        it = m_mapParameters.find("clr");
        if (it != m_mapParameters.end()) {
            m_cColorReceiverParameter = GetColorParameter(it->second, false);
        } else {
            LOGERR << "[FATAL] Missing parameter for the following behaviour:" << m_strLabel << std::endl;
            THROW_ARGOSEXCEPTION("Missing Parameter");
        }
	}

	/****************************************/
	/****************************************/

    void AutoMoDeBehaviourEpuckGoAwayColor::Reset() {
		m_bOperational = false;
		ResumeStep();
	}

	/****************************************/
	/****************************************/

    void AutoMoDeBehaviourEpuckGoAwayColor::ResumeStep() {
		m_bOperational = true;
	}
}
