#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
typedef struct node{
    int data;
    struct node* next;
} node;

void print_list(node* head)
{
    node* cursor = head;
    while(cursor != NULL)
    {
        printf("%d ", cursor->data);
        cursor = cursor->next;
    }
}

node* create(int data,node* next)
{
    node* new_node = (node*)malloc(sizeof(node));
    if(new_node == NULL)
    {
        printf("Error creating a new node.\n");
        exit(0);
    }
    new_node->data = data;
    new_node->next = next;

    return new_node;
}

node* append(node* head, int data)
{
    /* go to the last node */
    node *cursor = head;
    while(cursor->next != NULL)
        cursor = cursor->next;

    /* create a new node */
    node* new_node =  create(data,NULL);
    cursor->next = new_node;

    return head;
}

node* remove_front(node* head)
{
    if(head == NULL)
        return NULL;
    node *front = head;
    head = head->next;
    front->next = NULL;
    /* is this the last node in the list */
    if(front == head)
        head = NULL;
    free(front);
    return head;
}

node* remove_back(node* head)
{
    if(head == NULL)
        return NULL;

    node *cursor = head;
    node *back = NULL;
    while(cursor->next != NULL)
    {
        back = cursor;
        cursor = cursor->next;
    }
    if(back != NULL)
        back->next = NULL;

    /* if this is the last node in the list*/
    if(cursor == head)
        head = NULL;

    free(cursor);

    return head;
}

node* head = NULL;
#define MAX 5
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* create_list(void *arg){
  int max_number = (intptr_t) arg;
  int i;
  for(i = max_number - 5;i<max_number;i++){
    pthread_mutex_lock(&lock);
    if (head == NULL){
      head=create(0,head);
    }
    else{
      append(head,i);
    }
    pthread_mutex_unlock(&lock);
  }
}


int main(void) {
  pthread_t p1, p2;
  pthread_create(&p1, NULL, create_list, (void*)MAX);
  pthread_create(&p2, NULL, create_list, (void*)(2*MAX));

  pthread_join(p1, NULL);
  pthread_join(p2, NULL);

  print_list(head);
  for(int i = 0; i<943853;i++){;}
  printf("\nListo!\n");
  return 0;
}
