cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Lab OS 04 KD")

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL$<$<CONFIG:Debug>:Debug>")
endif()

add_executable(Receiver receiver.h receiver.cpp
                circular_queue.h circular_queue.cpp
                process_manager.h process_manager.cpp
                common.h common.cpp)

add_executable(Sender sender.h sender.cpp
                circular_queue.h circular_queue.cpp
                process_manager.h process_manager.cpp
                common.h common.cpp)

if (CMAKE_VERSION VERSION_GREATER 3.12)
		set_property(TARGET Receiver PROPERTY CXX_STANDARD 14)
        set_property(TARGET Sender PROPERTY CXX_STANDARD 14)
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

add_executable(TestCommon test_common.cpp test_common.h
                circular_queue.h circular_queue.cpp
                process_manager.h process_manager.cpp
                common.h common.cpp)

add_executable(TestCircularQueue test_circular_queue.cpp test_circular_queue.h
                circular_queue.h circular_queue.cpp
                process_manager.h process_manager.cpp
                common.h common.cpp)

add_executable(TestProcessManager test_process_manager.cpp test_process_manager.h
                circular_queue.h circular_queue.cpp
                process_manager.h process_manager.cpp
                common.h common.cpp)

add_executable(TestNamespaces test_namespaces.cpp test_namespaces.h
                circular_queue.h circular_queue.cpp
                process_manager.h process_manager.cpp
                common.h common.cpp)

target_link_libraries(TestCommon PRIVATE gtest gtest_main)
target_link_libraries(TestCircularQueue PRIVATE gtest gtest_main)
target_link_libraries(TestProcessManager PRIVATE gtest gtest_main)
target_link_libraries(TestNamespaces PRIVATE gtest gtest_main)

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET TestCommon PROPERTY CXX_STANDARD 14)
    set_property(TARGET TestCircularQueue PROPERTY CXX_STANDARD 14)
    set_property(TARGET TestProcessManager PROPERTY CXX_STANDARD 14)
    set_property(TARGET TestNamespaces PROPERTY CXX_STANDARD 14)

endif()

include(GoogleTest)
gtest_discover_tests(TestCommon)
gtest_discover_tests(TestCircularQueue)
gtest_discover_tests(TestProcessManager)
gtest_discover_tests(TestNamespaces)


add_custom_target(run_all_tests ALL
COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
 DEPENDS  TestCommon TestCircularQueue TestProcessManager TestNamespaces
  COMMENT "Running all tests..."
)