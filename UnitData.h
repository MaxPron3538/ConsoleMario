#pragma once

#include"UnitType.h"
#include"UnitOrder.h"

struct UnitData
{
   UnitType type;

   int health;
   
   float x;
   float y;

   float XSpeed;
   float YSpeed;

   UnitOrder xOrder;
   UnitOrder yOrder;

};