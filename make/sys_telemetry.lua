paths = require "paths"
-----------------------------------------------------------------------------------------------------------------------
project "SysTelemetry"
    language "C++"
    characterset "MBCS"
    kind "StaticLib"
    targetname "sys_telemetry"
    
    includedirs
    {
        paths.telemetry,
    }
    
    files
    {
        paths.telemetry .. "/**.cpp",
        paths.telemetry .. "/**.h",
    }
    
    vpaths
    {
        ["Source Files"] = 
        {
            paths.telemetry .. "/**.cpp",
        },
        ["Header Files"] = 
        {
            paths.telemetry .. "/**.h",
        },
    }
-----------------------------------------------------------------------------------------------------------------------
