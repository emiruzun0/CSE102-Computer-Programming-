//171044019 EMİRHAN UZUN //
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


typedef enum {
	NOONE,CAP,CAR
}player_type;

typedef enum {
	START,PROPERTY,TAX,PUNISH,FORTUNE
}block_type;

typedef struct {
	player_type type;
	int current_block_id;
	int owned_block_ids[12];
	int account;
	int turn_to_wait;
	char *name;
}player;

typedef struct block{
	int block_id;
	char * name;
	int price;
	int rent;
	int rent_1;
	int rent_2;
	int rent_3;
	int house_price;
	int house_count;
	player owner;
	block_type type;
	struct block *next;
}block;

typedef struct fortune_card{
	int card_number;
	struct fortune_card *next;
}fortune_card;


void init_the_board(block *temp);
void show_board(block *temp, player player_one,player player_two);
void show_properties(block *temp);
void gameplay( block *temp, player player_one, player player_two);
void buy_property(block* current_block,player* current_player);
void sell_property(block *temp, player* current_player);
void buy_house(block *temp,player *current_player);
void buy_house_fortune(block *board,player *current_player);
int show_properties2(block *temp,player *current_player);


int main(){
	int i;
	srand(time(NULL));
	block *head;
	head = (block*)malloc(sizeof(block));
	player player_one;
	player_one.type = CAP;
	player_one.current_block_id = 0;
	player_one.account = 100000;
	player_one.turn_to_wait = 0;
	for(i=0;i<12;++i){		//filling the array with -1 (It means these elements are empty)
		player_one.owned_block_ids[i] = -1;
	}
	player_one.name = (char*)malloc(strlen("Cap")*sizeof(char));
	strcpy(player_one.name,"Cap");
	player player_two;
	player_two.type = CAR;
	player_two.current_block_id = 0;
	player_two.account = 100000;
	player_two.turn_to_wait = 0;
	for(i=0;i<12;++i){		//filling the array with -1 (It means these elements are empty)
		player_two.owned_block_ids[i] = -1;
	}
	player_two.name = (char*)malloc(strlen("Car")*sizeof(char));
	strcpy(player_two.name,"Car");
	init_the_board(head);
	show_board(head,player_one,player_two);
	gameplay(head, player_one, player_two);
	return 0;
}

void buy_house(block *board,player *current_player){	
	if(board->house_count != 3){
		board->house_count++;
		current_player->account -= board->house_price;
		printf("You bought a house ! \n");
	}
	else printf("You've 3 house.You can't buy more houses ! \n");
}

void buy_house_fortune(block *board,player *current_player){	
	if(board->house_count != 3){
		board->house_count++;
		printf("You bought a house ! \n");
	}
	else printf("You've 3 house.You can't buy more houses ! \n");
}


int show_properties2(block *board,player *current_player){
	int i,j;
	int count=0;
	block *temp;
	temp = (block*)malloc(sizeof(block));
	temp = board;
	printf("\n\n\n");
	for(i=0;i<12;++i){
		if(current_player->owned_block_ids[i] != -1){		//if the array elements if not -1 , it will be printed .
			for(j=0;j<current_player->owned_block_ids[i] ; ++j){
				board = board->next;
			}
			printf("%d - %s \n",current_player->owned_block_ids[i],board->name);
			board = temp;
			count++;
		}
	}
	board = temp;
	printf("\n\n");
	//free(temp);
	return count;
}

void sell_property_pc(block *board, player* current_player){
	block *temp;
	int i,j,k;
	int id ;
	int max = 0;
	temp = board;
	if(show_properties2(board,current_player)){
		for(j=0;j<12;++j){
			for(k=0;k<current_player->owned_block_ids[j] ;++k){
				board = board -> next;
			}
			if(board->price > max ){
				max = board->price;
				id = board->block_id;
			}
			board = temp;
		}
		board = temp;
		for(k = 0 ; k < id;k++) board = board->next;
		if(board->owner.type == current_player->type){		//type control (CAR or CAP)
			current_player->account += (board->price)/2;		//owner earns half price of block 
			board->owner.type = NOONE;
			printf("Computer sold %s  ! \n",board->name);
			printf("NEW ACCOUNT (COMPUTER) : %d$ \n\n",current_player->account);
			for(i=0;i<12;++i){
				if(current_player->owned_block_ids[i] == id){	
					current_player->owned_block_ids[i] = -1;
				}
			}
			if(board->house_count != 0){				//owner earns half prices of houses if owner has some houses
				while(board->house_count != 0){
					current_player->account += (board->house_price)/2;
					board->house_count--;
				}
				printf("NEW ACCOUNT AFTER SOLD THE HOUSE(S): %d$ \n\n",current_player->account);
			}
		}
		else printf("You don't have this block !\nPlease try again !! \n\n\n\n");			//if owner has somewhere, this loop continues until he or she sell a block 
	}
	else printf("You have not property !  \n\n\n\n");
	board->owner.type = NOONE;
	board = temp;
	//free(temp);
}


void sell_property(block *board, player* current_player){
	int choice;
	int i;
	int flag = 0;
	block *temp;
	temp = (block*)malloc(sizeof(block));
	temp = board;
	if(show_properties2(board,current_player)){
		do{
			printf("Which property do you sell ? \n");
			scanf("%d",&choice);
			for(i=0;i<choice;++i){
				board = board->next;
			}
			if(board->owner.type == current_player->type){		//type control (CAR or CAP)
				flag = 1;
				current_player->account += (board->price)/2;		//owner earns half price of block 
				board->owner.type = NOONE;
				printf("You sold this place ! \n");
				printf("NEW ACCOUNT : %d$ \n\n",current_player->account);
				for(i=0;i<12;++i){
					if(current_player->owned_block_ids[i] == choice){	
						current_player->owned_block_ids[i] = -1;
					}
				}
				if(board->house_count != 0){				//owner earns half prices of houses if owner has some houses
					while(board->house_count != 0){
						current_player->account += (board->house_price)/2;
						board->house_count--;
					}
					printf("NEW ACCOUNT AFTER SOLD THE HOUSE(S): %d$ \n\n",current_player->account);
				}
			}
			else printf("You don't have this block !\nPlease try again !! \n\n\n\n");
			board = temp;
		}while(flag==0);		//if owner has somewhere, this loop continues until he or she sell a block 
	}
	else printf("You have not property !  \n\n\n\n");
	board = temp;
}

