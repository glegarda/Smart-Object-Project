/*
 * @file <src/modules/AutoMoDeBehaviour.cpp>
 *
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 *
 * @package ARGoS3-AutoMoDe
 *
 * @license MIT License
 */

#include "AutoMoDeBehaviour.h"


namespace argos {

	AutoMoDeBehaviour::~AutoMoDeBehaviour() {}

	/****************************************/
	/****************************************/

	const bool AutoMoDeBehaviour::IsLocked() const {
		return m_bLocked;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviour::SetIndex(const UInt32& un_index) {
		m_unIndex = un_index;
	}

	/****************************************/
	/****************************************/

	const UInt32& AutoMoDeBehaviour::GetIndex() const {
		return m_unIndex;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviour::SetIdentifier(const UInt32& un_id) {
		m_unIdentifier = un_id;
	}

	/****************************************/
	/****************************************/

	const UInt32& AutoMoDeBehaviour::GetIdentifier() const {
		return m_unIdentifier;
	}

	/****************************************/
	/****************************************/

	const std::string AutoMoDeBehaviour::GetDOTDescription() {
		std::stringstream ss;
		ss << m_strLabel;
		if (!m_mapParameters.empty()) {
			std::map<std::string, Real>::iterator it;
			for (it = m_mapParameters.begin(); it != m_mapParameters.end(); it++) {
				ss << "\\n" << it->first << "=" << it->second ;
			}
		}
		return ss.str();
	}


	/****************************************/
	/****************************************/

	void AutoMoDeBehaviour::AddParameter(const std::string& str_identifier, const Real& f_value) {
		m_mapParameters.insert(std::pair<std::string, Real>(str_identifier, f_value));
	}

	/****************************************/
	/****************************************/

	const bool AutoMoDeBehaviour::IsOperational() const {
		return m_bOperational;
	}

	/****************************************/
	/****************************************/

	const std::string& AutoMoDeBehaviour::GetLabel() const {
		return m_strLabel;
	}

	/****************************************/
	/****************************************/

	const std::map<std::string, Real> AutoMoDeBehaviour::GetParameters() {
		return m_mapParameters;
	}

}
