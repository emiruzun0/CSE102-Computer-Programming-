#include <stdio.h>
#include <string.h>
#define SIZE1 10.0   //The size of homework and lab grades
#define SIZE2 2.0	//The size of exam grades

void menu();
void menu2();
void shape();
int take_grades(int h[]);
int take_exam_grades(int e[]);
int add(int number1,int number2);
int sub(int number1,int number2);
int mul(int number1,int number2);
int div(int number1,int number2);
int pwr(int number1,int number2);
int mod(int number1,int number2);
int doit(int (*f)(int, int),int first_number,int second_number);
double calculate_homework(int h[]);
double calculate_lab(int l[]);
double calculate_all(int t1,int e[],int t2);


int main(){
	menu();
	return 0;
}

void menu(){
	int choice;
	int h[10],l[10],e[2];
	double t1,t2,t_all;
	do{
		printf("***** MENU *****\n");
		printf("1. Calculator\n");
		printf("2. Grades Average\n");
		printf("3. Draw Shape\n");
		printf("4. Exit\n");
		printf("Choice:");
		scanf("%d",&choice);
		switch(choice){
			case 1:
				menu2();
				break;
			case 2:
				printf("Enter your homework grades \n");
				take_grades(h);
				printf("Enter your lab grades \n");
				take_grades(l);
				take_exam_grades(e);
				t1 = (calculate_homework(h)) ;									//average of the homeworks
				t2 = (calculate_lab(l)) ;										//average of the labs
				t_all = calculate_all(t1,e,t2);									//weighted average
				printf("Your weighted average is %.2f \n\n\n\n",t_all);
				break;
			case 3: 
				shape();
				break;
			case 4:
				printf("Exiting...\n\n");
				break;
			default :
				printf("You entered invalid choice.Try again ! \n\n");
				break;
		}
	}while(choice!=4);
}

void menu2(){
	char control,operator[2];
	int nums[2];
	int i=0,last_result=0;
	printf("If you back to the menu , press enter 'q 1'\n");
	printf("Please enter this order 'operation -- space -- number -- (enter or other number)'\n");
	while(operator[0]!='q'){
		scanf("%s ",operator);
		i=0;												//for count numbers
		do{	
		    scanf("%d%c", &nums[i], &control); 				//If the number count is 1,it will use the previous value
		    i++; 											//If the number count is 2,it will use the entering value
		    } while(control!= '\n');
		if(operator[0]=='+'){
			if(i==1){										//Every i==1 conditions for the assign result to the nums[0] or nums[1]
				nums[1]=last_result;
			}
			last_result = doit(add,nums[0],nums[1]);
			printf("%d \n",last_result);
		}	 			
		else if(operator[0]=='-'){
			if(i==1){
				nums[1]=last_result;
				last_result = doit(sub,nums[1],nums[0]);
			}
			else{
				last_result = doit(sub,nums[0],nums[1]);
			}
			printf("%d \n",last_result);
		}
		else if(operator[0]=='*' && operator[1]=='*'){
			if(i==1){
				nums[1]=last_result;
				last_result = doit(pwr,nums[1],nums[0]);
			}
			else{
				last_result = doit(pwr,nums[0],nums[1]);
			}
			printf("%d \n",last_result);
		}
		else if(operator[0]=='*'){
			if(i==1){
				nums[1]=last_result;
			}
			last_result = doit(mul,nums[0],nums[1]);
			printf("%d \n",last_result);
		}
		else if(operator[0]=='/'){
			if(i==1){
				nums[1]=last_result;
				last_result = doit(div,nums[1],nums[0]);
				if(last_result == 0){
					break;
				}
			}
			else{
				last_result = doit(div,nums[0],nums[1]);
				if(last_result == 0){
					break;
				}
			}
			printf("%d \n",last_result);
		}
		else if(operator[0]=='%'){
			if(i==1){
				nums[1]=last_result;
				last_result = doit(mod,nums[1],nums[0]);
			}
			else{
				last_result = doit(mod,nums[0],nums[1]);
			}
			printf("%d \n",last_result);
		}
		else if(operator[0]=='q'){
			printf("Returning to the menu... \n\n\n");						//to quit calculator
		}
		else{
			printf("You have entered wrong input.Try again\n");
		}
	}
}


int doit(int (*f)(int, int),int first_number,int second_number){
	return (*f)(first_number,second_number);
}


int add(int number1,int number2){
	return number1+number2;
}

int sub(int number1,int number2){
	return number1-number2;
}

int pwr(int number1,int number2){
	int i,total=1;
	for(i=0;i<number2;++i){
		total *= number1;
	}
	return total;
}

int mul(int number1,int number2){
	return number1 * number2;
}

int div(int number1,int number2){
	if(number2 == 0){
		printf("This is undefined.\n\n\n\n");
		return 0;
	}
	else{
		return number1 / number2;
	}
}

int mod(int number1,int number2){
	return number1%number2;
}

void shape(){
	int a,i,j,k,star=0;
	printf("Enter a height of the shape : "); scanf("%d",&a);
	printf("\n");
	int space = a-1;			 //to determine the space number first
	for(i=0;i<a;++i){
		for(j=space;j>0;--j)	//print the whitespaces
			printf(" ");
		printf("/");
		for(k=0;k<star;++k)
			printf("*");
		printf("\\\n");
		star += 2;
		space--;
	}
	star-=2;
	space++;
	for(i=0;i<a;++i){
		for(j=0;j<space;++j)
			printf(" ");
		printf("\\");
		for(k=0;k<star;++k)
			printf("*");
		printf("/\n");
		star -= 2;
		space++;
	}
	printf("\n\n\n\n");
}

int take_grades(int h[]){
	int i;
	for(i=0;i<SIZE1;++i){
		printf("%d. grade : ",i+1);
		scanf("%d",&h[i]);
	}
	printf("\n\n");
}

int take_exam_grades(int e[]){
	int i;
	for(i=0;i<SIZE2;++i){
		printf("%d.exam grade : ",i+1);
		scanf("%d",&e[i]);
	}
}

double calculate_homework(int h[]){
	int i,total=0;
	for(i=0;i<SIZE1;++i){
		total += h[i];
	}
	printf("\n\n");
	return total / SIZE1 ;
}

double calculate_lab(int l[]){
	int i,total=0;
	for(i=0;i<SIZE1;++i){
		total += l[i];
	}
	printf("\n\n");
	return total / SIZE1 ;
}
	
double calculate_all(int t1,int e[],int t2){
	double average;
	average = t1*0.1 + t2*0.2 + e[0]*0.3 + e[1]*0.4 ; 
	return average;
}
	

