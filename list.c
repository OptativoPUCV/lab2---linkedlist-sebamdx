#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List* nuevaLista=(List*)malloc(sizeof(List));
  if (nuevaLista!=NULL) {
      nuevaLista->head=NULL;
      nuevaLista->tail=NULL;
      nuevaLista->current=NULL;
    }
  return nuevaLista;
}

void * firstList(List * list) {
  if (list!=NULL && list->head!=NULL) {
      list->current=list->head;
      return list->current->data;
  }
  return NULL;
}

void * nextList(List * list) {
  if (list!=NULL && list->current!=NULL && list->current->next!=NULL) {
      list->current=list->current->next;
      return list->current->data;
  }
  return NULL;
}

void * lastList(List * list) {
  if (list!=NULL && list->tail!=NULL) {
    list->current=list->tail;
    return list->current->data;
  }
  return NULL;
}

void * prevList(List * list) {
  if (list!=NULL && list->current!=NULL && list->current->prev!=NULL) {
    list->current=list->current->prev;
    return list->current->data;
  }
  return NULL;
}

void pushFront(List * list, void * data) {
   if (list!=NULL) {
      Node * nuevoNodo=createNode(data);
      if (list->head==NULL) {
        list->head=nuevoNodo;
        list->tail=nuevoNodo;
        list->current=nuevoNodo;
      } else {
        nuevoNodo->next=list->head;
        list->head->prev=nuevoNodo;
        list->head=nuevoNodo;
      }
  }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
   if (list!=NULL && list->current!=NULL) {
        Node * nuevoNodo=createNode(data);
        nuevoNodo->next=list->current->next;
        nuevoNodo->prev=list->current;
        if (list->current->next!=NULL) {
            list->current->next->prev=nuevoNodo;
        }
        list->current->next=nuevoNodo;
        list->tail=nuevoNodo;
    }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  if (list!=NULL && list->current!=NULL) {
    Node *borrarNodo=list->current;
    void *data=borrarNodo->data;
    if (borrarNodo->prev!=NULL) {
      borrarNodo->prev->next=borrarNodo->next;
    } else {
      list->head=borrarNodo->next;
    }
    if (borrarNodo->next!=NULL) {
        borrarNodo->next->prev=borrarNodo->prev;
    } else {
        list->tail=borrarNodo->prev;
    }
    list->current=borrarNodo->next;
    free(borrarNodo);
    return data;
  }
    return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}