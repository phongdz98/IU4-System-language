#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct User
{
    char name[50];
    char phone[15];
} User;

typedef struct Node
{
    User data;
    struct Node *next;
} Node;

typedef struct DanhSach
{
    struct Node *head;
    struct Node *tail;
} DanhSach;
void init(DanhSach *ds);
Node *createNode(User data);
void addTail(DanhSach *ds, User data);
void remove_user(DanhSach *ds, User data);
void printList(DanhSach ds);
void searchUser(DanhSach ds, char name[]);

int main()
{
    DanhSach ds;
    init(&ds);

    while (1)
    {
        int option;
        printf("\nMenu:\n");
        printf("1. Add user\n");
        printf("2. Remove user\n");
        printf("3. Print list\n");
        printf("4. Search user\n");
        printf("5. Exit\n");
        printf("Enter your option: ");
        scanf("%d", &option);

        User user;
        switch (option)
        {
        case 1:
            printf("Enter user name: ");
            scanf("%s", user.name);
            printf("Enter user phone: ");
            scanf("%s", user.phone);
            addTail(&ds, user);
            break;
        case 2:
            printf("Enter user name: ");
            scanf("%s", user.name);
            remove_user(&ds, user);
            break;
        case 3:
            printList(ds);
            break;
        case 4:
            printf("Enter user name to search: ");
            scanf("%s", user.name);
            searchUser(ds, user.name);
            break;
        case 5:
            exit(0);
            return 0;
        default:
            printf("Invalid option\n");
            break;
        }
    }

    return 0;
}

void init(DanhSach *ds)
{
    ds->head = ds->tail = NULL;
}
Node *createNode(User data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void addTail(DanhSach *ds, User data)
{
    Node *newNode = createNode(data);
    if (ds->head == NULL)
    {
        ds->head = ds->tail = newNode;
    }
    else
    {
        ds->tail->next = newNode;
        ds->tail = newNode;
    }
}
void remove_user(DanhSach *ds, User data)
{
    if (ds->head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    Node *current = ds->head;
    Node *prev = NULL;
    while (current != NULL && strcmp(current->data.name, data.name) != 0)
    {
        prev = current;
        current = current->next;
    }

    if (current == NULL)
    {
        printf("User not found\n");
        return;
    }

    if (prev == NULL)
    {
        ds->head = current->next;
    }
    else
    {
        prev->next = current->next;
    }

    if (current == ds->tail)
    {
        ds->tail = prev;
    }

    free(current);
}

void printList(DanhSach ds)
{
    Node *current = ds.head;
    while (current != NULL)
    {
        printf("%s - %s\n", current->data.name, current->data.phone);
        current = current->next;
    }
}

void searchUser(DanhSach ds, char name[]) {
    Node *current = ds.head;
    int found = 0;
    
    while (current != NULL) {
        if (strcmp(current->data.name, name) == 0) {
            printf("Found user: %s - %s\n", current->data.name, current->data.phone);
            found = 1;
            break;
        }
        current = current->next;
    }
    
    if (!found) {
        printf("User not found\n");
    }
}