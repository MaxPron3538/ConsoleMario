#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<Windows.h>
#include<conio.h>
#include<ctype.h>
#include"someModule.h"
#include"RenderSystem.h"
#include"input.h"
#include"level.h"
#include"UnitData.h"

const int MaxUnitsCount = 35;

const float CellBeginValue = 0.001f; 
const float CellEndValue = 0.999f;

bool IsGameActive = true;
clock_t clockLastFrame = 0;
int framesCounter = 0;
float framesTimeCounter = 0;
int fps = 0;

unsigned char leveldata[levelRows][levelColumns];
UnitData unitsdata[MaxUnitsCount];
int unitsCount = 0;
int heroIndex = 0;

void SetupSystem(){

    srand(time(0));

   RenderSystemInitialize(); 
}

void Initialize(){
 
 clockLastFrame = clock();

  unitsCount = 0;

  for(int r = 0;r < levelRows;r++)
    {
        for(int c = 0;c < levelColumns;c++)
        {
            unsigned char CellSymboll = levelData0[r][c];

            leveldata[r][c] = CellSymboll;

            switch(CellSymboll)
            {
              case CellSymboll_Hero:
                heroIndex = unitsCount;

              case CellSymboll_Goomba:

                   UnitType unit_type = GetUnitTypeFromCell(CellSymboll);
                   unitsdata[unitsCount].type = unit_type;
                   unitsdata[unitsCount].y = float(r);
                   unitsdata[unitsCount].x = float(c);
                   unitsdata[unitsCount].health = 1;
                   unitsdata[unitsCount].YSpeed = 0.0;
                   unitsdata[unitsCount].XSpeed = 0.0;
                   unitsdata[unitsCount].xOrder = UnitOrder_None;
                   unitsdata[unitsCount].yOrder = UnitOrder_None;
                   unitsCount++;
        
                  break;
            }
        }
    }
}


void Render(){

RenderSystemClear();

    for(int r = 0;r < levelRows;r++)
    {
        for(int c = 0;c < levelColumns;c++)
        {
             unsigned char CellSymboll = leveldata[r][c];

             unsigned char renderSymbol = GetRenderCellSymboll(CellSymboll);
             ConsoleColor SymbolColor = GetRenderCellSymbollColor(CellSymboll);
             ConsoleColor BackgroundColor = GetRenderCellSymbollBackgroundColor(CellSymboll);
             
             if(CellSymboll == CellSymboll_Hero)

              SymbolColor = GetRenderHerroColor( unitsdata[heroIndex].health );

            RenderSystemDrawChar(r, c,renderSymbol,SymbolColor,BackgroundColor);
                         
        } 
    }

 char textBuffer[32];
 sprintf(textBuffer,"FPS:","%d",fps);

 RenderSystemDrawText(0,0,textBuffer,ConsoleColor_Gray,ConsoleColor_Black);

RenderSystemFlush();

}

UnitData *GetUnitAt(int row, int column){

for(int i = 0;i < unitsCount;i++){

  if(unitsdata[i].health <= 0)
   continue;

   if(int(unitsdata[i].y == row && unitsdata[i].x == column)){

     return &unitsdata[i];
   }
 }

return 0;
}

void KillUnit(UnitData *pointerToUnitData){

  pointerToUnitData->health = 0;

  int row = int(pointerToUnitData->y);
  int column = int(pointerToUnitData->x);

  leveldata[row][column] = CellSymboll_Empty; 
}

