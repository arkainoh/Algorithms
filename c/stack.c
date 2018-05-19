#include <stdio.h>
#define STACK_SIZE 5

static int top;
int Stack[STACK_SIZE];

void initStack() {
  top = 0;
}

void push(int x) {
  Stack[top++] = x;
}

int pop() {
  return Stack[--top];
}

int isFullStack() {
  return top == STACK_SIZE;
}

int isEmptyStack() {
  return top == 0;
}

int testStack() {
  initStack();
  if(isEmptyStack()) printf("Stack is empty\n");
  else printf("Stack is not empty\n");

  for(int i = 1; ; i++) {
    if(!isFullStack()) {
      push(i);
      printf("push(%d)\n", i);
    }
    else {
      printf("Stack is full\n");
      break;
    }
  }

  if(isEmptyStack()) printf("Stack is empty\n");
  else printf("Stack is not empty\n");

  for(int i = 1; ; i++) {
    if(!isEmptyStack()) {
      printf("pop(): %d\n", pop());  
    }
    else {
      printf("Stack is empty\n");
      break;
    }
  }
  return 0;
}

int main() {
  testStack();
  return 0;
}