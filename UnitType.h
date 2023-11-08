#pragma once

#include"level.h"

enum UnitType{

    UnitType_None,
    UnitType_Hero,
    UnitType_Goomba
};

UnitType GetUnitTypeFromCell(unsigned char CellSymboll){

    switch(CellSymboll)
    {

        case CellSymboll_Hero:        return UnitType_Hero;
        case CellSymboll_Goomba:      return UnitType_Goomba;
    }

    return UnitType_None;
}

int GetUnitSpeedX(UnitType unit_type){

    switch(unit_type)
    {
      case UnitType_Hero:          return 10;
      case UnitType_Goomba:        return 2;
       
    }
    return 0;
}

int GetUnitJumpSpeed(UnitType unit_type){

    switch(unit_type)
    {
        case UnitType_Hero:        return 17;

    }
    return 0;
}