void buy_property_pc(block* current_block,player* current_player){
	int i=0,j;
	int flag = 0;
	current_player->account -= current_block->price;
	while(current_player->owned_block_ids[i] != -1 && i<12){
		i++;
	}
	if(i!=12){
		for(j=0;j<12 && flag == 0;++j){
			if(current_player->owned_block_ids[j] == -1){//checking the empty ones
				current_player->owned_block_ids[j] = current_player->current_block_id;//putting them into owned arrays
				current_block->owner.type = current_player->type;
				flag=1;
			}
		}
		//current_player->owned_block_ids[i] = current_player->current_block_id;
		printf("Computer bought %s ! \n",current_block->name);
		printf("NEW ACCOUNT (COMPUTER) : %d\n\n",current_player->account);
		if(current_player->account >= current_block->house_price){		//money control for house 
			current_block->house_count++;
			current_player->account -= current_block->house_price;
			printf("Computer bought a house !\nNEW ACCOUNT (COMPUTER): %d\n\n",current_player->account);
		}
		else printf("Computer doesn't have money for a house ! \n");
	}
	else printf("Computer doesn't have enough place for this block !! \n");
}


void buy_property(block* current_block,player* current_player){
	int i=0,j;
	int count;
	char choice;
	int flag = 0;
	if(current_block->type == PROPERTY){			//first control is if is the block property
		if(current_block->owner.type == NOONE){	//second control is if is the block's owner noone
			if(current_player->account >= current_block->price){	//money control 
				current_player->account -= current_block->price;
				current_block->owner.type = current_player->type;
				while(current_player->owned_block_ids[i] != -1 && i<12){
					i++;
				}
				if(i!=12){
					for(j=0;j<12 && flag == 0;++j){
						if(current_player->owned_block_ids[j] == -1){//checking the empty ones
							current_player->owned_block_ids[j] = current_player->current_block_id;//putting them into owned arrays
							current_block->owner.type = current_player->type;
							flag=1;
						}
					}
					current_player->owned_block_ids[i] = current_player->current_block_id;
					printf("You bought %s ! \n",current_block->name);
					printf("NEW ACCOUNT : %d\n\n",current_player->account);
					printf("Do you want to buy house ? y:yes n:no \n");
					do{				
						getchar();
						scanf("%c",&choice);
						if(choice == 'y'){
							flag = 1;
							do{
								printf("How many house do you want ? It must be minimum 1 and maximum 3. \n");
								scanf("%d",&count);
							}while(count <1 || count>3);
							if(current_player->account >= count*current_block->house_price){		//money control for house 
								current_block->house_count = count;
								current_player->account -= count*(current_block->house_price);
								printf("You bought %d house !\nNEW ACCOUNT : %d\n\n",count,current_player->account);
							}
							else printf("You don't have money for %d house ! \n",count);
						}
						else if (choice == 'n'){
							printf("You didn't buy house\nNEW ACCOUNT : %d\n\n",current_player->account);
							flag = 1;
						}
						else 	printf("You've entered invalid choice.Please try again ! \n");
					}while(flag == 0);
				}
				else printf("You don't have enough place for this block !! \n");
			}
			else printf("You don't have enough money ! \n");
		}
		else printf("This property has already bought ! \n");
	}
	else printf("This block is not property ! \n");
}

