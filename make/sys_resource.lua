paths = require "paths"
-----------------------------------------------------------------------------------------------------------------------
project "SysResource"
    language "C++"
    characterset "MBCS"
    kind "StaticLib"
    targetname "sys_resource"
    
    includedirs
    {
        paths.resource,
        paths.lib_multimedia,
        paths.glm.inc,
        paths.config,
        paths.game,
        paths.tinyxml2.inc,
    }
    
    files
    {
        paths.resource .. "/**.cpp",
        paths.resource .. "/**.h",
    }
    
    vpaths
    {
        ["Source Files"] = 
        {
            paths.resource .. "/**.cpp",
        },
        ["Header Files"] = 
        {
            paths.resource .. "/**.h",
        },
    }
-----------------------------------------------------------------------------------------------------------------------
