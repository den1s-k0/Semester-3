enable_testing()
include(GoogleTest)

function(add_lab_test target_name source_file extra_sources)
    add_executable(${target_name}
        ${source_file}
        ${extra_sources}
    )
    target_include_directories(${target_name} PRIVATE ${CMAKE_SOURCE_DIR})
    target_link_libraries(${target_name} PRIVATE gtest_main)
    set_property(TARGET ${target_name} PROPERTY CXX_STANDARD 20)
    add_test(NAME Run${target_name} COMMAND ${target_name})
    gtest_discover_tests(${target_name})
endfunction()

add_lab_test(TestEmployee test_employee.cpp "test_header.h;../employee.cpp;../employee.h;../header.h")
add_lab_test(TestFunction test_function.cpp "test_header.h;../function.cpp;../function.h;../employee.cpp;../employee.h;../header.h")
add_lab_test(TestCreator test_creator.cpp "test_header.h;../function.cpp;../function.h;../employee.cpp;../employee.h;../header.h")
add_lab_test(TestReporter test_reporter.cpp "test_header.h;../function.cpp;../function.h;../employee.cpp;../employee.h;../header.h")

 add_custom_target(run_all_tests ALL
 COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
  DEPENDS TestEmployee TestFunction TestCreator TestReporter
   COMMENT "Running all tests..."
)
