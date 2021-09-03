/**
 * @file <argos3/plugins/robots/object/control_interface/ci_smartobject_accelerometer_sensor.cpp
 */
#include "ci_smartobject_accelerometer_sensor.h"

#ifdef ARGOS_WITH_LUA
#include <argos3/core/wrappers/lua/lua_utility.h>
#endif

namespace argos {
   
   /****************************************/
   /****************************************/

#ifdef ARGOS_WITH_LUA
   void CCI_SmartObjectAccelerometerSensor::CreateLuaState(lua_State* pt_lua_state) {
      CLuaUtility::OpenRobotStateTable(pt_lua_state, "accelerometer");
      /* Velocity */
      CLuaUtility::StartTable(pt_lua_state, "velocity");
      CLuaUtility::AddToTable(pt_lua_state, "x",  m_sReading.vel.v_X);
      CLuaUtility::AddToTable(pt_lua_state, "y",  m_sReading.vel.v_Y);
      CLuaUtility::AddToTable(pt_lua_state, "z",  m_sReading.vel.v_Z);
      CLuaUtility::EndTable  (pt_lua_state);

      /* Acceleration */
      CLuaUtility::StartTable(pt_lua_state, "acceleration");
      CLuaUtility::AddToTable(pt_lua_state, "x",  m_sReading.acc.a_X);
      CLuaUtility::AddToTable(pt_lua_state, "y",  m_sReading.acc.a_Y);
      CLuaUtility::AddToTable(pt_lua_state, "z",  m_sReading.acc.a_Z);
      CLuaUtility::EndTable  (pt_lua_state);

      CLuaUtility::CloseRobotStateTable(pt_lua_state);
   }
#endif

   /****************************************/
   /****************************************/

#ifdef ARGOS_WITH_LUA
   void CCI_SmartObjectAccelerometerSensor::ReadingsToLuaState(lua_State* pt_lua_state) {
      /*  Velocity */
      lua_getfield(pt_lua_state, -2, "velocity");
      lua_pushnumber(pt_lua_state, m_sReading.vel.v_X);
      lua_setfield  (pt_lua_state, -2, "x"           );
      lua_pushnumber(pt_lua_state, m_sReading.vel.v_Y);
      lua_setfield  (pt_lua_state, -2, "y"           );
      lua_pushnumber(pt_lua_state, m_sReading.vel.v_Z);
      lua_setfield  (pt_lua_state, -2, "z"           );      
      lua_pop(pt_lua_state, 1);
 
      /* Acceleration */
      lua_getfield(pt_lua_state, -3, "acceleration");
      lua_pushnumber(pt_lua_state, m_sReading.acc.a_X);
      lua_setfield  (pt_lua_state, -3, "x"           );
      lua_pushnumber(pt_lua_state, m_sReading.acc.a_Y);
      lua_setfield  (pt_lua_state, -3, "y"           );
      lua_pushnumber(pt_lua_state, m_sReading.acc.a_Z);
      lua_setfield  (pt_lua_state, -3, "z"           );      
      lua_pop(pt_lua_state, 1);
   }
#endif

   /****************************************/
   /****************************************/

   std::ostream& operator<<(std::ostream& c_os,
                            const CCI_SmartObjectAccelerometerSensor::SReading& s_reading) {
      c_os << "SReading(Velocity = (" 
	   << s_reading.vel.v_X 
	   << "," << s_reading.vel.v_Y
           << "," << s_reading.vel.v_Z 
           << "), Acceleration = (" 
           << s_reading.acc.a_X
           << ","
           << s_reading.acc.a_Y
           << ","
           << s_reading.acc.a_Z
           << "))";
      return c_os;
   }
}
