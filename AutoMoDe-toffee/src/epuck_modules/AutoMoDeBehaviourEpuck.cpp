/*
 * @file <src/modules/AutoMoDeBehaviour.cpp>
 *
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 *
 * @package ARGoS3-AutoMoDe
 *
 * @license MIT License
 */

#include "AutoMoDeBehaviourEpuck.h"


namespace argos {

	AutoMoDeBehaviourEpuck::~AutoMoDeBehaviourEpuck() {}

    CVector2 AutoMoDeBehaviourEpuck::ComputeWheelsVelocity(Real fLeftVelocity, Real fRightVelocity) {
        // Transform relative velocity according to max velocity allowed
		Real fVelocityFactor = m_pcRobotDAO->GetMaxVelocity() / Max<Real>(std::abs(fRightVelocity), std::abs(fLeftVelocity));
		CVector2 cWheelsVelocity = CVector2(fVelocityFactor * fLeftVelocity, fVelocityFactor * fRightVelocity);

		return cWheelsVelocity;

    }


   	CVector2 AutoMoDeBehaviourEpuck::ComputeWheelsVelocityFromVector1(CVector2 c_vector_to_follow) {
		Real fLeftVelocity = 0;
		Real fRightVelocity = 0;
		CRange<CRadians> cLeftHemisphere(CRadians::ZERO, CRadians::PI);
		CRange<CRadians> cRightHemisphere(CRadians::PI, CRadians::TWO_PI);
		CRadians cNormalizedVectorToFollow = c_vector_to_follow.Angle().UnsignedNormalize();
		if (c_vector_to_follow.GetX() != 0 || c_vector_to_follow.GetY() != 0) {
			if (cLeftHemisphere.WithinMinBoundExcludedMaxBoundExcluded(cNormalizedVectorToFollow)) {
				fRightVelocity = 0.1;
				//fLeftVelocity = Cos(cNormalizedVectorToFollow);
                fLeftVelocity = -0.1;
			} else {
				//fRightVelocity = Cos(cNormalizedVectorToFollow);
                fRightVelocity = -0.1;
				fLeftVelocity = 0.1;
			}
		}

		// Transform relative velocity according to max velocity allowed
		Real fVelocityFactor = m_pcRobotDAO->GetMaxVelocity() / Max<Real>(std::abs(fRightVelocity), std::abs(fLeftVelocity));
		CVector2 cWheelsVelocity = CVector2(fVelocityFactor * fLeftVelocity, fVelocityFactor * fRightVelocity);

		return cWheelsVelocity;
	}


	/****************************************/
	/****************************************/

	CVector2 AutoMoDeBehaviourEpuck::ComputeWheelsVelocityFromVector(CVector2 c_vector_to_follow) {
		Real fLeftVelocity = 0;
		Real fRightVelocity = 0;
		CRange<CRadians> cLeftHemisphere(CRadians::ZERO, CRadians::PI);
		CRange<CRadians> cRightHemisphere(CRadians::PI, CRadians::TWO_PI);
		CRadians cNormalizedVectorToFollow = c_vector_to_follow.Angle().UnsignedNormalize();
		if (c_vector_to_follow.GetX() != 0 || c_vector_to_follow.GetY() != 0) {
			if (cLeftHemisphere.WithinMinBoundExcludedMaxBoundExcluded(cNormalizedVectorToFollow)) {
				fRightVelocity = 1;
				fLeftVelocity = Cos(cNormalizedVectorToFollow);
			} else {
				fRightVelocity = Cos(cNormalizedVectorToFollow);
				fLeftVelocity = 1;
			}
		}

		// Transform relative velocity according to max velocity allowed
		Real fVelocityFactor = m_pcRobotDAO->GetMaxVelocity() / Max<Real>(std::abs(fRightVelocity), std::abs(fLeftVelocity));
		CVector2 cWheelsVelocity = CVector2(fVelocityFactor * fLeftVelocity, fVelocityFactor * fRightVelocity);

		return cWheelsVelocity;
	}

	/****************************************/
	/****************************************/

	CVector2 AutoMoDeBehaviourEpuck::SumProximityReadings(CCI_EPuckProximitySensor::TReadings s_prox) {
		CVector2 cSum(0, 0);
		for (UInt8 i = 0; i < s_prox.size(); i++) {
			cSum += CVector2(s_prox[i].Value, s_prox[i].Angle);
		}
		return cSum;
	}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourEpuck::SetRobotDAO(void* pc_robot_dao) {
		m_pcRobotDAO = (EpuckDAO*) pc_robot_dao;
	}

    /****************************************/
    /****************************************/
    // Return the color parameter
    CColor AutoMoDeBehaviourEpuck::GetColorParameter(const UInt32& un_value, const bool& b_emiter) {

        CColor cColorParameter;

        //********************************************************
        // HARD CODED true for real robots, false for simulation
        // TODO Change for parameter in xml

        bool b_real_robot = false;

        //********************************************************

        if (b_real_robot && b_emiter){
            switch(un_value){
            case 0:
                cColorParameter = CColor::BLACK;
                break;
            case 1:
                cColorParameter = CColor::GREEN;
                break;
            case 2:
                cColorParameter = CColor::BLUE;
                break;
            case 3:
                cColorParameter = CColor::RED;
                break;
            case 4:
                cColorParameter = CColor(250,80,0);
                break;
            case 5:
                cColorParameter = CColor(150,0,60);
                break;
            case 6:
                cColorParameter = CColor(0,200,50);
                break;
            default:
                cColorParameter = CColor::BLACK;
            }
        }
        else {
            switch(un_value){
            case 0:
                cColorParameter = CColor::BLACK;
                break;
            case 1:
                cColorParameter = CColor::GREEN;
                break;
            case 2:
                cColorParameter = CColor::BLUE;
                break;
            case 3:
                cColorParameter = CColor::RED;
                break;
            case 4:
                cColorParameter = CColor::YELLOW;
                break;
            case 5:
                cColorParameter = CColor::MAGENTA;
                break;
            case 6:
                cColorParameter = CColor::CYAN;
                break;
            default:
                cColorParameter = CColor::BLACK;
            }
        }

        return cColorParameter;
    }

}
