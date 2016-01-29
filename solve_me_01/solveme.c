#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int id;
  struct Node* next;
} node;

int solveme(int n) {
  int nodeListLen = n;


  node* current = malloc(sizeof(node));
  node* head = current;
  current->id = 0;

  //initial linked list
  for (int i = 1; i < n; i++) {
    node* nextNode = malloc(sizeof(node));
    nextNode->id = i;
    current->next = nextNode;
    current = nextNode;
  }

  //make it circular
  current->next = head;

  while (nodeListLen > 1) {
    //remove node
    node* temp = head->next;
    head->next = temp->next;
    free(temp);
    //length - 1
    nodeListLen--;

    head = head->next;
  }

  return head->id + 1;


}

int main(){
  /* int N=3; */
  /* int N=4; */
  int N=11;

  printf("%d\n", solveme(N));

  return 0;
}
