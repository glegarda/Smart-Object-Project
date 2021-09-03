#
# Object simulator code
#
# Headers

set(ARGOS3_HEADERS_PLUGINS_ROBOTS_OBJECT_SIMULATOR
    simulator/dynamics2d_smartobject_model.h
    simulator/smartobject_entity.h
    simulator/smartobject_accelerometer_sensor.h
    simulator/smartobject_ground_rotzonly_sensor.h
    simulator/smartobject_leds_default_actuator.h
    simulator/accelerometer_equipped_entity.h
)
if(ARGOS_COMPILE_QTOPENGL)
    set(ARGOS3_HEADERS_PLUGINS_ROBOTS_OBJECT_SIMULATOR
      ${ARGOS3_HEADERS_PLUGINS_ROBOTS_OBJECT_SIMULATOR}
      simulator/qtopengl_smartobject.h)
endif(ARGOS_COMPILE_QTOPENGL)

# Install location for the object simulator headers
install(
  FILES ${ARGOS3_HEADERS_PLUGINS_ROBOTS_OBJECT_SIMULATOR}
  DESTINATION include/argos3/plugins/robots/smart-object/simulator)


# Sources
set(ARGOS3_SOURCES_PLUGINS_ROBOTS_OBJECT
  ${ARGOS3_SOURCES_PLUGINS_ROBOTS_OBJECT}
  ${ARGOS3_HEADERS_PLUGINS_ROBOTS_OBJECT_SIMULATOR}
    simulator/dynamics2d_smartobject_model.cpp
    simulator/smartobject_entity.cpp
    simulator/smartobject_accelerometer_sensor.cpp
    simulator/smartobject_ground_rotzonly_sensor.cpp
    simulator/smartobject_leds_default_actuator.cpp
    simulator/accelerometer_equipped_entity.cpp
)
if(ARGOS_COMPILE_QTOPENGL)
  set(ARGOS3_SOURCES_PLUGINS_ROBOTS_OBJECT
    ${ARGOS3_SOURCES_PLUGINS_ROBOTS_OBJECT}
    simulator/qtopengl_smartobject.cpp)
endif(ARGOS_COMPILE_QTOPENGL)

#
# Create object plugin
#
# Create target
add_library(argos3plugin_${ARGOS_BUILD_FOR}_smartobject SHARED
  ${ARGOS3_SOURCES_PLUGINS_ROBOTS_OBJECT})
# Link libraries
target_link_libraries(argos3plugin_${ARGOS_BUILD_FOR}_smartobject
  argos3core_${ARGOS_BUILD_FOR}
  argos3plugin_${ARGOS_BUILD_FOR}_genericrobot
  argos3plugin_${ARGOS_BUILD_FOR}_dynamics2d)
if(ARGOS_COMPILE_QTOPENGL)
  target_link_libraries(argos3plugin_${ARGOS_BUILD_FOR}_smartobject
    argos3plugin_${ARGOS_BUILD_FOR}_qtopengl)
endif(ARGOS_COMPILE_QTOPENGL)

# Install location for the object plugin
install(FILES ${ARGOS3_HEADERS_PLUGINS_ROBOTS_OBJECT_SIMULATOR}      
	DESTINATION include/argos3/plugins/robots/smart-object/simulator)
install(TARGETS argos3plugin_${ARGOS_BUILD_FOR}_smartobject
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib/argos3
  ARCHIVE DESTINATION lib/argos3)
