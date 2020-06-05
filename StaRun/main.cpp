//
//  main.cpp
//  StaRun
//
//  Created by Ciro De Vita and Gennaro Mellone on 13/05/2020.
//  Copyright © 2020 BesTeam-ing. All rights reserved.
//

#include "Game/Game.hpp"

int main(int argc, char **argv)
{
    srand(int(time(NULL)));
    
    Game game(argc,argv, "StaRun");
    game.init();
    
    return 0;
}
