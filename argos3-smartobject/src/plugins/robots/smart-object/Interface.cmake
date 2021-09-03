#
# object control interface headers
#
set(ARGOS3_HEADERS_PLUGINS_ROBOTS_OBJECT_CONTROLINTERFACE
  # Sensors
  control_interface/ci_smartobject_accelerometer_sensor.h
  control_interface/ci_smartobject_ground_sensor.h
  control_interface/ci_smartobject_leds_actuator.h
)

#
# object control interface sources
#
set(ARGOS3_SOURCES_PLUGINS_ROBOTS_OBJECT
  ${ARGOS3_HEADERS_PLUGINS_ROBOTS_OBJECT_CONTROLINTERFACE}
  # Sensors
  control_interface/ci_smartobject_accelerometer_sensor.cpp
  control_interface/ci_smartobject_ground_sensor.cpp
  control_interface/ci_smartobject_leds_actuator.cpp
)

#
# Install location for the object control interface headers
#
install(
  FILES ${ARGOS3_HEADERS_PLUGINS_ROBOTS_OBJECT_CONTROLINTERFACE}
  DESTINATION include/argos3/plugins/robots/smart-object/control_interface)
