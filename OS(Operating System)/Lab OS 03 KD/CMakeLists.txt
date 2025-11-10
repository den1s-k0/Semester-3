cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Lab OS 03 KD")

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL$<$<CONFIG:Debug>:Debug>")
endif()

set(THREADS_PREFER_PTHREAD_FLAG OFF)
find_package(Threads REQUIRED)

add_executable(Main main.h main.cpp
                thread_data.h thread_data.cpp
                marker.h marker.cpp
                core.h core.cpp)

target_link_libraries(Main PRIVATE Threads::Threads)

if (CMAKE_VERSION VERSION_GREATER 3.12)
		set_property(TARGET Main PROPERTY CXX_STANDARD 17)
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


add_executable(TestThreadData test_thread_data.cpp test_thread_data.h 
                thread_data.h thread_data.cpp)
add_executable(TestMarker test_marker.cpp test_marker.h 
                core.h core.cpp
                thread_data.h thread_data.cpp
                marker.h marker.cpp)
add_executable(TestCore test_core.cpp test_core.h
                test_marker.cpp test_marker.h
                core.h core.cpp
                thread_data.h thread_data.cpp
                marker.h marker.cpp)

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET TestThreadData PROPERTY CXX_STANDARD 17)
    set_property(TARGET TestMarker PROPERTY CXX_STANDARD 17)
    set_property(TARGET TestCore PROPERTY CXX_STANDARD 17)
endif()

target_link_libraries(TestThreadData PRIVATE gtest gtest_main Threads::Threads)
target_link_libraries(TestMarker PRIVATE gtest gtest_main Threads::Threads)
target_link_libraries(TestCore PRIVATE gtest gtest_main Threads::Threads)


include(GoogleTest)
gtest_discover_tests(TestThreadData)
gtest_discover_tests(TestMarker)
gtest_discover_tests(TestCore)


add_custom_target(run_all_tests ALL
COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
 DEPENDS  TestThreadData TestMarker TestCore
  COMMENT "Running all tests..."
)