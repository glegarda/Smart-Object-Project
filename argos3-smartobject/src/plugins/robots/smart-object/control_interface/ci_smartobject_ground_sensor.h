/**
 * @file <argos3/plugins/robots/generic/control_interface/ci_smartobject_ground_sensor.h>
 */
#ifndef CCI_SMARTOBJECT_GROUND_SENSOR_H
#define CCI_SMARTOBJECT_GROUND_SENSOR_H

namespace argos {
   class CCI_SmartObject_GroundSensor;
}

#include <argos3/core/control_interface/ci_sensor.h>

namespace argos {

   class CCI_SmartObject_GroundSensor : public CCI_Sensor {

   public:

      virtual ~CCI_SmartObject_GroundSensor() {}

      const Real& GetReading() const;

#ifdef ARGOS_WITH_LUA
      virtual void CreateLuaState(lua_State* pt_lua_state);

      virtual void ReadingsToLuaState(lua_State* pt_lua_state);
#endif

   protected:

	Real m_tReading;

   };

}

#endif
