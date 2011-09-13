IF (WIN32)
    # Require 2.6 for Windows
    CMAKE_MINIMUM_REQUIRED (VERSION 2.6 FATAL_ERROR)
ELSE (WIN32)
    CMAKE_MINIMUM_REQUIRED (VERSION 2.4.7 FATAL_ERROR)
ENDIF (WIN32)

# Set the project name
PROJECT (libfaults)
STRING (TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWER)

# Set the package version
SET (LIBRARY_VERSION 1.0.0 CACHE STRING "libfaults version")

IF (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")
   SET (LIB_DIR "lib64")
ELSE ()
   SET (LIB_DIR "lib")
ENDIF ()

IF (NOT CMAKE_BUILD_TYPE)
  SET (CMAKE_BUILD_TYPE "release" CACHE STRING "Choose the type of build, options are: release (default) debug, profile" FORCE)
ENDIF (NOT CMAKE_BUILD_TYPE)
STRING (TOUPPER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE)
MESSAGE (STATUS "Build type ${CMAKE_BUILD_TYPE}")

SET (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
SET (BUILD_SHARED_LIBS ON)

SET (srcFiles FaultModel.cc
              models/Constant.cc
              models/Cycle.cc
              #models/Lua.cc
              models/Noise.cc
              models/Offset.cc
              models/Random.cc
              models/Scale.cc)

SET (hdrFiles FaultModel.h)

SET (modelHdrFiles models/Constant.h
                   models/Cycle.h
                   #models/Lua.h
                   models/Noise.h
                   models/Offset.h
                   models/Random.h
                   models/Scale.h)

ADD_LIBRARY (faults ${srcFiles})
SET_TARGET_PROPERTIES (faults PROPERTIES
                              VERSION ${LIBRARY_VERSION})

MESSAGE (STATUS "${PROJECT_NAME} version ${LIBRARY_VERSION} will be installed to:")
MESSAGE (STATUS "  ${CMAKE_INSTALL_PREFIX}/${LIB_DIR}")
MESSAGE (STATUS "Header files will be installed to:")
MESSAGE (STATUS "  ${CMAKE_INSTALL_PREFIX}/include")

# TODO: Add versioning to output paths?
INSTALL (TARGETS faults LIBRARY DESTINATION ${LIB_DIR}/)
INSTALL (FILES ${hdrFiles} DESTINATION include/${PROJECT_NAME_LOWER}/)
INSTALL (FILES ${modelHdrFiles} DESTINATION include/${PROJECT_NAME_LOWER}/models/)

ENABLE_TESTING ()

ADD_EXECUTABLE (testConstant tests/testConstant.cc)
TARGET_LINK_LIBRARIES (testConstant faults)
ADD_TEST (testConstant ${CMAKE_CURRENT_BINARY_DIR}/testConstant)

ADD_EXECUTABLE (testCycle tests/testCycle.cc)
TARGET_LINK_LIBRARIES (testCycle faults)
ADD_TEST (testCycle ${CMAKE_CURRENT_BINARY_DIR}/testCycle)

#ADD_EXECUTABLE (testLua tests/testLua.cc)
#TARGET_LINK_LIBRARIES (testLua faults)
#ADD_TEST (testLua ${CMAKE_CURRENT_BINARY_DIR}/testLua)

ADD_EXECUTABLE (testNoise tests/testNoise.cc)
TARGET_LINK_LIBRARIES (testNoise faults)
ADD_TEST (testNoise ${CMAKE_CURRENT_BINARY_DIR}/testNoise)

ADD_EXECUTABLE (testOffset tests/testOffset.cc)
TARGET_LINK_LIBRARIES (testOffset faults)
ADD_TEST (testOffset ${CMAKE_CURRENT_BINARY_DIR}/testOffset)

ADD_EXECUTABLE (testRandom tests/testRandom.cc)
TARGET_LINK_LIBRARIES (testRandom faults)
ADD_TEST (testRandom ${CMAKE_CURRENT_BINARY_DIR}/testRandom)

ADD_EXECUTABLE (testScale tests/testScale.cc)
TARGET_LINK_LIBRARIES (testScale faults)
ADD_TEST (testScale ${CMAKE_CURRENT_BINARY_DIR}/testScale)

