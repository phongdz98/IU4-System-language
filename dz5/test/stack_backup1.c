#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100

typedef struct stack {
    int top;
    int A[MAXSIZE];
} stack;
void Init (stack *s);
int isempty(stack s);
int isfull(stack s);
void pop(stack *s);
void push(stack *s);
void list(stack *s);

int main(){
    int choice;
    stack s;
    Init(&s);
    while (1){
        printf("\n*********MENU**********");
        printf("\n1. Push");
        printf("\n2. Pop");
        printf("\n3. List");
        printf("\n4. Exit");
        printf("\nEnter the choice:");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1: push(&s);
            break;
        case 2: pop(&s);
            break;
        case 3: list(&s);
            break;
        case 4: exit(0);
            break;          
        default:
            printf("\nInvalid choice!!!");
        }
    }

    return 0;
}
void Init (stack *s){
    s->top = -1;
}

int isempty(stack s){
    if (s.top == -1) {
        return 1;
    }
    else{
        return 0;
    }
}

int isfull(stack s){
    if(s.top == MAXSIZE -1){
        return 1;
    }
    else {
        return 0;
    }
}

void pop(stack *s){
    int data;
    if(!isempty(*s)){
        s->top --;
    }
    else {
        printf("Stack is empty!");
    }
}

void push(stack *s){
    int data;
    if(!isfull(*s)){
        printf("\nEnter data:");
        scanf("%d",&data);
        s->top ++;
        s->A[s->top] = data;
    }
    else {
        printf("\nStack is full!");
    }
}
void list(stack *s){
    if(s->top == -1){
        printf("\nUnderflow!");

    }
    else{
        int a;
        
        for(int i= s->top;i >-1;i--){
            printf("%d \n",s->A[i]);
        }
        a=s->top;
        for(int i= s->top;i >-1;i--){
            pop(s);
        }
    }
}