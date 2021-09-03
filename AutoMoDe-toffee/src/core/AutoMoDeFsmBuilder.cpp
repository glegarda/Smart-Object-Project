/*
 * @file <src/core/AutoMoDeFsmBuilder.cpp>
 *
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 *
 * @package ARGoS3-AutoMoDe
 *
 * @license MIT License
 */

#include "AutoMoDeFsmBuilder.h"

namespace argos {

	/****************************************/
	/****************************************/

	AutoMoDeFsmBuilder::AutoMoDeFsmBuilder() {}

	/****************************************/
	/****************************************/

	AutoMoDeFsmBuilder::~AutoMoDeFsmBuilder() {
		delete cFiniteStateMachine;
	}

	/****************************************/
	/****************************************/

	AutoMoDeFiniteStateMachine* AutoMoDeFsmBuilder::BuildFiniteStateMachine(const std::string& str_fsm_config) {
		std::istringstream iss(str_fsm_config);
		std::vector<std::string> tokens;
		copy(std::istream_iterator<std::string>(iss),
			std::istream_iterator<std::string>(),
			std::back_inserter(tokens));
		return BuildFiniteStateMachine(tokens);
	}

	/****************************************/
	/****************************************/

	AutoMoDeFiniteStateMachine* AutoMoDeFsmBuilder::BuildFiniteStateMachine(std::vector<std::string>& vec_fsm_config) {
		cFiniteStateMachine = new AutoMoDeFiniteStateMachine();
		std::vector<std::string>::iterator it;
		try {
			it = std::find(vec_fsm_config.begin(), vec_fsm_config.end(), "--type");
			m_unType = atoi((*(it+1)).c_str());
			it = std::find(vec_fsm_config.begin(), vec_fsm_config.end(), "--nstates");
			m_unNumberStates = atoi((*(it+1)).c_str());

			std::vector<std::string>::iterator first_state;
			std::vector<std::string>::iterator second_state;
			for (UInt32 i = 0; i < m_unNumberStates; i++) {
				std::ostringstream oss;
				oss << "--s" << i;
				first_state = std::find(vec_fsm_config.begin(), vec_fsm_config.end(), oss.str());
				if (i+1 < m_unNumberStates) {
					std::ostringstream oss;
					oss << "--s" << i+1;
					second_state = std::find(vec_fsm_config.begin(), vec_fsm_config.end(), oss.str());
				} else {
					second_state = vec_fsm_config.end();
				}
				std::vector<std::string> vecStateConfig(first_state, second_state);
				HandleState(cFiniteStateMachine, vecStateConfig);
			}
		}
		catch (std::exception e) {
			THROW_ARGOSEXCEPTION("Could not create the Finite State Machine: Error while parsing.");
		}

		return cFiniteStateMachine;

	}

	/****************************************/
	/****************************************/

	void AutoMoDeFsmBuilder::HandleState(AutoMoDeFiniteStateMachine* c_fsm, std::vector<std::string>& vec_fsm_state_config) {
	//	AutoMoDeBehaviour* cNewBehaviour;
		std::vector<std::string>::iterator it;
		// Extraction of the index of the behaviour in the FSM
		UInt8 unBehaviourIndex =  atoi((*vec_fsm_state_config.begin()).substr(3,4).c_str());
		// Extraction of the identifier of the behaviour
		UInt8 unBehaviourIdentifier =  atoi((*(vec_fsm_state_config.begin()+1)).c_str());

		AutoMoDeBehaviour* cNewBehaviour = GetAutoMoDeBehaviour(unBehaviourIdentifier);
		cNewBehaviour->SetIndex(unBehaviourIndex);
		cNewBehaviour->SetIdentifier(unBehaviourIdentifier);

		// Checking for parameters
		std::vector<std::string> vecPossibleParameters = GetPossibleParameters(0);

		for (UInt8 i = 0; i < vecPossibleParameters.size(); i++) {
			std::string strCurrentParameter = vecPossibleParameters[i];
			std::ostringstream oss;
			oss << "--" <<strCurrentParameter << unBehaviourIndex;
			it = std::find(vec_fsm_state_config.begin(), vec_fsm_state_config.end(), oss.str());
			if (it != vec_fsm_state_config.end()) {
				Real fCurrentParameterValue = strtod((*(it+1)).c_str(), NULL);
				cNewBehaviour->AddParameter(strCurrentParameter, fCurrentParameterValue);
			}
		}
		cNewBehaviour->Init();
		// Add the constructed Behaviour to the FSM
		c_fsm->AddBehaviour(cNewBehaviour);

		/*
		 * Extract the transitions starting from the state and
		 * pass them to the transition handler, if they exist.
		 */
		std::ostringstream oss;
		oss << "--n" << unBehaviourIndex;
		it = std::find(vec_fsm_state_config.begin(), vec_fsm_state_config.end(), oss.str());
		if (it != vec_fsm_state_config.end()) {
			UInt8 unNumberTransitions = atoi((*(it+1)).c_str());

			std::vector<std::string>::iterator first_transition;
			std::vector<std::string>::iterator second_transition;

			for (UInt8 i = 0; i < unNumberTransitions; i++) {
				std::ostringstream oss, oss1;
				oss << "--n" << unBehaviourIndex << "x" << i;
				first_transition = std::find(vec_fsm_state_config.begin(), vec_fsm_state_config.end(), oss.str());
				if (i+1 < unNumberTransitions) {
					std::ostringstream oss;
					oss << "--n" << unBehaviourIndex << "x" << i+1;
					second_transition = std::find(vec_fsm_state_config.begin(), vec_fsm_state_config.end(), oss.str());
				} else {
					second_transition = vec_fsm_state_config.end();
				}
				std::vector<std::string> vecTransitionConfig(first_transition, second_transition);
				HandleTransition(vecTransitionConfig, unBehaviourIndex, i);
			}
		}
	}

