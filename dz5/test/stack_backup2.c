#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAXSIZE 100
typedef struct stack {
    char **name;
    int *telephone;
    int capacity;
    int size;
} stack;
stack *create_stack(int capacity);
void destroy_stack(stack *s);
int isempty(stack *s);
bool isfull(stack *s);
void pop(stack *s);
bool push(stack *s);
void list(stack *s);

int main(){
    int choice;
    stack *s = create_stack(MAXSIZE);
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
        case 1: push(s);
            break;
        case 2: pop(s);
            break;
        case 3: list(s);
            break;
        case 4: exit(0);
            break;          
        default:
            printf("\nInvalid choice!!!");
        }
    }

    destroy_stack(s);

    return 0;
}

stack *create_stack(int capacity){
    if (capacity <=0) return NULL;
    stack *s = (stack*)malloc(sizeof(stack));
    if (s == NULL) return NULL;
    s->name=(char**)malloc(sizeof(char*)*capacity);
    s->telephone=(int*)malloc(sizeof(int)*capacity);
    if (s->name == NULL || s -> telephone == NULL){
        free(s);
        return NULL;
    }
    s->capacity=capacity;
    s->size = 0;
    return s;
}
void destroy_stack(stack *s){
    free(s->name);
    free(s->telephone);
    free(s);
}
bool isfull(stack *s){
    return s->capacity == s ->size;
}
int isempty(stack *s){
    if (!s->size ) {
        return 1;
    }
    else{
        return 0;
    }
}
bool push(stack *s){
    char *pname = (char *)malloc(sizeof(char)*40);
    int telephone;
    if(isfull(s)) {
        printf("\nStack is full!!");
        return false;
    }
    printf("\nEnter name:");
    scanf("%s",pname);
    s->name[s->size] = pname;
    printf("\nEnter telephone:");
    scanf("%d",&telephone);
    s->telephone[s->size] = telephone;
    s->size ++;
    return true;
}
void pop(stack *s){
    if(!isempty(s)){
        s->size--;
    }
    else {
        printf("Stack is empty!");
    }
}

void list(stack *s){
    if(s->size == 0){
        printf("\nUnderflow!");

    }
    else{
        for(int i=  s->size-1;i >=0;i--){
            printf("\n%s : %d ",s->name[i],s->telephone[i]);
        }
        for(int i= s->size-1;i >=0;i--){
            pop(s);
        }
    }
}

