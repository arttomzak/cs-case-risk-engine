cmake_minimum_required(VERSION 3.12)
project(CaseRiskEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(case_risk_engine ${SOURCES})