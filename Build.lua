-- premake5.lua
workspace "DarkEngine"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "DarkApp"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group "Core"
    include "DarkCore/Build-Core.lua"

group "App"
    include "DarkApp/Build-App.lua"