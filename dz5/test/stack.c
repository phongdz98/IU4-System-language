#include<stdio.h>
#include<stdlib.h>
typedef  struct stack{
    char *name;
    int telephone;
    struct stack *pNext;
} stack;
int isempty(stack **head);
void push(stack **head);
void pop(stack **head);
int size(stack **head);
void list(stack **head);


int main(){

    stack *head = NULL;
    push(&head);
    push(&head);
    pop(&head);
    list(&head);

    return 0;
}
int isempty(stack **head){
    if (*head == NULL){
        return 1;
    }
    return 0;
}
void push(stack **head){
    char *pname = (char *)malloc(sizeof(char)*40);
    int telephone;
    printf("\nEnter name:");
    scanf("%s",pname);
    printf("\nEnter telephone:");
    scanf("%d",&telephone);
    stack *tmp = malloc(sizeof(stack));
    tmp ->name = pname;
    tmp -> telephone = telephone ;
    tmp -> pNext = (*head);
    (*head) = tmp;
}
void pop(stack **head){
    stack *prev = NULL;
    if (isempty(head)){
        printf("\nStack empty!");
    }
    else{
        prev= (*head);
        (*head) = (*head )-> pNext;
        free(prev);
    }
}
int size(stack **head){
    int size =0;
    for (stack *p =(*head);p!=NULL;p=p->pNext){
        size++;
    }
    return size;
}
void list(stack **head){
    for (stack *p =(*head);p!=NULL;p=p->pNext){
        printf("\n%s:%d", p->name,p->telephone);
    }
    printf("\n");
    int s = size(head);
    for (int i=s ; i >0; i--){
        pop(head);
    }
}