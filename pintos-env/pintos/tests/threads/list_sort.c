#include "listpop.h"
#include <list.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct element {
    int priority;
    struct list_elem node;
};

void populate(struct list *list, int * a, int n){
  int i;
  list_init(list);
  for(i = 0; i < n; i++){
    struct element *element = malloc(sizeof(struct element));
    if(element){
      element->priority = a[i];
      list_push_back(list, &element->node);
    }
  }
}

void free_list(struct list *list){
  struct list_elem *elem;
	while (!list_empty(list)) {
    	elem = list_pop_front(list);
    	struct element *element = list_entry(elem, struct element, node);
    	free(element);
	}
}


bool compare(const struct list_elem *a, const struct list_elem *b, void * aux){
  struct element *elem_a = list_entry(a, struct element, node);
  struct element *elem_b = list_entry(b, struct element, node);
  return elem_a->priority < elem_b->priority;
}

void print_sorted(struct list *list){
  list_sort(list, compare, NULL);
  struct list_elem *elem;
  for (elem = list_begin (list); elem != list_end (list);
       elem = list_next (elem))
  {
    struct element *f = list_entry(elem, struct element, node);
    printf("%d ", f->priority);
  }
}

extern void test_list_sort(){
  //Populate a list using ITEMARRAY elements
  struct list list;
  list_init(&list);
  int size = sizeof(ITEMARRAY)/sizeof(int);
  populate(&list, ITEMARRAY, size);
  //Sort it with the function
  print_sorted(&list);
  //Free allocated resources
  free_list(&list);
 }
