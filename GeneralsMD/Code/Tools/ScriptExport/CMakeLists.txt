# TheSuperHackers @feature AhmedSalah 12/01/2026 ScriptExport tool to decompile/compile SCB script files

add_executable(z_script_export
    ScriptExport.cpp
    ScriptParser.cpp
    ScriptParser.h
    ScriptWriter.cpp
    ScriptWriter.h
    ScriptTypes.h
    YamlEmitter.cpp
    YamlEmitter.h
    YamlParser.cpp
    YamlParser.h
    StdAfx.h
)

target_link_libraries(z_script_export PRIVATE
    core_config
    core_utility
)

if(WIN32 OR "${CMAKE_SYSTEM}" MATCHES "Windows")
    target_compile_definitions(z_script_export PRIVATE 
        NOMINMAX
        WIN32_LEAN_AND_MEAN
        NOGDI
        NOUSER
    )
    set_target_properties(z_script_export PROPERTIES OUTPUT_NAME ScriptExportZH)
else()
    set_target_properties(z_script_export PROPERTIES OUTPUT_NAME scriptexportzh)
endif()