//filling the informations 
void init_the_board(block *board){
	int length;
	block *temp;
	temp = (block*)malloc(sizeof(block));
	temp = board;
	/*for(i=0;i<20;++i){
		board[i].name = (char*)calloc(20,sizeof(char));
	}*/
	board->block_id = 0;
	length = strlen("Start");
	board->name = (char*)malloc(length*sizeof(char));
	strcpy(board->name,"Start");
	board->price = 0;
	board->rent = 0;
	board->rent_1 = 0;
	board->rent_2 = 0;
	board->rent_3 = 0;
	board->house_price = 0;
	board->house_count = 0;
	board->owner.type = NOONE;
	board->type = START;
	board->next = (block*)malloc(sizeof(block));
	board = board->next;

	board->block_id = 1;
	length = strlen("Esenyurt");
	board->name = (char*)malloc(length*sizeof(char));
	strcpy(board->name,"Esenyurt");
	board->price = 16000;
	board->rent = 800;
	board->rent_1 = 4000;
	board->rent_2 = 9000;
	board->rent_3 = 25000;
	board->house_price = 10000;
	board->house_count = 0;
	board->owner.type = NOONE;
	board->type = PROPERTY;
	board->next = (block*)malloc(sizeof(block));
	board = board->next;

	board->block_id = 2;
	length = strlen("Car Park");
	board->name = (char*)malloc(length*sizeof(char));
	strcpy(board->name,"Car Park");
	board->price = 0;
	board->rent = 1500;
	board->rent_1 = 0;
	board->rent_2 = 0;
	board->rent_3 = 0;
	board->house_price = 0;
	board->house_count = 0;
	board->owner.type = NOONE;
	board->type = TAX;
	board->next = (block*)malloc(sizeof(block));
	board = board->next;

	board->block_id = 3;
	length = strlen("Fortune Card");
	board->name = (char*)malloc(length*sizeof(char));
	strcpy(board->name,"Fortune Card");
	board->price = 0;
	board->rent = 0;
	board->rent_1 = 0;
	board->rent_2 = 0;
	board->rent_3 = 0;
	board->house_price = 0;
	board->house_count = 0;
	board->owner.type = NOONE;
	board->type = FORTUNE;
	board->next = (block*)malloc(sizeof(block));
	board = board->next;

	board->block_id = 4;
	length = strlen("Tuzla");
	board->name = (char*)malloc(length*sizeof(char));
	strcpy(board->name,"Tuzla");
	board->name = "Tuzla";
	board->price = 16500;
	board->rent = 850;
	board->rent_1 = 4250;
	board->rent_2 = 9500;
	board->rent_3 = 26000;
	board->house_price = 12000;
	board->house_count = 0;
	board->owner.type = NOONE;
	board->type = PROPERTY;
	board->next = (block*)malloc(sizeof(block));
	board = board->next;

	board->block_id = 5;
	length = strlen("Arnavutkoy");
	board->name = (char*)malloc(length*sizeof(char));
	strcpy(board->name,"Arnavutkoy");
	board->price = 17000;
	board->rent = 875;
	board->rent_1 = 4500;
	board->rent_2 = 10000;
	board->rent_3 = 28000;
	board->house_price = 12000;
	board->house_count = 0;
	board->owner.type = NOONE;
	board->type = PROPERTY;
	board->next = (block*)malloc(sizeof(block));
	board = board->next;

	board->block_id = 6;
	length = strlen("Wait 2 Turn");
	board->name = (char*)malloc(length*sizeof(char));
	strcpy(board->name,"Wait 2 Turn");
	board->price = 0;
	board->rent = 2;
	board->rent_1 = 0;
	board->rent_2 = 0;
	board->rent_3 = 0;
	board->house_price = 0;
	board->house_count = 0;
	board->owner.type = NOONE;
	board->type = PUNISH;
	board->next = (block*)malloc(sizeof(block));
	board = board->next;

	board->block_id = 7;
	length = strlen("Catalca");
	board->name = (char*)malloc(length*sizeof(char));
	strcpy(board->name,"Catalca");
	board->price = 20000;
	board->rent = 1000;
	board->rent_1 = 5000;
	board->rent_2 = 12000;
	board->rent_3 = 30000;
	board->house_price = 13000;
	board->house_count = 0;
	board->owner.type = NOONE;
	board->type = PROPERTY;
	board->next = (block*)malloc(sizeof(block));
	board = board->next;

	board->block_id = 8;
	length = strlen("Beykoz");
	board->name = (char*)malloc(length*sizeof(char));
	strcpy(board->name,"Beykoz");
	board->price = 23000;
	board->rent = 1100;
	board->rent_1 = 5500;
	board->rent_2 = 12500;
	board->rent_3 = 33000;
	board->house_price = 13000;
	board->house_count = 0;
	board->owner.type = NOONE;
	board->type = PROPERTY;
	board->next = (block*)malloc(sizeof(block));
	board = board->next;

	board->block_id = 9;
	length = strlen("Fortune Card");
	board->name = (char*)malloc(length*sizeof(char));
	strcpy(board->name,"Fortune Card");
	board->price = 0;
	board->rent = 0;
	board->rent_1 = 0;
	board->rent_2 = 0;
	board->rent_3 = 0;
	board->house_price = 0;
	board->house_count = 0;
	board->owner.type = NOONE;
	board->type = FORTUNE;
	board->next = (block*)malloc(sizeof(block));
	board = board->next;

	board->block_id = 10;
	length = strlen("Car Fix");
	board->name = (char*)malloc(length*sizeof(char));
	strcpy(board->name,"Car Fix");
	board->price = 0;
	board->rent = 1750;
	board->rent_1 = 0;
	board->rent_2 = 0;
	board->rent_3 = 0;
	board->house_price = 0;
	board->house_count = 0;
	board->owner.type = NOONE;
	board->type = TAX;
	board->next = (block*)malloc(sizeof(block));
	board = board->next;

	board->block_id = 11;
	length = strlen("Maltepe");
	board->name = (char*)malloc(length*sizeof(char));
	strcpy(board->name,"Maltepe");
	board->price = 30000;
	board->rent = 1350;
	board->rent_1 = 7000;
	board->rent_2 = 15000;
	board->rent_3 = 40000;
	board->house_price = 15000;
	board->house_count = 0;
	board->owner.type = NOONE;
	board->type = PROPERTY;
	board->next = (block*)malloc(sizeof(block));
	board = board->next;

	board->block_id = 12;
	length = strlen("Bills");
	board->name = (char*)malloc(length*sizeof(char));
	strcpy(board->name,"Bills");
	board->price = 0;
	board->rent = 2000;
	board->rent_1 = 0;
	board->rent_2 = 0;
	board->rent_3 = 0;
	board->house_price = 0;
	board->house_count = 0;
	board->owner.type = NOONE;
	board->type = TAX;
	board->next = (block*)malloc(sizeof(block));
	board = board->next;

	board->block_id = 13;
	length = strlen("Sisli");
	board->name = (char*)malloc(length*sizeof(char));
	strcpy(board->name,"Sisli");
	board->price = 33000;
	board->rent = 1500;
	board->rent_1 = 8000;
	board->rent_2 = 16000;
	board->rent_3 = 42000;
	board->house_price = 16000;
	board->house_count = 0;
	board->owner.type = NOONE;
	board->type = PROPERTY;
	board->next = (block*)malloc(sizeof(block));
	board = board->next;

	board->block_id = 14;
	length = strlen("Oil");
	board->name = (char*)malloc(length*sizeof(char));
	strcpy(board->name,"Oil");
	board->price = 0;
	board->rent = 2250;
	board->rent_1 = 0;
	board->rent_2 = 0;
	board->rent_3 = 0;
	board->house_price = 0;
	board->house_count = 0;
	board->owner.type = NOONE;
	board->type = TAX;
	board->next = (block*)malloc(sizeof(block));
	board = board->next;

	board->block_id = 15;
	length = strlen("Fortune Card");
	board->name = (char*)malloc(length*sizeof(char));
	strcpy(board->name,"Fortune Card");
	board->price = 0;
	board->rent = 0;
	board->rent_1 = 0;
	board->rent_2 = 0;
	board->rent_3 = 0;
	board->house_price = 0;
	board->house_count = 0;
	board->owner.type = NOONE;
	board->type = FORTUNE;
	board->next = (block*)malloc(sizeof(block));
	board = board->next;

	board->block_id = 16;
	length = strlen("Atasehir");
	board->name = (char*)malloc(length*sizeof(char));
	strcpy(board->name,"Atasehir");
	board->price = 35000;
	board->rent = 1600;
	board->rent_1 = 8500;
	board->rent_2 = 17000;
	board->rent_3 = 45000;
	board->house_price = 17000;
	board->house_count = 0;
	board->owner.type = NOONE;
	board->type = PROPERTY;
	board->next = (block*)malloc(sizeof(block));
	board = board->next;

	board->block_id = 17;
	length = strlen("Sariyer");
	board->name = (char*)malloc(length*sizeof(char));
	strcpy(board->name,"Sariyer");
	board->price = 40000;
	board->rent = 1750;
	board->rent_1 = 9500;
	board->rent_2 = 19000;
	board->rent_3 = 48000;
	board->house_price = 19000;
	board->house_count = 0;
	board->owner.type = NOONE;
	board->type = PROPERTY;
	board->next = (block*)malloc(sizeof(block));
	board = board->next;

	board->block_id = 18;
	length = strlen("Wait 1 Turn");
	board->name = (char*)malloc(length*sizeof(char));
	strcpy(board->name,"Wait 1 Turn");
	board->price = 0;
	board->rent = 1;
	board->rent_1 = 0;
	board->rent_2 = 0;
	board->rent_3 = 0;
	board->house_price = 0;
	board->house_count = 0;
	board->owner.type = NOONE;
	board->type = PUNISH;
	board->next = (block*)malloc(sizeof(block));
	board = board->next;

	board->block_id = 19;
	length = strlen("Kadikoy");
	board->name = (char*)malloc(length*sizeof(char));
	strcpy(board->name,"Kadikoy");
	board->price = 43000;
	board->rent = 1900;
	board->rent_1 = 11000;
	board->rent_2 = 21500;
	board->rent_3 = 55000;
	board->house_price = 23000;
	board->house_count = 0;
	board->owner.type = NOONE;
	board->type = PROPERTY;
	board->next = (block*)malloc(sizeof(block));
	board = board->next;

	board->block_id = 20;
	length = strlen("Besiktas");
	board->name = (char*)malloc(length*sizeof(char));
	strcpy(board->name,"Besiktas");
	board->price = 60000;
	board->rent = 2500;
	board->rent_1 = 15000;
	board->rent_2 = 28000;
	board->rent_3 = 60000;
	board->house_price = 30000;
	board->house_count = 0;
	board->owner.type = NOONE;
	board->type = PROPERTY;
	board->next = (block*)malloc(sizeof(block));
	board = board->next;

	board->block_id = 21;
	length = strlen("Fortune Card");
	board->name = (char*)malloc(length*sizeof(char));
	strcpy(board->name,"Fortune Card");
	board->price = 0;
	board->rent = 0;
	board->rent_1 = 0;
	board->rent_2 = 0;
	board->rent_3 = 0;
	board->house_price = 0;
	board->house_count = 0;
	board->owner.type = NOONE;
	board->type = FORTUNE;
	board->next = (block*)malloc(sizeof(block));
	board = board->next;

	board->block_id = 22;
	length = strlen("Vocation");
	board->name = (char*)malloc(length*sizeof(char));
	strcpy(board->name,"Vocation");
	board->price = 0;
	board->rent = 5000;
	board->rent_1 = 0;
	board->rent_2 = 0;
	board->rent_3 = 0;
	board->house_price = 0;
	board->house_count = 0;
	board->owner.type = NOONE;
	board->type = TAX;
	board->next = (block*)malloc(sizeof(block));
	board = board->next;

	board->block_id = 23;
	length = strlen("Bebek");
	board->name = (char*)malloc(length*sizeof(char));
	strcpy(board->name,"Bebek");
	board->price = 70000;
	board->rent = 3500;
	board->rent_1 = 20000;
	board->rent_2 = 35500;
	board->rent_3 = 65000;
	board->house_price = 35000;
	board->house_count = 0;
	board->owner.type = NOONE;
	board->type = PROPERTY;
	board->next = NULL;
	board = temp;
	free(temp);

}


