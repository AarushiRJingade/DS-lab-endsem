#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct Node{
    int data;
    struct Node* next;
};

struct queue{
    struct Node* rear;
    struct Node* front;
};

struct queue* createQueue()
{
    struct queue* q = (struct queue*)malloc(sizeof(struct queue));
    if(q == NULL)
    {
        printf("memory allocation failed.");
        return NULL;
    }

    q->front = NULL;
    q->rear = NULL;

    return q;
}

void enqueue(struct queue* q, int value)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    if(newNode == NULL)
    {
        printf("Heap memory full");
        return;
    }

    newNode->data = value;
    newNode->next = NULL;

    //queue is empty
    if(q->rear == NULL)
    {
        q->front = newNode;
        q->rear = newNode;
        printf("Enqueued: %d\n",value);
        return;
    }

    q->rear->next = newNode;
    q->rear = newNode;
    printf("Enqueued: %d\n",value);
    return;

}

int dequeue(struct queue* q)
{
    if(q->front == NULL)
    {
        printf("Empty queue.\n");
        return 0;
    }

    struct Node* temp = q->front;
    int value = temp->data;

    q->front = q->front->next;

    if(q->front == NULL)
    {
        q->rear = NULL;
    }

    free(temp);
    printf("Dequeued: %d\n",value);
    return value;
}

void display(struct queue* q)
{
    if(q->front == NULL)
    {
        printf("List is empty.");
        return;
    }

    struct Node* temp = q->front;
    printf("Queue elements:\n");
    while(temp != NULL)
    {
        printf("%d ->",temp->data);
        temp = temp->next;
    }
    printf(" NULL\n");
}

int main()
{
    struct queue* q = createQueue();

    int choice, value;

    do
    {
        printf("\n1.Enqueue");
        printf("\n2.Dequeue");
        printf("\n3.Display");
        printf("\n4.Exit");
        printf("\nEnter your choice:");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1: 
            printf("Enter value: ");
            scanf("%d",&value);
            enqueue(q,value);
            break;

            case 2:
            dequeue(q);
            break;

            case 3:
            display(q);
            break;

            case 4:
            printf("Exiting the program");
            exit(1);
            break;

            default:
            printf("invalid choice");
        }
    } while (choice != 4);
    
}