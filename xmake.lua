add_requires("glfw", "spdlog", "glm", "sol2", "entt")

add_rules("mode.debug", "mode.release", "mode.check")
add_cxflags("-Wall", "-Werror")

target("ThorEngine")
	set_kind("shared")

	add_includedirs(
		"engine", 
		"engine/core", 
		"engine/renderer", 
		"engine/scene",
		"engine/components",
		"engine/input",
		"engine/objects",
		"engine/os",
		"platform/linux/GLFWwindow",
		"platform/linux/OpenglRenderer",
		"platform/linux",
		"3rdparty/glad/include",
		"3rdparty/stb_image/include",
		"3rdparty/imgui/include",

        { public = true }
	)

	add_files(
		"engine/*.cpp",
		"engine/core/*.cpp",
		"engine/renderer/*.cpp",
		"engine/scene/*.cpp",
		"engine/input/*.cpp",
		"engine/objects/*.cpp",
		"platform/linux/GLFWwindow/*.cpp",
		"platform/linux/OpenglRenderer/*.cpp",
		"platform/linux/*.cpp",
		"3rdparty/glad/src/*.c",
		"3rdparty/imgui/src/*.cpp"
	)

	add_packages("spdlog", "glfw", "glm", "sol2", "entt", { public = true })

target("ThorTest")
	set_kind("binary")

	add_files(
		"test/main.cpp"
	)

    add_deps("ThorEngine")

