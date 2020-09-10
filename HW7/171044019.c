//171044019 EMİRHAN UZUN //
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


typedef enum {
	NOONE,CAP,CAR
}player_type;

typedef enum {
	START,PROPERTY,TAX,PUNISH
}block_type;

typedef struct {
	player_type type;
	int current_block_id;
	int owned_block_ids[12];
	int account;
	int turn_to_wait;
	char *name;
}player;

typedef struct {
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
}block;


void init_the_board( block board[20]);
void show_board(block board[20], player player_one,player player_two);
void show_properties(block board[20]);
void gameplay( block board[20], player player_one, player player_two);
void buy_property(block* current_block,player* current_player);
void sell_property(block board[20], player* current_player);
void buy_house(block board[20],player *current_player);
int show_properties2(block board[20],player *current_player);


int main(){
	int i;
	srand(time(NULL));
	block board[20];
	player player_one;
	player_one.type = CAP;
	player_one.current_block_id = 0;
	player_one.account = 100000;
	player_one.turn_to_wait = 0;
	for(i=0;i<12;++i){		//filling the array with -1 (It means these elements are empty)
		player_one.owned_block_ids[i] = -1;
	}
	player_one.name = "Cap";
	player player_two;
	player_two.type = CAR;
	player_two.current_block_id = 0;
	player_two.account = 100000;
	player_two.turn_to_wait = 0;
	for(i=0;i<12;++i){		//filling the array with -1 (It means these elements are empty)
		player_two.owned_block_ids[i] = -1;
	}
	player_two.name = "Car";
	init_the_board(board);
	show_board(board,player_one,player_two);
	gameplay(board, player_one, player_two);
	/*for(i=0;i<20;++i){	
		free(board[i].name);
	}*/
	return 0;
}

void buy_house(block board[20],player *current_player){
	if(board[current_player->current_block_id].owner.type == current_player->type){		//owner type control
		if(current_player->account >= board[current_player->current_block_id].house_price){		//money control 
			if(board[current_player->current_block_id].house_count != 3){
				board[current_player->current_block_id].house_count++;
				current_player->account -= board[current_player->current_block_id].house_price;
				printf("You bought a house ! \n");
			}
			else printf("You've 3 house.You can't buy more houses ! \n");
		}
		else printf("You don't have enough money ! \n");
	}
	else printf("This block is not yours ! \n");
}

int show_properties2(block board[20],player *current_player){
	int i,count=0;
	for(i=0;i<12;++i){
		if(current_player->owned_block_ids[i] != -1){		//if the array elements if not -1 , it will be printed .
			printf("%d - %s \n",current_player->owned_block_ids[i],board[current_player->owned_block_ids[i]].name);
			count++;
		}
	}
	printf("\n\n");
	return count;
}

void sell_property(block board[20], player* current_player){
	int choice;
	int i;
	int flag = 0;
	if(show_properties2(board,current_player)){
		do{
			printf("Which property do you sell ? \n");
			scanf("%d",&choice);
			if(board[choice].owner.type == current_player->type){		//type control (CAR or CAP)
				flag = 1;
				current_player->account += (board[choice].price)/2;		//owner earns half price of block 
				board[choice].owner.type = NOONE;
				printf("You sold this place ! \n");
				printf("NEW ACCOUNT : %d$ \n\n",current_player->account);
				for(i=0;i<12;++i){
					if(current_player->owned_block_ids[i] == choice){	
						current_player->owned_block_ids[i] = -1;
					}
				}
				if(board[choice].house_count != 0){				//owner earns half prices of houses if owner has some houses
					while(board[choice].house_count != 0){
						current_player->account += (board[choice].house_price)/2;
						board[choice].house_count--;
					}
					printf("NEW ACCOUNT AFTER SOLD THE HOUSE(S): %d$ \n\n",current_player->account);
				}
			}
			else printf("You don't have this block !\nPlease try again !! \n\n\n\n");
		}while(flag==0);		//if owner has somewhere, this loop continues until he or she sell a block 
	}
	else printf("You have not property !  \n\n\n\n");


}


