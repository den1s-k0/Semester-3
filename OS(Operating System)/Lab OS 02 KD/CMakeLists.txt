cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Lab OS 02 KD")

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL$<$<CONFIG:Debug>:Debug>")
endif()

set(THREADS_PREFER_PTHREAD_FLAG OFF)
find_package(Threads REQUIRED)

add_executable(Main main.cpp main.h
                core.h core.cpp 
                min_max.h min_max.cpp 
                average.h average.cpp 
                param_structure.h param_structure.cpp)

target_link_libraries(Main PRIVATE Threads::Threads)

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET Main PROPERTY CXX_STANDARD 98)
endif()

include(FetchContent)

set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(TestCore test_core.cpp test_core.h 
                core.h core.cpp
                min_max.h min_max.cpp
                average.h average.cpp
                param_structure.h param_structure.cpp)
add_executable(TestMinMax test_min_max.cpp test_min_max.h 
                min_max.h min_max.cpp)
add_executable(TestAverage test_average.cpp test_average.h 
                average.h average.cpp)
add_executable(TestParamStructure test_param_structure.cpp test_param_structure.h 
                param_structure.h param_structure.cpp)

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET TestCore PROPERTY CXX_STANDARD 98)
    set_property(TARGET TestMinMax PROPERTY CXX_STANDARD 98)
    set_property(TARGET TestAverage PROPERTY CXX_STANDARD 98)
    set_property(TARGET TestParamStructure PROPERTY CXX_STANDARD 98)
endif()

target_link_libraries(TestCore PRIVATE gtest gtest_main Threads::Threads)
target_link_libraries(TestAverage PRIVATE gtest gtest_main Threads::Threads)
target_link_libraries(TestMinMax PRIVATE gtest gtest_main Threads::Threads)
target_link_libraries(TestParamStructure PRIVATE gtest gtest_main Threads::Threads)


include(GoogleTest)
gtest_discover_tests(TestCore)
gtest_discover_tests(TestAverage)
gtest_discover_tests(TestMinMax)
gtest_discover_tests(TestParamStructure)

add_custom_target(run_all_tests ALL
COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
 DEPENDS TestCore TestAverage TestMinMax TestParamStructure
  COMMENT "Running all tests..."
)