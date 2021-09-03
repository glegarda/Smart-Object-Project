/**
 * @file <argos3/plugins/robots/generic/control_interface/ci_smartobject_ground_sensor.cpp>
 */

#include "ci_smartobject_ground_sensor.h"

#ifdef ARGOS_WITH_LUA
#include <argos3/core/wrappers/lua/lua_utility.h>
#endif

namespace argos {

   /****************************************/
   /****************************************/

#ifdef ARGOS_WITH_LUA
   void CCI_SmartObject_GroundSensor::CreateLuaState(lua_State* pt_lua_state) {
      CLuaUtility::StartTable(pt_lua_state, "ground");
      CLuaUtility::AddToTable(pt_lua_state, 1, m_tReading);
      CLuaUtility::EndTable(pt_lua_state);
   }
#endif

   /****************************************/
   /****************************************/

#ifdef ARGOS_WITH_LUA
   void CCI_SmartObject_GroundSensor::ReadingsToLuaState(lua_State* pt_lua_state) {
      lua_getfield(pt_lua_state, -1, "ground");
      lua_pushnumber(pt_lua_state, 1);
      lua_pushnumber(pt_lua_state, m_tReading);
      lua_settable  (pt_lua_state, -3);
      lua_pop(pt_lua_state, 1);
   }
#endif


   /****************************************/
   /****************************************/

   const Real& CCI_SmartObject_GroundSensor::GetReading() const {
     return m_tReading;
   }

   /****************************************/
   /****************************************/

}
