/*************************************************************
*
* author Andreas Dedousis csd3018@csd.uoc.gr
*
*
**************************************************************/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>



#define COLOR_RED     "\x1b[31m"
#define	COLOR_RESET   "\x1b[0m"
#define COLS 	100
#define ROWS    100

/*struct to store line and column of the array*/
struct array_line_rows{
	int line;
	int column;
};

int game_array[ROWS][COLS];
int second_array[ROWS][COLS]={0};

void print_array(int array[][COLS]);
void *change_cell_state(struct array_line_rows* thread_array);
void initialization_threads();
