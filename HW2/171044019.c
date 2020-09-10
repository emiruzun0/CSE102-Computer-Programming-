#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define COUNT 10 				//this is the trial for first game

void menu();
int make_a_guess (int trial, int min, int max);
void show_scores(int score_human, int score_program);
void draw_hourglass (int height);
void draw_mountain_road (int length, int max_radius);

void menu(){
	int min,max,count,LN,trial,guess;
	int choice,length,height,max_radius;
	int score_human=0, score_program=0;
	LN = 1+rand()%1024;
	do{
		printf("***** MENU *****\n");
		printf("1. Play Lucky Number\n");
		printf("2. Draw Hourglass\n");
		printf("3. Draw Mountain Road\n");
		printf("4. Exit\n");
		printf("Choice:");
		scanf("%d",&choice);
		switch(choice){
			case 1:
				trial=1;
				min=1,max=1024;											//count is the bound for the trial
				LN = min+rand()%max;
				printf("You have %d trial for this game\n\n",COUNT);
				do{
					guess = make_a_guess(trial, min, max);							//take guess from user
					trial++;
					if(guess<LN){													//For set new minimum limit
						min=guess;
					}
					else{
						max=guess;													//For set new maximum limit.
					}
					if(fabs(guess-LN)>=pow(2,9) && fabs(guess-LN)<pow(2,10)){
						printf("Distance is 10\n");
					}
					else if(fabs(guess-LN)>=pow(2,8) && fabs(guess-LN)<pow(2,9)){
						printf("Distance is 9\n");
					}
					else if(fabs(guess-LN)>=pow(2,7) && fabs(guess-LN)<pow(2,8)){
						printf("Distance is 8\n");
					}
					else if(fabs(guess-LN)>=pow(2,6) && fabs(guess-LN)<pow(2,7)){
						printf("Distance is 7\n");
					}
					else if(fabs(guess-LN)>=pow(2,5) && fabs(guess-LN)<pow(2,6)){
						printf("Distance is 6\n");
					}
					else if(fabs(guess-LN)>=pow(2,4) && fabs(guess-LN)<pow(2,5)){
						printf("Distance is 5\n");
					}
					else if(fabs(guess-LN)>=pow(2,3) && fabs(guess-LN)<pow(2,4)){
						printf("Distance is 4\n");
					}
					else if(fabs(guess-LN)>=pow(2,2) && fabs(guess-LN)<pow(2,3)){
						printf("Distance is 3\n");
					}
					else if(fabs(guess-LN)>pow(2,0) && fabs(guess-LN)<pow(2,2)){
						printf("Distance is 2\n");
					}
					else if(fabs(guess-LN)==1){
						printf("Distance is 1\n");
					}
					else if(guess==LN){
						printf("You win ! \n\n\n\n");
						score_human++;												//if the user knows the lucky number before the end of the trials,user wins.
					}
				}while(trial<=COUNT && guess!=LN);									//if the trials finish or guess equals to luck number,game is over.
				if(guess!=LN){
					printf("\n\nYou lost ! \n");
					printf("The LN was %d\n\n\n\n",LN);
					score_program++;												//if the user knows the lucky number before the end of the rights,program wins.
				}
				show_scores(score_human,score_program);
				break;
			case 2:
				printf("Enter a height:");
				do{
					scanf("%d",&height);
					if(height%2==0){
						printf("Please enter odd number!\nEnter a height:");
					}
				}while(height%2!=1);
				draw_hourglass(height);
				break;
			case 3:
				printf("Enter max radius:");
				scanf("%d",&max_radius);
				printf("Enter length:");
				scanf("%d",&length);
				draw_mountain_road(length,max_radius);
				break;
			case 4:
				printf("Exiting...\n\n");
				exit;
				break;
			default:
				printf("This is an invalid choice.Try again!\n\n");
				break;
		}
	}while(choice!=4);
}


int make_a_guess (int trial, int min, int max){
	int g;
	printf("(Trial: %d)Make a guess between %d and %d : ",trial,min,max);
	scanf("%d",&g);
	return g;
}


void show_scores(int score_human, int score_program){
	printf("Your Score: %d \nProgram Score: %d\n\n\n\n",score_human,score_program);	//End of the each first game,the function shows the scores 
}


void draw_hourglass (int height){
	int i,j,k,h,space,star;
	h=height/2+1;																	//h is for the half of hourglass
	space=0;
	star=height;
	for(i=0;i<h;i++){	
		for(j=0;j<space;j++){														//The spaces are printed first.
			printf(" ");
		}
		for(k=0;k<star;k++){														//And then stars are printed
			printf("*");
		}
		star-=2;																	//Stars must be decrease by 2 for each line
		space++;																	//And the spaces increase by 1 for each line.Because hourglass is shrinking
		printf("\n");
	}
	star+=4;
	space-=2;
	for(i=0;i<h-1;i++){																//This loop is for the other half of hourglass.
		for(j=0;j<space;j++){
			printf(" ");
		}
		for(k=0;k<star;k++){
			printf("*");
		}
		star+=2;
		space--;
		printf("\n");
	}
	printf("\n\n\n");
}

void draw_mountain_road (int length, int max_radius){
	int i,j,k,l,radius,space;
	for(i=1;i<=length;++i){															//The main loop is for the how many times return this road.
		radius=rand()%(max_radius+1);												//Radius must be random numbers from 0 to max radius.(I added +1 to include max radius.)
		space=max_radius;															//For my program,space is the most important value.Because each line depends o spaces.
		if(i%2==1){																	//I seperated 2 parts : odd and even numbers.Odd part is prints left side first,and then prints right side.
			for(j=0;j<radius;++j){
				for(k=space;k>0;--k){												//This loop prints the spaces first.
					printf(" ");
				}
				printf("/\n");
				space--;
			}
			for(j=0;j<space;j++){													//This loop is the space for the "|" character.
				printf(" ");
			}	
			printf("|\n");
			space++;
			for(j=0;j<radius;j++){													//This loop prints the right side.
				for(k=0;k<space;++k){	
					printf(" ");
				}
				printf("\\\n");
				space++;
			}
		}
		else{
			for(k=0;k<radius;++k){	
				for(l=0;l<space+1;++l){												//It turns until the space+1 because where we are to be able to continue.(After the first length)
					printf(" ");	
				}
				printf("\\\n");
				space++;
			}
			for(k=0;k<space+1;++k){													//This loop is the space again for the "|" character.
				printf(" ");
			}
			printf("|\n");
			for(k=0;k<radius;k++){
				for(l=0;l<space;++l){												//This loop prints the left side.
					printf(" ");
				}
				printf("/\n");
				space--;
			}
		}			
	}
	printf("\n\n\n\n");
}
	
int main(){
	srand(time(NULL));
	menu();
}
