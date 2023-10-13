add_requires("glfw", "spdlog", "glm")

add_rules("mode.debug", "mode.release")
add_cxflags("-Wall", "-Werror")

target("ThorTest")
	set_kind("binary")
	add_includedirs("engine", "engine/core", "engine/renderer", "engine/editor", "platform/linux/GLFWwindow", "platform/linux/OpenglRenderer", "3rdparty/glad/include", "3rdparty/stb_image/include", "3rdparty/imgui/include")
	add_files("test/*.cpp", "engine/*.cpp", "engine/core/*.cpp", "engine/renderer/*.cpp", "engine/editor/*.cpp", "platform/linux/GLFWwindow/*.cpp", "platform/linux/OpenglRenderer/*.cpp", "3rdparty/glad/src/*.c", "3rdparty/imgui/src/*.cpp")

	add_packages("spdlog", "glfw", "glm")
