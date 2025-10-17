# CMakeList.txt: проект CMake для Lab OS 01 KD; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Lab OS 01 KD")

function(add_exe target_name source_file extra_sources)
    add_executable(${target_name}
        ${source_file}
        ${extra_sources}
    )
	if (CMAKE_VERSION VERSION_GREATER 3.12)
		set_property(TARGET ${target_name} PROPERTY CXX_STANDARD 20)
	endif()
endfunction()

add_exe(Main main.cpp "main.h;employee.cpp;employee.h;function.cpp;function.h")
add_exe(Creator creator.cpp "creator.h;employee.cpp;employee.h")
add_exe(Reporter reporter.cpp "reporter.h;employee.cpp;employee.h")

# Поддиректория с тестами

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

add_subdirectory(tests)