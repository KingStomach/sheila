cmake_minimum_required(VERSION 3.28)

project(sheila)

add_compile_options(${CXX_COMPILER_OPTIONS})

add_library(${PROJECT_NAME} SHARED)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)

file(GLOB_RECURSE HEADERS "headers/*.h")
file(GLOB_RECURSE SOURCES "sources/*.cpp")
file(GLOB_RECURSE MODULES "modules/*.ixx")

source_group("Headers" FILES ${HEADERS})
source_group("Sources" FILES ${SOURCES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/modules PREFIX "Modules" FILES ${MODULES})

target_sources(
  ${PROJECT_NAME}
  PUBLIC FILE_SET ${PROJECT_NAME}_MODULES TYPE CXX_MODULES FILES ${MODULES}
  PRIVATE ${SOURCES} ${HEADERS}
  )

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/headers)

string(TOUPPER ${PROJECT_NAME} UPPER_PROJECT_NAME)
target_compile_definitions(${PROJECT_NAME} PRIVATE ${UPPER_PROJECT_NAME}_BUILD)

if(${PROJECT_NAME} IN_LIST ENABLE_TEST_PROJECTS)
  target_compile_definitions(${PROJECT_NAME} PRIVATE ${UPPER_PROJECT_NAME}_ENABLE_TEST)
  add_subdirectory("test")
endif()
