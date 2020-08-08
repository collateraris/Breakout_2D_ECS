paths = require "paths"
-----------------------------------------------------------------------------------------------------------------------
project "SysAudio"
    language "C++"
    characterset "MBCS"
    kind "StaticLib"
    targetname "sys_audio"
    
    includedirs
    {
        paths.audio,
        paths.game,
    }
    
    files
    {
        paths.audio .. "/**.cpp",
        paths.audio .. "/**.h",
    }
    
    vpaths
    {
        ["Source Files"] = 
        {
            paths.audio .. "/**.cpp",
        },
        ["Header Files"] = 
        {
            paths.audio .. "/**.h",
        },
    }
-----------------------------------------------------------------------------------------------------------------------
