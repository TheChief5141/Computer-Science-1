#include <stdio.h>
#include <string.h>
#include <stdlib.h>



//--37-- Please read the instruction provided above before starting your code --37--
// Write your name here:  Logan Kilburn
// your UCFID: 4629349


 typedef struct node{
	int info;
	struct node *next;
}node;

node* SortInsert(node *root, int item); //this function is complete
void simplePrint(node* root); //this function is complete
void printLast(node* root); //you have to write this function, see bellow //total grade 50
node* InsertAfter5 (node * root, int item); //you have to write this function, see bellow // total grade 50



int main()
{
    node* head=NULL;
	node* head2 = NULL;

	node *t;
	int ch,ele;
	head = SortInsert(head, 4);
	head = SortInsert(head,6);
	head = SortInsert(head,3);
	head = SortInsert(head,5);
	head = SortInsert(head,5);

    printf("\nSimple print List 1: ");
    simplePrint(head);

    printLast(head); ////modify the printLast function to make it work

    head = InsertAfter5(head, 100); //modify the InsertAfter5 function to make it work
    printf("\nSimple print after InsertAfter5 with 100: ");
    simplePrint(head); //This call should print 3, 4, 5, 100, 5, 100, 6

	return 0;
}

void simplePrint(node* root)
{
    node* t=root;
    while(t!=NULL)
    {
        printf("%d ",t->info);
        t=t->next;
    }
}

node*  SortInsert(node* root, int item)
{
    node *temp;
    node *t;
    temp= (node *) malloc(sizeof(node));
    temp->info=item;
    temp->next=NULL;
    if (root==NULL || root->info >=item)
    {
            temp->next = root;
            root = temp;
    }
    else
    {
         t = root;
         while (t->next != NULL && t->next->info < item){
             t = t->next;
         }
         temp->next = t->next;
         t->next = temp;
    }

    return root;
}


void printLast(node* root)
{
    /*this function takes the head of a linked list and print the last  or known as tail item in the linked list
    for example: passing the head of a linked list containing 3, 4, 5, 5, 6 would print 6
     you can do it using for loops or recursively. */

    node *t = NULL;
    
    if(root != NULL){
        printf("\nPrinting the last number in the linked list.");
        t = root;
        while(!(t->next == NULL)){
            printf("\nTraversing through the list...");
            t = t->next;
            printf("\n %d", t->info);
        }
        printf("\nThe last item in the list is: %d", t->info);

        
    }


};


node* InsertAfter5 (node * root, int item)
{
         /*this function takes the head of a linked list and an integer item.
        The function add the integer item in a node after the node containing 5. Next, it returns the head.
        Example: if item = 100, Linked list 3, 4, 5, 5, 6 will be changed to 3, 4, 5, 100, 5, 100, 6 */
        node *t;
        node *temp; 
        temp = (node*)malloc(sizeof(node));
        temp->next = NULL;
        temp->info = item;
        if(root != NULL){
            t = root;
            while(t->next != NULL || t->info != item){
                t = t->next;
            }

            if(t->info == item){
                temp->next = t->next;
                t->next = temp;
            }


        }

        return root;
};