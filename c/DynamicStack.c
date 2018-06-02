#include <stdio.h>
#include <malloc.h>
#define INIT_CAPACITY 4

typedef struct _dynamicStack {
  int top;
  int capacity;
  int* data;
} dynamicStack;
typedef dynamicStack* DynamicStack;

DynamicStack newDynamicStack() {
  DynamicStack ds = (DynamicStack)malloc(sizeof(DynamicStack));
  ds->data = (int*)malloc(sizeof(int) * INIT_CAPACITY);
  ds->top = 0;
  ds->capacity = INIT_CAPACITY;
  return ds;
}

void extend(DynamicStack ds) {
  ds->capacity *= 2;
  printf("extend to: %d\n", ds->capacity);
  ds->data = (int*)realloc(ds->data, sizeof(int) * ds->capacity);
}

void curtail(DynamicStack ds) {
  ds->capacity /= 2;
  printf("curtail to: %d\n", ds->capacity);
  ds->data = (int*)realloc(ds->data, sizeof(int) * ds->capacity);
}

void push(DynamicStack ds, int data) {
  if(ds->top >= ds->capacity * 3 / 4) extend(ds);
  ds->data[ds->top++] = data;
}

int pop(DynamicStack ds) {
  if(ds->top <= ds->capacity / 4 && ds->capacity > INIT_CAPACITY) curtail(ds);
  return ds->data[--ds->top];
}

int isEmptyDynamicStack(DynamicStack ds) {
  return ds->top == 0;
}

void removeDynamicStack(DynamicStack ds) {
  free(ds);
  ds = NULL;
}

int testDynamicStack() {
  DynamicStack ds = newDynamicStack();
  if(isEmptyDynamicStack(ds)) printf("DynamicStack is empty\n");
  else printf("DynamicStack is not empty\n");

  for(int i = 1; i < 100; i++) {
      push(ds, i);
      printf("push(%d)\n", i);
  }

  if(isEmptyDynamicStack(ds)) printf("DynamicStack is empty\n");
  else printf("DynamicStack is not empty\n");

  for(int i = 1; ; i++) {
    if(!isEmptyDynamicStack(ds)) {
      printf("pop(): %d\n", pop(ds));  
    }
    else {
      printf("DynamicStack is empty\n");
      break;
    }
  }

  removeDynamicStack(ds);
  return 0;
}

int main() {
  testDynamicStack();
  return 0;
}