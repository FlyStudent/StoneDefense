#include <iostream>

#include <gp/gp.h>
#include <time.h>

#include "defines.h"
#include "enums.h"

#include "game.h"
#include "tower/standard.h"
#include "tower/slowing.h"
#include "tower/explosive.h"
#include "enemy/weak.h"

extern "C"
{
    __declspec(dllexport) int NvOptimusEnablement = 1;
    __declspec(dllexport) int
    AmdPowerXpressRequestHighPerformance = 1;
}

int main(int argc, char* argv[])
{
    GPLib* gp = gpInit(SCREEN_WIDTH, SCREEN_HEIGHT, "Stone Defense", GP_INIT_VSYNC_ON);
    std::cout << std::endl; // Force flush stdout

    srand (time(NULL));

    Game game(gp);
    
    while (gpWindowShouldClose(gp) == false)
    {
        // Poll events (mouse, keyboards, etc...)
        gpEventsPoll(gp);

        //Update game and input
        game.update();

        //Draw game
        gpDrawBegin(gp);
        gpDrawClearBackground(gp, GP_CBLACK);

        game.draw();
        
        gpDrawEnd(gp);
    }

    gpShutdown(gp);
    return 0;
}
