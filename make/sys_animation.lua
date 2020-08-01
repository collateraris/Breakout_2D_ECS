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
        paths.lib_multimedia,
        paths.game,
        paths.memory,
        paths.glm.inc
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
