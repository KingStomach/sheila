cmake_minimum_required(VERSION 3.28)

project(sheila_test)

file(GLOB SOURCES "*.cpp")
file(GLOB MODULES "*.ixx")

source_group(source FILES ${SOURCES})
source_group(module FILES ${MODULES})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_executable(${PROJECT_NAME})

target_sources(
  ${PROJECT_NAME}
  PRIVATE FILE_SET ${PROJECT_NAME}_MODULES TYPE CXX_MODULES FILES ${MODULES}
  PRIVATE ${SOURCES})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)
target_link_libraries(${PROJECT_NAME} PRIVATE sheila)

string(TOUPPER ${PROJECT_NAME} UPPER_PROJECT_NAME)
target_compile_definitions(${PROJECT_NAME} PRIVATE ${UPPER_PROJECT_NAME}_BUILD)

set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