//part 2 
void show_board(block *board,player player_one,player player_two){
	int j,k;
	int upbound ;
	int lowbound;
	block *temp;
	temp = (block*)malloc(23*sizeof(block));
	temp = board;
	printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	int i=0,space_flag=0;
	for (i=0;i<7;i++)
	{
        if (strlen(board->name)<8)
		    printf("|\t%s\t\t",board->name);
        else
            printf("|\t%s\t",board->name);
        board = board->next;
	}
	printf("|\n");
	board = temp;
	for (i=0;i<7;i++)
	{
		if (board->type==PROPERTY) 
		    printf("|\t%d$ \t\t",board->price);
		else if(board->type==TAX)
		    printf("|\t%d$ \t\t",board->rent);
		else if (strlen(board->name)<8)
            printf("|\t     \t\t");
        else
            printf("|\t\t \t");
        board = board->next;
	}
    printf("|\n");
    board = temp;
    for (i=0;i<7;i++)
    {
        space_flag=0;
        printf("|\t");
        if (i==player_one.current_block_id && i==player_two.current_block_id)
        {
            printf("%s, %s \t",player_one.name,player_two.name);
            space_flag=1;
        }
        else {
            if (i == player_one.current_block_id) {
                printf("%s \t\t", player_one.name);
                space_flag = 1;
            }
            if (i == player_two.current_block_id) {
                printf("%s \t\t", player_two.name);
                space_flag = 1;
            }
        }
        if (space_flag==0) {
            if (strlen(board->name)<8)
                printf("     \t\t");
            else
                printf(" \t\t");
        }
        board = board->next;
    }
    printf("|\n");
	printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

	board = temp;
    //Middle
    upbound = 23;
	lowbound = 7;
    for (i=0;i<5;++i){
        //Names
    	for(j=0;j<upbound;++j){
    		board = board->next;
    	}
        if (strlen(board->name)<8)
            printf("|\t%s\t\t|",board->name);
        else
            printf("|\t%s\t|",board->name);
        printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");

        board = temp;
        
        for(k=0;k<lowbound;++k){
        	board = board->next;
        }

        if (strlen(board->name)<8)
            printf("|\t%s\t\t|",board->name);
        else
            printf("|\t%s\t|",board->name);
        printf("\n");

        board = temp;

        //prices
        for(j=0;j<upbound;++j){
    		board = board->next;
    	}
       if (board->type==PROPERTY) 
		    printf("|\t%d$ \t\t",board->price);
		else if(board->type==TAX)
		    printf("|\t%d$ \t\t",board->rent);
		else if (strlen(board->name)<8)
            printf("|\t     \t\t");
        else
            printf("|\t\t \t");

        printf("|");

	    board = temp;

        for(k=0;k<lowbound;++k){
        	board = board->next;
        }

        printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
        if (board->type==PROPERTY) 
		    printf("|\t%d$ \t\t",board->price);
		else if(board->type==TAX)
		    printf("|\t%d$ \t\t",board->rent);
		else if (strlen(board->name)<8)
            printf("|\t     \t\t");
        else
            printf("|\t\t \t");

        printf("|\n");
        
        //spaces

       space_flag=0;
       printf("|\t");
        if (23-i==player_one.current_block_id && 23-i==player_two.current_block_id)
        {
            printf("%s, %s \t|",player_one.name,player_two.name);
            space_flag=1;
        }
        else {
            if (23 - i == player_one.current_block_id) {
                printf("%s \t\t|", player_one.name);
                space_flag = 1;
            }
            if (23 - i == player_two.current_block_id) {
                printf("%s \t\t|", player_two.name);
                space_flag = 1;
            }
        }
        if (space_flag==0) {
            if (strlen(board->name)<8)
                printf("\t\t|");
            else
                printf("           \t|");
        }

        printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
        space_flag=0;
        printf("|\t");
        if (7+i==player_one.current_block_id && 7+i==player_two.current_block_id)
        {
            printf("%s, %s \t",player_one.name,player_two.name);
            space_flag=1;
        }
        else {

            if (7+i==player_one.current_block_id)
            {
                printf("%s \t\t",player_one.name);
                space_flag=1;
            }
            if (7+i==player_two.current_block_id)
            {
                printf("%s \t\t",player_two.name);
                space_flag=1;
            }
        }

        if (space_flag==0) {
            if (strlen(board->name)<8)
                printf("\t\t");
            else
                printf("%16s"," ");
        }

        printf("|\n");
        if (i!=4) {
            printf("-------------------------");
            printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
            printf("-------------------------");
            printf("\n");
        }
        upbound--;
        lowbound++;
 		board = temp;
    }
    upbound = 18;
    //bottom row
	printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    for (i=18;i>=12;i--)
    {
    	board = temp;
    	for(j=0;j<upbound;++j){
    		board = board->next;
    	}
        if (strlen(board->name)<8)
            printf("|\t%s\t\t",board->name);
        else
            printf("|\t%s\t",board->name);
        upbound--;
    }
    printf("|\n");
    upbound = 18;
 	for (i=18;i>=12;i--)
    {
   	    board = temp;

    	for(j=0;j<upbound;++j){
    		board = board->next;
    	}
        if (board->type==PROPERTY) 
		    printf("|\t%d$ \t\t",board->price);
		else if(board->type==TAX)
		    printf("|\t%d$ \t\t",board->rent);
		else if (strlen(board->name)<8)
            printf("|\t     \t\t");
        else
            printf("|\t\t \t");
        upbound--;
    }
    printf("|\n");
    for (i=18;i>=12;i--)
    {
        space_flag=0;
        printf("|\t");
        if (i==player_one.current_block_id && i==player_two.current_block_id)
        {
            printf("%s, %s \t",player_one.name,player_two.name);
            space_flag=1;
        }
        else {
            if (i == player_one.current_block_id) {
                printf("%s \t\t", player_one.name);
                space_flag = 1;
            }
            if (i == player_two.current_block_id) {
                printf("%s \t\t", player_two.name);
                space_flag = 1;
            }
        }
        if (space_flag==0) {
            if (strlen(board->name)<8)
                printf("     \t\t");
            else
                printf(" \t\t");
        }

    }
    printf("|\n");
	printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}
