# CMakeList.txt : CMake project for llvm_getting_started_tutorial, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (llvm_getting_started_tutorial "llvm_getting_started_tutorial.cpp" "llvm_getting_started_tutorial.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET llvm_getting_started_tutorial PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
