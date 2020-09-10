/* EMİRHAN UZUN 171044019*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

typedef enum{
	Charmander,Pikachu,Squirtle,Bulbasaur,Pidgeotto,Ratata,Mug,Caterpie,Zubat,Crabby
}pokemon;

typedef enum{
	Quadratic,Linear
}attack_type;



void menu(char Pokemon_name[10][11], int range[], attack_type type[],int attack_power[], int stamina[],pokemon Pokemons[]);
void pokedex(char Pokemon_name[10][11], int range[], attack_type type[],int attack_power[], int stamina[]);
void oaks_laboratory(char Pokemon_name[10][11], pokemon Pokemons[],pokemon *my_Pokemons);
void show_Pokemons(char Pokemon_name[10][11], pokemon Pokemons[],int pokemon_count);
void catch_a_pokemon(char Pokemon_name[10][11], pokemon Pokemons[],pokemon *my_pocket);
void release_a_pokemon(char Pokemon_name[10][11], pokemon Pokemons[],pokemon *my_pocket);
void battle(char Pokemon_name[10][11], int range[], attack_type type[], int attack_power[], int stamina[], pokemon user_Pokemons[]);
void show_area (char Pokemon_name[10][11],int area[8][8],int pokemon_staminas_view[8][8]);
int make_move(int area[8][8],int staminas_view[8][8],int stamina[],int cur_pokemon,int x,int y);
int control_move(int cur_x,int cur_y,int target_x,int target_y);
int strcomparison(char a[],char b[]);
int strlength(char a[11]);


int main(){
	char Pokemon_name[10][11] = {"Charmander","Pikachu","Squirtle","Bulbasaur","Pidgeotto","Ratata","Mug","Caterpie","Zubat","Crabby"};
	int range[] = {1,3,4,3,2,2,1,2,3,2};
	attack_type type[10] = {0,1,1,1,0,1,0,0,1,1};
	int attack_power[] = {500,350,300,400,250,250,350,200,350,300};
	int stamina[] = {2200,1500,1700,2500,1900,2500,3000,1200,1250,2600};
	pokemon Pokemons[] = {Charmander,Pikachu,Squirtle,Bulbasaur,Pidgeotto,Ratata,Mug,Caterpie,Zubat,Crabby};
	srand(time(NULL));
	menu(Pokemon_name,range,type,attack_power,stamina,Pokemons);
}

//pokedex length find function
int strlength(char a[11]){
	int i=0;
	while(a[i] != '\0'){
		++i;
	}
	return i;
}

//pokedex string comparison function
int strcomparison(char a[],char b[]){
	int i,lengtha,lengthb;
	lengtha = strlength(a);
	lengthb = strlength(b);
	if(lengtha != lengthb) return 0;
	for(i=0;i<lengtha;++i){
		if(a[i] != b[i]) return 0; 
	}
	return 1;
}
	
//pokedex print function
void pokedex(char Pokemon_name[10][11], int range[], attack_type type[],int attack_power[], int stamina[]){
	char s[11];
	int i;
	int pokemon_index=-1;
	printf("Please type name of the Pokémon (type exit to close Pokedex): ");
	scanf("%s",s);
	while(strcomparison(s,"exit") == 0){
		for(i=0;i<10;++i){
			if(strcomparison(s,Pokemon_name[i]) == 1){
				pokemon_index=i;	
				break;
			}		
		}
		if(pokemon_index != -1){ 
			printf("\nName : %s\n",Pokemon_name[pokemon_index]);
			if(type[pokemon_index] == 0) printf("Attack Type : Quadratic\n");
			else if(type[pokemon_index] == 1) printf("Attack Type : Linear\n");
			printf("Range : %d block \n",range[pokemon_index]);
			printf("Attack Power : %d\n",attack_power[pokemon_index]);
			printf("Stamina : %d\n\n",stamina[pokemon_index]);
		}
		else{
			printf("You've entered invalid choice.\n");
		}
		pokemon_index=-1;
		printf("Please type name of the Pokémon (type exit to close Pokedex): ");
		scanf("%s",s);
	}
	printf("Exiting...\n\n\n");
}
	
void oaks_laboratory(char Pokemon_name[10][11], pokemon Pokemons[],pokemon *my_Pokemons){
	int choice;
	int selected_pokemons = 0;
	do{
		printf("\n\n1) Show Pokémons\n2) Catch a Pokémon\n3) Release a Pokémon\n4) Show my pocket\n5) Back\n");
		scanf("%d",&choice);
		switch(choice){
			case 1:
				show_Pokemons(Pokemon_name,Pokemons,10);
				break;
			case 2:
				if(selected_pokemons<4){
					catch_a_pokemon(Pokemon_name, Pokemons,my_Pokemons);
					selected_pokemons++;	
				}
				else{
					printf("You've already choosen 4 pokemons.\n");
				}
				break;
			case 3:
				if(selected_pokemons == 0){
					printf("You don't have pokemon.\n");
				}
				else{
					release_a_pokemon(Pokemon_name, Pokemons,my_Pokemons);
					selected_pokemons--;
				}
				break;
			case 4:
				show_Pokemons(Pokemon_name, my_Pokemons, selected_pokemons);
				break;
			case 5:
				printf("Returning to the main menu\n\n");
				break;
			default:
				printf("You've entered invalid value.\n\n");
				break;
		}
	}while(choice != 5);
}
		
void catch_a_pokemon(char Pokemon_name[10][11], pokemon Pokemons[],pokemon *my_pocket){
	int choice,i,flag;
	int j;
	pokemon selected_pokemon;
	do{
		flag=1;
		show_Pokemons(Pokemon_name,Pokemons,10);
		printf("\nChoice : ");
		scanf("%d",&choice);
		for(i=0, j=0;i<4;++i){
			if(my_pocket[i] != -1) j++;
			if(my_pocket[i] == choice){
				printf("You've already choosen this pokemon.Please choose different pokemon.\n");
				flag=0;
				break;
			} 
		}
		if(flag==1){
			selected_pokemon = Pokemons[choice];
			my_pocket[j] = selected_pokemon;
		}
	}while(flag == 0);
}


void release_a_pokemon(char Pokemon_name[10][11], pokemon Pokemons[],pokemon *my_pocket){
	int choice,i,j,flag;
	int count=0;
	do{
		flag=0;
		show_Pokemons(Pokemon_name, my_pocket, count);
		printf("Which pokemon do you want to release ? : Enter 0 for back\n\n");
		scanf("%d",&choice);

		for(i=0;i<4;++i){
			if(my_pocket[i] >=0 && my_pocket[i] <=9) count++;
			if(my_pocket[i] == choice){
				flag=1;
			}
		}
		if(flag==0) printf("You don't have this pokemon.\n");
	}while(flag == 0|| choice != 0);


	if(flag == 1){
		for(i=0,j=0;j<=count-1;j++){
			if(my_pocket[j] == choice){
				if(j != count-1){
					i=j;
					while(i<count-1){
						my_pocket[i] = my_pocket[i+1];
						i++;
					}
					my_pocket[i] = -1;   
				}
				else if(j == count-1){	
					my_pocket[j] = -1;
				}
			}
		}
	}
}		


//show function
void show_Pokemons(char Pokemon_name[10][11], pokemon Pokemons[],int pokemon_count){
	int i;
	pokemon curr_pokemon ; 
	for(i=0;i<pokemon_count;++i){
		curr_pokemon = Pokemons[i];
		printf("%d - %s \n",curr_pokemon,Pokemon_name[curr_pokemon]);
	}
	printf("\n");
}


//menu function
void menu(char Pokemon_name[10][11], int range[], attack_type type[],int attack_power[], int stamina[],pokemon Pokemons[]){
	int choice,i,count;
	pokemon my_Pokemons[4];
	for(i=0;i<4;++i){
		my_Pokemons[i] = -1;
	}
	do{
		count=0;
		printf("Please select an option to continue : \n");
	 	printf("1) Open Pokedex \n");
		printf("2) Go to Oak's Laboratory \n");
		printf("3) Enter the tournament \n");
		printf("4) Exit \n\n");
		scanf("%d",&choice);
		switch(choice){
			case 1:
				pokedex(Pokemon_name,range,type,attack_power,stamina);
				break;
			case 2:
				oaks_laboratory(Pokemon_name,Pokemons,my_Pokemons);
				break;
			case 3:
				for(i=0;i<4;++i){
					if(my_Pokemons[i] == -1){
						count++;
					}
				}
				if(count != 0){
					printf("You have to chose 4 pokemon.\n");			//he/she must be chose 4 pokemons for battle ! 
				}
				else{
					battle(Pokemon_name,range,type,attack_power,stamina, my_Pokemons);
				}
				break;
			case 4:
				printf("Exiting...\n");
				break;
			default:
				printf("You have entered invalid value.\n");
				break;
		}
	}while(choice!=4);
}


void battle(char Pokemon_name[10][11], int range[], attack_type type[], int attack_power[], int stamina[], pokemon user_Pokemons[]){
	int a,c,i,j,x,y,rand_pokemon,user_turn=1;
	int flag,flag2,flag3;
	int area[8][8];
	int staminas_view[8][8];
	int pc_Pokemons[4];

	for(i=0;i<8;++i){
		for(j=0;j<8;++j){
			area[i][j] = -1;			//-1 is my junk value
			staminas_view[i][j] = -1;
		}
	}
	for(i=0;i<4;++i){
		do{    //select pokemon for pc 
			flag=0;
			rand_pokemon=rand()%10;
			for(j=i-1;j>=0;--j){				//control loop for if the pokemon was choosen before ? 
				if(pc_Pokemons[j] == rand_pokemon+10){
					flag=1;
					break;
				} 
			}
		}while(flag == 1);
		pc_Pokemons[i] = rand_pokemon+10;   // I added 10 because if we and pc chose same pokemon , it will be a problem
		do{ //select location
			flag2=0 ;
			x = 6+rand()%2;   //Pokemon should be at 6. or 7.row.
			y = rand()%9;
			if(area[x][y] != -1){
				flag2=1;
			}
		}while(flag2 == 1);
		area[x][y] = rand_pokemon+10;	
		staminas_view[x][y] = stamina[rand_pokemon];
	
	}
	//get user's locations
	for(i=0;i<4;++i){
		do{
			flag3=0;
			printf("Select a position for %s \n\n(Row must be 0 or 1,column must be 0 to 7)\n\n",Pokemon_name[user_Pokemons[i]]);
			scanf("%d%d",&x,&y);
			if(x < 0 || x > 1 || y<0 || y>7|| area[x][y] != -1){
				printf("This position is not available.\n");
				flag3=1;
			}
		}while(flag3 == 1);
		area[x][y] = user_Pokemons[i];
		staminas_view[x][y] = stamina[user_Pokemons[i]];
	}
		
	show_area(Pokemon_name,area,staminas_view);
		
	//get user's moves
	do{
		if(user_turn%2 == 1){
			printf("Chose pokemon : \n");
			show_Pokemons(Pokemon_name, user_Pokemons, 4);
			do{
				scanf("%d",&c);
				for(i=0;i<4;++i){
					flag3=0;         //control loop for the right choice
					if(c == user_Pokemons[i]){
						flag3=1;
						break;
					}
				}
				if(flag3==0) printf("You've entered invalid choice.Try again.\n\n");
			}while(flag3==0);
			do{
				flag3=0;
				printf("Select a position for %s \n(Row must be 0 or 7,column must be 0 to 7)\n",Pokemon_name[user_Pokemons[i]]);
				scanf("%d%d",&x,&y);
				if(area[x][y] != c){
					if(x < 0 || x > 8 || y<0 || y>7|| area[x][y] != -1 || make_move(area,staminas_view,stamina,c,x,y) == 0){
						printf("This position is not available.\n");
						flag3=1;
					}
				}
			}while(flag3 == 1);


			//for attack conditions (Linear or quadratic)
			area[x][y] = c;
			a = range[c] ; 
			if(type[c] == 1){
					for(i=-1 * a ;i<a + 1;++i){
						if(area[x+i][y] != -1){
							for(j=0;j<4;++j){
								if(area[x+i][y] == pc_Pokemons[j]){
									staminas_view[x+i][y] = stamina[pc_Pokemons[j]-10] - attack_power[c];
								}							
							}		
						}
					}
					for(i=-1 *a ;i<a +1;++i){
						if(area[x][y+i] != -1){
							for(j=0;j<4;++j){
								if(area[x][y+i] == pc_Pokemons[j]){
									staminas_view[x][y+i] = stamina[pc_Pokemons[j]-10] - attack_power[c];
								}							
							}		
						}
					}	
			}
			else{
				for(i=-1 * a;i<a +1;++i){
						if(area[x+i][y+i] != -1){
							for(j=0;j<4;++j){
								if(area[x+i][y+i] == pc_Pokemons[j]){
									staminas_view[x+i][y+i] = stamina[pc_Pokemons[j]-10] - attack_power[c];
								}							
							}		
						}
				}
				for(i=-1 * a;i<a +1;++i){
					if(area[x-i][y+i] != -1){
						for(j=0;j<4;++j){
							if(area[x-i][y+i] == pc_Pokemons[j]){
								staminas_view[x-i][y+i] = stamina[pc_Pokemons[j]-10] - attack_power[c];
							}							
						}		
					}
				}	
			}
		}
		// pc's turn
		else{
			c = rand()%4;
			x=rand()%8;
			y=rand()%8;
			do{
				flag3=0;
				x=rand()%8;
				y=rand()%8;
				if(x < 0 || x > 8 || y<0 || y>7|| area[x][y] != -1 || make_move(area,staminas_view,stamina,pc_Pokemons[c],x,y) == 0){
					flag3=1;
				}
			}while(flag3 == 1);	
		
			//pc attack conditions
			area[x][y]=c;
			a = range[c] ; 
			if(type[c] == 1){//if type is linear
					for(i=-1 * a;i<a +1;++i){	
						if(area[x+i][y] != -1){
							for(j=0;j<4;++j){
								if(area[x+i][y] == user_Pokemons[j]){
									staminas_view[x+i][y] = stamina[user_Pokemons[j]] - attack_power[c];
								}							
							}		
						}
					}
					for(i=-1 * a;i<a +1;++i){
						if(area[x][y+i] != -1){
							for(j=0;j<4;++j){
								if(area[x][y+i] == pc_Pokemons[j]){
									staminas_view[x][y+i] = stamina[user_Pokemons[j]] - attack_power[c];
								}							
							}		
						}
					}	
			}
			else{//type is quadratic
				for(i=-1 * a;i<a +1;++i){
					if(area[x+i][y+i] != -1){
						for(j=0;j<4;++j){
							if(area[x+i][y+i] == pc_Pokemons[j]){
								staminas_view[x+i][y+1] = stamina[user_Pokemons[j]] - attack_power[c];
							}							
						}		
					}
				}
				for(i=-1 * a;i<a +1;++i){
					if(area[x-i][y+i] != -1){
						for(j=0;j<4;++j){
							if(area[x-i][y+i] == pc_Pokemons[j]){
								staminas_view[x-i][y+i] = stamina[user_Pokemons[j]] - attack_power[c];
							}							
						}		
					}
				}	
			}
		}


		show_area(Pokemon_name,area,staminas_view);
		printf("\n\n\n");
		user_turn++;
	}while(1);
}

//move control function 
int make_move(int area[][8],int staminas_view[][8],int stamina[],int cur_pokemon,int x,int y){
	int i,j;
	for(i=0;i<8;++i){
		for(j=0;j<8;++j){
			if(area[i][j] == cur_pokemon){
				if(control_move(i,j,x,y) == 0) return 0; 
				else {
					area[x][y] = cur_pokemon;
					area[i][j] = -1; 
					staminas_view[x][y] = staminas_view[i][j];
					staminas_view[i][j] = -1;
					return 1;
				}
			}
		}
	}
}


//only move for 0,1,2 block.
int control_move(int cur_x,int cur_y,int target_x,int target_y){
	int a,b;
	a = cur_x - target_x;
	if(a<0) a= (-1)*a;
	b = cur_y - target_y;
	if(b<0) b = (-1)*b;
	

	if(a>0 && b>0) return 0;
	else if(a>2) return 0;
	else if(b>2) return 0;
	else return 1;

	
}


void show_area (char Pokemon_name[10][11],int area[8][8],int pokemon_staminas_view[8][8]){
	int i,j,k;
	for(i=0;i<8;++i){
		for(j=0;j<8;++j){
			printf("|");
			if(area[i][j] > -1 && area[i][j] < 20){
				switch(area[i][j]){
					case 0:
						printf("Ch\t");
						break;
					case 10: 
						printf("Ch*\t");
						break;
					case 1:
						printf("Pi\t");
						break;
					case 11: 
						printf("Pi*\t");
						break;
					case 2:
						printf("Sq\t");
						break;
					case 12: 
						printf("Sq*\t");
						break;
					case 3:
						printf("Bu\t");
						break;
					case 13: 
						printf("Bu*\t");
						break;
					case 4:
						printf("Pd\t");
						break;
					case 14: 
						printf("Pd*\t");
						break;
					case 5:
						printf("Ra\t");
						break;
					case 15: 
						printf("Ra*\t");
						break;
					case 6:
						printf("Mu\t");
						break;
					case 16: 
						printf("Mu*\t");
						break;
					case 7:
						printf("Ca\t");
						break;
					case 17: 
						printf("Ca*\t");
						break;
					case 8:
						printf("Zu\t");
						break;
					case 18: 
						printf("Zu*\t");
						break;
					case 9:
						printf("Cr\t");
						break;
					case 19: 
						printf("Cr*\t");
						break;
					default:
						break;
				}
			}
			else printf("\t");
		}
		printf("\n");
		for(j=0;j<8;++j){
			printf("|");
			if(pokemon_staminas_view[i][j] > 0 && pokemon_staminas_view[i][j]<3001 ) printf("%d \t",pokemon_staminas_view[i][j]);
			else printf("  \t");
		}
		printf("\n");
		for(k=0;k<65;++k){
			printf("_");
		}
		printf("\n");
	}
}


	
