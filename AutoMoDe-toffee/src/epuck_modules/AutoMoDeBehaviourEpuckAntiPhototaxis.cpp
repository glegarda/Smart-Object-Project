/**
  * @file <src/modules/AutoMoDeBehaviourAntiPhototaxis.cpp>
  *
  * @author Antoine Ligot - <aligot@ulb.ac.be>
  *
  * @package ARGoS3-AutoMoDe
  *
  * @license MIT License
  */

#include "AutoMoDeBehaviourEpuckAntiPhototaxis.h"


namespace argos {

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourEpuckAntiPhototaxis::AutoMoDeBehaviourEpuckAntiPhototaxis() {
		m_strLabel = "Anti-Phototaxis";
	}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourEpuckAntiPhototaxis::AutoMoDeBehaviourEpuckAntiPhototaxis(AutoMoDeBehaviourEpuckAntiPhototaxis* pc_behaviour) {
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

	AutoMoDeBehaviourEpuckAntiPhototaxis::~AutoMoDeBehaviourEpuckAntiPhototaxis() {}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviourEpuckAntiPhototaxis* AutoMoDeBehaviourEpuckAntiPhototaxis::Clone() {
		return new AutoMoDeBehaviourEpuckAntiPhototaxis(this);
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourEpuckAntiPhototaxis::ControlStep() {
		CVector2 sResultVector(0,CRadians::ZERO);
		CVector2 sLightVector(0,CRadians::ZERO);
		CVector2 sProxVector(0,CRadians::ZERO);

		CCI_EPuckLightSensor::SReading cLightReading = m_pcRobotDAO->GetLightReading();
		sLightVector = CVector2(cLightReading.Value, cLightReading.Angle);


		sProxVector = CVector2(m_pcRobotDAO->GetProximityReading().Value, m_pcRobotDAO->GetProximityReading().Angle);
		sResultVector = -sLightVector - 5*sProxVector;

		if (sResultVector.Length() < 0.1) {
			sResultVector = CVector2(1, CRadians::ZERO);
		}

		m_pcRobotDAO->SetWheelsVelocity(ComputeWheelsVelocityFromVector(sResultVector));

		m_bLocked = false;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourEpuckAntiPhototaxis::Init() {}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourEpuckAntiPhototaxis::Reset() {
		m_bOperational = false;
		ResumeStep();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourEpuckAntiPhototaxis::ResumeStep() {
		m_bOperational = true;
	}
}
