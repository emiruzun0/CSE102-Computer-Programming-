//EMİRHAN UZUN 171044019//
#include <stdio.h>

int find_gcd(int number1,int number2){
	if(number1 != number2){
		if(number1 > number2) return find_gcd(number1-number2,number2);
		else return find_gcd(number1,number2-number1);
	}
	return number1;
}

int view_multipliers(int number,int count){			//for find multipliers in gcd funtion's numbers
	if(number == 1) return 1;
	else if(number %count == 0){
		printf("%d ",count);
		return view_multipliers(number/count,count);
	}
	else 	return view_multipliers(number,count+1);
}

int gcd_function(){
	int n1,n2;
	printf("Enter first number : ");
	scanf("%d",&n1);
	printf("Enter second number : ");
	scanf("%d",&n2);
	printf("Factors of %d : { ",n1);      //find multipliers of numbers
	view_multipliers(n1,2);
	printf("}\n");
	printf("Factors of %d : { ",n2);
	view_multipliers(n2,2);
	printf("}\n");
	printf("The great common divisor of (%d,%d) is %d",n1,n2,find_gcd(n1,n2));
}

void merge(int arr[], int left, int middle, int right) 
{ 
    int i, j, k; 
    int n1 = middle - left + 1; 
    int n2 = right - middle; 
  	int Left[n1], Right[n2]; //these arrays are for the keep values(temporary arrays)
    
    
    for (i = 0; i < n1; i++)   	 //copy the values to the temporary arrrays
        Left[i] = arr[left + i];  //first loop is for the left side
    for (j = 0; j < n2; j++) 
        Right[j] = arr[middle + 1+ j]; 		//second loop is for the right side
  
    i = 0;     //it must be 0 because every entering the function it must start from 0.
    j = 0; 
    k = left; 
    while (i < n1 && j < n2) 
    { 
        if (Left[i] <= Right[j]) 		//sort the actual array.
        { 
            arr[k] = Left[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = Right[j]; 
            j++; 
        } 
        k++; 
    } 
  
    while (i < n1)  //copy the elements from temporary array to real array (Left side)
    { 
        arr[k] = Left[i]; 
        i++; 
        k++; 
    } 
 
    while (j < n2) //copy the elements from temporary array to real array (Right side)
    { 
        arr[k] = Right[j]; 
        j++; 
        k++; 
    } 
} 

void mergeSort(int arr[], int left, int right){ 
    if (left < right) 
    { 
        int middle = left+(right-left)/2;   //find miidle number
  
        mergeSort(arr, left, middle);    //recursive function (First,divided lists and then sorting)
        mergeSort(arr, middle+1, right);  
        merge(arr,left, middle, right); 
    } 
} 
  
int sorting_function(){
	int length,i;
	int arr[30];
	printf("Enter the length of the list : ");
	scanf("%d",&length);     //take the array size
	printf("Enter the elements of list : \n");
	for(i=0;i<length;++i){
		scanf("%d",&arr[i]);	//put the values in the array
	}
	mergeSort(arr,0,length-1);
	printf("Sorted array is : ");
	for(i=0;i<length;++i){
		printf("%d ",arr[i]);
	}
}

int find_selection(int number){			//for part3 selection function
	if(number == 0) return 0;
	if(number == 1){
		printf("%d  \n",number);
		return 1;
	}
	else if(number%2 == 0){
		printf("%d  ",number );
		return find_selection(number/ 2);
	}
	else{
		printf("%d  ",number);
		return find_selection(3*number +1);
	}
}

int selection_function(){
	int number;
	printf("Input : ");
	scanf("%d",&number);
	find_selection(number);				
}

int find_power(int base,int power){				//number^digit calculation
	int total ;
	if(power == 0 ) return 1;
	else
		return base*find_power(base,power-1);
}

int find_equal2(int number,int total,int digit){
	int a;
	if(a <= 0)	return total;
	else {
		a = number%10;
		total += find_power(a,digit);
		return find_equal2(number/10,total,digit);
	}
}

int find_digit(int number,int digit){			
	if(number <= 0) return digit;   	//find number digit recursively 
	else if(number == 0) return 1;	
	else return find_digit(number/10,++digit);
}

int equal_function(){
	int number,number2,a,k,digit;
	int total = 0;
	printf("Enter a number : ");
	scanf("%d",&number);
	digit = find_digit(number,0);
	number2 = find_equal2(number,total,digit);
	if(number == number2) printf("Output : Equal \n");
	else printf("Output : Not Equal\n");
}

char find_uppercase(char *s){    //for the find uppercase in string
    if((*s) == '\0'){
        return ' ';       
    }
    else if( (*s) >= 'A' && (*s) <= 'Z')
		return *s;
	else return find_uppercase(++s);
}

char find_string(){   //PART 5 
	char s[100],a;
	printf("Enter a string without space : ");
	scanf("%s",s);
	a= find_uppercase(s);
	if(a == ' ')	printf("There is no capital letters ...\n\n");
	else	printf("Output : %c \n",a);
}

int main(){
	int choice;
	do{
		printf("\n\n\n   WELCOME TO PROGRAM   \n");
		printf("1-GCD Find Program \n");
		printf("2-Array Sorting \n");
		printf("3-Selection Function (Formula)\n");
		printf("4-Equal Function \n");
		printf("5-First Capital Letter Finding \n");
		printf("6-Exit\n");
		printf("Choice : ");
		scanf("%d",&choice);
		switch(choice){
			case 1 :
				gcd_function();
				break;
			case 2 :
				sorting_function();
				break;
			case 3 :
				selection_function();
				break;
			case 4 :
				equal_function();
				break;
			case 5:
				find_string();
				break;
			case 6 : 
				printf("Successfully exiting...\n\n");
				break;
			default :
				printf("You've entered invalid value.Please try again !\n");
				break;
		}
	}while(choice!=6);
	
}