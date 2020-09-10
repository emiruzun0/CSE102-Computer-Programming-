#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#define tab "    "   //for the first and last line spaces
#define PI 3.00
#define SQUARE 1
#define RECTANGULAR 2
#define CIRCULAR 3
#define RED 0
#define YELLOW 1
#define BLUE 2 
#define BLACK 3
#define WHITE 4

double CreateBody (int shape);
int SetColor (int color);
double LoadMoves (int shape, double body_size);
int SetAttackPower (int lower_bound, int upper_bound);
void ShowPokemon(int shape,double body_size,int color,double move_length, int attack_power);


double CreateBody ( int shape ){
	double a,b;
	if(shape == SQUARE){
		printf("Please enter a posisitve number for square edge : ");          //takes edges for the areas of shapes
		scanf("%lf",&a);
		return a*a;
	}
	else if(shape == RECTANGULAR){													
		printf("Please enter edges for rectangular edge : ");
		scanf("%lf%lf",&a,&b);
		return a*b;
	}
	else{
		printf("Please enter a positive number for radius : ");
		scanf("%lf",&a);
		return PI*a*a;
	}
}

int SetColor ( int color){
	if(color<0 || color >1000){                             					//return 1 if color is not 0-1000 range
		return 1;      
	}
	else{
		color = color%5;  														//return modula 5 of color
		return color;
	}
}

double LoadMoves(int shape , double body_size){
	switch(shape){
		case SQUARE:
			body_size = sqrt(body_size);       									//square perimeter equals to 4 times edge 
			return 4.0*body_size;
			break;
		case RECTANGULAR:
			body_size = (body_size/5.0);										//Rectangular perimeter equals to 2 times area/5 added to 2 times 5.
			return 2.0*body_size+10.0;											 
			break;
		case CIRCULAR:	
			body_size = sqrt(body_size/PI);										//Circular shape perimeter equals to 2*PI*radius and to find the radius,we take square root of area/PI			
			return 2.0*PI*body_size;											
			break;
	}
}
			
int SetAttackPower( int lower_bound,int upper_bound){
	int r;	
	r=lower_bound+rand()%upper_bound;											//random number equals to lower + modula of upper bound
	return r;
}
	
void ShowPokemon(int shape,double body_size,int color,double move_length, int attack_power){
	int i,j,k,a,inspace,outspace;
	
	switch(shape){
		case SQUARE:
			a=sqrt(body_size);												//find edge of square		
			for(i=0;i<a;i++){
				for(j=0;j<a;j++){											//nested loops for the row and column 
					printf("X");
				}
				printf("\n");
			}
			printf("Name : Square Pokémon\n");
			break;
		case RECTANGULAR:
			a=body_size/5;													//we assume that short edge is 5.So we divided area into 5 
			for(i=0;i<5;i++){
				for(j=0;j<a;j++){
					printf("X");
				}
				printf("\n");
			}
			printf("Name : Rectangular Pokémon\n");
			break;
		case CIRCULAR:
			a=sqrt(body_size/PI);
			if(a%2==1){														//if radius is odd number,we don't use white space.
				outspace = a/2 ;											//outside space must be half of edge.If it is float number,we should take the integer part.
				inspace = 0;												//for the first line, inside space must be 0.
				for(i=0;i<a/2+1;i++){										//this loop is for the row number
					for(j=0;j<outspace;j++){								//this loop is for the column
						printf("\t");
					}
					printf("X");
					if(i!=0){												//first line (i=0) must be printed only one X.
						for(j=0;j<inspace;j++){
							printf("\t");
						}
						printf("X");
					}
					printf("\n");
					inspace+=2;												
					outspace--;
				}
				inspace -= 4;
				outspace = 1;
				for(i=0;i<a/2;i++){											//this loop for the underside of figure.
					for(j=0;j<outspace;j++){								//this loop for column 
						printf("\t");
					}
					printf("X");
					if(i!=a/2-1){											//for the last line of figure must be printed just one X.
						for(j=0;j<inspace;j++){
							printf("\t");
						}
						printf("X");
					}
					printf("\n");
					inspace -= 2;
					outspace++;
				}
			}
			else if(a%2==0){												//if radius is even number,we use white space.	
				inspace=1;													//inside space must be 1 because we directly start second line
				outspace=a/2-1;
				for(i=0;i<outspace;i++){									//this loop is used for first line.
					printf("\t");
				}
				printf("%sX\n",tab);
				for(i=0;i<a/2;i++){											//this loop start with second line.
					for(j=0;j<outspace;j++){
						printf("\t");
					}
					printf("X");
					for(k=0;k<inspace;k++){
						printf("\t");
					}
					printf("X");
					printf("\n");
					inspace+=2;
					outspace--;
				}
				inspace-=4;
				outspace=1;	
				for( i=0;i<a/2-1;i++){										//this loop for the underside of figure.
					for(j=0;j<outspace;j++){
					printf("\t");
					}
					printf("X");
					for(k=0;k<inspace;k++){
						printf("\t");
					}
					printf("X");
					printf("\n");
					inspace-=2;
					outspace++;
				}
				outspace=a/2-1;
				for(i=0;i<outspace;i++){									//this loop is used for last line.
					printf("\t");
				}
				printf("%sX\n",tab);
			}	
			printf("Name : Circular Pokémon\n");
		break;
	}
	printf("Size : %.2f \n",body_size);
	printf("Color : ");
	switch(color){
		case RED:	
			printf("Red \n");
			break;
		case BLUE:
			printf("Blue \n");
			break;
		case BLACK:
			printf("Black \n");
			break;
		case WHITE:
			printf("White \n");
			break;
		default:
			printf("Yellow \n");
			break;
		}
		printf("Move : %.2f \n",move_length);
		printf("Attack Power : %d\n",attack_power);
}	

int main(){
	int shape,color,attack_power;
	double size_of_body, move_length;
	srand(time(NULL));														//it is used for different random number for every time
	shape = CIRCULAR ;
  	size_of_body = CreateBody (shape);
	color = 808;
	color = SetColor(color);
	move_length = LoadMoves(shape,size_of_body);
	attack_power = SetAttackPower(0,150);
	ShowPokemon(shape,size_of_body,color,move_length,attack_power);			
}
