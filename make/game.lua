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
        "{COPY} " .. paths.irrKlang.bin .. "/ikpMP3.dll " .. paths.build,
		"{COPY} " .. paths.irrKlang.bin .. "/ikpMP3.dll " .. paths.genDebug,
        "{COPY} " .. paths.irrKlang.bin .. "/ikpMP3.dll " .. paths.genRelease,
        "{COPY} " .. paths.irrKlang.bin .. "/irrKlang.dll " .. paths.build,
		"{COPY} " .. paths.irrKlang.bin .. "/irrKlang.dll " .. paths.genDebug,
        "{COPY} " .. paths.irrKlang.bin .. "/irrKlang.dll " .. paths.genRelease,	
        "{COPY} " .. paths.freetype2.bin .. "/freetype.dll " .. paths.build,
		"{COPY} " .. paths.freetype2.bin .. "/freetype.dll " .. paths.genDebug,
		"{COPY} " .. paths.freetype2.bin .. "/freetype.dll " .. paths.genRelease,	
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
        paths.irrKlang.inc,
        paths.freetype2.inc,
        paths.config,
        paths.events,
        paths.gameState,
        paths.gameplay,
		paths.telemetry,
		paths.input,
		paths.memory,
        paths.ui,
        paths.ecs,
		paths.animation,
		paths.profile,
        paths.audio,
        paths.resource,
        paths.physics,
        paths.lib_multimedia,
    }
    
    libdirs
    {
        paths.GL.lib,
        paths.GLFW.lib,
        paths.irrKlang.lib,
        paths.freetype2.lib,
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
        "SysGameplay",
        "SysResource",
        "LibMultimedia",
        "opengl32",
        "glfw3",
        "glew32s",
        "irrKlang",
        "freetype"
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

        ["Source Files/Bindings"] = 
        {
            paths.bindings .. "/**.cpp",
        },
        ["Header Files/Bindings"] = 
        {
            paths.bindings .. "/**.h",
        },	

        ["Source Files/Components"] = 
        {
            paths.components .. "/**.cpp",
        },
        ["Header Files/Components"] = 
        {
            paths.components .. "/**.h",
        },

    }
-----------------------------------------------------------------------------------------------------------------------
