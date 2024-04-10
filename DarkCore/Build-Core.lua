project "DarkCore"
   kind "StaticLib"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files { "Source/**.h", "Source/**.cpp" }

   includedirs
   {
      "Source", "../Vendor/Glad/include", "../Vendor/glfw/include", "../Vendor/glm/glm", "../Vendor/stb", "../Vendor/Irrklang/include"
   }

   links
   {
       "GLFW", "opengl32.lib", "Glad", "../Vendor/Irrklang/lib/Winx64-visualStudio/irrKlang.lib", "../Vendor/Irrklang/bin/winx64-visualStudio/irrKlang.dll"
   }

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { }

   filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"