paths = require "paths"
-----------------------------------------------------------------------------------------------------------------------
project "SysMemory"
    language "C++"
    characterset "MBCS"
    kind "StaticLib"
    targetname "sys_memory"
    
    includedirs
    {
        paths.memory,
    }
    
    files
    {
        paths.memory .. "/**.cpp",
        paths.memory .. "/**.h",
    }
    
    vpaths
    {
        ["Source Files"] = 
        {
            paths.memory .. "/**.cpp",
        },
        ["Header Files"] = 
        {
            paths.memory .. "/**.h",
        },
    }
-----------------------------------------------------------------------------------------------------------------------
