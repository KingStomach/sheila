cmake_minimum_required(VERSION 3.28)

project(sheila)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(proxy REQUIRED)

add_library(${PROJECT_NAME} SHARED)

target_compile_options(${PROJECT_NAME} PUBLIC ${CXX_COMPILER_OPTIONS})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)

file(GLOB_RECURSE HEADERS "headers/*.h")
file(GLOB_RECURSE SOURCES "sources/*.cpp")
file(GLOB_RECURSE MODULES "modules/*.ixx")

source_group("Header" FILES ${HEADERS})
source_group("Source" FILES ${SOURCES})
source_group("Module" FILES ${MODULES})

target_sources(
  ${PROJECT_NAME}
  PUBLIC FILE_SET ${PROJECT_NAME}_MODULES TYPE CXX_MODULES FILES ${MODULES}
  PRIVATE ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/headers)

target_compile_definitions(${PROJECT_NAME} PRIVATE SHEILA_BUILD)

target_link_libraries(${PROJECT_NAME} PRIVATE msft_proxy4_module)

if(SHEILA_ENABLE_TESTING)
  option(BUILD_TESTING "Build the testing tree" ON)
  enable_testing()
  target_compile_definitions(${PROJECT_NAME} PRIVATE SHEILA_ENABLE_TEST)
  add_subdirectory("test")
endif()
