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
        paths.resource,
        paths.irrKlang.inc,
        paths.lib_multimedia,
        paths.glm.inc,
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
