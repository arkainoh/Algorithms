#include <stdio.h>
#include <malloc.h>
#define STACK_SIZE 10

typedef struct _stack {
  int top;
  int data[STACK_SIZE];
} stack;
typedef stack* Stack;

Stack newStack() {
  Stack s = (Stack)malloc(sizeof(stack));
  s->top = 0;
  return s;
}

void push(Stack s, int data) {
  s->data[s->top++] = data;
}

int pop(Stack s) {
  return s->data[--s->top];
}

int isFullStack(Stack s) {
  return s->top == STACK_SIZE;
}

int isEmptyStack(Stack s) {
  return s->top == 0;
}

void removeStack(Stack s) {
  free(s);
  s = NULL;
}

int testStack() {
  Stack s = newStack();
  if(isEmptyStack(s)) printf("Stack is empty\n");
  else printf("Stack is not empty\n");

  for(int i = 1; ; i++) {
    if(!isFullStack(s)) {
      push(s, i);
      printf("push(%d)\n", i);
    }
    else {
      printf("Stack is full\n");
      break;
    }
  }

  if(isEmptyStack(s)) printf("Stack is empty\n");
  else printf("Stack is not empty\n");

  for(int i = 1; ; i++) {
    if(!isEmptyStack(s)) printf("pop(): %d\n", pop(s));  
    else {
      printf("Stack is empty\n");
      break;
    }
  }

  removeStack(s);
  return 0;
}

int main() {
  testStack();
  return 0;
}