paths = require "paths"
-----------------------------------------------------------------------------------------------------------------------
project "SysECS"
    language "C++"
    characterset "MBCS"
    kind "StaticLib"
    targetname "sys_ecs"
    
    includedirs
    {
        paths.ecs,
        paths.memory,
    }
    
    files
    {
        paths.ecs .. "/**.cpp",
        paths.ecs .. "/**.h",
    }
    
    vpaths
    {
        ["Source Files"] = 
        {
            paths.ecs .. "/**.cpp",
        },
        ["Header Files"] = 
        {
            paths.ecs .. "/**.h",
        },
    }
-----------------------------------------------------------------------------------------------------------------------
