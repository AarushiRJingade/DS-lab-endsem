#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>

struct Node{
    int coeff;
    int expo;
    struct Node* next;
    struct Node* prev;
};

struct Node* createNode(int coeff,int expo)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if(newNode == NULL)
    {
        printf("Memory not allocated");
        return NULL;
    }

    newNode->coeff = coeff;
    newNode->expo = expo;
    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}

void insertSorted(struct Node** head, struct Node** tail, int expo, int coeff)
{
    if(coeff == 0)
        return;

    struct Node* newNode = createNode(coeff,expo);

    //empty list
    if(*head == NULL)
    {
        *head = *tail = newNode;
        return;

    }

    struct Node* temp = *head;

    while(temp != NULL && temp->expo > expo)
    {
        temp = temp->next;
    }

    //adding or subtracting same expo coeffients
    if(temp != NULL && temp->expo == expo)
    {
        temp->coeff += coeff;
        free(newNode);

        if(temp->coeff == 0)//cancels out
        {
            if(temp == *head)
            {
                *head = temp->next;
                (*head)->prev = NULL;
            }
            else if(temp == *tail)
            {
                *tail = temp->prev;
                (*tail)->next = NULL;
            }
            else
            {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }
            free(temp);
        }
        return;
    }
    
    //largest expo
    if(temp == *head)
    {
        newNode->next = *head;
        (*head)->prev = newNode;
        *head = newNode;
    }

    else if(temp == NULL)
    {
        newNode->prev = *tail;
        (*tail)->next = newNode;
        *tail = newNode;
    }
    else
    {
        newNode->next = temp;
        newNode->prev = temp->prev;
        temp->prev->next = newNode;
        temp->prev = newNode;
    }

    return;
}

void insertRear(struct Node** head, struct Node** tail,int coeff,int expo)
{
    if(coeff == 0)
        return;

    struct Node* newNode = createNode(coeff,expo);
    if(*head == NULL)
    {
        *head = *tail = newNode;
        return;
    }
    else
    {
        (*tail)->next = newNode;
        newNode->prev = *tail;
        *tail = newNode;
    }
}

struct Node* addpoly(struct Node* poly1, struct Node* poly2)
{
    struct Node* resHead = NULL;
    struct Node* resTail = NULL;

    while(poly1 != NULL && poly2 != NULL)
    {
        if(poly1->expo == poly2->expo)
        {
            int sum = poly1->coeff + poly2->coeff;
            insertRear(&resHead,&resTail,sum,poly1->expo);
            poly1 = poly1->next;
            poly2 = poly2->next;
        }

        else if(poly1->expo > poly2->expo)
        {
            insertRear(&resHead,&resTail,poly1->coeff,poly1->expo);
            poly1 = poly1->next;
        }
        
        else
        {
            insertRear(&resHead,&resTail,poly2->coeff,poly2->expo);
            poly2 = poly2->next;
        }
    }

    while(poly1 != NULL)
    {
        insertRear(&resHead,&resTail,poly1->coeff,poly1->expo);
        poly1 = poly1->next;
    }   

    while(poly2 != NULL)
    {
        insertRear(&resHead,&resTail,poly2->coeff,poly2->expo);
        poly2 = poly2->next;       
    }
    
    return resHead;
}

void display(struct Node* head)
{
    if(head == NULL)
    {
        printf("0\n");
        return;
    }

    struct Node* temp = head;

    while(temp != NULL)
    {
        if(temp->coeff >= 0)
        {
            printf(" + ");
        }
        else
        {
            printf(" - ");
        }

        printf("%d",abs(temp->coeff));

        if(temp->expo == 1)
        {
            printf("x");
        }
        else
        {
            printf("x^%d",temp->expo);
        }

        temp = temp->next;
    }

    printf("\n");
}

void createPoly(struct Node** head, struct Node** tail)
{
    int n,coeff,expo;
    printf("Enter the number of terms in polynomial: ");
    scanf("%d",&n);

    for(int i = 1; i <= n; i++)
    {
        printf("Term %d:\n",i);
        printf("Enter coeff and expo:\n");
        scanf("%d",&coeff);
        scanf("%d",&expo);
        insertSorted(head,tail,expo,coeff);
    }
    
}

int main()
{
    struct Node* poly1Head = NULL;
    struct Node* poly1Tail = NULL;
    struct Node* poly2Head = NULL;
    struct Node* poly2Tail = NULL;
    struct Node* resHead = NULL;

    createPoly(&poly1Head,&poly1Tail);
    createPoly(&poly2Head,&poly2Tail);

    printf("Polynomial 1:\n");
    display(poly1Head);

    printf("polynomial 2:\n");
    display(poly2Head);

    resHead = addpoly(poly1Head,poly2Head);
    printf("\nResult polynomial:\n");
    display(resHead);

    return 0;
}