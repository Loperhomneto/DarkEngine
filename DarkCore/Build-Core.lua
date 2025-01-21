project "DarkCore"
   kind "StaticLib"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files { "Source/**.h", "Source/**.cpp" }

   includedirs
   {
      "Source", "../Vendor/Glad/include", "../Vendor/glfw/include", "../Vendor/glm/glm", "../Vendor/stb", "../Vendor/Irrklang/include", "../Vendor/spdlog/include", "../Vendor/imgui", "../Vendor/imgui/backends"
   }

   libdirs
   {
      "../Vendor/Irrklang/lib/Winx64-visualStudio"
   }

   links
   {
       "GLFW", "opengl32.lib", "Glad", "irrKlang.lib", "ImGui"
   }

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { }

   filter "configurations:Debug"
       defines { "DK_DEBUG" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       defines { "DK_RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       defines { "DK_DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"