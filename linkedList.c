/*
* A simple implimentation of linked list to store the parameters
*/
#include <stdio.h>
#include <stdlib.h>
#include "parameters.c"

static int size=0;
static struct Node* head;
/*
* A Structure of a Node of a Single Linked List
* The Structure conatins the data and the pointer to the next Node
*/
struct Node
{
    int data;
    struct Node* next;
};

/*
* A function to add a new node with a particular data to the starting of the list
* Requires Parameter - a reference (pointer to pointer) to the head of the list
  and the data to insert
*/
void add(struct Node** head_ref, int new_data)
{
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    new_node->data  = new_data;

    // link the old list off the new node
    new_node->next = (*head_ref);

    // head points to new node 
    (*head_ref)    = new_node; 
    size++;
}

/*
* A function to the data from a particular index
* Requires Parameter - a pointer to the head of the list
  and the index of the data to get
* Returns the data at the index
*/
int getElementAt(struct Node* head, int index)
{
    struct Node* current = head;
    int count = 0; //current node

    //will run till we reach end of the list
    while (current != NULL) 
    {
       if (count == index)
          return(current->data);
       count++;
       current = current->next;
    }
    exit(0);
}

/*  @ for debugging purpose
* A function to display the linked list
** depriciated function
*/
void displayList(struct Node* head){
    while(head!=NULL){
        printf("%d ",head->data);
        head=head->next;
    }
    printf("\n%d \n",size);
}

/*
* A function to get all the parameters and return them in a linked list
*/
struct Node* getParameters()
{
    head = NULL; //list is empty at the start
    
    evaluateMousePointer();
    int mousex=getMouseX();
    int mousey=getMouseY();
    add(&head,mousex);
    add(&head,mousey);

    int processCount=getProcessCount();
    int timeInMillis=getTime();
    add(&head,processCount);
    add(&head,timeInMillis);

    int temperature = getTemperature();
    add(&head,temperature);

    //displayList(head);
    return head;
}
