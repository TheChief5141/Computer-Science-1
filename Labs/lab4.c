#include <stdio.h>
#include <stdlib.h>



struct node{
	int data;
	struct node* next;
};

struct queue{
	struct node* front;
	struct node* back;
};

void init(struct queue* qPtr);
int enqueue(struct queue* qPtr, int val);
int dequeue(struct queue* qPtr);
void displayq(struct queue* myqPtr);
int empty(struct queue* qPtr);
int front(struct queue* qPtr);

int main(){
	struct queue* myqPtr = (struct queue*)malloc(sizeof(struct queue));
	init(myqPtr);
	int choice;
	int data;
	while(1){
		printf("1:To add to the data queue\n 2:Delete the data from the queue\n 3:Print the queue\n 4:Exit the Program\n");
		printf("\nEnter Your Choice: ");
		scanf("%d", &choice);
		switch(choice){
			case 1:
				printf("Enter the value: ");
				scanf("%d", &data);
				enqueue(myqPtr, data);
				break;
			case 2:
				data = dequeue(myqPtr);
				if(data != -1){
					printf("Deleted the data from the queue");
				}else{
					printf("Empty Queue");
				}
				break;
			case 3:
				displayq(myqPtr);
				break;
			case 4:
				exit(1);
				break;
			default:
				printf("Enter a valid value");
		}
	}
	return 0;
}

void displayq(struct queue* myqPtr){
	struct node* t= myqPtr->front;
	while(t){
		printf("%d\t", t->data);
		t=t->next;
	}
	printf("\n");
}

void init(struct queue* qPtr){
	qPtr->front = NULL;
	qPtr->back = NULL;
}

int enqueue(struct queue* qPtr, int val){
	struct node* temp;
	temp = (struct node*)malloc(sizeof(struct node));
	if(temp!=NULL){
		temp->data = val;
		temp->next = NULL;
		if(qPtr->back != NULL){
			qPtr->back->next = temp;
		}
		qPtr->back = temp;
		if(qPtr->front == NULL){
			qPtr->front = temp;
		}
		return 1;
	}else{
		return 0;
	}
}

int dequeue(struct queue* qPtr){
	struct node* tmp;
	int retval;
	if(qPtr->front == NULL){
		return -1;
	}
	retval = qPtr->front->data;
	tmp = qPtr->front;
	qPtr->front = qPtr->front->next;
	if(qPtr->front == NULL){
		qPtr->back = NULL;
	}
	free(tmp);
	return retval;
}

int empty(struct queue* qPtr){
	return qPtr->front == NULL;
}

int front(struct queue* qPtr){
	if(qPtr->front != NULL){
		return qPtr->front->data;
	}else{
		return -1;
	}
}