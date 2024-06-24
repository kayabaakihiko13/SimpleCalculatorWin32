cmake_minimum_required(VERSION 3.0)
project(SimpleCalculatorWin32)
# specify the output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
add_executable(app_calculator WIN32 kalkulator_sederhana.cc)
