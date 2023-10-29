#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int number;
    char name[50];
    int age;
} Student;

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct StudentNode {
    Student data;
    struct StudentNode* next;
} StudentNode;

void addNumbersToList(Node** head);
void addRandomNumbers(Node** head, int count);
void printNumberList(Node* head);

void storeStudentInfo(StudentNode** head, int number, const char* name, int age);
void printStudentInfo(StudentNode* head);
void searchByName(StudentNode* head, const char* name);
void deleteByName(StudentNode** head, const char* name);
void printLongestName(StudentNode* head);

int main() {
    Node* numberHead = NULL;
    StudentNode* studentHead = NULL;

    int choice;
    do {
        printf("\n1. Add numbers to list\n");
        printf("2. Add random numbers\n");
        printf("3. Store student information\n");
        printf("4. Print number list\n");
        printf("5. Print student information\n");
        printf("6. Search by name\n");
        printf("7. Delete by name\n");
        printf("8. Print longest name\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addNumbersToList(&numberHead);
                break;
            case 2:
                addRandomNumbers(&numberHead, 100);
                break;
            case 3: {
                int number, age;
                char name[50];
                printf("Enter student number: ");
                scanf("%d", &number);
                printf("Enter student name: ");
                scanf("%s", name);
                printf("Enter student age: ");
                scanf("%d", &age);
                storeStudentInfo(&studentHead, number, name, age);
                break;
            }
            case 4:
                printNumberList(numberHead);
                break;
            case 5:
                printStudentInfo(studentHead);
                break;
            case 6: {
                char name[50];
                printf("Enter student name to search: ");
                scanf("%s", name);
                searchByName(studentHead, name);
                break;
            }
            case 7: {
                char name[50];
                printf("Enter student name to delete: ");
                scanf("%s", name);
                deleteByName(&studentHead, name);
                break;
            }
            case 8:
                printLongestName(studentHead);
                break;
            case 0:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    // Free the memory
    Node* currentNumber = numberHead;
    while (currentNumber != NULL) {
        Node* temp = currentNumber;
        currentNumber = currentNumber->next;
        free(temp);
    }

    StudentNode* currentStudent = studentHead;
    while (currentStudent != NULL) {
        StudentNode* temp = currentStudent;
        currentStudent = currentStudent->next;
        free(temp);
    }

    return 0;
}

// Function "1" add odd numbers to the beginning and even numbers to the end
void addNumbersToList(Node** head) {
    int num;
    Node* newNode;

    do {
        printf("Enter a number (-1 to stop): ");
        scanf("%d", &num);

        if (num != -1) {
            newNode = (Node*)malloc(sizeof(Node));
            newNode->data = num;
            newNode->next = *head;
            *head = newNode;
        }
    } while (num != -1);

    printf("Numbers added to the list.\n");
}

// Function "2" add random numbers to the list
void addRandomNumbers(Node** head, int count) {
    Node* newNode;

    for (int i = 0; i < count; ++i) {
        newNode = (Node*)malloc(sizeof(Node));
        newNode->data = rand() % 100; 
        newNode->next = *head;
        *head = newNode;
    }

    printf("Random numbers added to the list.\n");
}

// Function "4" store student information in the list
void storeStudentInfo(StudentNode** head, int number, const char* name, int age) {
    StudentNode* newNode = (StudentNode*)malloc(sizeof(StudentNode));
    newNode->data.number = number;
    strncpy(newNode->data.name, name, sizeof(newNode->data.name) - 1);
    newNode->data.name[sizeof(newNode->data.name) - 1] = '\0'; 
    newNode->data.age = age;
    newNode->next = *head;
    *head = newNode;
}

// Function "3" print the linked list of numbers
void printNumberList(Node* head) {
    printf("Number List: ");
    while (head != NULL) {
        printf("%d", head->data);
        if (head->next != NULL) {
            printf("->");
        }
        head = head->next;
    }
    printf("\n");
}

// Function "4" to print student information
void printStudentInfo(StudentNode* head) {
    int count = 0;
    printf("Student Information:\n");
    while (head != NULL) {
        ++count;
        printf("%d- %s %d %d\n", count, head->data.name, head->data.age, head->data.number);
        head = head->next;
    }
    printf("Total students: %d\n", count);
}

// Function "5" search by student name
void searchByName(StudentNode* head, const char* name) {
    while (head != NULL) {
        if (strcmp(head->data.name, name) == 0) {
            printf("Student found: %s %d %d\n", head->data.name, head->data.age, head->data.number);
            return;
        }
        head = head->next;
    }
    printf("Student not found.\n");
}

// Function "6" delete by student name
void deleteByName(StudentNode** head, const char* name) {
    StudentNode* current = *head;
    StudentNode* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->data.name, name) == 0) {
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Student deleted.\n");
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("Student not found.\n");
}

// Function "7" print the record with the longest name
void printLongestName(StudentNode* head) {
    int maxLength = 0;
    char longestName[50];

    while (head != NULL) {
        int currentLength = strlen(head->data.name);
        if (currentLength > maxLength) {
            maxLength = currentLength;
            strcpy(longestName, head->data.name);
        }
        head = head->next;
    }

    printf("The longest name in the list: %s\n", longestName);
    printf("Length: %d\n", maxLength);
}
