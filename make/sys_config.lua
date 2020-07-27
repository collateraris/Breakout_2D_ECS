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
        paths.tinyxml2.inc,
    }
    
    files
    {
        paths.config .. "/**.cpp",
        paths.config .. "/**.h",
        paths.tinyxml2.inc .. "/**.cpp",
        paths.tinyxml2.inc .. "/**.h",
    }
    
    vpaths
    {
        ["Source Files"] = 
        {
            paths.config .. "/**.cpp",
            paths.tinyxml2.inc .. "/**.cpp",
        },
        ["Header Files"] = 
        {
            paths.config .. "/**.h",
            paths.tinyxml2.inc .. "/**.h",
        },
    }
-----------------------------------------------------------------------------------------------------------------------
