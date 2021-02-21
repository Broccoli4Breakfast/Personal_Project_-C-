/*
Game of Life
If a spot is
-dead and have exact 3 alive neighbors then next turn this spot will be alive, else dead
-alive and have 2 or 3 alive neighbors then next turn this spot will be alive, else dead

Adjust the default look and this might create some interesting pattern
21.02.2021
*/

#include <stdio.h>
#include <unistd.h>
#define ALIVE 1
#define DEAD 0
#define LIVE_SYMB '#'
#define DEAD_SYMB '-'


// global variables
int height = 10;
int length = 10;


// Functions
void print_array (int height, int length, int array[height][length])
{
  for(int row = 0; row<height; row++)
  {
    for (int col = 0; col<length; col++)
    {
      printf(" %c", (array[row][col] == ALIVE) ? LIVE_SYMB : DEAD_SYMB);
    }
    printf("\n");
  }
  printf("\n*******************************************\n");
 } 

int neighbor_count (int height, int length, int array[height][length], int row, int col)
{
  int count = 0;

  //count row above
  if (row > 0)
  {
    count += array[row-1][col];
    if (col > 0)
    {
      count += array[row-1][col-1];
    }
    if (col < length - 1)
    {
      count += array[row-1][col+1];
    }
  }

  //count left right same row
  if (col > 0)
  {
    count += array[row][col-1];
  }
  if (col < length - 1)
  {
    count += array[row][col+1];
  }

  //count lower row
  if (row < height -1)
  {
    count += array[row+1][col];
    if (col > 0)
    {
      count += array[row+1][col-1];
    }
    if (col < length - 1)
    {
      count += array[row+1][col+1];
    }
  }

  return count;
}

char new_array (int height, int length, int array[height][length])
{
  int new_array[height][length];
  char gameover = 1;  //set game to be over, unless theres at least 1 spot still alive then game set back to on
  
  // set a new array based on state of the current array
  for (int row = 0; row < height; row++)
  {
    for (int col = 0; col < length; col++)
    {
      unsigned neighbor = neighbor_count(height, length, array, row, col);
      if (array[row][col] == ALIVE)  // current spot is alive
      {
        if ((neighbor == 2) || (neighbor == 3))
        {
          new_array[row][col] = ALIVE;  // set that spot to alive
          gameover = 0;
        }
        else
        {
          new_array[row][col] = DEAD;  // set that spot to dead
        }
      }
      else  // current spot is dead
      {
        if (neighbor_count(height, length, array, row, col) == 3)
        {
          new_array[row][col] = ALIVE;
          gameover = 0;
        }
        else
        {
          new_array[row][col] = DEAD;
        }
      }
    }
  }

  // copy new_array to the current array
  for (int row = 0; row < height; row++)
  {
    for (int col = 0; col < length; col++)
    {
      array[row][col] = new_array[row][col];
    }
  }
  return gameover;
}


// Main
int main()
{

  // default array
  int current_array[height][length];
  for(int row = 0; row<height; row++)
    for (int col = 0; col<length; col++)
      current_array[row][col] = ((3*row-2*col)%3 == 0) ? 1 : 0;  //change the values in this line to change the default look
  
  // print default array
  print_array(height, length, current_array);

  //loop
  char gameover = 0;
  while (!gameover)
  {
    gameover = new_array(height, length, current_array);  //set up next array and check if games over
    print_array(height, length, current_array);
    sleep(1);
  }
  printf("GAME OVER!\n");
  return 0;
}
