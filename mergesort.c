#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 100

// Структура для узла списка
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Структура для очереди
typedef struct {
    Node* head;
    Node* tail;
} Queue;

// Глобальные счетчики для операций
int comparisons = 0;
int moves = 0;

// Вспомогательные функции для работы со списком
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

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

// Функции для создания списков
Node* createAscendingList(int size) {
    Node* head = NULL;
    Node* tail = NULL;
    for (int i = 1; i <= size; i++) {
        Node* newNode = createNode(i);
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    return head;
}

Node* createDescendingList(int size) {
    Node* head = NULL;
    Node* tail = NULL;
    for (int i = size; i >= 1; i--) {
        Node* newNode = createNode(i);
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    return head;
}

Node* createRandomList(int size) {
    Node* head = NULL;
    Node* tail = NULL;
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        Node* newNode = createNode(rand() % 100);
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    return head;
}

// Функции для работы с очередью
void initQueue(Queue* q) {
    q->head = NULL;
    q->tail = NULL;
}

void enqueue(Queue* q, Node* node) {
    if (!q->head) {
        q->head = node;
        q->tail = node;
    } else {
        q->tail->next = node;
        q->tail = node;
    }
    node->next = NULL;
    moves++; // Считаем перемещение
}

// Пункт 2: Расщепление списка на два списка (через один элемент)
void splitList(Node* S, Node** a, Node** b, int* n) {
    *a = S;
    if (!S) {
        *b = NULL;
        *n = 0;
        return;
    }
    *b = S->next;
    *n = 1;
    
    Node* k = *a;
    Node* p = *b;
    while (p != NULL) {
        (*n)++;
        k->next = p->next;
        k = p;
        p = p->next;
    }
    if (k) k->next = NULL;
}

// Пункт 3: Слияние двух серий из списков a и b в очередь c
void mergeSeries(Node** a, int q, Node** b, int r, Queue* c) {
    Node* a_ptr = *a;
    Node* b_ptr = *b;
    while (q > 0 && r > 0) {
        comparisons++; // Сравнение
        if (a_ptr->data <= b_ptr->data) {
            Node* temp = a_ptr;
            a_ptr = a_ptr->next;
            enqueue(c, temp);
            q--;
        } else {
            Node* temp = b_ptr;
            b_ptr = b_ptr->next;
            enqueue(c, temp);
            r--;
        }
    }
    while (q > 0) {
        Node* temp = a_ptr;
        a_ptr = a_ptr->next;
        enqueue(c, temp);
        q--;
    }
    while (r > 0) {
        Node* temp = b_ptr;
        b_ptr = b_ptr->next;
        enqueue(c, temp);
        r--;
    }
    *a = a_ptr;
    *b = b_ptr;
}

// Вспомогательная функция для создания временного списка из первых len элементов
Node* copyFirstNElements(Node* head, int len) {
    if (!head || len <= 0) return NULL;
    
    Node* newHead = NULL;
    Node* newTail = NULL;
    Node* current = head;
    int count = 0;
    
    while (current && count < len) {
        Node* newNode = createNode(current->data);
        if (!newHead) {
            newHead = newNode;
            newTail = newNode;
        } else {
            newTail->next = newNode;
            newTail = newNode;
        }
        current = current->next;
        count++;
    }
    return newHead;
}

// Пункт 4: Сортировка методом прямого слияния
void mergeSortList(Node** S, int n) {
    if (n <= 1) return;
    
    Node* a = NULL;
    Node* b = NULL;
    int size = 0;
    splitList(*S, &a, &b, &size);
    moves += size; // Считаем перемещения при расщеплении
    
    int p = 1; // Размер серии
    int iteration = 1;
    while (p < n) {
        Queue c0, c1;
        initQueue(&c0);
        initQueue(&c1);
        
        int i = 0;
        int m = n;
        Node* a_ptr = a;
        Node* b_ptr = b;
        
        printf("\nИтерация %d (размер серии: %d):\n", iteration, p);
        int merge_count = 1;
        while (m > 0) {
            int q = (m >= p) ? p : m;
            m -= q;
            int r = (m >= p) ? p : m;
            m -= r;
            
            printf("Слияние %d:\n", merge_count);
            printf("  Список a (длина %d): ", q);
            Node* temp_a = a_ptr;
            for (int j = 0; j < q && temp_a; j++) {
                printf("%d ", temp_a->data);
                temp_a = temp_a->next;
            }
            printf("\n");
            
            // Подсчет checksum и series для списка a
            Node* a_copy = copyFirstNElements(a_ptr, q);
            printf("  Checksum a: %d, Series a: %d\n", calculateChecksum(a_copy), countSeries(a_copy));
            deleteList(&a_copy);
            
            printf("  Список b (длина %d): ", r);
            Node* temp_b = b_ptr;
            for (int j = 0; j < r && temp_b; j++) {
                printf("%d ", temp_b->data);
                temp_b = temp_b->next;
            }
            printf("\n");
            
            // Подсчет checksum и series для списка b
            Node* b_copy = copyFirstNElements(b_ptr, r);
            printf("  Checksum b: %d, Series b: %d\n", calculateChecksum(b_copy), countSeries(b_copy));
            deleteList(&b_copy);
            
            mergeSeries(&a_ptr, q, &b_ptr, r, (i == 0) ? &c0 : &c1);
            
            if (i == 0) {
                printf("  Очередь c0: ");
                printList(c0.head);
                printf("  Checksum c0: %d, Series c0: %d\n", calculateChecksum(c0.head), countSeries(c0.head));
            } else {
                printf("  Очередь c1: ");
                printList(c1.head);
                printf("  Checksum c1: %d, Series c1: %d\n", calculateChecksum(c1.head), countSeries(c1.head));
            }
            
            i = 1 - i;
            merge_count++;
        }
        
        a = c0.head;
        b = c1.head;
        p *= 2;
        iteration++;
    }
    
    if (a) {
        *S = a;
    } else {
        *S = b;
    }
}

// Основная программа
int main() {
    // Пункт 2: Проверка расщепления
    printf("Расщепление списка\n");
    Node* S = createAscendingList(20);
    printf("Исходный список S: ");
    printList(S);
    
    Node* a = NULL;
    Node* b = NULL;
    int n = 0;
    splitList(S, &a, &b, &n);
    printf("Список a: ");
    printList(a);
    printf("Список b: ");
    printList(b);
    printf("Количество элементов: %d\n", n);
    
    // Пункт 3: Подсчет характеристик
    printf("\nПодсчет характеристик\n");
    printf("Список a - Checksum: %d, Series: %d\n", calculateChecksum(a), countSeries(a));
    printf("Список b - Checksum: %d, Series: %d\n", calculateChecksum(b), countSeries(b));
    
    // Пункт 4 и 5: Сортировка и сравнение трудоемкости
    printf("\nСортировка и сравнение трудоемкости\n");
    int sizes[] = {10, 20}; // Уменьшено для наглядности вывода
    for (int i = 0; i < 2; i++) {
        int size = sizes[i];
        printf("Размер: %d\n", size);
        
        // Возрастающий список
        comparisons = 0;
        moves = 0;
        Node* asc = createAscendingList(size);
        printf("\nВозрастающий список:\nИсходный: ");
        printList(asc);
        mergeSortList(&asc, size);
        printf("Отсортированный: ");
        printList(asc);
        printf("Сравнений: %d, Пересылок: %d\n", comparisons, moves);
        deleteList(&asc);
        
        // Убывающий список
        comparisons = 0;
        moves = 0;
        Node* desc = createDescendingList(size);
        printf("\nУбывающий список:\nИсходный: ");
        printList(desc);
        mergeSortList(&desc, size);
        printf("Отсортированный: ");
        printList(desc);
        printf("Сравнений: %d, Пересылок: %d\n", comparisons, moves);
        deleteList(&desc);
        
        // Случайный список
        comparisons = 0;
        moves = 0;
        Node* randList = createRandomList(size);
        printf("\nСлучайный список:\nИсходный: ");
        printList(randList);
        mergeSortList(&randList, size);
        printf("Отсортированный: ");
        printList(randList);
        printf("Сравнений: %d, Пересылок: %d\n", comparisons, moves);
        deleteList(&randList);
    }
    
    deleteList(&a);
    deleteList(&b);
    return 0;
}