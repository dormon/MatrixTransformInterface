cmake_minimum_required(VERSION 3.10.1)

project(MatrixTransformInterface)

SET(CMAKE_CXX_STANDARD 14)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

set(MAJOR_VERSION 1)
set(MINOR_VERSION 0)
set(REVISION_VERSION 0)

set(LIB_NAME MatrixTransformInterface)

set(SOURCES
  )

set(INCLUDES
  src/${LIB_NAME}/Fwd.h
  src/${LIB_NAME}/MatrixTransformInterface.h
  )

add_library(${LIB_NAME} INTERFACE)
add_library(${LIB_NAME}::${LIB_NAME} ALIAS ${LIB_NAME})

target_include_directories(${LIB_NAME} INTERFACE $<INSTALL_INTERFACE:include>)
target_include_directories(${LIB_NAME} INTERFACE $<INSTALL_INTERFACE:src>)
target_include_directories(${LIB_NAME} INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)
target_include_directories(${LIB_NAME} INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

set(LIB_NAME_LOWER)
string(TOLOWER ${LIB_NAME} LIB_NAME_LOWER)

set(${LIB_NAME}_VERSION ${MAJOR_VERSION}.${MINOR_VERSION}.${REVISION_VERSION})

set_property(TARGET ${LIB_NAME} PROPERTY INTERFACE_${LIB_NAME}_MAJOR_VERSION 1)
set_property(TARGET ${LIB_NAME} APPEND PROPERTY COMPATIBLE_INTERFACE_STRING ${LIB_NAME}_MAJOR_VERSION)

install(TARGETS ${LIB_NAME} EXPORT ${LIB_NAME}Targets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
  )

install(
  FILES
  ${INCLUDES}
  DESTINATION
  include/${LIB_NAME}
  COMPONENT
  Devel
  )

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}/${LIB_NAME}ConfigVersion.cmake
  VERSION ${${LIB_NAME}_VERSION}
  COMPATIBILITY SameMajorVersion
  )

export(EXPORT ${LIB_NAME}Targets
  FILE ${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}/${LIB_NAME}Targets.cmake
  NAMESPACE ${LIB_NAME}::
  )

set(ConfigPackageLocation lib/cmake/${LIB_NAME})
install(EXPORT ${LIB_NAME}Targets
  FILE
  ${LIB_NAME}Targets.cmake
  NAMESPACE
  ${LIB_NAME}::
  DESTINATION
  ${ConfigPackageLocation}
  )

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}/${LIB_NAME}Config.cmake
  "include($" "{CMAKE_CURRENT_LIST_DIR}/${LIB_NAME}Targets.cmake)"
  )

install(
  FILES
  ${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}/${LIB_NAME}Config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}/${LIB_NAME}ConfigVersion.cmake
  DESTINATION
  ${ConfigPackageLocation}
  COMPONENT
  Devel
  )

