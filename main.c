#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
};

typedef struct {
    struct Node *head;
    struct Node *tail;
    int length;
} DoubleLinkedList;

void push(DoubleLinkedList *list, int data) {
    const auto newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    if (list->length == 0) {
        newNode->prev = NULL;
        list->head = list->tail = newNode;
    } else {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
    list->length++;
}

void pop(DoubleLinkedList *list) {
    if (list->length == 0) {
        return;
    }

    if (list->length == 1) {
        list->head = NULL;
        list->tail = NULL;
        list->length = 0;
        return;
    }

    struct Node *temp = list->tail;
    list->tail = temp->prev;
    list->tail->next = NULL;
    free(temp);
    list->length--;
}

void shift(DoubleLinkedList *list) {
    if (list->length == 0) {
        return;
    }
    if (list->length == 1) {
        struct Node *temp = list->head;
        list->tail = NULL;
        list->head = list->tail;
        list->length = 0;
        free(temp);
        return;
    }
    struct Node *temp = list->head;
    list->head = temp->next;
    list->head->prev = NULL;
    free(temp);
    list->length--;
}

void unshift(DoubleLinkedList *list, int data) {
    const auto newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    if (list->length == 0) {
        newNode->next = NULL;
        newNode->prev = NULL;
        list->head = list->tail = newNode;
    } else {
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
    }
    list->length++;
}

void get(const DoubleLinkedList *list, int index) {
    if (list->length == 0 || index >= list->length || index < 0) {
        return;
    }
    // can be improved but O(n/2) = 0(n) so i leave with this search
    const struct Node *temp = list->head;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    printf("found: [%d]\n", temp->data);
}

void set(const DoubleLinkedList *list, int index, int value) {
    if (list->length == 0 || index >= list->length || index < 0) {
        return;
    }

    struct Node *temp = list->head;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    temp->data = value;
}

void insert(DoubleLinkedList *list, int index, int data) {
    if (list->length == 0 || index >= list->length || index < 0) {
        return;
    }
    if (index == 0) {
        unshift(list, data);
        return;
    }
    if (index == list->length - 1) {
        push(list, data);
        return;
    }
    const auto newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    struct Node *temp = list->head;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    newNode->next = temp;
    newNode->prev = temp->prev;
    temp->prev->next = newNode;
    temp->prev = newNode;
    list->length++;
}

void removeNode(DoubleLinkedList *list, int index) {
    if (list->length == 0 || index >= list->length || index < 0) {
        return;
    }
    if (index == 0) {
        shift(list);
        return;
    }
    if (index == list->length - 1) {
        pop(list);
        return;
    }

    struct Node *temp = list->head;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    free(temp);
}

void traverse(const DoubleLinkedList *list) {
    if (list->length == 0) {
        return;
    }

    struct Node *temp = list->head;
    while (temp != NULL) {
        printf("[%d] ->", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main(void)
{
    DoubleLinkedList list;
    list.length = 0;

    push(&list, 1);
    push(&list, 2);
    push(&list, 3);
    push(&list, 4);
    push(&list, 5);
    traverse(&list);
    pop(&list);
    pop(&list);
    pop(&list);
    pop(&list);
    traverse(&list);
    shift(&list);
    shift(&list);
    traverse(&list);
    shift(&list);
    traverse(&list);
    unshift(&list, 4);
    unshift(&list, 5);
    unshift(&list, 6);
    traverse(&list);
    get(&list, 0);
    get(&list, 1);
    get(&list, 2);
    set(&list, 2, 4);
    traverse(&list);
    insert(&list, 2, 2);
    traverse(&list);
    insert(&list, 0, 7);
    traverse(&list);
    insert(&list, 4, 1);
    traverse(&list);
    insert(&list, 4, 3);
    traverse(&list);
    removeNode(&list, 0);
    traverse(&list);
    removeNode(&list, list.length-1);
    traverse(&list);
    removeNode(&list, 2);
    traverse(&list);
    return 0;
}
