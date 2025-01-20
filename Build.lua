-- premake5.lua
workspace "DarkEngine"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "DarkApp"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus", "/utf-8" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

include "DarkCore/Build-Core.lua"
include "DarkApp/Build-App.lua"
include "Vendor/glfw/premake5.lua"
include "Vendor/Glad/premake5.lua"
include "Vendor/premakes/ImGuiPremake5.lua"