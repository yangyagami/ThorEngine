{
    depfiles_gcc = "main.o: test/main.cpp\
",
    files = {
        "test/main.cpp"
    },
    values = {
        "/usr/bin/gcc",
        {
            "-m64"
        }
    }
}