bool MoveUnitTo(UnitData *pointerToUnitData,float newX,float newY)
{

if(pointerToUnitData->health <= 0)

   return false;

bool CanMoveToCell = false;

int newRow = int(newY);
int newColumn = int(newX);
int oldRow = int(pointerToUnitData->y);
int oldColumn = int(pointerToUnitData->x);

unsigned char unitSymboll = leveldata[oldRow][oldColumn];
unsigned char destinationCellSymboll = leveldata[newRow][newColumn];

int directionRow  = newRow - oldRow;
int directionColumn = newColumn - oldColumn;


switch(destinationCellSymboll){

    case CellSymboll_Empty:

    CanMoveToCell = true;
    break;

    case CellSymboll_Abyss:

    KillUnit(pointerToUnitData);
    break;

    case CellSymboll_Box:

    if(directionRow < 0){

      leveldata[newRow - 1][newColumn] = CellSymboll_Crystal;
      leveldata[newRow][newColumn] = CellSymboll_OpenedBox;

    }
    break;

    case CellSymboll_MushroomBox:

    if(directionRow < 0){

      leveldata[newRow - 1][newColumn] = CellSymboll_Mushroom;
      leveldata[newRow][newColumn] = CellSymboll_OpenedBox;
    }
    break;

}

if(pointerToUnitData->type = UnitType_Hero)
{
  switch(destinationCellSymboll)
  {
       
    case CellSymboll_Exit:

    IsGameActive = false;
    break;

    case CellSymboll_Crystal:

    IsGameActive = true;
    break;

    case CellSymboll_Mushroom:

    CanMoveToCell = true;

    if(pointerToUnitData->health < 2)

    pointerToUnitData->health = 2;
    break;

    case CellSymboll_BrickWall:

    if((directionRow < 0)  && (pointerToUnitData->health > 1))

      leveldata[newRow][newColumn] = CellSymboll_Empty;
    break;

    case CellSymboll_Goomba:

    if(directionRow > 0){

      UnitData *unitdata = GetUnitAt(newRow,newColumn);

      if(unitdata != 0)
      {
        KillUnit(unitdata);

        pointerToUnitData->YSpeed = -GetUnitJumpSpeed(pointerToUnitData->type);

      }
    }
    break;
  }
}

else
{

  switch(destinationCellSymboll)
  {
    case CellSymboll_Hero:
    
    unitsdata[heroIndex].health--;

    if(pointerToUnitData->xOrder = UnitOrder_Backward)

      pointerToUnitData->xOrder = UnitOrder_Forward;

    else
    
      pointerToUnitData->xOrder = UnitOrder_Backward;

    break;

  default:

     UnitType unitType = GetUnitTypeFromCell(destinationCellSymboll);

     if(unitType != UnitType_None){

       if(pointerToUnitData->xOrder = UnitOrder_Backward){

         pointerToUnitData->xOrder = UnitOrder_Forward;
       }
       else
       {
         pointerToUnitData->xOrder = UnitOrder_Backward;
       }
       
     }
     break;

  }

}

if(CanMoveToCell){

  leveldata[oldRow][oldColumn] = CellSymboll_Empty;

  pointerToUnitData->x = newX;
  pointerToUnitData->y = newY;

  leveldata[newRow][newColumn] = unitSymboll;

}

return CanMoveToCell;
}

void UpdateUnit(UnitData *pointerToUnitData,float deltaTime){

 int row = int(pointerToUnitData->y);
 int column = int(pointerToUnitData->x);


if(pointerToUnitData->yOrder = UnitOrder_Backward ){


 if( (pointerToUnitData->y >= (row + CellEndValue)) && (leveldata[row + 1][column] != CellSymboll_Empty)
  && (leveldata[row + 1][column] != CellSymboll_Abyss))

   {
      pointerToUnitData->YSpeed = -GetUnitJumpSpeed(pointerToUnitData->type);
   }

}

   if(pointerToUnitData->xOrder == UnitOrder_Backward)
   {
     pointerToUnitData->XSpeed = -GetUnitSpeedX(pointerToUnitData->type);

   }
   else
   {
     if(pointerToUnitData->xOrder == UnitOrder_Forward)
     { 
       pointerToUnitData->XSpeed = GetUnitSpeedX(pointerToUnitData->type);

     }
     else
     {
        pointerToUnitData->XSpeed = 0;
     }
     
   }
  
    float deltaY = pointerToUnitData->YSpeed * deltaTime;
    float deltaX = pointerToUnitData->XSpeed * deltaTime;
    float newY = pointerToUnitData->y + deltaY;
    float newX = pointerToUnitData ->x + deltaX;
    int newRow = int(newY);
    int newcolumn = int(newX);

    if(newRow != row)
    {
       
       if(MoveUnitTo(pointerToUnitData,pointerToUnitData->x,newY))
       {

          row = int(pointerToUnitData->y);
       }
       else
       {
           if(newRow > row)
           {

             pointerToUnitData->y = row + CellEndValue;

             if(pointerToUnitData->YSpeed > 0.0 )

             pointerToUnitData->YSpeed = 0.0;

           }
           else
           {
               pointerToUnitData->y = row + CellBeginValue;

               if(pointerToUnitData->YSpeed < 0.0)

               pointerToUnitData->YSpeed = 0.0;

          }
           
       }
       
    }
    else
    {
      pointerToUnitData->y = newY;
    }


    if(newcolumn != column)
    {
      if(MoveUnitTo(pointerToUnitData,newX,pointerToUnitData->y))
      {
              column = int(pointerToUnitData->x);
      }
      else
      {
           if(newcolumn > column)
           {
             pointerToUnitData->x = column + CellEndValue;

             if(pointerToUnitData->XSpeed > 0.0 )

             pointerToUnitData->XSpeed = 0.0;

           }
           else
           {
               pointerToUnitData->x = column + CellBeginValue;

               if(pointerToUnitData->XSpeed < 0.0)

               pointerToUnitData->XSpeed = 0.0;

           }
           
       } 

    }
    else
    {
      pointerToUnitData->x = newX;
    }

  pointerToUnitData->YSpeed += GravitySpeed * deltaTime;

  if(pointerToUnitData->YSpeed > GravitySpeed)
  {
    pointerToUnitData->YSpeed = GravitySpeed;
  }

}

