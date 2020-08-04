paths = require "paths"
-----------------------------------------------------------------------------------------------------------------------
project "SysInput"
    language "C++"
    characterset "MBCS"
    kind "StaticLib"
    targetname "sys_input"
    
    includedirs
    {
        paths.input,
        paths.game,
        paths.ecs,
        paths.events,
        paths.lib_multimedia,
    }
    
    files
    {
        paths.input .. "/**.cpp",
        paths.input .. "/**.h",
    }
    
    vpaths
    {
        ["Source Files"] = 
        {
            paths.input .. "/**.cpp",
        },
        ["Header Files"] = 
        {
            paths.input .. "/**.h",
        },
    }
-----------------------------------------------------------------------------------------------------------------------
