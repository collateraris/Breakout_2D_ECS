paths = require "paths"
-----------------------------------------------------------------------------------------------------------------------
project "SysConfig"
    language "C++"
    characterset "MBCS"
    kind "StaticLib"
    targetname "sys_config"
    
    includedirs
    {
        paths.config,
    }
    
    files
    {
        paths.config .. "/**.cpp",
        paths.config .. "/**.h",
    }
    
    vpaths
    {
        ["Source Files"] = 
        {
            paths.config .. "/**.cpp",
        },
        ["Header Files"] = 
        {
            paths.config .. "/**.h",
        },
    }
-----------------------------------------------------------------------------------------------------------------------
