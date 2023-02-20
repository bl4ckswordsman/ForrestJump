# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "MinSizeRel")
  file(REMOVE_RECURSE
  "CMakeFiles\\ForrestJumpV02_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ForrestJumpV02_autogen.dir\\ParseCache.txt"
  "ForrestJumpV02_autogen"
  )
endif()
