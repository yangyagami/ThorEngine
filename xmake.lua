add_requires("glfw", "spdlog", "glm")

add_rules("mode.debug", "mode.release")

target("ThorTest")
	set_kind("binary")
	add_includedirs("engine", "engine/core", "engine/renderer", "platform/linux/GLFWwindow", "platform/linux/OpenglRenderer", "3rdparty/glad/include")
	add_files("test/*.cpp", "engine/*.cpp", "engine/core/*.cpp", "engine/renderer/*.cpp", "platform/linux/GLFWwindow/*.cpp", "platform/linux/OpenglRenderer/*.cpp", "3rdparty/glad/src/*.c")

	add_packages("spdlog", "glfw", "glm")
