paths = require "paths"
-----------------------------------------------------------------------------------------------------------------------
project "SysUI"
    language "C++"
    characterset "MBCS"
    kind "StaticLib"
    targetname "sys_ui"
    
    includedirs
    {
        paths.ui,
        paths.ecs,
        paths.lib_multimedia,
        paths.memory,
        paths.resource,
        paths.gameplay,
        paths.game,
        paths.gameState,
        paths.events,
        paths.glm.inc,
    }
    
    files
    {
        paths.ui .. "/**.cpp",
        paths.ui .. "/**.h",
    }
    
    vpaths
    {
        ["Source Files"] = 
        {
            paths.ui .. "/**.cpp",
        },
        ["Header Files"] = 
        {
            paths.ui .. "/**.h",
        },
    }
-----------------------------------------------------------------------------------------------------------------------
