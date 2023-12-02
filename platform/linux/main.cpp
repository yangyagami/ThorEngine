#include <iostream>

#include "ThorEngine.h"
#include "LinuxOS.h"

void GameInit();

int main(int argc, char **argv) {
    Thor::LinuxOS os;
    os.init(); 

    Thor::Engine engine(&os, argc, argv);
    engine.init();

    GameInit();

    while (!os.appClosedRequested()) {
        engine.run();

        os.process();
    }

	return 0;
}
