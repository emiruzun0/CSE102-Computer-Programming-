#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 20


struct person{
	char *name;
 	char *surname;
	char *musical_Work;
	int age;
	struct person *next;
}*top;

void addNode(char *name, char *surname , char *creation , int age);
void deleteNode();
void Sort_Alphabetically();
void Sort_Increasingly();
void print_stack();
int compare_strings(char name1[], char name2[]);
int isSortedName();
int isSortedAge();


int main(){

	top = NULL;
	char *name,*surname,*musical_Work;
	int age;
	name = (char*)malloc(SIZE*sizeof(char));				//memory allocated
	surname = (char*)malloc(SIZE*sizeof(char));
	musical_Work = (char*)malloc(SIZE*sizeof(char));
	
	int choice;
	
	while(choice != 5){
		printf("****MENU****\n");
		printf("1-Add a Person to the Stack\n");
		printf("2-Pop a Person from the Stack\n");
		printf("3-Sort Alphabetical Order \n");
		printf("4-Sort Age in Increasing Order\n");
		printf("5-Exit menu \n");
		printf("************\n");
		printf("Select your choice : ");
		scanf("%d",&choice);
		switch(choice){
			case 1:	
				printf("Name : ");
				getchar();						//read buffer character
				scanf("%[^\n]s",name);			//^n means it takes varieable until user press enter .
				printf("Surname : ");
				getchar();
				scanf("%[^\n]s",surname);
				getchar();
				printf("Creation : ");
				scanf("%[^\n]s",musical_Work);
				printf("Age : ");
				scanf("%d",&age);
				addNode(name,surname,musical_Work ,age);	
				print_stack();
				break;
			case 2:
				deleteNode();
				print_stack();
				break;
			case 3:
				Sort_Alphabetically();
				print_stack();
				break;
			case 4:
				Sort_Increasingly();
				print_stack();
				break;
			case 5:
				printf("Exiting..\n");
				break;
			default :
				printf("You've entered invalid value.Please try again ! \n");
				break;
		}
	}
	free(name);
	free(surname);
	free(musical_Work);
	free(top);
}


void addNode(char name[], char surname[] , char creation[] , int age){
	struct person* node;
	node = (struct person*)malloc(sizeof(struct person));
	
	node->name = (char*)malloc(SIZE*sizeof(char));
	node->surname = (char*)malloc(SIZE*sizeof(char));
	node->musical_Work = (char*)malloc(SIZE*sizeof(char));

	strcpy(node->name,name);
	strcpy(node->surname,surname);
	strcpy(node->musical_Work,creation);
	node->age = age;	
	if(top == NULL){			//this condition is for the first node .
		top = node;
		top->next = NULL;
	}
	else{
		node->next = top;
		top = node;
	}
}

void deleteNode()
{
	struct person *temp;
	temp = top;
	if(top->next == NULL ){
		top = NULL;
		return;
	}
	//if(top != NULL)
	else{
		top = top->next;				//now top points top->next . So we have to delete previous top's area.
		free(temp);
	}
}

void Sort_Alphabetically()
{
	struct person* prev;
	struct person* temp;
	struct person* cur;
	int i;
	
	while(isSortedName() == -1)
	{
		prev = NULL;
		temp = top;
		cur = top->next;
		i = 0;
		while(cur != NULL)
		{
			if(compare_strings(temp->name, cur->name) == 1)
			{
				if(i == 0)	top = cur;
				else	prev->next = cur;
				
				temp->next = cur->next;		//swap 
				cur->next = temp;	
				prev = cur;
				cur = temp->next;
			}
			else
			{
				prev = temp;				//control for next pointers
				temp = cur;
				cur = cur->next;	
			}	
			
			i++;
		}
	}
}

int isSortedName()
{
	struct person* temp = top;
	char* name = (char*)malloc(SIZE*sizeof(char));
	int flag = 1;
	
	while(temp != NULL && flag == 1)
	{
		strcpy(name,temp->name);
		temp = temp->next;
		if(temp != NULL && compare_strings(name,temp->name) == 1 ) flag = -1;			
	}
	return flag;
}

int compare_strings(char name1[], char name2[])
{
	int i = 0;
	int flag = 1;
	char ch1, ch2;
	do
	{
		ch1 = name1[i];					//initialize 
		ch2 = name2[i];
		if(ch1 >= 65 && ch1 <= 90)	ch1 += 32;			//this condition is for the if the letters are upper,they will turn the lowercase.
		if(ch2 >= 65 && ch2 <= 90)	ch2 += 32;
		if (ch1 == '\0' || ch2 == '\0')		flag = 0;
	  	i++;
	}
	while (flag == 1 && ch1 == ch2); 
   
   if (ch1 == '\0' && ch2 == '\0')			
      return 0;
   else if(ch1 > ch2)				//in this condition , sort_alphabetically function swaps the datas.
      return 1;
    else return -1;
}

void Sort_Increasingly()
{
	struct person* prev;
	struct person* temp;
	struct person* cur;
	int i;
	
	while(isSortedAge() == -1)
	{
		prev = NULL;
		temp = top;
		cur = top->next;
		i = 0;
		while(cur != NULL)
		{
			if(temp->age > cur->age == 1)
			{
				if(i == 0)	top = cur;
				else	prev->next = cur;
				
				temp->next = cur->next;		//swap
				cur->next = temp;
				prev = cur;
				cur = temp->next;
			}
			else
			{
				prev = temp;			//control for next pointers 
				temp = cur;
				cur = cur->next;	
			}	
			
			i++;
		}
	}
}




int isSortedAge()
{
	struct person* temp = top;
	int num;
	int flag = 1;
	
	while(temp != NULL && flag == 1)
	{
		num = temp->age;
		temp = temp->next;
		if(temp != NULL && num > temp->age) flag = -1;		
	}
	return flag;
}


void print_stack()
{ 
    struct person* temp = top; 
  	int i=1;

    if (temp == NULL) { 
        printf("\nStack is empty ! \n\n\n"); 
        return;
    } 
    else { 
        temp = top; 
        printf("--------------------\n");
        while (temp != NULL) { 
  
            printf("%d) ",i);
            printf("%s\n",temp->name); 
            printf("%s\n",temp->surname);
            printf("%s\n",temp->musical_Work );
            printf("%d\n",temp->age );
            i++;
  
            temp = temp->next; 
        }
    } 
    printf("\n\n\n");
} 
