#include <iostream>

#include "ThorEngine.h"
#include "LinuxOS.h"

int main(int argc, char **argv) {
    Thor::LinuxOS os;
    os.init(); 

    Thor::Engine engine(&os, argc, argv);
    engine.init();

    while (!os.appClosedRequested()) {
        engine.run();

        os.process();
    }

	return 0;
}
