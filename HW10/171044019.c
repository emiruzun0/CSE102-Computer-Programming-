#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 20

typedef struct stack 
{ 
    int data; 
    struct stack* next; 
}stack;

typedef struct QNode 
{ 
    int data; 
    struct QNode *next; 
}QNode;

typedef struct queue 
{ 
    struct QNode *front, *rear; 
}queue; 

typedef struct bst 
{ 
    int data; 
    struct bst *left, *right; 
}bst;   


void fill_structures(stack ** stack_, queue ** queue_, bst ** bst_, int data[SIZE]);
void ordered_print(stack * stack_, queue * queue_, bst * bst_);
void search(stack * stack_, queue * queue_, bst * bst_, int val_to_search);
void special_traverse(stack * stack_, queue * queue_, bst * bst_);
int search_bst(bst *node,int value);



void addstack(stack** stack_, int data);
void addqueue(queue* queue_, int data);
bst* addbst(bst* bst_, int data);
bst* newNode(int data);
QNode* newQNode(int data);
void printbst(bst* bst_);
void printstack(stack* stack_);
void printqueue(queue* queue_);
void rprintbst(bst* bst_);


int main()
{
	int data[SIZE]={5, 2, 7, 8, 11, 3, 21, 7, 6, 15, 19, 35, 24, 1, 8, 12, 17, 8, 23, 4};
	
	bst * bst_;
	queue * queue_;
	stack * stack_;
	
	fill_structures(&stack_, &queue_, &bst_, data);

	ordered_print(stack_, queue_, bst_);
	search(stack_, queue_, bst_, 19);
	special_traverse(stack_, queue_, bst_);
	
	return 0;
}

void fill_structures(stack ** stack_, queue ** queue_, bst ** bst_, int data[SIZE])
{
	clock_t start_t,end_t;
	double diff,diff2,diff3;
	
	int i;
	
	start_t = clock();
	*stack_ = NULL;
	for(i = 0 ; i < SIZE ; i++)
	{
		addstack(stack_, data[i]);
	}
	end_t = clock();
	diff = (double)(end_t-start_t) / (CLOCKS_PER_SEC / 1000.0);
	
	start_t = clock();
	*queue_ = (queue*)malloc(sizeof(queue));
	(*queue_)->front = NULL;
	(*queue_)->rear = NULL; 
	for(i = 0 ; i < SIZE ; i++)
	{
		addqueue((*queue_), data[i]);
	}
	end_t = clock();
	diff2 = (double)(end_t-start_t) / (CLOCKS_PER_SEC / 1000.0) ;
	
	start_t = clock();
	*bst_ = NULL;
	for(i = 0 ; i < SIZE ; i++)
	{
		*bst_ = addbst(*bst_, data[i]);
	}
	end_t = clock();
	diff3 = (double)(end_t-start_t) / (CLOCKS_PER_SEC / 1000.0) ;
	
	printf("\n FILL TIMES:");
	printf("\n Structures \t Stack \t \t Queue \t \t BST");
	printf("\n Exec. Time \t %lf \t %lf \t %lf\n", diff, diff2, diff3);

	printf("\n Stack: ");
	printstack(*stack_);
	printf("\n Queue: ");
	printqueue(*queue_);
	printf("\n Bst: ");
	printbst(*bst_);
}

void ordered_print(stack * stack_, queue * queue_, bst * bst_)
{
	printf("\n\n Ordered Print:");
	clock_t start_t,end_t;
	double diff,diff2,diff3;
	
	start_t = clock();
	printf("\n Stack: ");
	stack* orderedStack = NULL;
	stack* temp = stack_;
	while(temp != NULL) 
    { 
		addstack(&orderedStack, temp->data);
        temp = temp->next;
    }

	stack* tempNode = orderedStack;
	stack* tempNode2;
	stack* BigNode, *prevBigNode, *prevNode;
	while(tempNode != NULL)
	{
		tempNode2 = tempNode;
		prevNode = tempNode;
		BigNode = tempNode;
		prevBigNode = tempNode;
		while(tempNode2 != NULL)
		{
			if(tempNode2->data >= BigNode->data)
			{
				BigNode = tempNode2;
				prevBigNode = prevNode;
			}
			prevNode = tempNode2;
			tempNode2 = tempNode2->next;	
		}
		if(BigNode != tempNode)
		{
			prevBigNode->next = BigNode->next;
		}
		else
		{
			tempNode = tempNode->next;
		}
		printf("%d ", BigNode->data);
	}
	end_t = clock();
	diff = (double)(end_t-start_t) / (CLOCKS_PER_SEC / 1000.0);
	
	
	start_t = clock();
	printf("\n Queue: ");
	queue *orderedQueue = (queue*)malloc(sizeof(queue));
	orderedQueue->front = NULL;
	orderedQueue->rear = NULL; 
	int i;
	QNode* tempqueue = queue_->front;
	while(tempqueue != NULL) 
    { 
		addqueue(orderedQueue, tempqueue->data);
        tempqueue = tempqueue->next;
    }
    
    QNode* tempQNode = orderedQueue->front;
	QNode* tempQNode2;
	QNode* BigQNode, *prevBigQNode, *prevQNode;
	while(tempQNode != NULL)
	{
		tempQNode2 = tempQNode;
		prevQNode = tempQNode;
		BigQNode = tempQNode;
		prevBigQNode = tempQNode;
		while(tempQNode2 != NULL)
		{
			if(tempQNode2->data >= BigQNode->data)
			{
				BigQNode = tempQNode2;
				prevBigQNode = prevQNode;
			}
			prevQNode = tempQNode2;
			tempQNode2 = tempQNode2->next;	
		}
		if(BigQNode != tempQNode)
		{
			prevBigQNode->next = BigQNode->next;
		}
		else
		{
			tempQNode = tempQNode->next;
		}
		printf("%d ", BigQNode->data);
	}
	end_t = clock();
	diff2 = (double)(end_t-start_t) / (CLOCKS_PER_SEC / 1000.0);

	start_t = clock();
	printf("\n Bst: ");
	rprintbst(bst_);
    end_t = clock();
	diff3 = (double)(end_t-start_t) / (CLOCKS_PER_SEC / 1000.0);
	
	printf("\n\n ORDER TIMES:");
	printf("\n Structures \t Stack \t \t Queue \t \t BST");
	printf("\n Exec. Time \t %lf \t %lf \t %lf", diff, diff2, diff3);
	
}


