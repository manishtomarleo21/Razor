workspace "Razor"
    architecture "x64"
    startproject "Razoredge" 

    configurations {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["Glad"] = "Razor/vendor/Glad/include"
IncludeDir["GLFW"] = "Razor/vendor/GLFW/include"
IncludeDir["ImGui"] = "Razor/vendor/imgui/include"
IncludeDir["glm"] = "Razor/vendor/glm"
IncludeDir["stb_image"] = "Razor/vendor/stb_image"
IncludeDir["entt"] = "Razor/vendor/entt/include" 
IncludeDir["yaml_cpp"] = "Razor/vendor/yaml-cpp/include" 
IncludeDir["Box2D"] = "Razor/vendor/Box2D/include" 
IncludeDir["ImGuizmo"] = "Razor/vendor/ImGuizmo" 



include "Razor/vendor/Box2D"
include "Razor/vendor/Glad"
include "Razor/vendor/GLFW"
include "Razor/vendor/imgui"
include "Razor/vendor/yaml-cpp"

project "Razor"
    location "Razor"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "rzpch.h"
    pchsource "Razor/src/rzpch.cpp"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/stb_image/**.h",
        "%{prj.name}/vendor/stb_image/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl",
        "%{prj.name}/vendor/ImGuizmo/ImGuizmo.h",
        "%{prj.name}/vendor/ImGuizmo/ImGuizmo.cpp"

    }

    includedirs {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.Box2D}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.entt}",
        "%{IncludeDir.yaml_cpp}",
        "%{IncludeDir.ImGuizmo}",
       
    }

    links{
        "Box2D",
        "Glad",
        "GLFW",
        "ImGui",
        "yaml-cpp",
        "opengl32.lib",
        "dwmapi.lib"
    }

   filter { "files:Razor/vendor/ImGuizmo/**.cpp" }
    flags { "NoPCH" }
filter {}


    filter "system:windows"
        systemversion "latest"
        --staticruntime "On"

    defines {
        "RZ_PLATFORM_WINDOWS",
        "RZ_BUILD_DLL",
        "GLFW_INCLUDE_NONE",
		"YAML_CPP_STATIC_DEFINE"

      --  "IMGUI_API=__declspec(dllexport)" 
    }

   -- postbuildcommands {
      --   "{RMDIR} ../bin/" .. outputdir .. "/Sandbox",
   --     "{MKDIR} ../bin/" .. outputdir .. "/Sandbox",
   --     "{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox"
  --  }

filter "configurations:Debug"
    defines "RZ_DEBUG"
 --   buildoptions "/MDd"
    symbols "on"
    runtime "Debug"
    systemversion "latest"  -- Add this to ensure the configuration is applied

    


filter "configurations:Release"
    defines "RZ_RELEASE"
--    buildoptions "/MD"
    runtime "Release"
    optimize "on"
    systemversion "latest"  -- Add this to ensure the configuration is applied

   

filter "configurations:Dist"
    defines "RZ_DIST"
--    buildoptions "/MD"
    runtime "Release"
    optimize "on"
    systemversion "latest"  -- Add this to ensure the configuration is applied


    

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        --"%{prj.name}/ImGuiLayer.h"
    }

    includedirs {
        "Razor/vendor/spdlog/include",
        "Razor/src",
        "Razor/vendor",
        "%{IncludeDir.glm}",
        "%{IncludeDir.entt}"

        
       
    }

    links {
        "Razor"
    }

    filter "system:windows"
        systemversion "latest"

    defines {
        "RZ_PLATFORM_WINDOWS"
    }

filter "configurations:Debug"
    defines "RZ_DEBUG"
 --   buildoptions "/MDd"
    runtime "Debug"
    symbols "on"
    systemversion "latest"

filter "configurations:Release"
    defines "RZ_RELEASE"
  --  buildoptions "/MD"
    runtime "Release"

    optimize "on"
    systemversion "latest"

filter "configurations:Dist"
    defines "RZ_DIST"
    --buildoptions "/MD"
    runtime "Release"
    optimize "on"
    systemversion "latest"

project "Razoredge"
    location "Razoredge"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        --"%{prj.name}/ImGuiLayer.h"
    }

    includedirs {
        "Razor/vendor/spdlog/include",
        "Razor/src",
        "Razor/vendor",
        "%{IncludeDir.Box2D}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.entt}",
        "%{IncludeDir.yaml_cpp}",
        "%{IncludeDir.ImGuizmo}"
    }


  
    links {
        "Razor"
        
    }

    filter "system:windows"
        systemversion "latest"

    defines {
        "RZ_PLATFORM_WINDOWS",
        "YAML_CPP_STATIC_DEFINE"
    }

filter "configurations:Debug"
    defines "RZ_DEBUG"
 --   buildoptions "/MDd"
    runtime "Debug"
    symbols "on"
    systemversion "latest"

filter "configurations:Release"
    defines "RZ_RELEASE"
  --  buildoptions "/MD"
    runtime "Release"

    optimize "on"
    systemversion "latest"

filter "configurations:Dist"
    defines "RZ_DIST"
    --buildoptions "/MD"
    runtime "Release"
    optimize "on"
    systemversion "latest"