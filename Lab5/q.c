#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node{
    int data;
    struct Node* next;
    struct Node* prev;
};

struct Node* createNode(int data)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if(newNode == NULL)
    {
        printf("Memory allocation failed");
        return NULL;
    }

    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}

void insertRear(struct Node** head, struct Node** tail, int data)
{
    // first element being inserted
    if(*head == NULL)
    {
        struct Node* newNode = createNode(data);
        *head = *tail = newNode;
        return; 
    }

    

    struct Node* newNode = createNode(data);
   ( *tail)->next = newNode;
    newNode->prev = *tail;
    *tail = newNode;
}

void deleteRear(struct Node** head, struct Node** tail)
{
    if(*tail == NULL)
    {
        printf("List is empty.");
        return;
    }

    struct Node* temp = *tail;

    //only one node
    if(*head == *tail)
    {
        *head = *tail = NULL;
    }
    else
    {
        *tail = (*tail)->prev;
        (*tail)->next = NULL;
    }

    free(temp);

}

void insertAtpos(struct Node** head,struct Node** tail, int pos,int data)
{
    if(pos < 1)
    {
        printf("Invalid position");
        return;
    }

    struct Node* newNode = createNode(data);
    struct Node* temp = *head;
    if(pos == 1)
    {
        //no node present
        if(*head == NULL)
        {
            *head = *tail = newNode;
            return;
        }
        else
        {
            newNode->next = *head;
            *tail = *head;
            *head = newNode;
            return;
        }

    }

    for(int i = 1; i < pos-1 && temp != NULL ; i++)
    {
        temp = temp->next;
    }

    if(temp == NULL)
    {
        printf("Position out of bounds");
        free(newNode);
        return;
    }

    //last node
    if(temp == *tail)
    {
        (*tail)->next = newNode;
        newNode->prev = *tail;
        *tail = newNode;
    }
    else
    {
        newNode->next = temp->next;
        newNode->prev = temp;
        temp->next->prev = newNode;
        temp->next = newNode;
    }

    return;
}

void deleteAtpos(struct Node** head,struct Node** tail,int pos)
{
    if(*head == NULL)
    {
        printf("List is empty");
        return;
    }

    if(pos < 1)
    {
        printf("Invalid position");
        return;
    }

        struct Node* temp = *head;
    if(pos == 1)
    {
        *head = (*head)->next;
        if(*head != NULL)
        {
            (*head)->prev = NULL;
            
        }
        else
        {
            *tail = NULL;
            
        }
        free(temp);
        return;
    }



    for(int i = 1; i<pos && temp!=NULL ;i++)
    {
        temp = temp->next;
    }

    if(temp == NULL)
    {
        printf("position out of bounds");
        return;
    }
    if(temp == *tail)
    {
        *tail = (*tail)->prev;
        (*tail)->next = NULL;
    }

    else
    {
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
    }
    free(temp);
}

void insertAfter(struct Node** head,struct Node** tail,int data,int target)
{
    if(*head == NULL)
    {
        printf("List is empty.");
        return;
    }


    struct Node* temp = *head;
    while(temp != NULL && temp->data != target)
    {
        temp = temp->next;
    }

    if(temp == NULL)
    {
        printf("Element not found.");
        return;
    }

    if(temp == *tail)
    {
        struct Node* newNode = createNode(data);
        (*tail)->next = newNode;
        newNode->prev = *tail;
        *tail = newNode;
    }
    else
    {
        struct Node* newNode = createNode(data);
        newNode->next = temp->next;
        newNode->prev = temp;
        temp->next->prev = newNode;
        temp->next = newNode;
    }

    return;
}

void traverseForward(struct Node* head)
{
    if(head == NULL)
    {
        printf("List is empty");
        return;
    }

    struct Node* temp = head;

    while(temp != NULL)
    {
        printf("%d ->",temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
        return;
}

void traverseReverse(struct Node* tail)
{
    if(tail == NULL)
    {
        printf("List is empty.");
        return;
    }

    struct Node* temp = tail;
    while(temp != NULL)
    {
        printf("%d ->",temp->data);
        temp = temp->prev;
    }
    printf("NULL\n");
    return;
}

int main()
{
    struct Node* head = NULL;
    struct Node* tail = NULL;
    int choice,data,target,pos;

    do
    {
        printf("\n--- Doubly Linked List Operations ---\n");
        printf("1. Insert at Rear\n");
        printf("2. Delete from Rear\n");
        printf("3. Insert at Position\n");
        printf("4. Delete from Position\n");
        printf("5. Insert After Value\n");
        printf("6. Traverse Forward\n");
        printf("7. Traverse Reverse\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert at rear: ");
                scanf("%d", &data);
                insertRear(&head, &tail, data);
                break;
            case 2:
                deleteRear(&head, &tail);
                break;
            case 3:
                printf("Enter position (1-based): ");
                scanf("%d", &pos);
                printf("Enter data to insert: ");
                scanf("%d", &data);
                insertAtpos(&head, &tail, pos, data);
                break;
            case 4:
                printf("Enter position to delete (1-based): ");
                scanf("%d", &pos);
                deleteAtpos(&head, &tail, pos);
                break;
            case 5:
                printf("Enter target value to insert AFTER: ");
                scanf("%d", &target);
                printf("Enter data to insert: ");
                scanf("%d", &data);
                insertAfter(&head, &tail, data, target);
                break;
            case 6:
                traverseForward(head);
                break;
            case 7:
                traverseReverse(tail);
                break;
            case 8:
                printf("Exiting program...\n");
                // Clean up memory
                while (head != NULL) {
                    deleteRear(&head, &tail);
                }
                return 0;
            default:
                printf("Invalid choice! Please select a valid option (1-9).\n");
        }
    }while(choice!=8);
    return 0;

}