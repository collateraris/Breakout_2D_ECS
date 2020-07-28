paths = require "paths"
-----------------------------------------------------------------------------------------------------------------------
project "Game"
    language "C++"
    characterset "MBCS"
    kind "ConsoleApp"
    targetname "Breakout"
    
    postbuildcommands
    {
        "{MKDIR} " .. paths.build,
        "{DELETE} " .. paths.build .. "/%{cfg.buildtarget.name}",		
		"{COPY} " .. paths.root .. "/assets " .. paths.build .. "/assets",
		"{COPY} " .. paths.root .. "/assets " .. paths.genDebug .. "/assets",
		"{COPY} " .. paths.root .. "/assets " .. paths.genRelease .. "/assets",
		"{COPY} " .. paths.root .. "/assets " .. paths.genPrj .. "/assets",
		
        "{COPY} %{cfg.buildtarget.directory}%{cfg.buildtarget.name} " .. paths.build,
    }
      
    includedirs
    {
        paths.game,
        paths.GL.inc,
        paths.GLFW.inc,
        paths.glm.inc,
        paths.stb_image.inc,
        paths.tinyxml2.inc,
        paths.config,
        paths.events,
		paths.gameState,
		paths.telemetry,
		paths.input,
		paths.memory,
        paths.ui,
        paths.ecs,
		paths.animation,
		paths.profile,
        paths.audio,
        paths.resource,
        paths.lib_multimedia
    }
    
    libdirs
    {
        paths.GL.lib,
        paths.GLFW.lib
    }
    
    links
    {
        "SysConfig",
        "SysAnimation",
        "SysAudio",
        "SysEvents",
        "SysInput",
        "SysMemory",
        "SysPhysics",
        "SysProfile",
        "SysTelemetry",
        "SysUI",
        "SysECS",
        "SysGameState",
        "SysResource",
        "LibMultimedia",
        "opengl32",
        "glfw3",
        "glew32s"
    }
    
    files
    {
        paths.game .. "/**.cpp",
        paths.game .. "/**.h",
    }

    vpaths
    {
        ["Source Files"] = 
        {
            paths.game .. "/*.cpp",
        },
        ["Header Files"] = 
        {
            paths.game .. "/*.h",
        },		
    }
-----------------------------------------------------------------------------------------------------------------------
