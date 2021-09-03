# Set up ARGoS compilation information
include_directories(${CMAKE_SOURCE_DIR} ${ARGOS_INCLUDE_DIRS})
link_directories(${ARGOS_LIBRARY_DIRS})

# Headers
set(AUTOMODE_HEADERS
	core/AutoMoDeController.h
	core/AutoMoDeFiniteStateMachine.h
	core/AutoMoDeFsmBuilder.h
	core/AutoMoDeFsmHistory.h
	core/epuck_controller/AutoMoDeControllerEpuck.h
	#general
    	modules_general/AutoMoDeBehaviour.h
    	modules_general/AutoMoDeCondition.h
    	#Behaviours
    	#epuck
    	epuck_modules/AutoMoDeBehaviourEpuck.h
	epuck_modules/AutoMoDeBehaviourEpuckAntiPhototaxis.h
	epuck_modules/AutoMoDeBehaviourEpuckPhototaxis.h
	epuck_modules/AutoMoDeBehaviourEpuckAttraction.h
	epuck_modules/AutoMoDeBehaviourEpuckRepulsion.h
	epuck_modules/AutoMoDeBehaviourEpuckStop.h
	epuck_modules/AutoMoDeBehaviourEpuckExploration.h
    	epuck_modules/AutoMoDeBehaviourEpuckGoToColor.h
    	epuck_modules/AutoMoDeBehaviourEpuckGoAwayColor.h
    	#smartobject
    	smartobject_modules/AutoMoDeBehaviourSmartObject.h
    	smartobject_modules/AutoMoDeBehaviourSmartObjectLightColor.h
	# Conditions
	#epuck
	epuck_modules/AutoMoDeConditionEpuck.h
	epuck_modules/AutoMoDeConditionEpuckBlackFloor.h
	epuck_modules/AutoMoDeConditionEpuckWhiteFloor.h
	epuck_modules/AutoMoDeConditionEpuckGrayFloor.h
	epuck_modules/AutoMoDeConditionEpuckNeighborsCount.h
	epuck_modules/AutoMoDeConditionEpuckInvertedNeighborsCount.h
    	epuck_modules/AutoMoDeConditionEpuckFixedProbability.h
    	epuck_modules/AutoMoDeConditionEpuckProbColor.h
    	#smartobject
    	smartobject/AutoMoDeConditionSmartObject.h
    	smartobject/AutoMoDeConditionSmartObjectBlackFloor.h
    	smartobject/AutoMoDeConditionSmartObjectMoving.h
    	smartobject/AutoMoDeConditionSmartObjectWhiteFloor.h
    	smartobject/AutoMoDeConditionSmartObjectGrayFloor.h
    	
    	)

# Sources
set(AUTOMODE_SOURCES
	core/AutoMoDeController.cpp
	core/AutoMoDeFiniteStateMachine.cpp
	core/AutoMoDeFsmBuilder.cpp
	core/AutoMoDeFsmHistory.cpp
	core/epuck_controller/AutoMoDeControllerEpuck.cpp
	 #general
    	modules_general/AutoMoDeBehaviour.cpp
    	modules_general/AutoMoDeCondition.cpp
    	#Behaviours
    	#epuck
    	epuck_modules/AutoMoDeBehaviourEpuck.cpp
	epuck_modules/AutoMoDeBehaviourEpuckAntiPhototaxis.cpp
	epuck_modules/AutoMoDeBehaviourEpuckPhototaxis.cpp
	epuck_modules/AutoMoDeBehaviourEpuckAttraction.cpp
	epuck_modules/AutoMoDeBehaviourEpuckRepulsion.cpp
	epuck_modules/AutoMoDeBehaviourEpuckStop.cpp
	epuck_modules/AutoMoDeBehaviourEpuckExploration.cpp
    	epuck_modules/AutoMoDeBehaviourEpuckGoToColor.cpp
    	epuck_modules/AutoMoDeBehaviourEpuckGoAwayColor.cpp
    	#smartobject
    	smartobject_modules/AutoMoDeBehaviourSmartObject.cpp
    	smartobject_modules/AutoMoDeBehaviourSmartObjectLightColor.cpp
	# Conditions
	#epuck
	epuck_modules/AutoMoDeConditionEpuck.cpp
	epuck_modules/AutoMoDeConditionEpuckBlackFloor.cpp
	epuck_modules/AutoMoDeConditionEpuckWhiteFloor.cpp
	epuck_modules/AutoMoDeConditionEpuckGrayFloor.cpp
	epuck_modules/AutoMoDeConditionEpuckNeighborsCount.cpp
	epuck_modules/AutoMoDeConditionEpuckInvertedNeighborsCount.cpp
    	epuck_modules/AutoMoDeConditionEpuckFixedProbability.cpp
    	epuck_modules/AutoMoDeConditionEpuckProbColor.cpp
    	#smartobject
    	smartobject/AutoMoDeConditionSmartObject.cpp
    	smartobject/AutoMoDeConditionSmartObjectBlackFloor.cpp
    	smartobject/AutoMoDeConditionSmartObjectMoving.cpp
    	smartobject/AutoMoDeConditionSmartObjectWhiteFloor.cpp
    	smartobject/AutoMoDeConditionSmartObjectGrayFloor.cpp
    	)


add_library(automode SHARED ${AUTOMODE_HEADERS} ${AUTOMODE_SOURCES})
target_link_libraries(automode argos3plugin_${ARGOS_BUILD_FOR}_epuck)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
add_executable(automode_main AutoMoDeMain.cpp)
target_link_libraries(automode_main automode argos3core_${ARGOS_BUILD_FOR} argos3plugin_${ARGOS_BUILD_FOR}_epuck argos3_demiurge_loop_functions argos3_demiurge_epuck_dao argos3plugin_${ARGOS_BUILD_FOR}_smartobject  argos3_demiurge_smartobject_dao)

add_executable(visualize_fsm AutoMoDeVisualizeFSM.cpp)
target_link_libraries(visualize_fsm automode argos3core_${ARGOS_BUILD_FOR} argos3plugin_${ARGOS_BUILD_FOR}_epuck argos3_demiurge_epuck_dao)
