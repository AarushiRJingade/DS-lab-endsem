    #include<stdio.h>
    #include<stdlib.h>

    struct Node{
        int data;
        struct Node* next;
    };

    struct Node* createNode(int data)
    {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        if(newNode == NULL)
        {
            printf("Memory not allocated");
            return NULL;
        }

        newNode->data = data;
        newNode->next = NULL;
        return newNode;
    }

    void displayList(struct Node* head)
    {
        if(head == NULL)
        {
            printf("List is empty.");
            return;
        }

        struct Node* temp = head;
        while(temp != NULL)
        {
            printf("%d ->",temp->data);
            temp =temp->next;
        }
        printf("NULL\n");
    }

    void insertBefore(struct Node** head,int target, int data)
    {
        if(*head == NULL)
        {
            printf("List is empty.");
            return;
        }

        if((*head)->data == target)
        {
            struct Node* newNode = createNode(data);
            newNode->next = *head;
            *head = newNode;
            return;
        }

        struct Node* temp = *head;
        while(temp->next != NULL && temp->next->data != target)
        {
            temp = temp->next;
        }

        if(temp->next == NULL)
        {
            printf("Target element not found.");
            return;
        }

        struct Node* newNode = createNode(data);
        newNode->next = temp->next;
        temp->next = newNode;
    }

    void insertAfter(struct Node* head, int target, int data)
    {
        if(head == NULL)
        {
            printf("List is empty");
            return;
        }

        struct Node* temp = head;

        while(temp != NULL && temp->data != target)
        {
            temp = temp->next;
        }

        if(temp == NULL)
        {
            printf("target element not found");
            return;
        }

        struct Node* newNode = createNode(data);
        newNode->next = temp->next;
        temp->next = newNode;

    }

    void deleteElement(struct Node** head, int target)
    {
        if(head == NULL)
        {
            printf("List is empty.");
            return;
        }

        if((*head)->data == target)
        {
            struct Node* todel = *head;
            *head = todel->next;
            free(todel);
            return;
        }

        struct Node* temp = *head;

        while(temp->next != NULL && temp->next->data != target)
        {
            temp = temp->next;
        }

        if(temp == NULL)
        {
            printf("Target not found");
            return;
        }

        struct Node* todel;
        todel = temp->next;
        temp->next = todel->next;
        free(todel);

    }

    void reverseList(struct Node** head)
    {
        if(head == NULL || (*head)->next == NULL)
        {
            printf("List is empty or has only one element");
            return;
        }

        struct Node* prev = NULL;
        struct Node* curr = *head;
        struct Node* next = NULL;

        while(curr != NULL)
        {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        *head = prev;
    }

    void sortList(struct Node ** head)
    {
        if(head == NULL || (*head)->next == NULL)
        {
            printf("List has only one or no elements");
            return;
        }

        int swapped;
        struct Node* ptr;
        struct Node* lptr = NULL;

        do
        {
            swapped = 0;
            ptr = *head;

            while(ptr->next != lptr )
            {
                if(ptr->data > ptr->next->data)
                {
                    int temp = ptr->data;
                    ptr->data = ptr->next->data;
                    ptr->next->data = temp;
                    swapped = 1;
                }

                ptr = ptr->next;
            }
            lptr = ptr;

        }while(swapped);
    }

    void deleteAlternate(struct Node* head)
    {
        if(head == NULL)
        {
            printf("List is empty");
            return;
        }

        struct Node* prev = head;
        struct Node* curr = head->next;

        while(prev != NULL && curr != NULL)
        {
            prev->next = curr->next;
            free(curr);

            prev = prev->next;
            if(prev != NULL)
            {
                curr = prev->next;
            }
        }
    }

    void insertSorted(struct Node** head, int data) {
        struct Node* newNode = createNode(data);

        // Edge Case: Empty list or element is smaller than head
        if (*head == NULL || (*head)->data >= data) {
            newNode->next = *head;
            *head = newNode;
            return;
        }

        struct Node* current = *head;
        // Traverse to find the correct insertion point
        while (current->next != NULL && current->next->data < data) {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }

    void insertAtEnd(struct Node** head, int data) {
        struct Node* newNode = createNode(data);
        if (*head == NULL) {
            *head = newNode;
            return;
        }
        struct Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    // Driver code to demonstrate functionality
    int main() {
        struct Node* head = NULL;

        printf("--- Building Initial List ---\n");
        insertAtEnd(&head, 25);
        insertAtEnd(&head, 15);
        insertAtEnd(&head, 50);
        displayList(head);

        printf("\n--- 1. Insert 10 before 25 ---\n");
        insertBefore(&head, 25, 10);
        displayList(head);

        printf("\n--- 2. Insert 40 after 25 ---\n");
        insertAfter(head, 25, 40);
        displayList(head);

        printf("\n--- 3. Delete node containing 15 ---\n");
        deleteElement(&head, 15);
        displayList(head);

        printf("\n--- 4. Reverse the linked list ---\n");
        reverseList(&head);
        displayList(head);

        printf("\n--- 5. Sort the list in ascending order ---\n");
        sortList(&head);
        displayList(head);

        printf("\n--- 6. Insert 28 into sorted list ---\n");
        insertSorted(&head, 28);
        displayList(head);

        printf("\n--- 7. Delete every alternate node ---\n");
        deleteAlternate(head);
        displayList(head);

        return 0;
    }