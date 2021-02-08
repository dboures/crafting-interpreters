#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

void string_init (char* string_ptr)
{
    char *ptr = malloc(16);
    *string_ptr = ptr;
}

void string_free(char** string_ptr) 
{
    free(*string_ptr);
}

void string_set(string_t** destination, char* value)
{
    *destination=realloc(*destination, sizeof(char)*new_size + 1);

    if(*destination == NULL)
    {
        printf("Unable to realloc ptr!??");
    } else {
        strcpy(*destination, value);
    }
}

void push(struct Node** head_ref, int new_data)
{
    // allocate node 
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    // put in the new data
    new_node->data = new_data;
    // make next of new node head, and make previous null
    new_node->next = (*head_ref);
    new_node->prev = NULL;
    // change prev of head node to new node
    if ((*head_ref) != NULL)
        (*head_ref)->prev = new_node;
    //move the head to point to a new node
    (*head_ref) = new_node;
}

void insertBefore(struct Node** head_ref, struct Node* next_node, int new_data)
{
    //check if next_node is null
    if (next_node == NULL) {
        printf("the given next_node cannot be NULL");
        return;
    }

    // allocate node 
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    // put in the new data
    new_node->data = new_data;


    // prev of new node is prev of next node
    new_node->prev = next_node->prev;
    //next of new node is next node
    new_node->next = next_node;
    // prev of next nod is new node
    next_node->prev = new_node;

    //set next of new node - 1 to new node
    if (new_node->prev != NULL)
        new_node->prev->next = new_node;
    else // if prev of new node is null, it's the new head
        (*head_ref) = new_node;

}

void myDelete(struct Node* node, int node_data)
{
    while (node->data != node_data){
        node = node->next;
        if (node == NULL){
            return;
        }
    }
    //we have reached the node

    //adjust ptrs from node
    node->next->prev = node->prev;
    node->prev->next = node->next;

    //is that it?


}

void delete(struct Node** head_ref, struct Node* del)
{
    //to take in just a value, iterate until we get to del, then do this

    if (*head_ref == NULL || del == NULL){
        return;
    }

    if (*head_ref == del)
        *head_ref = del->next;

    if (del->next != NULL)
        del->next->prev = del->prev;

    if (del->prev != NULL)
        del->prev->next = del->next;

    //free memory
    free(del);
    return;


}

void printList(struct Node* node)
{
    struct Node* last;
    while (node != NULL){
        printf(" %d ", node->data); //%s
        last = node;
        node = node->next;
    }
}

int indexOf(struct Node* node, int find_data)
{
    //0 indexed
    int count = 0;
    while (node->data != find_data){
        node = node->next;
        count += 1;
        if (node == NULL){
            return -1;
            break;
        }
    }
    return count;
}

int main()
{
    /* Start with the empty list */
    struct Node* head = NULL;
    push(&head, 7);
 
    push(&head, 1);
 
    push(&head, 4);
    push(&head, 5);
    push(&head, 6);
 
    // Insert 8, before 1. So linked list becomes
    // 4->8->1->7->NULL
    insertBefore(&head, head->next, 8);
 
    printf("Created DLL is: ");
    printList(head);
    printf("\n");

    //Delete 4
    delete(&head,head->next);
    printf("Created DLL is: ");
    printList(head);
    printf("\n");

    printf(" %d ", indexOf(head, 1));
    printf("\n");


    return 0;
}
