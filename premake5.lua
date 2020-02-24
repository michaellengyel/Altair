workspace "Altair"
	architecture "x86"

	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Altair"
	location "Altair"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++14"
		staticruntime "On"
		systemversion "10.0.18362.0"

		defines
		{
			"ALTAIR_PLATFORM_WINDOWS",
			"ALTAIR_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/System")
		}

	filter "configurations:Debug"
		defines "ALTAIR_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "ALTAIR_RELEASE"
		optimize "On"

	filter "configurations:Distribution"
		defines "ALTAIR_DISTRIBUTION"
		symbols "On"

project "System"
	location "System"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Altair/vendor/spdlog/include",
		"Altair/src"
	}

	links
	{
		"Altair"
	}

	filter "system:windows"
		cppdialect "C++14"
		staticruntime "On"
		systemversion "10.0.18362.0"

		defines
		{
			"ALTAIR_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "ALTAIR_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "ALTAIR_RELEASE"
		optimize "On"

	filter "configurations:Distribution"
		defines "ALTAIR_DISTRIBUTION"
		symbols "On"