void search(stack * stack_, queue * queue_, bst * bst_, int val_to_search){
	int i,step=1,count=0,found;
	clock_t start_t,end_t;
	double diff,diff2,diff3;
	stack *temp_stack;
	queue *temp_queue;
	QNode *temp3;

	queue *orderedQueue = (queue*)malloc(sizeof(queue));
	orderedQueue->front = NULL;
	orderedQueue->rear = NULL; 
	
	QNode* tempqueue = queue_->front;
	temp_queue=(queue *)malloc(sizeof(queue));
	temp_stack=(stack *)malloc(sizeof(stack));

	temp_queue=queue_;
	temp_stack=stack_;

	temp3 = queue_->front;
	start_t=clock();

	printf("\nIn the stack;\n");	
	do{
		if(stack_->data == val_to_search){
			printf("1 result founded on %d. step\n",step);
			count++;
		}
		stack_=stack_->next;
		step++;
	}while(stack_->next != NULL);
	stack_=temp_stack;	

	if(count != 0)
		printf("\n%d result founded for %d.\n",count,val_to_search );
	else
		printf("\n%d not founded in stack.\n",val_to_search);

	end_t=clock();

	diff=(double)(end_t-start_t) / (CLOCKS_PER_SEC / 1000.0);

	count=0;
	step=1;

	printf("\nIn the queue;\n");	
	do{
		if(temp3->data == val_to_search){
			printf("1 result founded on %d. step\n",step);
			count++;
		}
		temp3 = temp3->next;
		step++;
	}while(temp3->next != NULL);	
	queue_=temp_queue;

	if(count != 0)
		printf("\n%d result founded for %d.\n",count,val_to_search );
	else
		printf("\n%d not founded in queue.\n",val_to_search);

	end_t=clock();

	diff2=(double)(end_t-start_t) / (CLOCKS_PER_SEC / 1000.0);

	count=0;
	step=1;

	printf("\nIn the BST\n");

	start_t = clock();
	found=search_bst(bst_,val_to_search);
	end_t = clock();

	diff3=(double)(end_t-start_t) / (CLOCKS_PER_SEC / 1000.0);

	if(found == 1)
		printf("\n%d founded on the BST.\n",val_to_search );
	if(found == -1)
		printf("\n%d not founded on the BST.\n",val_to_search );

	printf("\nStructures     Stack        Queue        BST\n");
	printf("Exec. Time     %lf     %lf     %lf\n",diff,diff2,diff3);

	
}

int search_bst(bst *node,int value){
	if(node == NULL)
		return -1;


	if(node->data == value)
		return 1;

	if(search_bst(node->left,value)==1)
		return 1;
	
	if(search_bst(node->right,value)==1)
		return 1;

	return-1;
}

