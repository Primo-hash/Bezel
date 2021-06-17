-- In scope of the complete project
workspace "Bezel"
	architecture "x64"

	configurations 
	{
		"Debug",
		"Release",
		"Dist"
	}

-- output directory name example -> DebugWindowsX64
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- In scope of The Bezel library
project "Bezel"
	location "Bezel"
	kind "SharedLib"	-- Translates to Dynamic library (DLL)
	language "C++"

	-- target directory name example -> bin/DebugWindowsX64/Bezel
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	-- include files
	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	-- include libraries
	includedirs
	{
		"%{prj.name}/vendor/spdlog/include"
	}

	-- For windows in case system defaults to unsupported configurations
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines 
		{
			"BZ_PLATFORM_WINDOWS",
			"BZ_BUILD_DLL"
		}

		-- For updating the Bezel DLL in the client application 'Sandbox', each build
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	-- Configuration options and definitions
	filter "configurations:Debug"
	defines "BZ_DEBUG"
	symbols "On"

	filter "configurations:Release"
	defines "BZ_RELEASE"
	optimize "On"

	filter "configurations:Dist"
	defines "BZ_DIST"
	optimize "On"


-- In scope of The Bezel library
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"	-- Translates to executable
	language "C++"

	-- target directory name example -> bin/DebugWindowsX64/Bezel
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	-- include files
	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	-- include libraries
	includedirs
	{
		"Bezel/src",
		"Bezel/vendor/spdlog/include"
	}

	-- For windows in case system defaults to unsupported configurations
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines 
		{
			"BZ_PLATFORM_WINDOWS"
		}

	-- Link to Bezel library
	links 
	{
		"Bezel"
	}

	-- Configuration options and definitions
	filter "configurations:Debug"
	defines "BZ_DEBUG"
	symbols "On"

	filter "configurations:Release"
	defines "BZ_RELEASE"
	optimize "On"

	filter "configurations:Dist"
	defines "BZ_DIST"
	optimize "On"