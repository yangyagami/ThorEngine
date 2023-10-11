add_requires("glfw", "spdlog")

add_rules("mode.debug", "mode.release")

target("ThorTest")
	set_kind("binary")
	add_includedirs("engine", "engine/core", "platform/linux/GLFWwindow", "3rdparty/glad/include")
	add_files("test/*.cpp", "engine/*.cpp", "engine/core/*.cpp", "platform/linux/GLFWwindow/*.cpp", "3rdparty/glad/src/*.c")

	add_packages("spdlog", "glfw")
