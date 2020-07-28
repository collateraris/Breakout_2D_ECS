local function get_sdk_version()
    local version10 = os.getWindowsRegistry("HKLM:SOFTWARE\\Wow6432Node\\Microsoft\\Microsoft SDKs\\Windows\\v10.0\\ProductVersion")
    if version10 ~= nil then
        return version10 .. ".0"
    end
    local version8 = os.getWindowsRegistry("HKLM:SOFTWARE\\Wow6432Node\\Microsoft\\Microsoft SDKs\\Windows\\v8.1a\\ProductVersion")
    if version8 ~= nil then
        return "8.1"
    end
    return ""
end
-----------------------------------------------------------------------------------------------------------------------
workspace ("Breakout")
    configurations { "Debug", "Release" }
    
    location ("../.gen/prj")
    targetdir ("../.gen/bin/%{cfg.buildcfg}/%{prj.targetname}")
    objdir ("../.gen/obj/%{prj.name}_%{cfg.buildcfg}")

    flags ("MultiProcessorCompile")
    warnings ("Extra")
    architecture ("x86")
    system ("Windows")
    systemversion (get_sdk_version())
    linkoptions { '/NODEFAULTLIB:"libcmt.lib"' }

    filter ("configurations:Debug*")
        defines { "_DEBUG", "GLEW_STATIC"}
        symbols ("FastLink")
        optimize ("Off")
        targetsuffix "-d"
        
    filter ("configurations:Release*")
        defines { "NDEBUG", "GLEW_STATIC"}
        symbols ("Off")
        optimize ("Speed")
       
    filter {}
-----------------------------------------------------------------------------------------------------------------------
group ("libraries")
    include ("sys_config")
    include ("sys_animation")
    include ("sys_audio")
    include ("sys_events")
    include ("sys_input")
    include ("sys_memory")
    include ("sys_physics")
    include ("sys_profile")
    include ("sys_telemetry")
    include ("sys_ui")
    include ("sys_ecs")
    include ("sys_gameState")
    include ("sys_resource")
    include ("lib_multimedia")
group ("")
    include ("game")
-----------------------------------------------------------------------------------------------------------------------