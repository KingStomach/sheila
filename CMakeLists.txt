cmake_minimum_required(VERSION 3.28)

project(sheila)

add_library(${PROJECT_NAME} SHARED)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)

file(GLOB HEADERS "headers/*.h")
file(GLOB MODULES "modules/*.ixx")
file(GLOB SOURCES "sources/*.cpp")

source_group("Headers" FILES ${HEADERS})
source_group("Modules" FILES ${MODULES})
source_group("Sources" FILES ${SOURCES})

target_sources(
  ${PROJECT_NAME}
  PUBLIC FILE_SET ${PROJECT_NAME}_MODULES TYPE CXX_MODULES FILES ${MODULES}
  PUBLIC FILE_SET ${PROJECT_NAME}_HEADERS TYPE HEADERS FILES ${HEADERS}
  PRIVATE ${SOURCES}
  )

target_precompile_headers(${PROJECT_NAME} PUBLIC "headers/global.h" INTERFACE "headers/sheila.h")

string(TOUPPER ${PROJECT_NAME} UPPER_PROJECT_NAME)
target_compile_definitions(${PROJECT_NAME} PRIVATE ${UPPER_PROJECT_NAME}_BUILD)

if(MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE /Zc:preprocessor)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${OUTPUT_DIRECTORY})

if(${PROJECT_NAME} IN_LIST ENABLE_TEST_PROJECTS)
  target_compile_definitions(${PROJECT_NAME} PRIVATE ${UPPER_PROJECT_NAME}_ENABLE_TEST)
  add_subdirectory("test")
endif()
