cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Lab OS 05 KD")

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL$<$<CONFIG:Debug>:Debug>")
endif()


function(add_exe target_name source_file extra_sources)
    add_executable(${target_name}
        ${source_file}
        ${extra_sources}
    )
	if (CMAKE_VERSION VERSION_GREATER 3.12)
		set_property(TARGET ${target_name} PROPERTY CXX_STANDARD 11)
	endif()
endfunction()

add_exe(Server server.cpp "server.h;shared_constants.h;employee.cpp;employee.h;record_lock.cpp;record_lock.h;pipe_manager.cpp;pipe_manager.h;process_manager.cpp;process_manager.h;file_manager.cpp;file_manager.h")
add_exe(Client client.cpp "client.h;shared_constants.h;employee.cpp;employee.h;pipe_manager.cpp;pipe_manager.h;file_manager.cpp;file_manager.h")

include(FetchContent)

set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

include(GoogleTest)


function(add_lab_test target_name source_file extra_sources)
    add_executable(${target_name}
        ${source_file}
        ${extra_sources}
    )
    target_include_directories(${target_name} PRIVATE ${CMAKE_SOURCE_DIR})
    target_link_libraries(${target_name} PRIVATE gtest_main)
    set_property(TARGET ${target_name} PROPERTY CXX_STANDARD 11)
    add_test(NAME Run${target_name} COMMAND ${target_name})
    gtest_discover_tests(${target_name})
endfunction()

add_lab_test(TestEmployee test_employee.cpp "test_employee.h;employee.cpp;employee.h")
add_lab_test(TestFileManager test_file_manager.cpp "test_file_manager.h;file_manager.cpp;file_manager.h;employee.cpp;employee.h")
add_lab_test(TestRecordLock test_record_lock.cpp "test_record_lock.h;record_lock.cpp;record_lock.h")
add_lab_test(TestConstants test_constants.cpp "test_constants.h;shared_constants.h")
add_lab_test(TestPipeManager test_pipe_manager.cpp "test_pipe_manager.h;pipe_manager.cpp;pipe_manager.h")
add_lab_test(TestProcessManager test_process_manager.cpp "test_process_manager.h;process_manager.cpp;process_manager.h;record_lock.cpp;record_lock.h;employee.cpp;employee.h;pipe_manager.cpp;pipe_manager.h")


add_custom_target(run_all_tests ALL
COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
 DEPENDS  TestEmployee TestFileManager TestRecordLock TestConstants TestPipeManager TestProcessManager
  COMMENT "Running all tests..."
)