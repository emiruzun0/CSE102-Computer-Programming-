#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define DICT_SIZE 15
#define WORD_LEN 10
#define LINE_LEN 18
#define MAP_SIZE 15

int get_line_size(char *line) {
	char *ch_iter = line; // so as not to lose beginning of line
	int counter = 0;
	// go until you see new line or null char
	while(*ch_iter != '\n' && *ch_iter != '\0') {
		ch_iter++; // next char
		counter++; // increment counter
	}
	
	return counter;
}

void copy_string(char *source, char *destination) {
	// get iterators over original pointers
	char *src_iter = source;
	char *dst_iter = destination;
	// until null char
	while (*src_iter != '\0') {
		// copy pointers
		*dst_iter = *src_iter;
		// advance to next char
		src_iter++;
		dst_iter++;
   }
   // terminate string
   *dst_iter = '\0';
}

void remove_newline(char *line) {
	char *ch_iter = line;
	// go until you see new line
	while(*ch_iter != '\n') {
		ch_iter++; // next char
	}
	*ch_iter = '\0'; // overwrite new line
}

void print_dictionary(char *dict[]) {//I didn't use this
	int i;
	for(i = 0 ; i < DICT_SIZE ; i++) {
		printf("%s\n", dict[i]);
	}
}

void print_coord(int coord[DICT_SIZE][4]) {//I didn't use this
	int i, j;
	for(i = 0 ; i < DICT_SIZE ; i++) {
		for(j = 0 ; j < 4 ; j++) {
			printf("%d ", coord[i][j]);
		}
		printf("\n");
	}
}

void fill_rand(char map[15][15])   //15x15 random characters
{
	srand(time(NULL));
	int i,j;
	for(i = 0; i < MAP_SIZE; i++)
	{
		for(j = 0; j < MAP_SIZE; j++)
		{
			map[i][j] = (rand()%26) + 97;    //for the lowercase letters
		}
	}
}

void print_map(char map[15][15])  //print function
{
	int i, j;
	for(i = 0; i < MAP_SIZE; i++)
	{
		for(j = 0; j < MAP_SIZE; j++)
		{
			printf("%c ",map[i][j]);
		}
		printf("\n");
	}
}

void fill_words(char map[15][15], char* dict[], int coord[DICT_SIZE][4])  //fill the map with words from file
{
	int i, j, x = 0 , y = 0, x_ = 0, y_ = 0;
	for(i = 0 ; i < DICT_SIZE ; i++)
	{
		x = coord[i][0];
		y = coord[i][1];
		x_ = coord[i][0] - coord[i][2];
		y_ = coord[i][1] - coord[i][3];
		for(j = 0; dict[i][j] != '\0' && !(x_ == 0 && y_ == 0); j++)
		{
			map[x][y] = dict[i][j];		
			if(x_ < 0) {			//if the difference (between first and last letter of word's x-position) is negative,x will be increase.Because row is increasing.
				x++;
				x_++;				//the negative number is increasing until 0.
			}
			else if(x_ > 0) {		
				x--;
				x_--;				//the positive number is decreasing until 0.
			}

			if(y_ < 0) {				
				y++;
				y_++;
			}
			else if(y_ > 0) {
				y--;
				y_--;
			}
		}
    	if(x_ == 0 && y_ == 0){
    		map[x][y] = dict[i][j];
    	}
	}
}

void change(char map[15][15], int r1, int c1, int r2, int c2)//I didn't use this
{
	int i, j;
	for(i = r1; i <= r2; i++)
	{
		for(j = c1; j <= c2; j++)
		{
			
			map[i][j] -= 32;
		}
	}
}

int search_direction(char map[15][15], char word[], int index, int row, int colm, int direct)
{
	int check=0;
	if(word[index] == '\0') return 1;				//end of the word
	else if(row < 0 || row > 15 || colm < 0 || colm > 15) return 0;			//wrong row and column values
	else if(word[index] == map[row][colm] || word[index] == (map[row][colm] + 32))		//upper or lower cases.
	{
		if(direct == 2) check = search_direction(map, word, index+1, row+1, colm, direct);	//the directions are like keyboard key layout(for instance 2-down , 8 -up)
		else if(direct == 8) check = search_direction(map, word, index+1, row-1, colm, direct);	//recursive searches in all directions until end of the word.
		else if(direct == 6) check = search_direction(map, word, index+1, row, colm+1, direct);
		else if(direct == 4) check = search_direction(map, word, index+1, row, colm-1, direct);
		else if(direct == 1) check = search_direction(map, word, index+1, row+1, colm-1, direct);
		else if(direct == 3) check = search_direction(map, word, index+1, row+1, colm+1, direct);
		else if(direct == 7) check = search_direction(map, word, index+1, row-1, colm-1, direct);
		else if(direct == 9) check = search_direction(map, word, index+1, row-1, colm+1, direct);
		
		if(check == 1)
		{
			if(word[index] == map[row][colm])	map[row][colm] -= 32;  //if the word is true,the characters will be lowercase
			return 1;
		}
	}
	return 0;
	
}
int search_inverse_direction(char map[15][15], char word[], int index, int row, int colm, int direct)
{
	int check=0;
	if(index == 0)
	{
		if(word[index] == map[row][colm] || word[index] == (map[row][colm] + 32))	//upper or lower cases.
		{
			map[row][colm] -= 32;		//if the word is true,the characters will be lowercase	
			return 1;
		}
		else return 0;
	}
	else if(row < 0 || row > 15 || colm < 0 || colm > 15) return 0;   //wrong values
	else if(word[index] == map[row][colm] || word[index] == (map[row][colm] + 32))		//upper or lower cases.
	{
		if(direct == 2) check = search_inverse_direction(map, word, index-1, row+1, colm, direct);
		else if(direct == 8) check = search_inverse_direction(map, word, index-1, row-1, colm, direct);
		else if(direct == 6) check = search_inverse_direction(map, word, index-1, row, colm+1, direct);
		else if(direct == 4) check = search_inverse_direction(map, word, index-1, row, colm-1, direct);
		else if(direct == 1) check = search_inverse_direction(map, word, index-1, row+1, colm-1, direct);
		else if(direct == 3) check = search_inverse_direction(map, word, index-1, row+1, colm+1, direct);
		else if(direct == 7) check = search_inverse_direction(map, word, index-1, row-1, colm-1, direct);
		else if(direct == 9) check = search_inverse_direction(map, word, index-1, row-1, colm+1, direct);
		if(check == 1)
		{
			if(word[index] == map[row][colm])	map[row][colm] -= 32;
			return 1;
		}
	}
	return 0;
	
}

