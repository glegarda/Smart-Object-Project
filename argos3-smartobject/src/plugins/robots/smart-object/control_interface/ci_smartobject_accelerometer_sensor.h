/**
 * @file <argos3/plugins/robots/object/control_interface/ci_smartobject_accelerometer_sensor.h
 */
#ifndef CCI_SMARTOBJECT_ACCELEROMETER_SENSOR_H
#define CCI_SMARTOBJECT_ACCELEROMETER_SENSOR_H

namespace argos {
   class CCI_SmartObjectAccelerometerSensor;
}

#include <argos3/core/control_interface/ci_sensor.h>
#include <math.h>

namespace argos {

   class CCI_SmartObjectAccelerometerSensor : virtual public CCI_Sensor {

   public:

      /**
       * Destructor
       */
      virtual ~CCI_SmartObjectAccelerometerSensor() {}


       /**
       * Struct representing the values of the sensor
       */
	 struct SReading {

		 struct Velocity {
			/**
		      * velocity in X direction
		      */
		     Real v_X;

		     /**
		      * velocity in Y direction
		      */
		     Real v_Y;

		     /**
		      * velocity in Z direction
		      */
		     Real v_Z;

			 const Real getVelocity() const {
			   return sqrt(pow(v_X, 2.0) + 
				       pow(v_Y, 2.0) + 
				       pow(v_Z, 2.0));

			}

			 Velocity() :
				v_X(0.0f),
				v_Y(0.0f),
				v_Z(0.0f) {}

		 };

		 struct Acceleration {
		     /**
		      * acceleration in X direction
		      */
		     Real a_X;

		     /**
		      * acceleration in Y direction
		      */
		     Real a_Y;

		     /**
		      * acceleration in Z direction
		      */
		     Real a_Z;

		     const Real getAcceleration() const {
			   return sqrt(pow(a_X, 2.0) + 
				       pow(a_Y, 2.0) + 
				       pow(a_Z, 2.0));

		     }

		     Acceleration() : 
				a_X(0.0f),
				a_Y(0.0f),
				a_Z(0.0f) {}		
		 };
	
		 Velocity vel;
		 Acceleration acc;
       
         /**
          * Empty constructor
          */
         SReading() {
			Reset();
		  }

         /**
          * Reset the reading (ie. all 0)
          */
         void Reset() {
			vel.v_X = 0.0f;
			vel.v_Y = 0.0f;
			vel.v_Z = 0.0f;
			acc.a_X = 0.0f;
			acc.a_Y = 0.0f;
			acc.a_Z = 0.0f;  
		}
	};


      inline virtual const SReading& GetReading() const {
         return m_sReading;
      }

#ifdef ARGOS_WITH_LUA
      /**
       *
       * @param pt_lua_state
       */
      virtual void CreateLuaState(lua_State* pt_lua_state);

      /**
       *
       * @param pt_lua_state
       */
      virtual void ReadingsToLuaState(lua_State* pt_lua_state);
#endif

   protected:

      /**
       * Values read by the sensor
       */
      SReading m_sReading;

   };

   /**
    * Redefine the operator "<<" for readings
    */
   std::ostream& operator<<(std::ostream& c_os,
                            const CCI_SmartObjectAccelerometerSensor::SReading& s_reading);
}
#endif
