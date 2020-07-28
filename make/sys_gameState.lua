paths = require "paths"
-----------------------------------------------------------------------------------------------------------------------
project "SysGameState"
    language "C++"
    characterset "MBCS"
    kind "StaticLib"
    targetname "sys_gameState"
    
    includedirs
    {
        paths.gameState,
        paths.game,
        paths.events,
        paths.telemetry
    }
    
    files
    {
        paths.gameState .. "/**.cpp",
        paths.gameState .. "/**.h",
    }
    
    vpaths
    {
        ["Source Files"] = 
        {
            paths.gameState .. "/**.cpp",
        },
        ["Header Files"] = 
        {
            paths.gameState .. "/**.h",
        },
    }
-----------------------------------------------------------------------------------------------------------------------