void buy_property(block* current_block,player* current_player){
	int i=0;
	int count;
	char choice;
	int flag = 0;
	if(current_block[current_player->current_block_id].type == PROPERTY){			//first control is if is the block property
		if(current_block[current_player->current_block_id].owner.type == NOONE){	//second control is if is the block's owner noone
			if(current_player->account >= current_block[current_player->current_block_id].price){	//money control 
				current_player->account -= current_block[current_player->current_block_id].price;
				current_block[current_player->current_block_id].owner.type = current_player->type;
				while(current_player->owned_block_ids[i] != -1 && i<12){
					i++;
				}
				if(i!=12){
					current_player->owned_block_ids[i] = current_player->current_block_id;
					printf("You bought this place ! \n");
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
							if(current_player->account >= count*current_block[current_player->current_block_id].house_price){		//money control for house 
								current_block[current_player->current_block_id].house_count = count;
								current_player->account -= count*(current_block[current_player->current_block_id].house_price);
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
void init_the_board(block board[20]){
	int i;
	/*for(i=0;i<20;++i){
		board[i].name = (char*)calloc(20,sizeof(char));
	}*/
	board[0].block_id = 0;
	board[0].name = "Start";
	board[0].price = 0;
	board[0].rent = 0;
	board[0].rent_1 = 0;
	board[0].rent_2 = 0;
	board[0].rent_3 = 0;
	board[0].house_price = 0;
	board[0].house_count = 0;
	board[0].owner.type = NOONE;
	board[0].type = START;

	board[1].block_id = 1;
	board[1].name = "Esenyurt";
	board[1].price = 16000;
	board[1].rent = 800;
	board[1].rent_1 = 4000;
	board[1].rent_2 = 9000;
	board[1].rent_3 = 25000;
	board[1].house_price = 10000;
	board[1].house_count = 0;
	board[1].owner.type = NOONE;
	board[1].type = PROPERTY;

	board[2].block_id = 2;
	board[2].name = "Car Park";
	board[2].price = 0;
	board[2].rent = 1500;
	board[2].rent_1 = 0;
	board[2].rent_2 = 0;
	board[2].rent_3 = 0;
	board[2].house_price = 0;
	board[2].house_count = 0;
	board[2].owner.type = NOONE;
	board[2].type = TAX;

	board[3].block_id = 3;
	board[3].name = "Tuzla";
	board[3].price = 16500;
	board[3].rent = 850;
	board[3].rent_1 = 4250;
	board[3].rent_2 = 9500;
	board[3].rent_3 = 26000;
	board[3].house_price = 12000;
	board[3].house_count = 0;
	board[3].owner.type = NOONE;
	board[3].type = PROPERTY;

	board[4].block_id = 4;
	board[4].name = "Arnavutkoy";
	board[4].price = 17000;
	board[4].rent = 875;
	board[4].rent_1 = 4500;
	board[4].rent_2 = 10000;
	board[4].rent_3 = 28000;
	board[4].house_price = 12000;
	board[4].house_count = 0;
	board[4].owner.type = NOONE;
	board[4].type = PROPERTY;

	board[5].block_id = 5;
	board[5].name = "Wait 2 Turn";
	board[5].price = 0;
	board[5].rent = 2;
	board[5].rent_1 = 0;
	board[5].rent_2 = 0;
	board[5].rent_3 = 0;
	board[5].house_price = 0;
	board[5].house_count = 0;
	board[5].owner.type = NOONE;
	board[5].type = PUNISH;

	board[6].block_id = 6;
	board[6].name = "Catalca";
	board[6].price = 20000;
	board[6].rent = 1000;
	board[6].rent_1 = 5000;
	board[6].rent_2 = 12000;
	board[6].rent_3 = 30000;
	board[6].house_price = 13000;
	board[6].house_count = 0;
	board[6].owner.type = NOONE;
	board[6].type = PROPERTY;

	board[7].block_id = 7;
	board[7].name = "Beykoz";
	board[7].price = 23000;
	board[7].rent = 1100;
	board[7].rent_1 = 5500;
	board[7].rent_2 = 12500;
	board[7].rent_3 = 33000;
	board[7].house_price = 13000;
	board[7].house_count = 0;
	board[7].owner.type = NOONE;
	board[7].type = PROPERTY;

	board[8].block_id = 8;
	board[8].name = "Car Fix";
	board[8].price = 0;
	board[8].rent = 1750;
	board[8].rent_1 = 0;
	board[8].rent_2 = 0;
	board[8].rent_3 = 0;
	board[8].house_price = 0;
	board[8].house_count = 0;
	board[8].owner.type = NOONE;
	board[8].type = TAX;

	board[9].block_id = 9;
	board[9].name = "Maltepe";
	board[9].price = 30000;
	board[9].rent = 1350;
	board[9].rent_1 = 7000;
	board[9].rent_2 = 15000;
	board[9].rent_3 = 40000;
	board[9].house_price = 15000;
	board[9].house_count = 0;
	board[9].owner.type = NOONE;
	board[9].type = PROPERTY;

	board[10].block_id = 10;
	board[10].name = "Bills";
	board[10].price = 0;
	board[10].rent = 2000;
	board[10].rent_1 = 0;
	board[10].rent_2 = 0;
	board[10].rent_3 = 0;
	board[10].house_price = 0;
	board[10].house_count = 0;
	board[10].owner.type = NOONE;
	board[10].type = TAX;

	board[11].block_id = 11;
	board[11].name = "Sisli";
	board[11].price = 33000;
	board[11].rent = 1500;
	board[11].rent_1 = 8000;
	board[11].rent_2 = 16000;
	board[11].rent_3 = 42000;
	board[11].house_price = 16000;
	board[11].house_count = 0;
	board[11].owner.type = NOONE;
	board[11].type = PROPERTY;

	board[12].block_id = 12;
	board[12].name = "Oil";
	board[12].price = 0;
	board[12].rent = 2250;
	board[12].rent_1 = 0;
	board[12].rent_2 = 0;
	board[12].rent_3 = 0;
	board[12].house_price = 0;
	board[12].house_count = 0;
	board[12].owner.type = NOONE;
	board[12].type = TAX;

	board[13].block_id = 13;
	board[13].name = "Atasehir";
	board[13].price = 35000;
	board[13].rent = 1600;
	board[13].rent_1 = 8500;
	board[13].rent_2 = 17000;
	board[13].rent_3 = 45000;
	board[13].house_price = 17000;
	board[13].house_count = 0;
	board[13].owner.type = NOONE;
	board[13].type = PROPERTY;

	board[14].block_id = 14;
	board[14].name = "Sariyer";
	board[14].price = 40000;
	board[14].rent = 1750;
	board[14].rent_1 = 9500;
	board[14].rent_2 = 19000;
	board[14].rent_3 = 48000;
	board[14].house_price = 19000;
	board[14].house_count = 0;
	board[14].owner.type = NOONE;
	board[14].type = PROPERTY;

	board[15].block_id = 15;
	board[15].name = "Wait 1 Turn";
	board[15].price = 0;
	board[15].rent = 1;
	board[15].rent_1 = 0;
	board[15].rent_2 = 0;
	board[15].rent_3 = 0;
	board[15].house_price = 0;
	board[15].house_count = 0;
	board[15].owner.type = NOONE;
	board[15].type = PUNISH;

	board[16].block_id = 16;
	board[16].name = "Kadikoy";
	board[16].price = 43000;
	board[16].rent = 1900;
	board[16].rent_1 = 11000;
	board[16].rent_2 = 21500;
	board[16].rent_3 = 55000;
	board[16].house_price = 23000;
	board[16].house_count = 0;
	board[16].owner.type = NOONE;
	board[16].type = PROPERTY;

	board[17].block_id = 17;
	board[17].name = "Besiktas";
	board[17].price = 60000;
	board[17].rent = 2500;
	board[17].rent_1 = 15000;
	board[17].rent_2 = 28000;
	board[17].rent_3 = 60000;
	board[17].house_price = 30000;
	board[17].house_count = 0;
	board[17].owner.type = NOONE;
	board[17].type = PROPERTY;

	board[18].block_id = 18;
	board[18].name = "Vocation";
	board[18].price = 0;
	board[18].rent = 5000;
	board[18].rent_1 = 0;
	board[18].rent_2 = 0;
	board[18].rent_3 = 0;
	board[18].house_price = 0;
	board[18].house_count = 0;
	board[18].owner.type = NOONE;
	board[18].type = TAX;

	board[19].block_id = 19;
	board[19].name = "Bebek";
	board[19].price = 70000;
	board[19].rent = 3500;
	board[19].rent_1 = 20000;
	board[19].rent_2 = 35500;
	board[19].rent_3 = 65000;
	board[19].house_price = 35000;
	board[19].house_count = 0;
	board[19].owner.type = NOONE;
	board[19].type = PROPERTY;

}
//part 2 
void show_board(block board[20],player player_one,player player_two){
	char show[25][145];
	int i,j,k=0,l=0;
	int m=0;
	block temp[20];
	//filling the array elements with whitespace 
	for(i=0;i<25;++i){
		for(j=0;j<145;++j){
			show[i][j] = ' ';
		} 
	}
	//assign to the temp array 
	for(i=0;i<20;++i){
		temp[i].price = board[i].price;
		temp[i].rent = board[i].rent;
	}
	//block drawing loop
	for(i=0;i<25;++i){
		for(j=0;j<145;++j){
			if(i%4==0){
				if(i<5  || i>19) show[i][j] = '-';
				else{
					if(j<25 || j>119) show[i][j] = '-';
				}
			}
			else if(i%4!=0){
				if(j%24==0){
					if(i<4 || i>19){
						if(j%24==0) show[i][j] = '|';
					}
					else {
						if(j%24==0 && (j< 30 || j>119)) show[i][j] = '|';	
					}
				}
			}
		}
	}
	//Names printing
	//first row
	for(i=1,j=8;j<145;j+=24){
		m=j;
		while(board[k].name[l] != '\0'){
			show[i][m] = board[k].name[l];
			l++;
			m++;
		}
		l=0;
		k++;
	}
	l=0;
	k=19;
	//first column names printing
	for(i=5;i<21;i+=4){
		for(j=8;j<20;j+=20){
			m=j;
			while(board[k].name[l] != '\0'){
				show[i][m] = board[k].name[l];
				l++;
				m++;
			}
			l=0;
			k--;
		}
	}
	k=6;
	l=0;
	//last column names printing 
	for(i=5;i<21;i+=4){
		for(j=128;j<144;j+=40){
			m=j;
			while(board[k].name[l] != '\0'){
				show[i][m] = board[k].name[l];
				l++;
				m++;
			}
			l=0;
			k++;
		}
	}
	k=15;
	//last row names printing
	for(i=21,j=8;j<145;j+=24){
		m=j;
		while(board[k].name[l] != '\0'){
			show[i][m] = board[k].name[l];
			l++;
			m++;
		}
		l=0;
		k--;
	}
	k=0;
	//Prices
	for(i=2,j=8;j<145;j+=24){
		m=j;
		if(k==0 || k==5) show[i][m+5] = ' ';		//if it is wait turn or start, it will print whitespace
		else show[i][m+5] = '$';					//Else will print $ sign
		if(k!=2 && k!= 5){
			while(temp[k].price > 0){				//This is print char-to-char because I created char array for this part 
			show[i][m+4] =  (temp[k].price)%10+'0';
			temp[k].price/=10;
			m--;
			}
		}
		else if(k!=5){ 
			while(temp[k].rent > 0){
				show[i][m+4] =  (temp[k].rent)%10+'0';
				temp[k].rent/=10;
				m--;
			}
		}
		l=0;
		k++;
	}
	l=0;
	k=19;
	for(i=6;i<21;i+=4){
		for(j=8;j<20;j+=20){
			m=j;
			show[i][m+5] = '$';
		if(k!=18){
			while(temp[k].price > 0){
			show[i][m+4] =  (temp[k].price)%10+'0';
			temp[k].price/=10;
			m--;
			}
		}
		else{
			while(temp[k].rent > 0){
			show[i][m+4] =  (temp[k].rent)%10+'0';
			temp[k].rent/=10;
			m--;
			}
		}
		l=0;
		k--;
		}
	}
	k=6;
	l=0;
	for(i=6;i<21;i+=4){
		for(j=128;j<144;j+=40){
			m=j;
			show[i][m+5] = '$';
		if(k!=8){
			while(temp[k].price > 0){
				show[i][m+4] =  (temp[k].price)%10+'0';
				temp[k].price/=10;
				m--;
			}
		}
		else{
			while(temp[k].rent > 0){
			show[i][m+4] =  (temp[k].rent)%10+'0';
			temp[k].rent/=10;
			m--;
			}
		}
		l=0;
		k++;
		}
	}
	k=15;
	for(i=22,j=8;j<145;j+=24){
		m=j;
		if(board[k].name[0] != 'W') show[i][m+5] = '$';
		if(k!=12 && k!=10){
			while(temp[k].price > 0){
			show[i][m+4] =  (temp[k].price)%10+'0';
			temp[k].price/=10;
			m--;
			}
		}
		else{
			while(temp[k].rent > 0){
			show[i][m+4] =  (temp[k].rent)%10+'0';
			temp[k].rent/=10;
			m--;
			}
		}
		l=0;
		k--;
	}
	l=8;
	//Car cap print 
	for(i=0;i<6;++i){ //control for first row 
		m=0;
		if(player_one.current_block_id == i && player_two.current_block_id == i){  //if there are in same block
			show[3][l] = 'C';
			show[3][l+1] = 'a';
			show[3][l+2] = 'p';
			show[3][l+3] = '-';
			show[3][l+4] = 'C';
			show[3][l+5] = 'a';
			show[3][l+6] = 'r';
		}
		else if(player_one.current_block_id == i && player_two.current_block_id != i){	
			show[3][l] = 'C';
			show[3][l+1] = 'a';
			show[3][l+2] = 'p';
		}
		else if(player_one.current_block_id != i && player_two.current_block_id == i){
			show[3][l] = 'C';
			show[3][l+1] = 'a';
			show[3][l+2] = 'r';
		}
		l+=24;;
	}
	l=8;
	for(i=7,m=19;m>14;--m,i+=4){  //control for the first column 
		if(player_one.current_block_id == m && player_two.current_block_id == m){
			show[i][l] = 'C';
			show[i][l+1] = 'a';
			show[i][l+2] = 'p';
			show[i][l+3] = '-';
			show[i][l+4] = 'C';
			show[i][l+5] = 'a';
			show[i][l+6] = 'r';
		}
		else if(player_one.current_block_id == m && player_two.current_block_id != m){
			show[i][l] = 'C';
			show[i][l+1] = 'a';
			show[i][l+2] = 'p';
		}
		else if(player_one.current_block_id != m && player_two.current_block_id == m){
			show[i][l] = 'C';
			show[i][l+1] = 'a';
			show[i][l+2] = 'r';
		}
	}
	l=130;
	for(i=7,m=6;m<10;++m,i+=4){ 	//control for the last column 
		if(player_one.current_block_id == m && player_two.current_block_id == m){
			show[i][l] = 'C';
			show[i][l+1] = 'a';
			show[i][l+2] = 'p';
			show[i][l+3] = '-';
			show[i][l+4] = 'C';
			show[i][l+5] = 'a';
			show[i][l+6] = 'r';
		}
		else if(player_one.current_block_id == m && player_two.current_block_id != m){
			show[i][l] = 'C';
			show[i][l+1] = 'a';
			show[i][l+2] = 'p';
		}
		else if(player_one.current_block_id != m && player_two.current_block_id == m){
			show[i][l] = 'C';
			show[i][l+1] = 'a';
			show[i][l+2] = 'r';
		}
	}
	l=8;
	for(i=15;i>9;--i){ 	//control for the first row 
		m=0;
		if(player_one.current_block_id == i && player_two.current_block_id == i){
			show[23][l] = 'C';
			show[23][l+1] = 'a';
			show[23][l+2] = 'p';
			show[23][l+3] = '-';
			show[23][l+4] = 'C';
			show[23][l+5] = 'a';
			show[23][l+6] = 'r';
		}
		else if(player_one.current_block_id == i && player_two.current_block_id != i){
			show[23][l] = 'C';
			show[23][l+1] = 'a';
			show[23][l+2] = 'p';
		}
		else if(player_one.current_block_id != i && player_two.current_block_id == i){
			show[23][l] = 'C';
			show[23][l+1] = 'a';
			show[23][l+2] = 'r';
		}
		l+=24;;
	}
	//Print
	for(i=0;i<25;++i){
		for(j=0;j<145;++j){
			printf("%c",show[i][j]);
		}
		printf("\n");
	}
}

//part 3 
void show_properties(block board[20]){
	int choice,i;
	
	do{
		printf("Please select a property to see details : \n");
		for(i=1;i<20;++i){
			if(i!=2 && i!=5 && i!=8 && i!=10 && i!=12 && i!=15 && i!=18){
				printf("%d -   %s\n",i,board[i].name);
			}
		}
		printf("0 - Exit\n");
		scanf("%d",&choice);
		switch(choice){
			case 1:
			case 3:
			case 4:
			case 6:
			case 7:
			case 9:
			case 11:
			case 13:
			case 14:
			case 16:
			case 17: 
			case 19:   	//from 1 to 19 it print same informations.So I didn't put break 
				printf("\n\n\n");
				printf("----------------------------------\n");
				printf("|%25s       |\n",board[choice].name);
				printf("----------------------------------\n");
				printf("|%11s%19d$ |\n","Rent",board[choice].rent);
				printf("|%15s%15d$ |\n","Rent 1 H",board[choice].rent_1);
				printf("|%15s%15d$ |\n","Rent 2 H",board[choice].rent_2);
				printf("|%15s%15d$ |\n","Rent 3 H",board[choice].rent_3);
				printf("----------------------------------\n");
				printf("|%18s%13d$|\n","House Price",board[choice].house_price);
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
	}while(choice!=0);
}

void gameplay( block board[20], player player_one, player player_two){
	int choice,dice;
	int turn=0;
	int count,temp ;
	int i;
	int house ;
	int control = 0,control2=0;
	int flag=0;
	char opt;
	while(player_one.account >0 && player_two.account >0){
		if(turn%2==0) {
			count=0;
			for(i=0;i<12;++i){
				if(player_one.owned_block_ids[i] != -1){
					count++;				//this count is for the which property do you have 
				}
			}
			temp=count;
			if(player_one.turn_to_wait == 0){   	//if player one has not punishment
				printf("%s's TURN ! \n",player_one.name);
				printf("1-Roll the dice \n");
				printf("2-Show my account\n");
				printf("3-Show my properties\n");
				printf("4-Show property deeds\n");
				printf("5-Buy property\n");
				printf("6-Buy house\n");
				printf("7-Sell property\n");
				printf("Please select an option to continue : ");
				scanf("%d",&choice);
				switch(choice){
					case 1:
						dice=1+rand()%6;
						printf("The dice is %d \n",dice);
						player_one.current_block_id += dice;
						if(player_one.current_block_id > 19 ){
							player_one.current_block_id = player_one.current_block_id%20; 
							player_one.account += 10000;
							printf("You complete a tour and earned 10000$ ! \n\n");
						}
						show_board(board,player_one,player_two);
						if(board[player_one.current_block_id].owner.type == player_one.type){
							printf("Do you want to buy a house? y:Yes n:No \n");
							do{				
								//getchar();
								scanf(" %c",&opt);
								if(opt == 'y'){
								flag = 1;
								buy_house(board,&player_one);
								}				
								else if (opt == 'n'){
									printf("You didn't buy house\n\n\n");
									flag = 1;
								}
								else 	printf("You've entered invalid choice.Please try again ! \n");
							}while(flag == 0);
							flag=0;
						}
						else if(board[player_one.current_block_id].owner.type == NOONE  && board[player_one.current_block_id].type == PROPERTY &&player_one.account >= board[player_one.current_block_id].price){
							printf("Do you want to buy this property ?  y:Yes n:No \n");
							do{				
								//getchar();
								scanf(" %c",&opt);
								if(opt == 'y'){
								flag = 1;
								buy_property(board,&player_one);
								}				
								else if (opt == 'n'){
									printf("You didn't buy property\n\n\n");
									flag = 1;
								}
								else 	printf("You've entered invalid choice.Please try again ! \n");
							}while(flag == 0);
							flag=0;
						}
						else if(board[player_one.current_block_id].type == PUNISH)	player_one.turn_to_wait = board[player_one.current_block_id].rent ;			//punishment 
						else if(board[player_one.current_block_id].type == TAX){	//tax control 
							if(player_one.account < board[player_one.current_block_id].rent){			//money control 
								if(count == 0) player_one.account = 0 ;
								else {
									while(count !=0 && player_one.account < board[player_one.current_block_id].rent){	//if it is not enough,owner has to sell something 
									sell_property(board,&player_one);
									count--;
									}
								}
								if(player_one.account < board[player_one.current_block_id].rent) player_one.account = 0;	//still if it is not enough, I initialize 0 to finish the game 
								else{
									player_one.account -= board[player_one.current_block_id].rent;
									printf("You paid tax !!\nNew account : %d$\n\n",player_one.account);
								}
							}
							else{
								player_one.account -= board[player_one.current_block_id].rent;
								printf("You paid tax!!\nNew account : %d$\n\n",player_one.account);
							}
						}
						else if(board[player_one.current_block_id].owner.type == CAR ){		//if block's owner is opponent user,this user has to pay tax 
							house = board[player_one.current_block_id].house_count;							//determines the house numbers 
							if(house == 0){
								if(player_one.account < board[player_one.current_block_id].rent){			//if money is not enough 
									if(temp == 0) player_one.account = 0 ;									//to finish the game 
									else {
										while(temp !=0 && player_one.account < board[player_one.current_block_id].rent){		//sell something for tax 
											printf("You have to sell something because you don't have enough money \n\n");
											sell_property(board,&player_one);
											temp--;
										}
									}
									if(player_one.account < board[player_one.current_block_id].rent) player_one.account = 0;
									else{
										player_one.account -= board[player_one.current_block_id].rent;
										player_two.account += board[player_one.current_block_id].rent;
										printf("You paid block rent !!\nNew account : %d$\n\n",player_one.account);
									}
								}
								else{
									player_one.account -= board[player_one.current_block_id].rent;
									player_two.account += board[player_one.current_block_id].rent;
									printf("You paid block rent !!\nNew account : %d$\n\n",player_one.account);
								}
							}
							else if(house == 1){															//same processing but if house is 1 
								if(player_one.account < board[player_one.current_block_id].rent_1){
									if(temp == 0) player_one.account = 0 ;
									else {
										while(temp !=0 && player_one.account < board[player_one.current_block_id].rent_1){
											printf("You have to sell something because you don't have enough money \n\n");
											sell_property(board,&player_one);
											temp--;
										}
									}
									if(player_one.account < board[player_one.current_block_id].rent_1) player_one.account = 0;
									else{
										player_one.account -= board[player_one.current_block_id].rent_1;
										player_two.account += board[player_one.current_block_id].rent_1;
										printf("You paid block rent !!\nNew account : %d$\n\n",player_one.account);
									}
								}
								else{
									player_one.account -= board[player_one.current_block_id].rent_1;
									player_two.account += board[player_one.current_block_id].rent_1;
									printf("You paid block rent with 1 house !!\nNew account : %d$\n\n",player_one.account);
								}
							}
							else if(house == 2){															//same processing but if house is 2
								if(player_one.account < board[player_one.current_block_id].rent_2){
									if(temp == 0) player_one.account = 0 ;
									else {
										while(temp !=0 && player_one.account < board[player_one.current_block_id].rent_2){
											printf("You have to sell something because you don't have enough money \n\n");
											sell_property(board,&player_one);
											temp--;
										}
									}
									if(player_one.account < board[player_one.current_block_id].rent_2) player_one.account = 0;
									else{
										player_one.account -= board[player_one.current_block_id].rent_2;
										player_two.account += board[player_one.current_block_id].rent_2;
										printf("You paid block rent !!\nNew account : %d$\n\n",player_one.account);
									}
								}
								else{
									player_one.account -= board[player_one.current_block_id].rent_2;
									player_two.account += board[player_one.current_block_id].rent_2;
									printf("You paid block rent with 2 houses!!\nNew account : %d$\n\n",player_one.account);
								}
							}
							else if(house == 3){															//same processing but if house is 3
								if(player_one.account < board[player_one.current_block_id].rent_3){
									if(temp == 0) player_one.account = 0 ;
									else {
										while(temp !=0 && player_one.account < board[player_one.current_block_id].rent_3){
											printf("You have to sell something because you don't have enough money \n\n");
											sell_property(board,&player_one);
											temp--;
										}
									}
									if(player_one.account < board[player_one.current_block_id].rent_3) player_one.account = 0;
									else{
										player_one.account -= board[player_one.current_block_id].rent_3;
										player_two.account += board[player_one.current_block_id].rent_3;
										printf("You paid block rent !!\nNew account : %d$\n\n",player_one.account);
									}
								}
								else{
									player_one.account -= board[player_one.current_block_id].rent_3;
									player_two.account += board[player_one.current_block_id].rent_3;
									printf("You paid block rent with 3 houses !!\nNew account : %d$\n\n",player_one.account);
								}
							}
						}
						break;
					case 2:
						printf("Your account is %d$ \n\n",player_one.account);
						turn--;
						break;
					case 3:
						if(show_properties2(board,&player_one) == 0) printf("You have not properties ! \n");
						turn--;
						break;
					case 4:
						show_properties(board);
						turn--;
						break;
					case 5:
						buy_property(board,&player_one);
						turn--;
						break;
					case 6:
						buy_house(board,&player_one);
						turn--;
						break;
					case 7:
						sell_property(board,&player_one);
						turn--;				
						break;
					default:
						printf("You've entered invalid choice ! \n\n");
						turn--;
						break;	
				}
			}
			else{ 		//if player one has punishment
				printf("\n\n\nYou have to wait %d more turn %s ! \n\n\n",player_one.turn_to_wait,player_one.name);
				player_one.turn_to_wait--;
			}
			turn++;
		}
		else if(turn%2==1){
			count=0;
			for(i=0;i<12;++i){
				if(player_two.owned_block_ids[i] != -1){
					count++;
				}
			}
			temp = count ;
			if(player_two.turn_to_wait == 0){		//if player one has not punishment
				printf("%s's TURN ! \n",player_two.name);
				printf("1-Roll the dice \n");
				printf("2-Show my account\n");
				printf("3-Show my properties\n");
				printf("4-Show property deeds\n");
				printf("5-Buy property\n");
				printf("6-Buy house\n");
				printf("7-Sell property\n");
				printf("Please select an option to continue : ");
				scanf("%d",&choice);
				switch(choice){
					case 1:
						dice=1+rand()%6;
						printf("The dice is %d \n",dice);
						player_two.current_block_id += dice;
						if(player_two.current_block_id > 19 ){
							player_two.current_block_id = player_two.current_block_id%20;
							player_two.account += 10000;
							printf("You complete a tour and earned 10000$ ! \n\n");
						}
						show_board(board,player_one,player_two);
						if(board[player_two.current_block_id].owner.type == player_two.type){
							printf("Do you want to buy a house? y:Yes n:No \n");
							do{				
								//getchar();
								scanf(" %c",&opt);
								if(opt == 'y'){
								flag = 1;
								buy_house(board,&player_two);
								}				
								else if (opt == 'n'){
									printf("You didn't buy house ! \n\n\n");
									flag = 1;
								}
								else 	printf("You've entered invalid choice.Please try again ! \n");
							}while(flag == 0);
							flag=0;
						}
						else if(board[player_two.current_block_id].owner.type == NOONE && board[player_two.current_block_id].type == PROPERTY && player_two.account >= board[player_two.current_block_id].price){
							printf("Do you want to buy a property? y:Yes n:No \n");
							do{				
								//getchar();
								scanf(" %c",&opt);
								if(opt == 'y'){
								flag = 1;
								buy_property(board,&player_two);
								}				
								else if (opt == 'n'){
									printf("You didn't buy property\n\n\n");
									flag = 1;
								}
								else 	printf("You've entered invalid choice.Please try again ! \n");
							}while(flag == 0);
							flag=0;
						}
						else if(board[player_two.current_block_id].type == PUNISH)	player_two.turn_to_wait = board[player_two.current_block_id].rent ;			//punishment 
						else if(board[player_two.current_block_id].type == TAX ){
							if(player_two.account < board[player_two.current_block_id].rent){
								if(count == 0) player_two.account = 0 ;
								else {
									while(count !=0 && player_two.account < board[player_two.current_block_id].rent){
										printf("You have to sell something because you don't have enough money \n\n");
										sell_property(board,&player_two);
										count--;
									}
								}
								if(player_two.account < board[player_two.current_block_id].rent) player_two.account = 0;
								else{
									player_two.account -= board[player_two.current_block_id].rent;
									printf("You paid tax  !!\nNew account : %d$\n\n",player_two.account);
								}
							}
							else{
								player_two.account -= board[player_two.current_block_id].rent;
								printf("You paid tax !!\nNew account : %d$\n\n",player_two.account);
							}
						}
						else if(board[player_two.current_block_id].owner.type == CAP ){
							house = board[player_two.current_block_id].house_count;
							if(house == 0){
								if(player_two.account < board[player_two.current_block_id].rent){
									if(temp == 0) player_two.account = 0 ;
									else {
										while(temp !=0 && player_two.account < board[player_two.current_block_id].rent){
											printf("You have to sell something because you don't have enough money \n\n");
											sell_property(board,&player_two);
											temp--;
										}
									}
									if(player_two.account < board[player_two.current_block_id].rent) player_two.account = 0;
									else{
										player_two.account -= board[player_two.current_block_id].rent;
										player_one.account += board[player_two.current_block_id].rent;
										printf("You paid block rent !!\nNew account : %d$\n\n",player_two.account);
									}
								}
								else{
									player_two.account -= board[player_two.current_block_id].rent;
									player_one.account += board[player_two.current_block_id].rent;
									printf("You paid block rent !!\nNew account : %d$\n\n",player_two.account);
								}
							}
							else if(house == 1){
								if(player_two.account < board[player_two.current_block_id].rent_1){
									if(temp == 0) player_two.account = 0 ;
									else {
										while(temp !=0 && player_two.account < board[player_two.current_block_id].rent_1){
											printf("You have to sell something because you don't have enough money \n\n");
											sell_property(board,&player_two);
											temp--;
										}
									}
									if(player_two.account < board[player_two.current_block_id].rent_1) player_two.account = 0;
									else{
										player_two.account -= board[player_two.current_block_id].rent_1;
										player_one.account += board[player_two.current_block_id].rent_1;
										printf("You paid block rent !!\nNew account : %d$\n\n",player_two.account);
									}
								}
								else{
									player_two.account -= board[player_two.current_block_id].rent_1;
									player_one.account += board[player_two.current_block_id].rent_1;
									printf("You paid block rent with 1 house !!\nNew account : %d$\n\n",player_two.account);
								}
							}
							else if(house == 2){
								if(player_two.account < board[player_two.current_block_id].rent_2){
									if(temp == 0) player_two.account = 0 ;
									else {
										while(temp !=0 && player_two.account < board[player_two.current_block_id].rent_2){
											printf("You have to sell something because you don't have enough money \n\n");
											sell_property(board,&player_two);
											temp--;
										}
									}
									if(player_two.account < board[player_two.current_block_id].rent_2) player_two.account = 0;
									else{
										player_two.account -= board[player_two.current_block_id].rent_2;
										player_one.account += board[player_two.current_block_id].rent_2;
										printf("You paid block rent !!\nNew account : %d$\n\n",player_two.account);
									}
								}
								else{
									player_two.account -= board[player_two.current_block_id].rent_2;
									player_one.account += board[player_two.current_block_id].rent_2;
									printf("You paid block rent with 2 houses!!\nNew account : %d$\n\n",player_two.account);
								}
							}
							else if(house == 3){
								if(player_two.account < board[player_two.current_block_id].rent_3){
									if(temp == 0) player_two.account = 0 ;
									else {
										while(temp !=0 && player_two.account < board[player_two.current_block_id].rent_3){
											printf("You have to sell something because you don't have enough money \n\n");
											sell_property(board,&player_two);
											temp--;
										}
									}
									if(player_two.account < board[player_two.current_block_id].rent_3) player_two.account = 0;
									else{
										player_two.account -= board[player_two.current_block_id].rent_3;
										player_one.account += board[player_two.current_block_id].rent_3;
										printf("You paid block rent !!\nNew account : %d$\n\n",player_two.account);
									}
								}
								else{
									player_two.account -= board[player_two.current_block_id].rent_3;
									player_one.account += board[player_two.current_block_id].rent_3;
									printf("You paid block rent with 3 houses !!\nNew account : %d$\n\n",player_two.account);
								}
							}
						}	
						break;
					case 2:
						printf("Your account is %d$ \n\n",player_two.account);
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
						buy_house(board,&player_two);
						turn--;
						break;
					case 7:
						sell_property(board,&player_two);
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

}
