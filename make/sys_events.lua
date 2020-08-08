paths = require "paths"
-----------------------------------------------------------------------------------------------------------------------
project "SysEvents"
    language "C++"
    characterset "MBCS"
    kind "StaticLib"
    targetname "sys_events"
    
    includedirs
    {
        paths.events,
        paths.physics,
        paths.ecs,
    }
    
    files
    {
        paths.events .. "/**.cpp",
        paths.events .. "/**.h",
    }
    
    vpaths
    {
        ["Source Files"] = 
        {
            paths.events .. "/**.cpp",
        },
        ["Header Files"] = 
        {
            paths.events .. "/**.h",
        },
    }
-----------------------------------------------------------------------------------------------------------------------
