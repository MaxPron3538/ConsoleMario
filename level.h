#pragma once

#include"RenderSystem.h"


const int levelRows = screenRows;
const int levelColumns = screenColumns;

const int GravitySpeed = 38;

const unsigned char CellSymboll_Empty        = ' ';
const unsigned char CellSymboll_BrickWall    = '#'; 
const unsigned char CellSymboll_SteelWall    = '@';
const unsigned char CellSymboll_Abyss        = 'a';
const unsigned char CellSymboll_Pipe         = 'p';
const unsigned char CellSymboll_Crystal      = '0';
const unsigned char CellSymboll_Box          = '?';
const unsigned char CellSymboll_OpenedBox    = '&';
const unsigned char CellSymboll_Mushroom     = '^';
const unsigned char CellSymboll_MushroomBox  = '!';
const unsigned char CellSymboll_Hero         = 'h';
const unsigned char CellSymboll_Goomba       = 'g';
const unsigned char CellSymboll_Exit         = '|';
const unsigned char CellSymbollFlag          = '>';


const unsigned char levelData0[levelRows][levelColumns + 1] =
{
    "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
    "#        0                                                           g         #",
    "#     @                                                              @     |>  #",
    "#    @@     @                   ##?#     0 0 0                      @@     |   #",
    "#   @@@     @@      pppp                           pppp            @@@     |   #",
    "#  @@@@ g   @@@      pp    g         g g            pp            @@@@     |   #",
    "# @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#",
    "#                                                                              #",
    "#                  0                                      0 0                  #",
    "#@@      #??#     ###            !                  ?### ######                #",
    "# @@                                                                           #",
    "# @@@                                                                          #",
    "# @@@@    ##      ######     ?   ?   ?    ?#        #             ##           #",
    "# @@@@@                                                                        #",
    "# @@@@@@              # g g g g           k               g g            #     #",
    "# @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@##@    #",
    "#                                                                              #",
    "#                ?                                                           ###",
    "#                                                                              #",
    "#                                               pppp                    #!#    #",
    "#           ?  #!#?#                pppp         pp       pppp          # #    #",
    "#                        pppp        pp       #  pp        pp                  #",
    "#  h              g         pp    j    pp g        pp   g gpp        #   g     #",
    "# ##########################################s######################  ###########",
    "#a#################################################################aa###########"
};


unsigned char GetRenderCellSymboll(unsigned char CellSymboll){

    switch(CellSymboll)
    {
       case CellSymboll_Empty:        return ' ';
       case CellSymboll_BrickWall:    return 177; 
       case CellSymboll_SteelWall:    return 178;
       case CellSymboll_Abyss:        return ' ';
       case CellSymboll_Pipe:         return 178;
       case CellSymboll_Crystal:      return 4;
       case CellSymboll_Box:          return '?';
       case CellSymboll_OpenedBox:    return 254;
       case CellSymboll_Mushroom:     return 6;
       case CellSymboll_MushroomBox:  return '?';
       case CellSymboll_Hero:         return 1;
       case CellSymboll_Goomba:       return 2;
       case CellSymboll_Exit:         return 222;
       case CellSymbollFlag:          return  16;
    }

    return '?';
}

ConsoleColor GetRenderCellSymbollColor(unsigned char CellSymboll){

    switch(CellSymboll)
    {
       case CellSymboll_BrickWall:    return ConsoleColor_DarkYellow; 
       case CellSymboll_SteelWall:    return ConsoleColor_White;
       case CellSymboll_Pipe:         return ConsoleColor_Green;
       case CellSymboll_Crystal:      return ConsoleColor_Cyan;
       case CellSymboll_Box:          return ConsoleColor_DarkRed;
       case CellSymboll_OpenedBox:    return ConsoleColor_Gray;
       case CellSymboll_Mushroom:     return ConsoleColor_Red;
       case CellSymboll_MushroomBox:  return ConsoleColor_DarkRed;
       case CellSymboll_Hero:         return ConsoleColor_Yellow;
       case CellSymboll_Goomba:       return ConsoleColor_DarkRed;
       case CellSymboll_Exit:         return ConsoleColor_Green;
       case CellSymbollFlag:          return ConsoleColor_White;
    }

    return ConsoleColor_Gray;
}

ConsoleColor GetRenderCellSymbollBackgroundColor(unsigned char CellSymboll){

    switch(CellSymboll)
    {
       case CellSymboll_BrickWall:    return ConsoleColor_Red; 
       case CellSymboll_SteelWall:    return ConsoleColor_DarkGray;
       case CellSymboll_Pipe:         return ConsoleColor_DarkGreen;
       case CellSymboll_Box:          return ConsoleColor_Yellow;
       case CellSymboll_OpenedBox:    return ConsoleColor_DarkGray;
       case CellSymboll_MushroomBox:  return ConsoleColor_Yellow;
    }

    return ConsoleColor_Black;
}


ConsoleColor GetRenderHerroColor(int heroHealth){

    switch(heroHealth)
    {
       case 2:    return ConsoleColor_Red; 
    }

    return ConsoleColor_Yellow;
}
