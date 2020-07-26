paths = require "paths"
-----------------------------------------------------------------------------------------------------------------------
project "SysProfile"
    language "C++"
    characterset "MBCS"
    kind "StaticLib"
    targetname "sys_profile"
    
    includedirs
    {
        paths.profile,
    }
    
    files
    {
        paths.profile .. "/**.cpp",
        paths.profile .. "/**.h",
    }
    
    vpaths
    {
        ["Source Files"] = 
        {
            paths.profile .. "/**.cpp",
        },
        ["Header Files"] = 
        {
            paths.profile .. "/**.h",
        },
    }
-----------------------------------------------------------------------------------------------------------------------