int search(char map[15][15], char word[], int row, int colm)
{
	int check=0;
	int temp = get_line_size(word)-1;

	if(word[0] == map[row][colm] || word[0] == (map[row][colm]) + 32)
	{
		check = 0;
		check += search_direction(map, word, 0, row, colm, 1);  
		check += search_direction(map, word, 0, row, colm, 2);
		check += search_direction(map, word, 0, row, colm, 3);
		check += search_direction(map, word, 0, row, colm, 4);
		check += search_direction(map, word, 0, row, colm, 6);
		check += search_direction(map, word, 0, row, colm, 7);
		check += search_direction(map, word, 0, row, colm, 8);
		check += search_direction(map, word, 0, row, colm, 9);
	}
	if(word[get_line_size(word)-1] == map[row][colm] || word[get_line_size(word)-1] == (map[row][colm] + 32))
	{
		check = 0;
		check += search_inverse_direction(map, word, temp, row, colm, 1);
		check += search_inverse_direction(map, word, temp, row, colm, 2);
		check += search_inverse_direction(map, word, temp, row, colm, 3);
		check += search_inverse_direction(map, word, temp, row, colm, 4);
		check += search_inverse_direction(map, word, temp, row, colm, 6);
		check += search_inverse_direction(map, word, temp, row, colm, 7);
		check += search_inverse_direction(map, word, temp, row, colm, 8);
		check += search_inverse_direction(map, word, temp, row, colm, 9);
	}
	
	return check;
}

int is_exit(char word[],char word2[])
{
	char exit[] = "exit";   //for the exit control
	char exit2[] = "game";
	int i;
	for(i = 0; word[i] != '\0' && exit[i] != '\0' ; i++)
	{
		if(word[i] != exit[i]) return 0;
	}
	for(i = 0; word2[i] != '\0' && exit2[i] != '\0'; i++)
	{
		if(word2[i] != exit2[i]) return 0;;
	}
	return 1;	
}


int main(){
	char *dict[DICT_SIZE];
    int coord[DICT_SIZE][4];    
    char line[LINE_LEN];
    char map[MAP_SIZE][MAP_SIZE];
    char a;
    int flag = 0,flag2 =0;  
	int row, column, check;
	char word[WORD_LEN],word2[WORD_LEN];
	FILE *fp = fopen("word_hunter.dat", "r");
	
	int line_counter = 0;
	int dict_counter = 0;
	while(fgets(line, LINE_LEN, fp) != NULL) {
		if(line_counter%5 == 0) {
			dict[dict_counter] = (char*) malloc(sizeof(char) * get_line_size(line));
			remove_newline(line);
			copy_string(line, dict[dict_counter]);
		} else if (line_counter%5 == 1){
			coord[dict_counter][0] = atoi(line);
		} else if (line_counter%5 == 2){			
			coord[dict_counter][1] = atoi(line);		
		} else if (line_counter%5 == 3){
			coord[dict_counter][2] = atoi(line);
		} else if (line_counter%5 == 4){
			coord[dict_counter][3] = atoi(line);
			dict_counter++;
		}
		line_counter++;
	}
	
	fclose(fp);
	fill_rand(map);
	fill_words(map, dict, coord);
	printf(" \tWELCOME TO WORD HUNTER GAME \n");
	printf("\nMAP:\n");
	print_map(map);
	while(flag == 0 && flag2!=14)   //flag for the exit control , flag 2 for the if whole words are found the game will finish.
	{
		printf("\nEnter the word to search or Enter 'exit game' to exit game: ");
		scanf("%s%c",word,&a);
		if(a == ' ') scanf("%s",word2);		//"exit game" is 2 words.So a is control if the character between words is space,it takes other string from users. 
		flag = is_exit(word,word2);
		if(flag == 0)
		{
			printf("Enter the row: ");
			scanf("%d", &row);
			printf("Enter the column: ");
			scanf("%d", &column);
			while(row < 0 || row > 14 || column < 0 || column > 14)
			{
				printf("\nYou entered the wrong coordinate, please check and try again!\n");
				printf("Enter the row: ");
				scanf("%d", &row);
				printf("Enter the column: ");
				scanf("%d", &column);
			}
			check = search(map, word, row, column);
			if(check == 1)
			{
				printf("\n   '\'%s  \'' word found!\n\n",word);
				print_map(map);
				flag2 += 1;
			}
			else
			{
				printf("\n  '\'%s \'' word not found!\n\n",word);
				print_map(map);

			}
		}
		else
		{
			printf("\nSuccessfully exit.\n");
			printf("\nGame is over ! \n\n");

		}
	}
		
	return 0;
}






