paths = require "paths"
-----------------------------------------------------------------------------------------------------------------------
project "SysAnimation"
    language "C++"
    characterset "MBCS"
    kind "StaticLib"
    targetname "sys_animation"
    
    includedirs
    {
        paths.animation,
        paths.ecs,
    }
    
    files
    {
        paths.animation .. "/**.cpp",
        paths.animation .. "/**.h",
    }
    
    vpaths
    {
        ["Source Files"] = 
        {
            paths.animation .. "/**.cpp",
        },
        ["Header Files"] = 
        {
            paths.animation .. "/**.h",
        },
    }
-----------------------------------------------------------------------------------------------------------------------
