paths = require "paths"
-----------------------------------------------------------------------------------------------------------------------
project "LibMultimedia"
    language "C++"
    characterset "MBCS"
    kind "StaticLib"
    targetname "lib_multimedia"
    
    includedirs
    {
        paths.lib_multimedia,
        paths.GL.inc,
        paths.GLFW.inc,
        paths.glm.inc,
        paths.stb_image.inc,
    }
    
    files
    {
        paths.lib_multimedia .. "/**.cpp",
        paths.lib_multimedia .. "/**.h",
    }
    
    vpaths
    {
        ["Source Files"] = 
        {
            paths.lib_multimedia .. "/**.cpp",
        },
        ["Header Files"] = 
        {
            paths.lib_multimedia .. "/**.h",
        },
    }
-----------------------------------------------------------------------------------------------------------------------