	/****************************************/
	/****************************************/

	void AutoMoDeFsmBuilder::HandleTransition(std::vector<std::string>& vec_fsm_transition_config, const UInt32& un_initial_state_index, const UInt32& un_condition_index) {
		AutoMoDeCondition* cNewCondition;

		std::stringstream ss;
		ss << "--n" << un_initial_state_index << "x" << un_condition_index;
		std::vector<UInt32> vecPossibleDestinationIndex = GetPossibleDestinationBehaviour(un_initial_state_index);
		std::vector<std::string>::iterator it;
		it = std::find(vec_fsm_transition_config.begin(), vec_fsm_transition_config.end(), ss.str());
		// TODO: Check here whether unToBehaviour is smaller than the total number of states.
		UInt32 unIndexBehaviour = atoi((*(it+1)).c_str());
		UInt32 unToBehaviour = vecPossibleDestinationIndex.at(unIndexBehaviour);
		if (unToBehaviour < m_unNumberStates) {
			ss.str(std::string());
			ss << "--c" << un_initial_state_index << "x" << un_condition_index;
			it = std::find(vec_fsm_transition_config.begin(), vec_fsm_transition_config.end(), ss.str());

			UInt8 unConditionIdentifier = atoi((*(it+1)).c_str());

			cNewCondition = GetAutoMoDeCondition(unConditionIdentifier);

			cNewCondition->SetOriginAndExtremity(un_initial_state_index, unToBehaviour);
			cNewCondition->SetIndex(un_condition_index);
			cNewCondition->SetIdentifier(unConditionIdentifier);


			// Checking for parameters
			std::vector<std::string> vecPossibleParameters = GetPossibleParameters(1);
			for (UInt8 i = 0; i < vecPossibleParameters.size(); i++) {
				std::string strCurrentParameter = vecPossibleParameters[i];
				ss.str(std::string());
				ss << "--" << strCurrentParameter << un_initial_state_index << "x" << un_condition_index;
				it = std::find(vec_fsm_transition_config.begin(), vec_fsm_transition_config.end(), ss.str());
				if (it != vec_fsm_transition_config.end()) {
					Real fCurrentParameterValue = strtod((*(it+1)).c_str(), NULL);
					cNewCondition->AddParameter(strCurrentParameter, fCurrentParameterValue);
				}
			}
			cNewCondition->Init();
			cFiniteStateMachine->AddCondition(cNewCondition);
		}
	}

	/****************************************/
	/****************************************/

	const std::vector<UInt32> AutoMoDeFsmBuilder::GetPossibleDestinationBehaviour(const UInt32& un_initial_state_index) {
		std::vector<UInt32> vecPossibleDestinationIndex;
		for (UInt32 i = 0; i < m_unNumberStates; i++) {
			if (i != un_initial_state_index) {
				vecPossibleDestinationIndex.push_back(i);
			}
		}
		return vecPossibleDestinationIndex;
	}

	/****************************************/
	/****************************************/

