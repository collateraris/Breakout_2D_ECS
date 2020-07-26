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
