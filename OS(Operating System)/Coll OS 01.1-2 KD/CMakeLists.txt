# CMakeList.txt: проект CMake для Coll OS 01.1-2 KD; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Coll OS 01.1-2 KD")

function(add_exe target_name source_file extra_sources)
    add_executable(${target_name}
        ${source_file}
        ${extra_sources}
    )
	if (CMAKE_VERSION VERSION_GREATER 3.12)
		set_property(TARGET ${target_name} PROPERTY CXX_STANDARD 20)
	endif()
endfunction()

add_exe(Main main.cpp "main.h;fib.cpp;fib.h")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
