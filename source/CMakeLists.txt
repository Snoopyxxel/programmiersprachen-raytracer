add_executable(example example.cpp)

target_link_libraries(example ${FRAMEWORK_NAME} ${LIBRARIES})
add_dependencies(example glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS example DESTINATION .)

add_executable(raytracer raytracer.cpp)

target_link_libraries(raytracer ${FRAMEWORK_NAME} ${LIBRARIES}
  glfw
  ${GLFW_LIBRARIES}
  )
add_dependencies(raytracer glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS raytracer DESTINATION .)

# Build tests
add_executable(tests tests.cpp ../framework/Box.cpp ../framework/Box.hpp ../framework/Shape.cpp ../framework/Shape.hpp ../framework/Sphere.cpp ../framework/Sphere.hpp ../framework/ray.hpp ../framework/hitpoint.hpp ../framework/vec3_functions.hpp ../framework/vec3_functions.cpp ../framework/Material.cpp ../framework/Material.hpp)
target_link_libraries(tests
  ${GLFW_LIBRARIES}
  )

