#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Patient{
    char name[50];
    int age;
    int priority;
};

struct Node{
    struct Patient data;
    struct Node* next;
};

struct queue{
    struct Node* front;
};

struct queue* createQueue()
{
    struct queue* q = (struct queue*)malloc(sizeof(struct queue));
    if(q == NULL)
    {
        printf("Memory not allocated.");
        return NULL;
    }

    q->front = NULL;
    return q;
}

void enqueue(struct queue* q, struct Patient newP)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    if(newNode == NULL)
    {
        printf("Memory not allocated.");
        return;
    }

    newNode->data = newP;
    newNode->next = NULL;

    struct Node* temp = q->front;

    if(q->front == NULL || newP.priority <= q->front->data.priority)
    {
        newNode->next = q->front;
        q->front = newNode;
        printf("\nNew patient added\n");
        return;
    }

    if(temp->next != NULL && newP.priority >= temp->next->data.priority)
    {
        temp = temp->next;
    }

    newNode->next = temp->next;
    temp->next = newNode;

    printf("new Patient added");


}

void dequeue(struct queue* q)
{
    if(q->front == NULL)
    {
        printf("list is empty.");
        return;
    }

    struct Node* temp = q->front;

    q->front = q->front->next;

    printf("\n===Treating patient===\n");
    printf("Name: %s\n",temp->data.name);
    printf("Age: %d\n",temp->data.age);
    printf("Priority: %d\n",temp->data.priority);

    free(temp);
    return;
}

void display(struct queue* q)
{
    if(q->front == NULL)
    {
        printf("queue is empty");
        return;
    }

    struct Node* temp = q->front;

    printf("===Patient next in line===");
    int i = 1;
    while(temp != NULL)
    {
        printf("\nPatient: %d",i);
        printf("Name: %s\n",temp->data.name);
        printf("Age: %d\n",temp->data.age);
        printf("Priority: %d\n\n",temp->data.priority);
        i++;
        temp = temp->next;
    }

}

int main()
{
    struct queue* q = createQueue();
    int choice;
    struct Patient p;
    do{
        printf("\n=== Hospital Priority Queue ===\n");
        printf("1. Register New Patient (Enqueue)\n");
        printf("2. Call Next Patient (Dequeue)\n");
        printf("3. View Patient Queue (Display)\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nEnter Patient Name: ");
                // Space before %[^\n] allows it to read strings with spaces safely
                scanf(" %[^\n]s", p.name); 
                
                printf("Enter Patient Age: ");
                scanf("%d", &p.age);
                
                printf("Enter Priority (1 = Highest Emergency, 5 = Routine): ");
                scanf("%d", &p.priority);
                
                enqueue(q, p);
                break;
                
            case 2:
                dequeue(q);
                break;
                
            case 3:
                display(q);
                break;
                
            case 4:
                printf("Exiting program and clearing memory...\n");
                
                // Clean up remaining nodes to prevent memory leaks before exiting
                while (q->front != NULL) {
                    struct Node* temp = q->front;
                    q->front = q->front->next;
                    free(temp);
                }
                free(q); 
                
                return 0; 
                
            default:
                printf("Invalid choice! Please enter a number between 1 and 4.\n");
        }
    
    }while(choice != 4);
    return 0;
}