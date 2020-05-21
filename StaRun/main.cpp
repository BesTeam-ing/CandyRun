#include "Game/Game.hpp"

int main(int argc, char **argv)
{
    srand(int(time(NULL)));
    
    Game game(argc,argv, "StaRun");
    game.init();
    
    return 0;
}
