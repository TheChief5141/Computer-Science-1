#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define size 100
#define EMPTY -1

struct stack{
    int items[size];
    int top;
};


void initialize(struct stack *stackPtr);
int full(struct stack* stackPtr);
int push(char ch, struct stack *stackPtr);
int isEmpty(struct stack *stackPtr);
char pop(struct stack *stackPtr);
int peek(struct stack *stackPtr);
void print_stack(struct stack *stackPtr);

int checkBalance(char exp[]);

int priority(char ch);
int isOperator(char ch);
char *infixToPostfix(char infix[]);
int isParentheses(char ch1);


int main(){
    int ch;
    char exp[size];
    int valid;

    printf("\n Enter expression: ");
    scanf("%[^\n]s" , exp);

    printf("\nYour input expression: %s", exp);

    valid = checkBalance(exp);

    if(valid){
        char *postfix = infixToPostfix(exp);
        printf("The postfix is: %s\n", postfix);
        free(postfix);
    }


    return 0;
}

int checkBalance(char exp[]){
    int valid = 1;
    struct stack mine;

    initialize(&mine);

    printf("\nChecking balance...\n");
    for(int i = 0; exp[i] != '\0'; i++){
        if(exp[i]== '(' || exp[i] == '{' || exp[i] == '['){
            printf("\n I see a parentheses...\n");
            push(exp[i], &mine);
        }else if(exp[i]==')'){
            char a = pop(&mine);
            if(a == 'I' || a != '('){
                valid = 0;
                printf("\nMissing parentheses\n");
                return valid;
            }
            
        }else if(exp[i]=='}'){
            char a = pop(&mine);
            if(a == 'I' || a!='{'){
                valid = 0;
                printf("\nMissing curly brackets\n");
                return valid;
            }
        }else if(exp[i]==']'){
            char a = pop(&mine);
            if(a == 'I' || a!='['){
                valid = 0;
                printf("\nMissing brackets\n");
                return valid;
            }
        }
        printf("\n So far, valid...\n");
    }

    if(pop(&mine)!='I'){
        valid = 0;
        printf("\nInvalid expression, you have extra brackets");
        return valid;
    }

    if(valid == 1){
        printf("\nValid Expression");
        return valid;
    }
}

char *infixToPostfix(char infix[]){
    struct stack operators;
    initialize(&operators);
    int count = 0;
    char *postfix = (char*)malloc(strlen(infix+1) * sizeof(char));

    printf("\nBeginning of infixToPostfix function");

    for(int i = 0; i < strlen(infix); i++){
        if(isdigit(infix[i])){
            while(isdigit(infix[i])){
                postfix[count] = infix[i];
                i++;
                count++;
            }
            i--;
            postfix[count] = ' ';
            count++;
        }else if(isOperator(infix[i])){
            if(isEmpty(&operators)){
                push(infix[i], &operators);
            }else if(priority(infix[i]) > priority(peek(&operators))){
                push(infix[i], &operators);
            }else{
                while(!isEmpty(&operators) && priority(infix[i]) <= priority(peek(&operators)) && !isParentheses(peek(&operators))){
                    postfix[count] = pop(&operators);
                    count++;
                    postfix[count] = ' ';
                    count++;
                }

                push(infix[i], &operators);
            }
        }else if(infix[i] == '(' || infix[i] == ')'){
            if(infix[i] == '('){
                push(infix[i], &operators);
            }else{
                while(peek(&operators) != '('){
                    postfix[count] = pop(&operators);
                    count++;
                    postfix[count] = ' ';
                    count++;
                }
                pop(&operators);
            }
        }

    }
    while(!isEmpty(&operators)){
        postfix[count] = ' ';
        count ++;
        postfix[count] = pop(&operators);
        count++;
    }
    postfix[count] = '\0';
    printf("\nEnd of infixToPostfix function\n");
    return postfix;
}

int full(struct stack *stackPtr){
    if(stackPtr->top == size - 1){
        return 1;
    }else{
        return 0;
    }
}

int priority(char ch){
    if(ch == '(' || ch== '[' || ch == '{') return 0;
    if(ch == '+' || ch == '-') return 1;
    if(ch == '*' || ch== '/' || ch == '%') return 2;
    if(ch == '^') return 3;
}

int isOperator(char ch){
    if(ch == '+' || ch == '-' || ch == '*' || ch == '/'){
        return 1;
    }
    return 0;
}

int isParentheses(char ch1){
    if(ch1 == '(' || ch1 == ')'){
        return 1;
    }
    return 0;
}

void initialize(struct stack *stackPtr){
    stackPtr->top = -1;
}

int push(char ch, struct stack *stackPtr){
    if(full(stackPtr)){
        return 0;
    }
    printf("\nIt has pushed.\n");
    stackPtr->items[stackPtr->top + 1] = ch;
    (stackPtr->top)+=1;
    
    return 1;
}

int isEmpty(struct stack *stackPtr){
    return (stackPtr->top == -1);
}

int peek(struct stack *stackPtr){
    if(isEmpty(stackPtr)){
        return EMPTY;
    }else{
        return stackPtr->items[stackPtr->top];
    }
}

char pop(struct stack *stackPtr){
    char retval;
    if(isEmpty(stackPtr)){
        return 'I';
    }else{
        retval = stackPtr->items[stackPtr->top];
        (stackPtr->top)--;
        return retval;
    }
}

void print_stack(struct stack* stackPtr){
    for(int i = 0; i <= stackPtr->top; i++){
        printf("%c-->", stackPtr->items[i]);

        printf("/n");
    }

}