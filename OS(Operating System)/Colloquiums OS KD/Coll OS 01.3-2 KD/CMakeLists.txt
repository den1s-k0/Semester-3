# CMakeList.txt: проект CMake для Coll OS 01.3-2 KD; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Coll OS 01.3-2 KD")

add_executable(Main main.cpp main.h core.cpp core.h linked_list.h)

if (CMAKE_VERSION VERSION_GREATER 3.12)
		set_property(TARGET Main PROPERTY CXX_STANDARD 20)
endif()
# TODO: Добавьте тесты и целевые объекты, если это необходимо.

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(TestLinkedList test_linked_list.cpp test_linked_list.h linked_list.h)

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET TestLinkedList PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(TestLinkedList PRIVATE gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(TestLinkedList)

add_custom_target(run_all_tests ALL
COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
 DEPENDS TestLinkedList
  COMMENT "Running all tests..."
)