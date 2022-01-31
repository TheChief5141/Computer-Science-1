#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define nameSIZE 20
#define SIZE 12


typedef struct customer{
    char name[nameSIZE];
    int num_of_items;
    int line_num;
    int time;
}customer;

typedef struct node{  
    struct node *next;
    struct customer *cPtr;
    struct queue *qPtr;
} node;

typedef struct queue{
    struct customer arrayQueue[SIZE];   
    int *rear;   
    int *front;   
    int capacity;
} queue;


queue* init(int cust_size);
void enqueue(queue *q, customer  item);
void dequeue(queue *q);
customer * peek(queue *q);
int isEmpty(queue *q);

node * findMininLine(node * n, queue * q);
void createNodes(node * head);
customer readCustomerInfo(FILE * ptr, customer * q);
node * createStoreLine(node * firstNode, int custAmount);

node *  findMininLine(node * n, queue * q){
    node * t;
    node * minNode;
    t = n;
    minNode = n;
    int min = 999;
    while(t->next != NULL){
        if(q->arrayQueue->num_of_items < min){
            min = q->arrayQueue->num_of_items;
            minNode = t;
        }
        t = t->next;
    }
    return minNode;
}

queue* init(int cust_size)  {   
    queue* q =(queue*)malloc((cust_size) * sizeof(queue));     
    q->front = 0;   
    q->rear = 0;   
    q->capacity = SIZE;   
    return q;
}

int isEmpty(queue *q){
    if(q == NULL){
        return 1;
    }else{
        return 0;
    }
}

void enqueue(queue *q, customer item){   
    if(isEmpty(q)){ 
        if(*(q->rear) < q->capacity){         
            q->arrayQueue[*(q->rear)]=item;       
            (q->rear)++;      
        }else{
            printf("Queue is FULL\n");
        }
    }else{
        printf("Queue is EMPTY\n");
    }
}

void dequeue(queue *q){ 
    if(isEmpty(q))   {    
        if(*(q->rear) != *(q->front))     {           
            *(q->front)++;   
        }else{     
            printf("Queue is EMPTY\n");        
        }   
    }else{
        printf("Queue is EMPTY\n");
    }
}

customer * peek(queue *q){
    if(isEmpty(q)){
        return &(q->arrayQueue[*(q->front)]);
    }else{
        printf("Queue is EMPTY\n");
    }
}

customer readCustomerInfo(FILE * ptr, customer * q){
    fscanf(ptr, "%d %d %s %d", &(q->time), &(q->line_num), q->name, &(q->num_of_items));
    return *q;
}

void createNodes(node* head){
    node *t;
    node *temp;
    temp = (node *)malloc(sizeof(node));
    temp->next=NULL;
    if(head==NULL){
        head=temp;
    }else{
        t=head;
    }     
    while(t->next!=NULL){
        t=t->next;        
    }         
    t->next=temp;
    t->next->next=NULL;
}

node * createStoreLine(node * firstNode, int custAmount){
    node * t;
    t = firstNode;
    for(int y = 0; y < SIZE; y++){
        createNodes(firstNode);
        while(t->next != NULL){
            t = t->next;
        }
        t->qPtr = init(custAmount);
    }

    return firstNode;

}


int main(){
    int cust_amount, test_cases, node_line_num;
    node * headStoreLine = NULL;
    node * t = NULL; 

    headStoreLine = (node*)malloc(sizeof(node));
    headStoreLine->next = NULL;

    //start of the program
    printf("Welcome to the Store!\n");
    //open file
    FILE * fPtr = fopen("assignment2.txt", "r");
    //find the amount of test cases
    fscanf(fPtr, "%d", &test_cases);
    //run the program for each test case
    for(int i = 0; i < test_cases; i++){
        //find the amount of customers in store
        fscanf(fPtr, "%d", &cust_amount);
        //creates an initial line to store the values of the customers in
        customer * initialCustomerLine = (customer*)malloc((cust_amount)*sizeof(customer));

        //creates the actual store lines 1-12, with queues for each line
        headStoreLine = createStoreLine(headStoreLine, cust_amount);
        //set our traversing variable equal to the head of the node line
        t = headStoreLine;
        //run for each customer we have in the store
        for(int j = 0; j < cust_amount; j++){
            //tracks where we are in our node, to compare to line_num variable to find the correct line
            node_line_num  = 0;
            //sets the value of each spot in the array to store the customer information
            initialCustomerLine[j] = readCustomerInfo(fPtr, &(initialCustomerLine[j]));
            //traverse through the node list to find the correct line to put the customer in
            while(node_line_num != initialCustomerLine[j].line_num || t->next == NULL){
                //sets the traversing variable to the next node in the line
                t = t->next;
                //updates the node_line_num variable to find the correct line in the node list
                node_line_num++;
            }
            //puts customer value into the correct line number
            enqueue(t->qPtr, initialCustomerLine[j]);
        }

        //run customers through the line
        for(int k = 0; k < SIZE; k++){
            //finds the node at which the person in the front of the queue has the fewest num of items
            t = findMininLine(headStoreLine, headStoreLine->qPtr);
            //time =  30 + (amount of items * 5)
            int calTime = 30 + (5 * t->qPtr->arrayQueue[*(t->qPtr->front)].num_of_items);
            //store the time into customer struct
            t->qPtr->arrayQueue[*(t->qPtr->front)].time = calTime;
            //checkout the customer that has the fewest items
            printf("\n %s from line %d checks out at time %d",t->qPtr->arrayQueue[*(t->qPtr->front)].name , t->qPtr->arrayQueue[*(t->qPtr->front)].line_num, calTime);
            //dequeue the queue to tell the queue that the customer checked out
            dequeue(t->qPtr);
            

        }

        
    }
   //free all memory used in this test case
   //set traversing variable back to the back of the linked list
    t = headStoreLine;
    //free the initialCustomerLine Array
    for(int h = 0; h == SIZE; h++){
        while(t->next != NULL){
            t = t->next;
        }
        //free the queue in last node
        free(t->qPtr);
        //free each node
        


    }

     free(headStoreLine);

}