//part 3 
void show_properties(block *board){
	block *temp;
	int choice,i;
	temp = board;

	do{
		printf("Please select a property to see details : \n");
		for(i=0;i<24;++i){
			if(board->type == PROPERTY){
				printf("%d -   %s\n",i,board->name);
			}
			board = board->next;
		}
		printf("0 - Exit\n");
		board = temp;
		scanf("%d",&choice);
		switch(choice){
			case 1:
			case 4:
			case 5:
			case 7:
			case 8:
			case 11:
			case 13:
			case 16:
			case 17:
			case 19:
			case 20: 
			case 23:   	//from 1 to 19 it print same informations.So I didn't put break 
			for(i=0 ; i<choice ; ++i) board = board->next; 
				printf("\n\n\n");
				printf("----------------------------------\n");
				printf("|%25s       |\n",board->name);
				printf("----------------------------------\n");
				printf("|%11s%19d$ |\n","Rent",board->rent);
				printf("|%15s%15d$ |\n","Rent 1 H",board->rent_1);
				printf("|%15s%15d$ |\n","Rent 2 H",board->rent_2);
				printf("|%15s%15d$ |\n","Rent 3 H",board->rent_3);
				printf("----------------------------------\n");
				printf("|%18s%13d$|\n","House Price",board->house_price);
				printf("----------------------------------\n");
				printf("\n\n\n");
				break;
			case 0:
				printf("Exiting...\n");
				break;
			default:
				printf("You've entered invalid value.Please try again !\n\n\n");
				break;
		}
		board = temp;
	}while(choice!=0);
	board = temp;
	//free(temp);
}

int roll_dice(){
    int i=rand()%6+1;
    return i;
}

int find_average(block *board){
	block *temp;
	temp = board ;
	int total;
	int i = 0;
	while(board != NULL){
		if(board->type == PROPERTY){
			total += board->price;
			i++;
		}
		board = board->next;
	}
	board = temp;
	return total / i;

}

