add_requires("glfw", "spdlog")

add_rules("mode.debug", "mode.release")

target("ThorTest")
	set_kind("binary")
	add_includedirs("engine")
	add_files("test/*.cpp", "engine/*.cpp")

	add_packages("spdlog")
