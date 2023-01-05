# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\ForrestJumpV01_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ForrestJumpV01_autogen.dir\\ParseCache.txt"
  "ForrestJumpV01_autogen"
  )
endif()
