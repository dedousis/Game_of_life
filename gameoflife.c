/*************************************************************
*
* author Andreas Dedousis csd3018@csd.uoc.gr
*
*
**************************************************************/
#include "gameoflife.h"
#include <pthread.h>

pthread_mutex_t my_mutex;

/*function to print the state of the game array*/
void print_array(int array[][COLS])
{
	int i,j;
	for(i=0;i<ROWS;i++)
	{
		for(j=0;j<COLS;j++)
		{
			if(array[i][j]==1)
			{
				printf(COLOR_RED"%d"COLOR_RESET,array[i][j]);
			}else{
				printf("%d",array[i][j]);
			}
		}
		printf("\n");
	}
}

/*function to check each cell and at the end change the cell state */
void *change_cell_state(struct array_line_rows* thread_array)
{
	pthread_mutex_lock( &my_mutex);
	int i,j,alive_neigh=0;
	int current_line=thread_array->line; 	//take the first line which will check 
	int current_col=thread_array->column; 	// take the first column which will checked
	
	int final_col=current_col+10;			// the last column
	int final_line=current_line+10;			//the last line 
	
	/* here i check for a 10x10 array of cells */
	for(i=current_line;i<final_line;i++)
	{

		for(j=current_col;j<final_col;j++)
		{	
	
					/*NEIGHBOOR CHIECKING*/
			if(i==0&&j==0) //top left corner
			{

				if(game_array[i][j+1]==1)
				{
					alive_neigh++;
				}
				if(game_array[i+1][j]==1)
				{
					alive_neigh++;
				}
				if(game_array[i+1][j+1]==1)
				{
					alive_neigh++;
				}
			}
			else if(j==COLS-1&&i==0) //top right corner
			{

				if(game_array[i][j-1]==1)
				{
					alive_neigh++;
				}
				if(game_array[i+1][j-1]==1)
				{
					alive_neigh++;
				}
				if(game_array[i+1][j]==1)
				{
					alive_neigh++;
				}
			}
			else if(j==0&&i==ROWS-1) //down left corner
			{

				if(game_array[i-1][j]==1)
				{
					alive_neigh++;
				}
				if(game_array[i-1][j+1]==1)
				{
					alive_neigh++;
				}
				if(game_array[i][j+1]==1)
				{
					alive_neigh++;
				}
			}
			else if(j==COLS-1&&i==ROWS-1) //down right corner
			{
				if(game_array[i-1][j-1]==1)
				{
					alive_neigh++;
				}
				if(game_array[i-1][j]==1)
				{
					alive_neigh++;
				}
				if(game_array[i][j-1]==1)
				{
					alive_neigh++;
				}
			}
			else if(i==0&&j!=0)			//top line
			{
				if(game_array[i][j-1]==1)
				{
					alive_neigh++;
				}
				if(game_array[i][j+1]==1)
				{
					alive_neigh++;
				}
				if(game_array[i+1][j-1]==1)
				{
					alive_neigh++;
				}
				if(game_array[i+1][j]==1)
				{
					alive_neigh++;
				}
				if(game_array[i+1][j+1]==1)
				{
					alive_neigh++;
				}
			}
			else if(i==ROWS-1&&j!=0)		//down line
			{
				if(game_array[i-1][j-1]==1)
				{
					alive_neigh++;
				}
				if(game_array[i-1][j]==1)
				{
					alive_neigh++;
				}
				if(game_array[i-1][j+1]==1)
				{
					alive_neigh++;
				}
				if(game_array[i][j-1]==1)
				{
					alive_neigh++;
				}
				if(game_array[i][j+1]==1)
				{
					alive_neigh++;
				}
			}
			else if(i!=0&&j==0)			//left row
			{
				if(game_array[i-1][j]==1)
				{
					alive_neigh++;
				}
				if(game_array[i-1][j+1]==1)
				{
					alive_neigh++;
				}
				if(game_array[i][j+1]==1)
				{
					alive_neigh++;
				}
				if(game_array[i+1][j]==1)
				{
					alive_neigh++;
				}
				if(game_array[i+1][j+1]==1)
				{
					alive_neigh++;
				}
			}
			else if(j==COLS-1&&i!=0) 		//right row
			{
				if(game_array[i-1][j-1]==1)
				{
					alive_neigh++;
				}
				if(game_array[i-1][j]==1)
				{
					alive_neigh++;
				}
				if(game_array[i][j-1]==1)
				{
					alive_neigh++;
				}

				if(game_array[i+1][j-1]==1)
				{
					alive_neigh++;
				}
				if(game_array[i+1][j]==1)
				{
					alive_neigh++;
				}

			}else{
				if(game_array[i-1][j-1]==1)
				{
					alive_neigh++;
				}
				if(game_array[i-1][j]==1)
				{
					alive_neigh++;
				}
				if(game_array[i-1][j+1]==1)
				{
					alive_neigh++;
				}
				if(game_array[i][j-1]==1)
				{
					alive_neigh++;
				}
				if(game_array[i][j+1]==1)
				{
					alive_neigh++;
				}
				if(game_array[i+1][j-1]==1)
				{
					alive_neigh++;
				}
				if(game_array[i+1][j]==1)
				{
					alive_neigh++;
				}
				if(game_array[i+1][j+1]==1)
				{
					alive_neigh++;
				}
			}
						//CHANGE CELL STATE	
			if(alive_neigh>0)
			{
				if(game_array[i][j]==1)
				{
					if(alive_neigh<2){
						second_array[i][j]=0;
					}else if(alive_neigh==2||alive_neigh==3){
						second_array[i][j]=1;
					}else if(alive_neigh>3){
						second_array[i][j]=0;
					}
				}else if(game_array[i][j]==0)
				{
					if(alive_neigh==3){
						second_array[i][j]=1;
					}
				}
			}
			alive_neigh=0;
		}
	}
	pthread_mutex_unlock( &my_mutex);
}

