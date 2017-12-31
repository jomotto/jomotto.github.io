#include <stdio.h>
#include <string.h>
#define MAXCOL 10
#define MAXROW 10


int main()
{
 int tablero[MAXCOL][MAXROW];
// char tablero[MAXCOL][MAXROW];

  int row, column;

  memset(&tablero, '\0', sizeof(tablero));
  for (row=0; row < MAXROW; row++)
     for (column=0; column < MAXCOL; column++)
          tablero[row][column]=row+column*10;
 
}
