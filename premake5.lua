workspace "Altair"
	architecture "x86"

	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--Project Altair
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
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/UnitTest"),
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

--Project System
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

--Project GoogleTest
project "GoogleTest"
	location "GoogleTest"
	kind "StaticLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		--"%{prj.name}/src/**.h",
		--"%{prj.name}/src/**.cpp"
		--TODO: Generalize these paths:
		"%{wks.location}/Altair/vendor/googletest/googletest/src/gtest_main.cc",
		"%{wks.location}/Altair/vendor/googletest/googletest/src/gtest-all.cc"
	}

	includedirs
	{
		"Altair/vendor/googletest/googletest/include",
		"Altair/vendor/googletest/googletest",
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

--Project UnitTest
project "UnitTest"
	location "UnitTest"
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
		"Altair/vendor/googletest/googletest/include",
		"Altair/vendor/googletest/googletest",
		"Altair/vendor/spdlog/include",
		"Altair/src"
		--"Altair/src/Altair",
,
	}

	links
	{
		"Altair",
		"GoogleTest"
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