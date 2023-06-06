// Copyright 2022 NNTU-CS
#include <stdexcept>
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

template<typename T>
class TPQueue {
 private:
    struct ITEM {
        T data;
        ITEM* next;
    };
    ITEM* head;
    ITEM* last;
    ITEM* create(const T& data, ITEM* next);
    void destroy(ITEM* item);
 public:
    TPQueue() : head(nullptr), last(nullptr) {}
    ~TPQueue();
    void push(const T& data);
    T pop();
};
template<typename T>
typename TPQueue<T>::ITEM* TPQueue<T>::create(const T& data, ITEM* next) {
    ITEM* item = new ITEM;
    item->data = data;
    item->next = next;
    return item;
}
template<typename T>
void TPQueue<T>::destroy(ITEM* item) {
    delete item;
}

template<typename T>
TPQueue<T>::~TPQueue() {
    while (head)
        pop();
}
template<typename T>
void TPQueue<T>::push(const T& data) {
    if (last && data.prior <= last->data.prior) {
    last->next = create(data, nullptr);
    last = last->next;
} else if (!last) {
    head = create(data, nullptr);
    last = head;
} else {
    ITEM* current = head;
    ITEM* prev = nullptr;
    while (current && data.prior < current->data.prior) {
        prev = current;
        current = current->next;
    }
    if (!prev) {
        head = create(data, head);
    } else {
        prev->next = create(data, current);
    }
}
}
template<typename T>
T TPQueue<T>::pop() {
    if (head) {
        ITEM* temp = head->next;
        T data = head->data;
        destroy(head);
        head = temp;
        if (!head) {
            last = nullptr;
        }
        return data;
    } else {
        throw std::out_of_range("Queue is empty");
    }
}

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
