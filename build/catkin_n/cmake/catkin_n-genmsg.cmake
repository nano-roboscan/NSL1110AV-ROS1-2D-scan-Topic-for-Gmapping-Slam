# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "catkin_n: 1 messages, 0 services")

set(MSG_I_FLAGS "-Icatkin_n:/home/nanosys/catkin_n/src/catkin_n/msg;-Igeometry_msgs:/opt/ros/melodic/share/geometry_msgs/cmake/../msg;-Istd_msgs:/opt/ros/melodic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(catkin_n_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/nanosys/catkin_n/src/catkin_n/msg/pose.msg" NAME_WE)
add_custom_target(_catkin_n_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "catkin_n" "/home/nanosys/catkin_n/src/catkin_n/msg/pose.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(catkin_n
  "/home/nanosys/catkin_n/src/catkin_n/msg/pose.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/catkin_n
)

### Generating Services

### Generating Module File
_generate_module_cpp(catkin_n
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/catkin_n
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(catkin_n_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(catkin_n_generate_messages catkin_n_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/nanosys/catkin_n/src/catkin_n/msg/pose.msg" NAME_WE)
add_dependencies(catkin_n_generate_messages_cpp _catkin_n_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(catkin_n_gencpp)
add_dependencies(catkin_n_gencpp catkin_n_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS catkin_n_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(catkin_n
  "/home/nanosys/catkin_n/src/catkin_n/msg/pose.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/catkin_n
)

### Generating Services

### Generating Module File
_generate_module_eus(catkin_n
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/catkin_n
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(catkin_n_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(catkin_n_generate_messages catkin_n_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/nanosys/catkin_n/src/catkin_n/msg/pose.msg" NAME_WE)
add_dependencies(catkin_n_generate_messages_eus _catkin_n_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(catkin_n_geneus)
add_dependencies(catkin_n_geneus catkin_n_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS catkin_n_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(catkin_n
  "/home/nanosys/catkin_n/src/catkin_n/msg/pose.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/catkin_n
)

### Generating Services

### Generating Module File
_generate_module_lisp(catkin_n
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/catkin_n
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(catkin_n_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(catkin_n_generate_messages catkin_n_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/nanosys/catkin_n/src/catkin_n/msg/pose.msg" NAME_WE)
add_dependencies(catkin_n_generate_messages_lisp _catkin_n_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(catkin_n_genlisp)
add_dependencies(catkin_n_genlisp catkin_n_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS catkin_n_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(catkin_n
  "/home/nanosys/catkin_n/src/catkin_n/msg/pose.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/catkin_n
)

### Generating Services

### Generating Module File
_generate_module_nodejs(catkin_n
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/catkin_n
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(catkin_n_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(catkin_n_generate_messages catkin_n_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/nanosys/catkin_n/src/catkin_n/msg/pose.msg" NAME_WE)
add_dependencies(catkin_n_generate_messages_nodejs _catkin_n_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(catkin_n_gennodejs)
add_dependencies(catkin_n_gennodejs catkin_n_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS catkin_n_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(catkin_n
  "/home/nanosys/catkin_n/src/catkin_n/msg/pose.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/catkin_n
)

### Generating Services

### Generating Module File
_generate_module_py(catkin_n
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/catkin_n
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(catkin_n_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(catkin_n_generate_messages catkin_n_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/nanosys/catkin_n/src/catkin_n/msg/pose.msg" NAME_WE)
add_dependencies(catkin_n_generate_messages_py _catkin_n_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(catkin_n_genpy)
add_dependencies(catkin_n_genpy catkin_n_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS catkin_n_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/catkin_n)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/catkin_n
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(catkin_n_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/catkin_n)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/catkin_n
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(catkin_n_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/catkin_n)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/catkin_n
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(catkin_n_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/catkin_n)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/catkin_n
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(catkin_n_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/catkin_n)
  install(CODE "execute_process(COMMAND \"/usr/bin/python2\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/catkin_n\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/catkin_n
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(catkin_n_generate_messages_py geometry_msgs_generate_messages_py)
endif()
