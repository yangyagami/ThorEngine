{
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-fvisibility=hidden",
            "-fvisibility-inlines-hidden",
            "-O3",
            "-Iengine",
            "-isystem",
            "/home/yangsiyu/.xmake/packages/s/spdlog/v1.12.0/e24126f106564f7c97234caa2b9c81c5/include",
            "-DNDEBUG"
        }
    },
    depfiles_gcc = "main.o: test/main.cpp engine/ThorEngine.h\
",
    files = {
        "test/main.cpp"
    }
}