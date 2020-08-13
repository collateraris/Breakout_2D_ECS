paths = require "paths"
-----------------------------------------------------------------------------------------------------------------------
project "SysGameplay"
    language "C++"
    characterset "MBCS"
    kind "StaticLib"
    targetname "sys_gameplay"
    
    includedirs
    {
        paths.gameplay,
        paths.animation,
        paths.events,
        paths.game,
        paths.ecs,
        paths.lib_multimedia,
        paths.memory,
        paths.physics,
        paths.GLFW.inc,
        paths.GL.inc,
        paths.glm.inc,
    }
    
    files
    {
        paths.gameplay .. "/**.cpp",
        paths.gameplay .. "/**.h",
    }
    
    vpaths
    {
        ["Source Files"] = 
        {
            paths.gameplay .. "/**.cpp",
        },
        ["Header Files"] = 
        {
            paths.gameplay .. "/**.h",
        },
    }
-----------------------------------------------------------------------------------------------------------------------
