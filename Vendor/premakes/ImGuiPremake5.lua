project "ImGui"
	kind "StaticLib"
	language "C++"
        cppdialect "C++17"
        systemversion "latest"
        staticruntime "On"
	warnings "off"

	targetdir ("bin/" .. OutputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. OutputDir .. "/%{prj.name}")

	includedirs
	{
		"../imgui", "../glfw/include"
	}

	links
	{
		"GLFW"
	}

	files
	{
		"../imgui/imconfig.h",
		"../imgui/imgui.h",
		"../imgui/imstb_rectpack.h",
		"../imgui/imstb_textedit.h",
		"../imgui/imstb_truetype.h",
		"../imgui/imgui_internal.h",
		"../imgui/imgui.cpp",
		"../imgui/imgui_demo.cpp",
		"../imgui/imgui_draw.cpp",
		"../imgui/imgui_tables.cpp",
		"../imgui/imgui_widgets.cpp",
		"../imgui/backends/imgui_impl_glfw.h",
		"../imgui/backends/imgui_impl_glfw.cpp",
		"../imgui/backends/imgui_impl_opengl3.h",
		"../imgui/backends/imgui_impl_opengl3.cpp"
	}

