project "ImGui"
	kind "StaticLib"
	language "C"
	staticruntime "off"
	warnings "off"

	targetdir ("bin/" .. OutputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. OutputDir .. "/%{prj.name}")

	files
	{
		"../imgui/imconfig.h",
		"../imgui/imgui.cpp",
		"../imgui/imgui.h",
		"../imgui/imgui_demo.cpp",
		"../imgui/imgui_draw.cpp",
		"../imgui/imgui_internal.h",
		"../imgui/imgui_tables.cpp",
		"../imgui/imgui_widgets.cpp",
		"../imgui/imstb_rectpack.h",
		"../imgui/imstb_textedit.h",
		"../imgui/imstb_truetype.h"
	}