void special_traverse(stack * stack_, queue * queue_, bst * bst_)
{
	printf("\n\n Special Traverse :");
	clock_t start_t,end_t;
	double diff,diff2,diff3;
	
	start_t = clock();
	printf("\n Stack: ");
	stack* orderedStack = NULL;
	stack* temp = stack_;
	while(temp != NULL) 
    { 
		addstack(&orderedStack, temp->data);
        temp = temp->next;
    }

	stack* tempNode = orderedStack;
	stack* tempNode2;
	stack* BigNode, *prevBigNode, *SmallNode, *prevSmallNode, *prevNode;
	while(tempNode != NULL)
	{
		tempNode2 = tempNode;
		prevNode = tempNode;
		BigNode = tempNode;
		prevBigNode = tempNode;
		SmallNode = tempNode;
		prevSmallNode = tempNode;
		while(tempNode2 != NULL)
		{
			if(tempNode2->data >= BigNode->data)
			{
				BigNode = tempNode2;
				prevBigNode = prevNode;
			}
			else if(tempNode2->data <= SmallNode->data)
			{
				SmallNode = tempNode2;
				prevSmallNode = prevNode;
			}
			prevNode = tempNode2;
			tempNode2 = tempNode2->next;	
		}
		if(BigNode != tempNode)
		{
			prevBigNode->next = BigNode->next;
		}
		else
		{
			tempNode = tempNode->next;
		}
		if(BigNode != SmallNode)
		{
			if(SmallNode != tempNode)
			{
				prevSmallNode->next = SmallNode->next;
			}
			else
			{
				tempNode = tempNode->next;
			}
		}
		
		printf("%d %d ", BigNode->data, SmallNode->data);
	}
	end_t = clock();
	diff = (double)(end_t-start_t) / (CLOCKS_PER_SEC / 1000.0);
	
	start_t = clock();
	printf("\n Queue: ");
	queue *orderedQueue = (queue*)malloc(sizeof(queue));
	orderedQueue->front = NULL;
	orderedQueue->rear = NULL; 
	int i;
	QNode* tempqueue = queue_->front;
	while(tempqueue != NULL) 
    { 
		addqueue(orderedQueue, tempqueue->data);
        tempqueue = tempqueue->next;
    }
    
    QNode* tempQNode = orderedQueue->front;
	QNode* tempQNode2;
	QNode* BigQNode, *prevBigQNode, *SmallQNode, *prevSmallQNode, *prevQNode;
	while(tempQNode != NULL)
	{
		tempQNode2 = tempQNode;
		prevQNode = tempQNode;
		BigQNode = tempQNode;
		prevBigQNode = tempQNode;
		SmallQNode = tempQNode;
		prevSmallQNode = tempQNode;
		while(tempQNode2 != NULL)
		{
			if(tempQNode2->data >= BigQNode->data)
			{
				BigQNode = tempQNode2;
				prevBigQNode = prevQNode;
			}
			else if(tempQNode2->data <= SmallQNode->data)
			{
				SmallQNode = tempQNode2;
				prevSmallQNode = prevQNode;
			}
			prevQNode = tempQNode2;
			tempQNode2 = tempQNode2->next;	
		}
		if(BigQNode != tempQNode)
		{
			prevBigQNode->next = BigQNode->next;
		}
		else
		{
			tempQNode = tempQNode->next;
		}
		if(BigQNode != SmallQNode)
		{
			if(SmallQNode != tempQNode)
			{
				prevSmallQNode->next = SmallQNode->next;
			}
			else
			{
				tempQNode = tempQNode->next;
			}
		}
		
		printf("%d %d ", BigQNode->data, SmallQNode->data);
	}
	end_t = clock();
	diff2 = (double)(end_t-start_t) / (CLOCKS_PER_SEC / 1000.0);

	printf("\n\n TRAVERSE TIMES : ");
	printf("\n Structures \t Stack \t \t Queue \t \t BST");
	printf("\n Exec. Time \t %lf \t %lf \t \n", diff, diff2);
}

void addstack(stack** stack_, int data)
{
	stack* temp = (stack*) malloc(sizeof(stack)); 
	temp->data = data; 
    temp->next = *stack_; 
    *stack_ = temp; 
}

QNode* newQNode(int data) 
{ 
    struct QNode *temp = (QNode*)malloc(sizeof(QNode)); 
    temp->data = data; 
    temp->next = NULL; 
    return temp;  
}   

void addqueue(queue* queue_, int data)
{
    struct QNode *temp = newQNode(data); 
  
    if (queue_->rear == NULL) 
    { 
       queue_->front = temp;
	   queue_->rear = temp; 
    } 
  	else
  	{
		queue_->rear->next = temp; 
    	queue_->rear = temp; 	
	}
    
}

bst* newNode(int data) 
{ 
    bst* temp =  (bst*)malloc(sizeof(bst)); 
    temp->data = data; 
    temp->left = NULL;
	temp->right = NULL; 
    return temp; 
}

bst* addbst(bst* bst_, int data)
{
	if (bst_ == NULL) return newNode(data); 
  
    if (data < bst_->data) 
        bst_->left  = addbst(bst_->left, data); 
    else
        bst_->right = addbst(bst_->right, data); 

    return bst_; 
}

void printbst(bst* bst_) 
{ 	
    if (bst_ != NULL) 
    { 
        printbst(bst_->left); 
        printf("%d ", bst_->data); 
        printbst(bst_->right); 
    } 
}

void rprintbst(bst* bst_) 
{ 	
    if (bst_ != NULL) 
    { 
        rprintbst(bst_->right); 
        printf("%d ", bst_->data); 
        rprintbst(bst_->left); 
    } 
}

void printstack(stack* stack_) 
{ 
	stack* temp = stack_;
    while(temp != NULL) 
    { 
        printf("%d ", temp->data); 
        temp = temp->next;
    } 
}   

void printqueue(queue* queue_) 
{ 
	QNode* temp = queue_->front;
    while(temp != NULL) 
    { 
        printf("%d ", temp->data); 
        temp = temp->next;
    } 
}