void UpdateAI(){

for(int i = 0;i < unitsCount;i++){

  if(i == heroIndex)
  continue;
  
  if(unitsdata[i].health <= 0)
  continue;

  int row = int(unitsdata[i].y);
  int column = int(unitsdata[i].x);

  if(unitsdata[i].xOrder == UnitOrder_None)
  {

   if(leveldata[row][column - 1] == CellSymboll_Empty){
  
    unitsdata[i].xOrder = UnitOrder_Backward;
   }
   else
   {
    unitsdata[i].xOrder = UnitOrder_Forward;
   }
  }
  else
  {

    if(unitsdata[i].xOrder == UnitOrder_Backward){

      unsigned char CellLeft = leveldata[row][column - 1];
      UnitType unittype = GetUnitTypeFromCell(CellLeft);

      if((unitsdata[i].x <= (column + CellBeginValue)) && (CellLeft != CellSymboll_Empty) && (unittype == UnitType_None)){
        
        unitsdata[i].xOrder = UnitOrder_Forward;

      }

    }
    else
    {
      unsigned char CellRight = leveldata[row][column + 1];
      UnitType unittype = GetUnitTypeFromCell(CellRight);

      if((unitsdata[i].x >= (column + CellEndValue)) && (CellRight != CellSymboll_Empty) && (unittype == UnitType_None)){

        unitsdata[i].xOrder = UnitOrder_Backward;
      }
    }
    
  }
  
}

}

void Update(){
 
clock_t clockNow = clock();
clock_t deltaclock = clockNow - clockLastFrame;
float deltaTime = float(deltaclock)/ CLOCKS_PER_SEC;
clockLastFrame = clockNow;

framesCounter++;
framesTimeCounter += deltaTime;

 if(framesTimeCounter >= 1.0)
 {
  framesTimeCounter -= 1.0;
  fps = framesCounter;
  framesCounter = 0;

 }

 if(IsKeyDown(VK_UP))

 unitsdata[heroIndex].yOrder = UnitOrder_Backward;

 else
 
  unitsdata[heroIndex].yOrder = UnitOrder_None;

  if(IsKeyDown(VK_LEFT))

  unitsdata[heroIndex].xOrder = UnitOrder_Backward;

  else{

    if(IsKeyDown(VK_RIGHT))

    unitsdata[heroIndex].xOrder = UnitOrder_Forward;

    else
    
    unitsdata[heroIndex].xOrder = UnitOrder_None;
    
  }

  for(int i = 0;i < unitsCount;i++){

    UpdateUnit(&unitsdata[i],deltaTime);
  }
  
  UpdateAI();

  if(unitsdata[heroIndex].health <= 0)

      Initialize();
 
}

void ShutDown(){


}



int main(){

 SomeFunction(true);

 SetupSystem();
 
 Initialize();

do
{
  Render();
  Update();

} while (IsGameActive);

 ShutDown();

return 0;
}