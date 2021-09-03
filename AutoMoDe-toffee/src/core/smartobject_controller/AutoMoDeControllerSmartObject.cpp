/*
 * @file <src/core/AutoMoDeController.cpp>
 *
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 *
 * @package ARGoS3-AutoMoDe
 *
 * @license MIT License
 */

#include "AutoMoDeControllerSmartObject.h"

namespace argos {

	/****************************************/
	/****************************************/

	AutoMoDeControllerSmartObject::AutoMoDeControllerSmartObject() {
        m_pcRobotState = new SOReferenceModel1Dot1();
		m_unTimeStep = 0;
		m_strFsmConfiguration = "";
		m_bMaintainHistory = false;
		m_bPrintReadableFsm = false;
		m_strHistoryFolder = "./";
		m_bFiniteStateMachineGiven = false;
		init = false;
	}

	/****************************************/
	/****************************************/

	AutoMoDeControllerSmartObject::~AutoMoDeControllerSmartObject() {
		delete m_pcRobotState;
		if (m_strFsmConfiguration.compare("") != 0) {
			delete m_pcFsmBuilder;
		}
	}

	/****************************************/
	/****************************************/

	void AutoMoDeControllerSmartObject::Init(TConfigurationNode& t_node) {
		// Parsing parameters
		try {
			GetNodeAttributeOrDefault(t_node, "fsm-config", m_strFsmConfiguration, m_strFsmConfiguration);
			GetNodeAttributeOrDefault(t_node, "history", m_bMaintainHistory, m_bMaintainHistory);
			GetNodeAttributeOrDefault(t_node, "hist-folder", m_strHistoryFolder, m_strHistoryFolder);
			GetNodeAttributeOrDefault(t_node, "readable", m_bPrintReadableFsm, m_bPrintReadableFsm);
			GetNodeAttributeOrDefault(t_node, "partialLighting", m_bPartialLighting, false);
		} catch (CARGoSException& ex) {
			THROW_ARGOSEXCEPTION_NESTED("Error parsing <params>", ex);
		}

		m_unRobotID = atoi(GetId().substr(5, 6).c_str());
		m_pcRobotState->SetRobotIdentifier(m_unRobotID);
		//m_pcRobotState->SetVelocity(0.0f);

		/*
		 * If a FSM configuration is given as parameter of the experiment file, create a FSM from it
		 */
		if (m_strFsmConfiguration.compare("") != 0 && !m_bFiniteStateMachineGiven) {
			m_pcFsmBuilder = new AutoMoDeFsmBuilder();
			SetFiniteStateMachine(m_pcFsmBuilder->BuildFiniteStateMachine(m_strFsmConfiguration));
			if (m_bMaintainHistory) {
				m_pcFiniteStateMachine->SetHistoryFolder(m_strHistoryFolder);
				m_pcFiniteStateMachine->MaintainHistory();
			}
			if (m_bPrintReadableFsm) {
				std::cout << "Finite State Machine description: " << std::endl;
				std::cout << m_pcFiniteStateMachine->GetReadableFormat() << std::endl;
			}
		} else {
			LOGERR << "Warning: No finite state machine configuration found in .argos" << std::endl;
		}
		/*
		 *  Initializing sensors and actuators
		 */
		try{
			m_pcGroundSensor = GetSensor<CCI_SmartObject_GroundSensor>("smart_object_ground");
			m_pcAccelerometerSensor = GetSensor<CCI_SmartObjectAccelerometerSensor>("smart_object_accelerometer");
		} catch (CARGoSException ex) {
			LOGERR<<"Error while initializing a Sensor!\n";
		}

		try{
			m_pcLEDsActuator = GetActuator<CCI_SmartObjectLEDsActuator>("smart_object_leds");
		} catch (CARGoSException ex) {
			LOGERR<<"Error while initializing an Actuator!\n";
		}

		/*
		 * Starts actuation.
		 */
		 InitializeActuation();
	}

	/****************************************/
	/****************************************/

	void AutoMoDeControllerSmartObject::ControlStep() {
		//Smart objects are moved by a loop function meaning we need to reset the accelerometer's values
		if (!init) {
			init = true;
			if (m_pcAccelerometerSensor != NULL) {
				m_pcAccelerometerSensor->Reset();
			}
		}
		/*
		 * 1. Update SmartObjectDAO
		 */
		if (m_pcAccelerometerSensor != NULL) {
			const CCI_SmartObjectAccelerometerSensor::SReading& reading = m_pcAccelerometerSensor->GetReading();
			m_pcRobotState->SetAccelerometerReading(reading);
		}
		if (m_pcGroundSensor != NULL) {
			const Real& reading = m_pcGroundSensor->GetReading();
			m_pcRobotState->SetGroundReading(reading);
		}

		if (m_pcAccelerometerSensor != NULL) {
			m_pcRobotState->SetVelocityReading(m_pcAccelerometerSensor->GetReading().vel.getVelocity());
		}

		/*
		 * 2. Execute step of FSM
		 */
		m_pcFiniteStateMachine->ControlStep();

		/*
		 * 3. Update Actuators
		 */
		if (m_pcLEDsActuator != NULL) {
			if (!m_bPartialLighting) {
				m_pcLEDsActuator->SetAllColors(m_pcRobotState->GetLEDsColor());
				//m_pcLEDsActuator->SetAllColors(CColor::RED);
			} else {
				m_pcLEDsActuator->SetSingleColor(0, m_pcRobotState->GetLEDsColor());
				m_pcLEDsActuator->SetSingleColor(1, m_pcRobotState->GetLEDsColor());
				m_pcLEDsActuator->SetSingleColor(2, m_pcRobotState->GetLEDsColor());
			}
		}

		m_unTimeStep++;

	}

	/****************************************/
	/****************************************/

	void AutoMoDeControllerSmartObject::Destroy() {}

	/****************************************/
	/****************************************/

	void AutoMoDeControllerSmartObject::Reset() {
		m_pcFiniteStateMachine->Reset();
		m_pcRobotState->Reset();
		// Restart actuation.
		InitializeActuation();
	}


	/****************************************/
	/****************************************/

	void AutoMoDeControllerSmartObject::InitializeActuation() {}

	/****************************************/
	/****************************************/

	void AutoMoDeControllerSmartObject::SetFiniteStateMachine(AutoMoDeFiniteStateMachine* pc_finite_state_machine) {
		m_pcFiniteStateMachine = pc_finite_state_machine;
		m_pcFiniteStateMachine->SetRobotDAO((void*) m_pcRobotState, 1);
		m_pcFiniteStateMachine->Init();
		m_bFiniteStateMachineGiven = true;
	}

	

	REGISTER_CONTROLLER(AutoMoDeControllerSmartObject, "automode_controller_smartobject");
}