void gameplay( block *board, player player_one, player player_two){
	int h_choice;	//in fortune card, to pick a property which he/she wants to build a house on 
	int c;
	int ave;
	int choice,dice;
	int turn=0;
	int count,counter ;
	int i;
	int house ;
	int flag=0;
	char opt;
	ave = find_average(board);
	block *temp1,*temp2,*temp4;
	temp1 = (block*)malloc(sizeof(block));
	temp2 = (block*)malloc(sizeof(block));
	temp4 = (block*)malloc(sizeof(block));
	temp1 = board ;
	temp2 = board ;
	temp4 = board;
	fortune_card *start,* temp3;
	temp3 = (fortune_card*)malloc(sizeof(fortune_card));
	start = (fortune_card*)malloc(sizeof(fortune_card));
	temp3 = start ; 
	for(i=1;i<=5;++i){
		start->card_number = i;
		if(i != 5){
			start->next = (fortune_card*)malloc(sizeof(fortune_card));
			start = start->next;
		} 

	}
	start->next = NULL;
	while(player_one.account >0 && player_two.account >0){
		start = temp3;
		if(turn%2==0) {
			count=0;
			for(i=0;i<12;++i){
				if(player_one.owned_block_ids[i] != -1){
					count++;				//this count is for the which property do you have 
				}
			}
			counter=count;
			if(player_one.turn_to_wait == 0){   	//if player one has not punishment
				printf("%s's TURN ! \n",player_one.name);
				dice=roll_dice();
				printf("Computer rolled dice :  %d \n",dice);
				player_one.current_block_id += dice;
				for(i=0;i<dice;++i){
					temp1 = temp1->next;
					if(temp1 == NULL ){
						temp1 = board;
					}
				}
				printf("----%s----\n",temp1->name );
				if(player_one.current_block_id > 23 ){
					player_one.current_block_id = player_one.current_block_id%24; 
					player_one.account += 10000;
					printf("Computer complete a tour and earned 10000$ ! \n\n");
					printf("ACCOUNT(COMPUTER) : %d \nACCOUNT CAR : %d\n\n",player_one.account,player_two.account );
				}
				show_board(board,player_one,player_two);
				if(temp1->type == FORTUNE){
					dice = 1+rand()%5; //for pick a random card number 
					for(i=1;i<dice;++i){
						start = start->next;
					}
					c = start->card_number;
					switch(c){
						case 1:
							printf("This fortune card is free house ! Computer has a house for free ! \n");
							if(show_properties2(board,&player_one)){
								while(temp4->next != NULL && flag == 0  ){
									if(temp4->owner.type == player_one.type && temp4->house_count != 3){
										buy_house_fortune(temp4,&player_one);
										flag = 1;
									}
									temp4 = temp4->next;
								}
							}
							else printf("You don't have property ! \n");
							flag = 0;
							temp4 = board;
							break;
						case 2:
							printf("This fortune card is time travel ! Computer roll a dice : \n");
							dice = roll_dice();
							printf("Computer rolled dice : %d \n",dice );
							if(dice>= 1 && dice<= 3){
								printf("Computer moves forward 2 block ! \n");
								player_one.current_block_id += 2;
								for(i=0;i<2;++i){
									temp1 = temp1->next;
								}
							}
							else{
								printf("Computer moves backward 2 block ! \n");
								player_one.current_block_id -= 2;
								temp1 = board;
								for(i=0;i<player_one.current_block_id;++i){
									temp1 = temp1->next;
								}
							}
							show_board(board,player_one,player_two);
							break;
						case 3:
							printf("This fortune card is garnishment ! Computer pays 5.000$ to the bank \n");
							if(player_one.account >= 5000 ) player_one.account -= 5000;
							else if(show_properties2(board,&player_one))	sell_property_pc(board,&player_one);
							else player_one.account -= 5000;
							printf("ACCOUNT(COMPUTER) : %d \nACCOUNT CAR : %d\n\n",player_one.account,player_two.account ); 
							break;
						case 4:
							printf("This fortune card is generosity ! Computer pays 10.000$ to the Car :) \n");
							if(player_one.account >= 10000 ) player_one.account -= 10000;
							else if(show_properties2(board,&player_one))	sell_property_pc(board,&player_one);
							else player_one.account -= 10000;
							player_two.account += 10000;
							printf("ACCOUNT(COMPUTER) : %d \nACCOUNT CAR : %d\n\n",player_one.account,player_two.account );
							break;
						case 5:
							printf("This fortune card is treasure hunter ! Computer takes 20.000$ from the bank;\n"); 
							player_one.account += 20000;
							printf("ACCOUNT(COMPUTER) : %d \nACCOUNT CAR : %d\n\n",player_one.account,player_two.account );
							break;
					}
					start = temp3;
				}
				if(temp1->owner.type == NOONE  && temp1->type == PROPERTY && player_one.account >= temp1->price){
					if(temp1->price < ave ){
						buy_property_pc(temp1 , &player_one);
					}
					else{
						dice = roll_dice();
						if(dice >= 1 && dice <= 3){
							printf("\n\n\nThe dice is %d.So the computer bought %s ! \n\n",dice,temp1->name);
							buy_property_pc(temp1,&player_one);
						}
						else{
							printf("\n\n\nThe dice is %d.So the computer didn't buy %s ! \n\n",dice,temp1->name);
						}
					}
				}
				else if(temp1->owner.type == player_one.type){
					if(count >= 4){
						dice = roll_dice();
						if(dice >= 1 && dice <= 3){
							printf("Computer rolled dice : %d \n",dice );
							if(player_one.account >= temp1->house_price){
								player_one.account -= temp1->house_price;
								buy_house(temp1,&player_one);
							}
							else printf("The dice is %d .But computer doesn't have enough money !  \n",dice );
							//printf("\n\n\nThe dice is %d.So the computer bought a house ! \n\n",dice);

						}
						else{
							printf("\n\n\nThe dice is %d.So the computer didn't buy a house ! \n\n",dice);
						}
					}
					else printf("Computer doesn't have 1/3 of all properties.So computer didn't buy a house !  \n"); 
				}
				else if(temp1->type == PUNISH)	player_one.turn_to_wait = temp1->rent ;			//punishment 
				else if(temp1->type == TAX){	//tax control 
					if(player_one.account < temp1->rent){			//money control 
						if(count == 0) player_one.account = 0 ;		//if pc has not property, count  = 0
						else {
							while(count !=0 && player_one.account < temp1->rent){	//if it is not enough,owner has to sell something 
							sell_property_pc(board,&player_one);
							count--;
							}
						}
						if(player_one.account < temp1->rent) player_one.account = 0;	//still if it is not enough, I initialize 0 to finish the game 
						else{
							player_one.account -= temp1->rent;
							printf("Computer paid tax !!\n");
							printf("ACCOUNT(COMPUTER) : %d \nACCOUNT CAR : %d\n\n",player_one.account,player_two.account );
						}
					}
					else{
						player_one.account -= temp1->rent;
						printf("Computer paid tax!!\n");
						printf("ACCOUNT(COMPUTER) : %d \nACCOUNT CAR : %d\n\n",player_one.account,player_two.account );
					}
				}
				else if(temp1->owner.type == CAR ){		//if block's owner is opponent user,this user has to pay tax 
					house = temp1->house_count;							//determines the house numbers 
					if(house == 0){
						if(player_one.account < temp1->rent){			//if money is not enough 
							if(counter == 0) player_one.account = 0 ;									//to finish the game 
							else {
								while(counter !=0 && player_one.account < temp1->rent){		//sell something for tax 
									printf("Computer have to sell something because you doesn't have enough money \n\n");
									sell_property_pc(board,&player_one);
									counter--;
								}
							}
							if(player_one.account < temp1->rent) player_one.account = 0;
							else{
								player_one.account -= temp1->rent;
								player_two.account += temp1->rent;
								printf("Computer paid block rent !!\n");
								printf("ACCOUNT(COMPUTER) : %d \nACCOUNT CAR : %d\n\n",player_one.account,player_two.account );
							}
						}
						else{
							player_one.account -= temp1->rent;
							player_two.account += temp1->rent;
							printf("Computer paid block rent !!\n");
							printf("ACCOUNT(COMPUTER) : %d \nACCOUNT CAR : %d\n\n",player_one.account,player_two.account );
						}
					}
					else if(house == 1){															//same processing but if house is 1 
						if(player_one.account < temp1->rent_1){
							if(counter == 0) player_one.account = 0 ;
							else {
								while(counter !=0 && player_one.account < temp1->rent_1){
									printf("Computer have to sell something because Computer doesn't have enough money \n\n");
									sell_property_pc(board,&player_one);
									counter--;
								}
							}
							if(player_one.account < temp1->rent_1) player_one.account = 0;
							else{
								player_one.account -= temp1->rent_1;
								player_two.account += temp1->rent_1;
								printf("Computer paid block rent !!\n");
								printf("ACCOUNT(COMPUTER) : %d \nACCOUNT CAR : %d\n\n",player_one.account,player_two.account );
							}
						}
						else{
							player_one.account -= temp1->rent_1;
							player_two.account += temp1->rent_1;
							printf("Computer paid block rent !!\n");
							printf("ACCOUNT(COMPUTER) : %d \nACCOUNT CAR : %d\n\n",player_one.account,player_two.account );
						}
					}
					else if(house == 2){															//same processing but if house is 2
						if(player_one.account < temp1->rent_2){
							if(counter == 0) player_one.account = 0 ;
							else {
								while(counter !=0 && player_one.account < temp1->rent_2){
									printf("Computer have to sell something because Computer doesn't have enough money \n\n");
									sell_property_pc(board,&player_one);
									counter--;
								}
							}
							if(player_one.account < temp1->rent_2) player_one.account = 0;
							else{
								player_one.account -= temp1->rent_2;
								player_two.account += temp1->rent_2;
							}
						}
						else{
							player_one.account -= temp1->rent_2;
							player_two.account += temp1->rent_2;
						}
						printf("Computer paid block rent with 2 houses !!\n");
						printf("ACCOUNT(COMPUTER) : %d \nACCOUNT CAR : %d\n\n",player_one.account,player_two.account );
					}
					else if(house == 3){															//same processing but if house is 3
						if(player_one.account < temp1->rent_3){
							if(counter == 0) player_one.account = 0 ;
							else {
								while(counter !=0 && player_one.account < temp1->rent_3){
									printf("Computer have to sell something because Computer doesn't have enough money \n\n");
									sell_property_pc(board,&player_one);
									counter--;
								}
							}
							if(player_one.account < temp1->rent_3) player_one.account = 0;
							else{
								player_one.account -= temp1->rent_3;
								player_two.account += temp1->rent_3;
								printf("Computer paid block rent !!\n");
								printf("ACCOUNT(COMPUTER) : %d \nACCOUNT CAR : %d\n\n",player_one.account,player_two.account );
							}
						}
						else{
							player_one.account -= temp1->rent_3;
							player_two.account += temp1->rent_3;
							printf("Computer paid block rent !!\n");
							printf("ACCOUNT(COMPUTER) : %d \nACCOUNT CAR : %d\n\n",player_one.account,player_two.account );
						}
					}
				}
				
				//show_board(board,player_one,player_two);
			}
			else{ 		//if player one has punishment
				printf("\n\n\nYou have to wait %d more turn %s ! \n\n\n",player_one.turn_to_wait,player_one.name);
				player_one.turn_to_wait--;
			}
			turn++;
		}
		else if(turn%2==1){
			count=0;
			start = temp3;
			for(i=0;i<12;++i){
				if(player_two.owned_block_ids[i] != -1){
					count++;
				}
			}
			counter = count ;
			if(player_two.turn_to_wait == 0){		//if player one has not punishment
				printf("%s's TURN ! \n",player_two.name);
				printf("1-Roll the dice \n");
				printf("2-Show my account\n");
				printf("3-Show my properties\n");
				printf("4-Show property deeds\n");
				printf("5-Buy property\n");
				printf("6-Buy house\n");
				printf("7-Sell property\n");
				printf("8-Show computer's properties \n");
				printf("Please select an option to continue : ");
				scanf("%d",&choice);
				switch(choice){
					case 1:
						dice=1+rand()%6;
						printf("The dice is %d \n",dice);
						player_two.current_block_id += dice;
						for(i=0;i<dice;++i){
							temp2 = temp2->next;
							if(temp2 == NULL ){
								temp2 = board;
							}
						}
						printf("-----%s----\n",temp2->name );
						if(player_two.current_block_id > 23 ){
							player_two.current_block_id = player_two.current_block_id%24;
							player_two.account += 10000;
							printf("You complete a tour and earned 10000$ ! \n\n");
							//temp2 = board;
						}
						show_board(board,player_one,player_two);
						if(temp2->type == FORTUNE){
							dice = 1+rand()%5; //for pick a random card number 
							for(i=1;i<dice;++i){
								start = start->next;
							}
							c = start->card_number;
							switch(c){
								case 1:

									printf("This fortune card is free house ! You have a house for free ! Which propertiey do you build house \n");
									if(show_properties2(board,&player_two)){
										while(flag == 0){
											scanf("%d",&h_choice);
											for(i=0;i<h_choice;++i){
												temp4 = temp4->next;
											}
											if(temp4->owner.type == player_two.type){
												flag =1;
												buy_house_fortune(temp4,&player_two);
											}
											else printf("You've entered choice ! \n\n");
											temp4 = board;
										}
									}
									else printf("You don't have property ! \n");
									flag = 0;
									temp4 = board;
									break;
								case 2:
									printf("This fortune card is time travel ! You rolled a dice : \n");
									dice = roll_dice();
									printf("You rolled dice : %d \n",dice );
									if(dice>= 1 && dice<= 3){
										printf("You moves forward 2 block ! \n");
										player_two.current_block_id += 2;
										for(i=0;i<2;++i){
											temp2 = temp2->next;
										}
									}
									else{
										printf("You moves backward 2 block ! \n");
										player_two.current_block_id -= 2;
										temp2 = board;
										for(i=0;i<player_two.current_block_id;++i){
											temp2 = temp2->next;
										}
									}
									show_board(board,player_one,player_two);	
									break;
								case 3:
									printf("This fortune card is garnishment ! You pay 5.000$ to the bank \n");
									if(player_two.account >= 5000) player_two.account -= 5000;
									else if(show_properties2(board,&player_two))	sell_property(board,&player_two);
									else player_two.account -= 5000;
									printf("ACCOUNT(COMPUTER) : %d \nACCOUNT CAR : %d\n\n",player_one.account,player_two.account ); 
									break;
								case 4:
									printf("This fortune card is generosity ! You pay 10.000$ to the computer :) \n");
									if(player_two.account >= 10000) player_two.account -= 10000;
									else if(show_properties2(board,&player_two))	sell_property(board,&player_two);
									else player_two.account -= 10000;
									player_one.account += 10000;
									printf("ACCOUNT(COMPUTER) : %d \nACCOUNT CAR : %d\n\n",player_one.account,player_two.account );
									break;
								case 5:
									printf("This fortune card is treasure hunter ! You take 20.000$ from the bank;\n"); 
									player_two.account += 20000;
									printf("ACCOUNT(COMPUTER) : %d \nACCOUNT CAR : %d\n\n",player_one.account,player_two.account );
									break;
							}
							start = temp3;
						}
						if(temp2->owner.type == NOONE && temp2->type == PROPERTY && player_two.account >= temp2->price){
							printf("Do you want to buy a property? y:Yes n:No \n");
							do{				
								//getchar();
								scanf(" %c",&opt);
								if(opt == 'y'){
								flag = 1;
								buy_property(temp2,&player_two);
								}				
								else if (opt == 'n'){
									printf("You didn't buy property\n\n\n");
									flag = 1;
								}
								else 	printf("You've entered invalid choice.Please try again ! \n");
							}while(flag == 0);
							flag=0;
						}
						else if(temp2->owner.type == player_two.type && player_two.account >= temp2->house_price){
							printf("Do you want to buy a house? y:Yes n:No \n");
							do{				
								//getchar();
								scanf(" %c",&opt);
								if(opt == 'y'){
								flag = 1;
								buy_house(temp2,&player_two);
								}				
								else if (opt == 'n'){
									printf("You didn't buy house ! \n\n\n");
									flag = 1;
								}
								else 	printf("You've entered invalid choice.Please try again ! \n");
							}while(flag == 0);
							flag=0;
						}
						else if(temp2->type == PUNISH)	player_two.turn_to_wait = temp2->rent ;			//punishment 
						else if(temp2->type == TAX ){
							if(player_two.account < temp2->rent){
								if(count == 0) player_two.account = 0 ;
								else {
									while(count !=0 && player_two.account < temp2->rent){
										printf("You have to sell something because you don't have enough money \n\n");
										sell_property(board,&player_two);
										count--;
									}
								}
								if(player_two.account < temp2->rent) player_two.account = 0;
								else{
									player_two.account -= temp2->rent;
									printf("You paid tax!!\n");
									printf("ACCOUNT(COMPUTER) : %d \nACCOUNT CAR : %d\n\n",player_one.account,player_two.account );
								}
							}
							else{
								player_two.account -= temp2->rent;
								printf("You paid tax!!\n");
								printf("ACCOUNT(COMPUTER) : %d \nACCOUNT CAR : %d\n\n",player_one.account,player_two.account );
							}
						}
						else if(temp2->owner.type == CAP ){
							house = temp2->house_count;
							if(house == 0){
								if(player_two.account < temp2->rent){
									if(counter == 0) player_two.account = 0 ;
									else {
										while(counter !=0 && player_two.account < temp2->rent){
											printf("You have to sell something because you don't have enough money \n\n");
											sell_property(board,&player_two);
											counter--;
										}
									}
									if(player_two.account < temp2->rent) player_two.account = 0;
									else{
										player_two.account -= temp2->rent;
										player_one.account += temp2->rent;
										printf("You paid block rent !!\n");
										printf("ACCOUNT(COMPUTER) : %d \nACCOUNT CAR : %d\n\n",player_one.account,player_two.account );
									}
								}
								else{
									player_two.account -= temp2->rent;
									player_one.account += temp2->rent;
									printf("You paid block rent !!\n");
									printf("ACCOUNT(COMPUTER) : %d \nACCOUNT CAR : %d\n\n",player_one.account,player_two.account );
								}
							}
							else if(house == 1){
								if(player_two.account < temp2->rent_1){
									if(counter == 0) player_two.account = 0 ;
									else {
										while(counter !=0 && player_two.account < temp2->rent_1){
											printf("You have to sell something because you don't have enough money \n\n");
											sell_property(board,&player_two);
											counter--;
										}
									}
									if(player_two.account < board[player_two.current_block_id].rent_1) player_two.account = 0;
									else{
										player_two.account -= temp2->rent_1;
										player_one.account += temp2->rent_1;
										printf("You paid block rent with 1 house !!\n");
										printf("ACCOUNT(COMPUTER) : %d \nACCOUNT CAR : %d\n\n",player_one.account,player_two.account );
									}
								}
								else{
									player_two.account -= temp2->rent_1;
									player_one.account += temp2->rent_1;
									printf("You paid block rent with 1 house !!\n");
									printf("ACCOUNT(COMPUTER) : %d \nACCOUNT CAR : %d\n\n",player_one.account,player_two.account );
								}
							}
							else if(house == 2){
								if(player_two.account < temp2->rent_2){
									if(counter == 0) player_two.account = 0 ;
									else {
										while(counter !=0 && player_two.account < temp2->rent_2){
											printf("You have to sell something because you don't have enough money \n\n");
											sell_property(board,&player_two);
											counter--;
										}
									}
									if(player_two.account < temp2->rent_2) player_two.account = 0;
									else{
										player_two.account -= temp2->rent_2;
										player_one.account += temp2->rent_2;
										printf("You paid block rent with 2 house !!\n");
										printf("ACCOUNT(COMPUTER) : %d \nACCOUNT CAR : %d\n\n",player_one.account,player_two.account );
									}
								}
								else{
									player_two.account -= temp2->rent_2;
									player_one.account += temp2->rent_2;
									printf("You paid block rent with 2 house !!\n");
									printf("ACCOUNT(COMPUTER) : %d \nACCOUNT CAR : %d\n\n",player_one.account,player_two.account );
								}
							}
							else if(house == 3){
								if(player_two.account < temp2->rent_3){
									if(counter == 0) player_two.account = 0 ;
									else {
										while(counter !=0 && player_two.account < temp2->rent_3){
											printf("You have to sell something because you don't have enough money \n\n");
											sell_property(board,&player_two);
											counter--;
										}
									}
									if(player_two.account < temp2->rent_3) player_two.account = 0;
									else{
										player_two.account -= temp2->rent_3;
										player_one.account += temp2->rent_3;
										printf("You paid block rent with 3 house !!\n");
										printf("ACCOUNT(COMPUTER) : %d \nACCOUNT CAR : %d\n\n",player_one.account,player_two.account );
									}
								}
								else{
									player_two.account -= temp2->rent_3;
									player_one.account += temp2->rent_3;
									printf("You paid block rent with 3 house !!\n");
									printf("ACCOUNT(COMPUTER) : %d \nACCOUNT CAR : %d\n\n",player_one.account,player_two.account );
								}
							}
						}
						
						//show_board(board,player_one,player_two);	
						break;
					case 2:
						printf("Your account is %d$ \n",player_two.account);
						printf("CAP's account is %d \n\n",player_one.account );
						turn--;
						break;
					case 3:
						if(show_properties2(board,&player_two) == 0) printf("You have not properties ! \n\n");
						turn--;
						break;
					case 4:
						show_properties(board);
						turn--;
						break;
					case 5:
						buy_property(board,&player_two);
						turn--;
						break;
					case 6:
						if(player_two.account >= temp2->house_price){
							buy_house(temp2,&player_two);
						}
						else printf("You don't have enough money ! \n");
						turn--;
						break;
					case 7:
						sell_property(board,&player_two);
						turn--;
						break;
					case 8:
						if(show_properties2(board,&player_one) == 0) printf("You have not properties ! \n");
						turn--;
						break;
					default:
						printf("You've entered invalid choice ! \n");
						turn--;
						break;
					}
			}
			else{			//if player one has punishment
				printf("\n\n\nYou have to wait %d more turn %s ! \n\n\n",player_two.turn_to_wait,player_two.name);
				player_two.turn_to_wait--;
			}
			turn++;
		}
	}
	if(player_one.account <= 0) printf("\n\n\nGAME OVER !! \n%s WIN ! \n\n",player_two.name); 	//print the winner
	else printf("\n\n\nGAME OVER !! \n%s WIN ! \n\n",player_one.name); 		
	printf("%s'S ACCOUNT : %d\n",player_one.name,player_one.account);							//print the accounts 
	printf("%s'S ACCOUNT : %d\n",player_two.name,player_two.account);
	/*free(temp1);
	free(temp2);
	free(temp3);
	free(temp4);
	free(start);*/
}
