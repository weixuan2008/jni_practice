# CMakeList.txt : CMake project for Calculation, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Configure JNI header files
include_directories("E:/workspace_oxygen/java/oracle/jdk-11.0.12/include/win32")
include_directories("E:/workspace_oxygen/java/oracle/jdk-11.0.12/include")

# Add source to this project's executable.
# add_executable (Calculation "Calculation.cpp" "Calculation.h")

# Add source to dynamic library
add_library(Calculation SHARED  "Food.h"  "com_hy_report_api_Food.h" "com_hy_report_api_Food.cpp")


# TODO: Add tests and install targets if needed.