	AutoMoDeBehaviour* AutoMoDeFsmBuilder::GetAutoMoDeBehaviour(UInt8 unBehaviourIdentifier) {
		AutoMoDeBehaviour* cNewBehaviour;
		// Creation of the Behaviour object
		switch(m_unType) {
			case 0:
				switch(unBehaviourIdentifier) {
					case 0:
						cNewBehaviour = new AutoMoDeBehaviourEpuckExploration();
						break;
					case 1:
						cNewBehaviour = new AutoMoDeBehaviourEpuckStop();
						break;
					case 2:
						cNewBehaviour = new AutoMoDeBehaviourEpuckPhototaxis();
						break;
					case 3:
						cNewBehaviour = new AutoMoDeBehaviourEpuckAntiPhototaxis();
						break;
					case 4:
						cNewBehaviour = new AutoMoDeBehaviourEpuckAttraction();
						break;
					case 5:
						cNewBehaviour = new AutoMoDeBehaviourEpuckRepulsion();
						break;
					case 8:
						cNewBehaviour = new AutoMoDeBehaviourEpuckGoToColor();
						break;
					case 9:
						cNewBehaviour = new AutoMoDeBehaviourEpuckGoAwayColor();
						break;
					case 10:
						cNewBehaviour = new AutoMoDeBehaviourEpuckPushColor();
						break;
				}
				break;
			case 1:
				switch(unBehaviourIdentifier) {
					case 0:
						cNewBehaviour = new AutoMoDeBehaviourSmartObjectLightColor();
						break;
				}
				break;
		}
		return cNewBehaviour;
	}

	/****************************************/
	/****************************************/

	AutoMoDeCondition* AutoMoDeFsmBuilder::GetAutoMoDeCondition(UInt8 unConditionIdentifier) {
		AutoMoDeCondition* cNewCondition;
		switch(m_unType) {
			case 0:
				switch(unConditionIdentifier) {
						case 0:
							cNewCondition = new AutoMoDeConditionEpuckBlackFloor();
							break;
						case 1:
							cNewCondition = new AutoMoDeConditionEpuckGrayFloor();
							break;
						case 2:
							cNewCondition = new AutoMoDeConditionEpuckWhiteFloor();
							break;
						case 3:
							cNewCondition = new AutoMoDeConditionEpuckNeighborsCount();
							break;
						case 4:
							cNewCondition = new AutoMoDeConditionEpuckInvertedNeighborsCount();
							break;
						case 5:
							cNewCondition = new AutoMoDeConditionEpuckFixedProbability();
							break;
						case 7:
							cNewCondition = new AutoMoDeConditionEpuckProbColor();
							break;
					}
				break;
			case 1:
				switch(unConditionIdentifier) {
						case 0:
							cNewCondition = new AutoMoDeConditionSmartObjectBlackFloor();
							break;
						case 1:
							cNewCondition = new AutoMoDeConditionSmartObjectMoving();
							break;
						case 2:
							cNewCondition = new AutoMoDeConditionSmartObjectGrayFloor();
							break;	
						case 3:
							cNewCondition = new AutoMoDeConditionSmartObjectWhiteFloor();
							break;
					}
				break;
		}
		return cNewCondition;


	}

	/****************************************/
	/****************************************/


	std::vector<std::string> AutoMoDeFsmBuilder::GetPossibleParameters(UInt8 param_type) {
		std::vector<std::string> vecPossibleParameters;
		switch(m_unType){
			case 0:
				switch(param_type){	
					case 0:
						vecPossibleParameters.push_back("rwm");
						vecPossibleParameters.push_back("att");
						vecPossibleParameters.push_back("rep");
						vecPossibleParameters.push_back("cle");
						vecPossibleParameters.push_back("clr");
						vecPossibleParameters.push_back("vel");
						//vecPossibleParameters = {"rwm", "att", "rep", "cle", "clr", "vel"};
						break;
					case 1:
						vecPossibleParameters.push_back("p");
						vecPossibleParameters.push_back("w");
						vecPossibleParameters.push_back("l");
						//vecPossibleParameters = {"p", "w", "l"};
						break;
				}
				break;
			case 1:
				switch(param_type){	
					case 0:
						vecPossibleParameters.push_back("rwm");
						vecPossibleParameters.push_back("att");
						vecPossibleParameters.push_back("rep");
						vecPossibleParameters.push_back("cle");
						vecPossibleParameters.push_back("clr");
						vecPossibleParameters.push_back("vel");
						//vecPossibleParameters = {"rwm", "att", "rep", "cle", "clr", "vel"};
						break;
					case 1:
						vecPossibleParameters.push_back("p");
						vecPossibleParameters.push_back("w");
						vecPossibleParameters.push_back("l");
						//vecPossibleParameters = {"p", "w", "l", "t"};
						break;
				}
				break;
		}
		return vecPossibleParameters;
	}

}
