#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 100

// Структура для стека
typedef struct {
    int items[MAX_SIZE];
    int top;
} Stack;

// Структура для очереди
typedef struct {
    int items[MAX_SIZE];
    int front;
    int rear;
} Queue;

// Структура для узла списка
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Функции для стека
void initStack(Stack* s) {
    s->top = -1;
}

int isStackFull(Stack* s) {
    return s->top == MAX_SIZE - 1;
}

int isStackEmpty(Stack* s) {
    return s->top == -1;
}

void push(Stack* s, int value) {
    if (!isStackFull(s)) {
        s->items[++s->top] = value;
    }
}

void fillStackAscending(Stack* s, int size) {
    initStack(s);
    for (int i = 1; i <= size && !isStackFull(s); i++) {
        push(s, i);
    }
}

void fillStackDescending(Stack* s, int size) {
    initStack(s);
    for (int i = size; i >= 1 && !isStackFull(s); i--) {
        push(s, i);
    }
}

void fillStackRandom(Stack* s, int size) {
    initStack(s);
    srand(time(NULL));
    for (int i = 0; i < size && !isStackFull(s); i++) {
        push(s, rand() % 100);
    }
}

void printStack(Stack* s) {
    if (isStackEmpty(s)) {
        printf("Стек пустой\n");
        return;
    }
    printf("Стек: ");
    for (int i = 0; i <= s->top; i++) {
        printf("%d ", s->items[i]);
    }
    printf("\n");
}

int calculateStackChecksum(Stack* s) {
    int sum = 0;
    for (int i = 0; i <= s->top; i++) {
        sum += s->items[i];
    }
    return sum;
}

int countStackSeries(Stack* s) {
    if (isStackEmpty(s)) return 0;
    if (s->top == 0) return 1;
    
    int series = 1;
    for (int i = 0; i < s->top; i++) {
        if (s->items[i] > s->items[i + 1]) {
            series++;
        }
    }
    return series;
}

// Функции для очереди
void initQueue(Queue* q) {
    q->front = 0;
    q->rear = -1;
}

int isQueueFull(Queue* q) {
    return q->rear == MAX_SIZE - 1;
}

int isQueueEmpty(Queue* q) {
    return q->rear < q->front;
}

void enqueue(Queue* q, int value) {
    if (!isQueueFull(q)) {
        q->items[++q->rear] = value;
    }
}

void fillQueueAscending(Queue* q, int size) {
    initQueue(q);
    for (int i = 1; i <= size && !isQueueFull(q); i++) {
        enqueue(q, i);
    }
}

void fillQueueDescending(Queue* q, int size) {
    initQueue(q);
    for (int i = size; i >= 1 && !isQueueFull(q); i--) {
        enqueue(q, i);
    }
}

void fillQueueRandom(Queue* q, int size) {
    initQueue(q);
    srand(time(NULL));
    for (int i = 0; i < size && !isQueueFull(q); i++) {
        enqueue(q, rand() % 100);
    }
}

void printQueue(Queue* q) {
    if (isQueueEmpty(q)) {
        printf("Очередь пуста\n");
        return;
    }
    printf("Очередь: ");
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d ", q->items[i]);
    }
    printf("\n");
}

int calculateQueueChecksum(Queue* q) {
    int sum = 0;
    for (int i = q->front; i <= q->rear; i++) {
        sum += q->items[i];
    }
    return sum;
}

int countQueueSeries(Queue* q) {
    if (isQueueEmpty(q)) return 0;
    if (q->front == q->rear) return 1;
    
    int series = 1;
    for (int i = q->front; i < q->rear; i++) {
        if (q->items[i] > q->items[i + 1]) {
            series++;
        }
    }
    return series;
}

// Функции для списка
void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int calculateChecksum(Node* head) {
    int sum = 0;
    Node* current = head;
    while (current != NULL) {
        sum += current->data;
        current = current->next;
    }
    return sum;
}

int countSeries(Node* head) {
    if (!head) return 0;
    if (!head->next) return 1;
    
    int series = 1;
    Node* current = head;
    while (current->next != NULL) {
        if (current->data > current->next->data) {
            series++;
        }
        current = current->next;
    }
    return series;
}

void deleteList(Node** head) {
    Node* current = *head;
    Node* next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

// Рекурсивные функции печати
void printListForward(Node* head) {
    if (head == NULL) return;
    printf("%d ", head->data);
    printListForward(head->next);
}

void printListBackward(Node* head) {
    if (head == NULL) return;
    printListBackward(head->next);
    printf("%d ", head->data);
}

// Вспомогательная функция для создания списка
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Пример использования
int main() {
    // Тестирование стека
    Stack s;
    printf("Тест Стека:\n");
    fillStackAscending(&s, 5);
    printStack(&s);
    printf("Checksum: %d\n", calculateStackChecksum(&s));
    printf("Number of series: %d\n", countStackSeries(&s));
    fillStackDescending(&s, 5);
    printStack(&s);
    printf("Checksum: %d\n", calculateStackChecksum(&s));
    printf("Number of series: %d\n", countStackSeries(&s));
    fillStackRandom(&s, 5);
    printStack(&s);
    printf("Checksum: %d\n", calculateStackChecksum(&s));
    printf("Number of series: %d\n", countStackSeries(&s));
    
    // Тестирование очереди
    Queue q;
    printf("\nТест Очереди:\n");
    fillQueueAscending(&q, 5);
    printQueue(&q);
    printf("Checksum: %d\n", calculateQueueChecksum(&q));
    printf("Number of series: %d\n", countQueueSeries(&q));
    fillQueueDescending(&q, 5);
    printQueue(&q);
    printf("Checksum: %d\n", calculateQueueChecksum(&q));
    printf("Number of series: %d\n", countQueueSeries(&q));
    fillQueueRandom(&q, 5);
    printQueue(&q);
    printf("Checksum: %d\n", calculateQueueChecksum(&q));
    printf("Number of series: %d\n", countQueueSeries(&q));
    
    // Тестирование списка
    printf("\nТест Списка:\n");
    Node* head = createNode(1);
    head->next = createNode(1);
    head->next->next = createNode(2);
    head->next->next->next = createNode(3);
    head->next->next->next->next = createNode(2);
    head->next->next->next->next->next = createNode(4);
    
    printf("Список: ");
    printList(head);
    
    printf("Checksum: %d\n", calculateChecksum(head));
    printf("Number of series: %d\n", countSeries(head));
    
    printf("Прямая рекурсивная печать: ");
    printListForward(head);
    printf("\n");
    
    printf("Обратная рекурсивная печать: ");
    printListBackward(head);
    printf("\n");
    
    deleteList(&head);
    printf("Список: ");
    printList(head);
    
    return 0;
}