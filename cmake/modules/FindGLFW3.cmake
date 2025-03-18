find_path(GLFW3_INCLUDE_DIR
  NAMES GLFW/glfw3.h
  HINTS ${CMAKE_CURRENT_LIST_DIR}/external/glfw/include
        /usr/local/include
        /usr/include
        /opt/homebrew/include
)

find_library(GLFW3_LIBRARY
  NAMES glfw3
  HINTS ${CMAKE_CURRENT_LIST_DIR}/external/glfw/lib
        /usr/local/lib
        /usr/lib
        /opt/homebrew/lib
)

if (NOT GLFW3_INCLUDE_DIR)
  message(FATAL_ERROR "GLFW3 include directory not found")
endif()

if (NOT GLFW3_LIBRARY)
  message(FATAL_ERROR "GLFW3 library not found")
endif()

set(GLFW3_INCLUDE_DIRS ${GLFW3_INCLUDE_DIR} CACHE PATH "Path to GLFW3 include directory")
set(GLFW3_LIBRARIES ${GLFW3_LIBRARY} CACHE FILEPATH "Path to GLFW3 library")

message(STATUS "Found GLFW3 include directory: ${GLFW3_INCLUDE_DIR}")
message(STATUS "Found GLFW3 library: ${GLFW3_LIBRARY}")