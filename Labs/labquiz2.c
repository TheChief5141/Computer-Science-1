#include <stdio.h>
#include <stdlib.h>

struct tree_node {
  int income;
  int count;
  struct tree_node *left;
  struct tree_node *right;
};

struct tree_node* insert(struct tree_node *root, struct tree_node *element);
struct tree_node* readData(FILE* fPtr, struct tree_node *head, int size);
void printInOrder(struct tree_node *nodePtr);
void leafNodeTotal(struct tree_node *nodePtr, int total);
int isLeaf(struct tree_node *leaf);

struct tree_node* insert(struct tree_node *root, struct tree_node *element) {

    // element should be inserted to the right.
    if (element->income > root->income) {

      // There is a right subtree to insert the node.
      if (root->right != NULL)
        root->right = insert(root->right, element);

      // Place the node directly to the right of root.
      else
        root->right = element;
    }
    // element should be inserted to the left.
    else {

      // There is a left subtree to insert the node.
      if (root->left != NULL)
        root->left = insert(root->left, element);

      // Place the node directly to the left of root.
      else
        root->left = element;
    }
   
    return root;
}

struct tree_node* readData(FILE* fPtr, struct tree_node *head, int size){
    int i, placeHolderIncome, placeHolderCount;
    struct tree_node *newNode;
    newNode = (struct tree_node*)malloc(sizeof(struct tree_node));
    fscanf(fPtr, "%d %d", &placeHolderIncome, &placeHolderCount);
    newNode->income = placeHolderIncome;
    newNode->count = placeHolderCount;
    if(head != NULL){
       if(size == 0){
            return head;
        }
        head = insert(head, newNode);
        printf("New leaf\n");
        readData(fPtr, head, size-1);
        
    }else{
        head = newNode;
        printf("new head\n");
        readData(fPtr, head, size-1);
        
    }
    
}


void printInOrder(struct tree_node *nodePtr) {

  // Only traverse the node if it's not null.
  if (nodePtr != NULL) {
    printInOrder(nodePtr->left); // Go Left.
    printf("(%d, %d), ", nodePtr->income, nodePtr->count); // Print the root.
    printInOrder(nodePtr->right); // Go Right.
  }
}

void leafNodeTotal(struct tree_node *nodePtr, int total){

    if(nodePtr != NULL){
        leafNodeTotal(nodePtr->left, total);
        if(isLeaf(nodePtr) == 1){
            printf("%d ", nodePtr->income);
            total++;
        }
        leafNodeTotal(nodePtr->right, total);
    }
}

int isLeaf(struct tree_node *leaf) {

  return (leaf->left == NULL && leaf->right == NULL);
}

void lowestIncome(struct tree_node *nodePtr){
    if(nodePtr != NULL){
        lowestIncome(nodePtr->left);
        if(isLeaf(nodePtr) == 1){
            printf("Total People with the lowest income: %d", nodePtr->count);
        }
    }
}

int main(){
    FILE* readFile;
    int numOfLeaves;
    int total = 0;
    readFile = fopen("in.txt", "r");
    struct tree_node *root = NULL;
    struct tree_node *leftLeaf = NULL;
    fscanf(readFile, "%d", &numOfLeaves);
    root = readData(readFile, root, numOfLeaves);
    printf("Tree constructed from the file\n");
    printf("In Order: ");
    printInOrder(root);
    printf("\n");
    printf("Income in Leaf Nodes: ");
    leafNodeTotal(root, total);
    printf("Counts: %d", total);
    printf("\n");
    lowestIncome(root);
    


}