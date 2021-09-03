/**
 * @file <argos3/plugins/robots/object/simulator/object_accelerometer_sensor.h>
 * @author Piotr Rochala
 */

#ifndef SMARTOBJECT_ACCELEROMETER_SENSOR_H
#define SMARTOBJECT_ACCELEROMETER_SENSOR_H

namespace argos {
   class CSmartObjectAccelerometerSensor;
   class CAccelerometerEquippedEntity;
}

#include <argos3/plugins/robots/smart-object/control_interface/ci_smartobject_accelerometer_sensor.h>
#include <argos3/core/utility/math/range.h>
#include <argos3/core/utility/math/rng.h>
#include <argos3/core/simulator/space/space.h>
#include <argos3/core/simulator/sensor.h>

namespace argos {
   class CSmartObjectAccelerometerSensor : public CSimulatedSensor, public CCI_SmartObjectAccelerometerSensor {

   public :

         CSmartObjectAccelerometerSensor();

         virtual ~CSmartObjectAccelerometerSensor() {}

         virtual void SetRobot(CComposableEntity& c_entity);

         void Init(TConfigurationNode& t_tree);

         virtual void Update();

         virtual void Reset();

   private:
         /** Reference to embodied entity associated to this sensor */
         CEmbodiedEntity* m_pcEmbodiedEntity;

         /** Reference to accelerometer equipped entity associated to this sensor */
         CAccelerometerEquippedEntity* m_pcAcceleratorEntity;

         /** Reference to controllable entity associated to this sensor */
         CControllableEntity* m_pcControllableEntity;
         
         /** Random number generator */
      	 CRandom::CRNG* m_pcRNG;
      	 
      /** Whether to add noise or not */
      bool m_bAddNoise;

      /** Noise range */
      CRange<Real> m_cNoiseRange;

	 /* the last known position of the object */
         Real oldPosX;
         Real oldPosY;
         Real oldPosZ;

	 /* the last known velocity of the object */
         Real oldVelX;
         Real oldVelY;
         Real oldVelZ;
      };
}
#endif
