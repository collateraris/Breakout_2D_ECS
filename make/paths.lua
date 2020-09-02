-----------------------------------------------------------------------------------------------------------------------
local paths     = {}
-----------------------------------------------------------------------------------------------------------------------
paths.root      = path.getabsolute("..")
paths.source    = paths.root   .. "/source"
paths.game      = paths.source .. "/game"
paths.bindings  = paths.game .. "/bindings"
paths.components = paths.game .. "/components"
paths.config    = paths.source .. "/sys_config"
paths.animation = paths.source .. "/sys_animation"
paths.audio     = paths.source .. "/sys_audio"
paths.events    = paths.source .. "/sys_events"
paths.input     = paths.source .. "/sys_input"
paths.memory    = paths.source .. "/sys_memory"
paths.physics   = paths.source .. "/sys_physics"
paths.profile   = paths.source .. "/sys_profile"
paths.telemetry = paths.source .. "/sys_telemetry"
paths.ui        = paths.source .. "/sys_ui"
paths.ecs       = paths.source .. "/sys_ecs"
paths.gameState = paths.source .. "/sys_gameState"
paths.resource  = paths.source .. "/sys_resource"
paths.gameplay  = paths.source .. "/sys_gameplay"
paths.lib_multimedia = paths.source .. "/lib_multimedia"

-----------------------------------------------------------------------------------------------------------------------
paths.GL      = {}
paths.GL.root = paths.root .. "/libraries/GL"
paths.GL.inc  = paths.GL.root .. "/include"
paths.GL.lib  = paths.GL.root .. "/lib"
-----------------------------------------------------------------------------------------------------------------------
paths.GLFW      = {}
paths.GLFW.root = paths.root .. "/libraries/GLFW"
paths.GLFW.inc  = paths.GLFW.root .. "/include"
paths.GLFW.lib  = paths.GLFW.root .. "/lib"
-----------------------------------------------------------------------------------------------------------------------
paths.glm      = {}
paths.glm.root = paths.root .. "/libraries/glm"
paths.glm.inc  = paths.glm.root .. "/include"
-----------------------------------------------------------------------------------------------------------------------
paths.stb_image      = {}
paths.stb_image.root = paths.root .. "/libraries/stb_image"
paths.stb_image.inc  = paths.stb_image.root .. "/include"
-----------------------------------------------------------------------------------------------------------------------
paths.tinyxml2      = {}
paths.tinyxml2.root = paths.root .. "/libraries/tinyxml2"
paths.tinyxml2.inc  = paths.tinyxml2.root .. "/include"
-----------------------------------------------------------------------------------------------------------------------
paths.irrKlang      = {}
paths.irrKlang.root = paths.root .. "/libraries/irrKlang"
paths.irrKlang.inc  = paths.irrKlang.root .. "/include"
paths.irrKlang.bin  = paths.irrKlang.root .. "/bin"
paths.irrKlang.lib  = paths.irrKlang.root .. "/lib"
-----------------------------------------------------------------------------------------------------------------------
paths.freetype2      = {}
paths.freetype2.root = paths.root .. "/libraries/freetype2"
paths.freetype2.inc  = paths.freetype2.root .. "/include"
paths.freetype2.bin  = paths.freetype2.root .. "/bin"
paths.freetype2.lib  = paths.freetype2.root .. "/lib"
-----------------------------------------------------------------------------------------------------------------------
paths.build     = paths.root .. "/.bin"
paths.genPrj    = paths.root .. "/.gen/prj"
paths.genDebug  = paths.root .. "/.gen/bin/Debug/Breakout"
paths.genRelease= paths.root .. "/.gen/bin/Release/Breakout"
-----------------------------------------------------------------------------------------------------------------------
return paths