#include <stdio.h>
#include <malloc.h>

template <typename T>
class HeapManager {
private:
  int capacity = 0;
  int remaining = 0;
  int cursor = 0;
  bool* used = NULL;
  T** items = NULL;

  int _moveToUnused() {
    register int cnt = 0;
    while(used[cursor]) {
      cursor = (cursor + 1) % capacity;
      cnt++;
      if(cnt == capacity) {
        printf("<ERROR> HeapManager: Couldn't find unused one\n");
        return -1;
      }
    }
    return 0;
  }

  int _moveToUsed() {
    register int cnt = 0;
    while(!used[cursor]) {
      cursor = (cursor + 1) % capacity;
      cnt++;
      if(cnt == capacity) {
        printf("<ERROR> HeapManager: Couldn't find used one\n");
        return -1;
      }
    }
    return 0;
  }

  int _moveToItem(T* item) {
    register int cnt = 0;
    cursor = 0;
    while(items[cursor] != item) {
      cursor = (cursor + 1) % capacity;
      cnt++;
      if(cnt == capacity) {
        printf("<ERROR> HeapManager: Couldn't find the item %x\n", item);
        return -1;
      }
    }
    return 0;
  }

public:
  HeapManager(int capacity) {
    init(capacity);
  }

  T* get() {
    if(isEmpty()) {
      printf("<ERROR> Heap Manager: Nothing to get");
      return NULL;
    }

    if(_moveToUnused() != -1) {
      used[cursor] = true;
      remaining--;
      return items[cursor];
    } else {
      return NULL;
    }
  }

  void drop(T* item) {
    if(isFull()) {
      printf("<ERROR> Heap Manager: Nothing to be dropped");
      return;
    }

    if(_moveToItem(item) != -1) {
      remaining++;
      used[cursor] = false;
    }
  }

  bool isFull() {
    return remaining == capacity;
  }

  bool isEmpty() {
    return !remaining;
  }

  void init(int capacity) {
    if(used || items) {
      printf("<ERROR> Heap Manager: Please clear first");
      return;
    }

    this->capacity = capacity;
    this->remaining = capacity;
    this->cursor = 0;
    this->used = (bool*)malloc(sizeof(bool) * capacity);
    this->items = (T**)malloc(sizeof(T*) * capacity);
    for(register int i = 0; i < capacity; i++) {
      used[i] = false;
      items[i] = (T*)malloc(sizeof(T));
    }
  }

  void clear() {
    capacity = remaining = cursor = 0;
    for(register int i = 0; i < capacity; i++) {
      used[i] = false;
      if(items[i]) {
        free(items[i]);
        items[i] = NULL;
      }
    }

    free(items);
    items = NULL;
    free(used);
    used = NULL;
  }
};

typedef struct _node *NODE;
typedef struct _node {
  int data;
  NODE next;
} Node;

int main() {
  HeapManager<Node> manager = HeapManager<Node>(10);
  NODE n = manager.get();
  n->data = 3;
  n->next = NULL;
  manager.get()->data = 8;
  manager.get()->data = 2;
  manager.get()->data = 6;
  manager.drop(n);
  manager.clear();
  return 0;
}