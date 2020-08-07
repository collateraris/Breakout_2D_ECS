paths = require "paths"
-----------------------------------------------------------------------------------------------------------------------
project "SysPhysics"
    language "C++"
    characterset "MBCS"
    kind "StaticLib"
    targetname "sys_physics"
    
    includedirs
    {
        paths.physics,
        paths.game,
        paths.ecs,
        paths.memory,
    }
    
    files
    {
        paths.physics .. "/**.cpp",
        paths.physics .. "/**.h",
    }
    
    vpaths
    {
        ["Source Files"] = 
        {
            paths.physics .. "/**.cpp",
        },
        ["Header Files"] = 
        {
            paths.physics .. "/**.h",
        },

    }
-----------------------------------------------------------------------------------------------------------------------