/* initialization of the threads and give them the space they will manage*/
void initialization_threads()
{
	int thread_num=0,c=0,i,j;
	int tmp;
	tmp= pthread_mutex_init( &my_mutex, NULL );
	pthread_t thread[100];
	/* parse the array with step 10 so every 10 lines and every 10 ccolumns  change thread*/
	for(i=0;i<ROWS;i=i+10)
	{
		for(j=0;j<COLS;j=j+10)
		{
			struct array_line_rows*  thr_array =malloc(sizeof(struct array_line_rows));
			thr_array->column=j;
			thr_array->line=i;
			/*store the current line nad column in order for the function to handle them */
			pthread_create(&thread[thread_num], NULL, (void*)change_cell_state,thr_array); //maybe take 10x10 grid have to check 
			thread_num++;
		}
	}

	for(c=0;c<100;c++)
	{
		pthread_join(thread[c],NULL); //synchronizes the threads 
	}
	pthread_mutex_destroy(&my_mutex); // the same with above 
	
	for(i=0;i<ROWS;i++)
	 {
		 for(j=0;j<COLS;j++)
		 {
			 game_array[i][j]=second_array[i][j]; // pass the current generation in the previous 
		 }
	 }
}

int main(int argc, char* argv[]){
	int i=0;
	int j=0;
	int c;
	FILE *file=fopen(argv[1],"r");
	if(file==NULL)
	{
		printf("Unable to open file\n");
	}
	
	/*INITIALIZATION OF THE ARRAY*/
	for(i=0;i<ROWS;i++)
	{
		for(j=0;j<COLS;j++)
		{
			fscanf(file,"%d",&game_array[i][j]);
		}
	}
	print_array(game_array);
	i=0;
	while(1){
		initialization_threads();
		printf("---------------------------------------\n");
		print_array(second_array);
		sleep(10000);  
	}
	return 0;
}