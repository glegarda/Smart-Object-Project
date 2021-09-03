/*
 * @file <src/modules/AutoMoDeBehaviour.cpp>
 *
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 *
 * @package ARGoS3-AutoMoDe
 *
 * @license MIT License
 */

#include "AutoMoDeBehaviourSmartObject.h"


namespace argos {

   AutoMoDeBehaviourSmartObject::AutoMoDeBehaviourSmartObject() {
        c_CurrentColor = CColor::BLACK;
		color_index = 0;
        color_cycle.push_back(CColor::RED);
        color_cycle.push_back(CColor::GREEN);
        color_cycle.push_back(CColor::BLUE);
		//color_cycle = {CColor::RED, CColor::GREEN, CColor::BLUE};

   }
	/****************************************/
	/****************************************/

	AutoMoDeBehaviourSmartObject::~AutoMoDeBehaviourSmartObject() {}

	/****************************************/
	/****************************************/

	void AutoMoDeBehaviourSmartObject::SetRobotDAO(void* pc_robot_dao) {
		m_pcRobotDAO = (SmartObjectDAO*) pc_robot_dao;
	}

    /****************************************/
    /****************************************/
    // Return the color parameter
    CColor AutoMoDeBehaviourSmartObject::GetColorParameter(const UInt32& un_value, const bool& b_emiter) {

        CColor cColorParameter;

        //********************************************************
            switch(un_value){
            case 0:
                cColorParameter = CColor::BLACK;
                break;
            case 1:
                cColorParameter = CColor::RED;
                color_index = 0;
                break;
            case 2:
                cColorParameter = CColor::GREEN;
                color_index = 1;
                break;
            case 3:
                cColorParameter = CColor::BLUE;
                color_index = 2;
                break;
            case 4:
                cColorParameter = RandomColor();
                break;
            case 5:
                cColorParameter = NextColor();
                break;
            case 6:
                cColorParameter = CurrentColor();
                break;
            default:
                cColorParameter = CColor::BLACK;
            }

        return cColorParameter;
    }

    /****************************************/
    /****************************************/

    CColor AutoMoDeBehaviourSmartObject::RandomColor() {
        try{
            CRandom::CRNG* m_pcRng = CRandom::CreateRNG("argos");
            UInt16 size = color_cycle.size();
            color_index = m_pcRng->Uniform(CRange<UInt32>(0, size));
            std::cout << color_cycle[color_index] << std::endl;
            return color_cycle[color_index];
        } catch(const std::exception &e){
            e.what();
        }
      return CColor::BLACK;

    }

    /****************************************/
    /****************************************/

    CColor AutoMoDeBehaviourSmartObject::NextColor() {
        CColor current_color = CurrentColor();
        color_index = 0;
        for (color_index = 0; color_index < color_cycle.size(); color_index++) {
            if (current_color == color_cycle[color_index]){
                break;
            }
        }
        color_index++;
        if (color_index >= color_cycle.size()){
            color_index = 0;
        }
        return color_cycle[color_index];
    }

    /****************************************/
    /****************************************/

    CColor AutoMoDeBehaviourSmartObject::CurrentColor() {
        return m_pcRobotDAO->GetLEDsColor();
    }

}
