#include <stdio.h>
#include <stdlib.h>
struct MemoryBlock {
    int blockID;
    int size;
    int isOccupied;
    struct MemoryBlock* next;
};
struct MemoryBlock* createMemoryBlock(int blockID, int size) {
    struct MemoryBlock* block = (struct MemoryBlock*)malloc(sizeof(struct MemoryBlock));
    block->blockID = blockID;
    block->size = size;
    block->isOccupied = 0;
    block->next = NULL;
    return block;
}
void displayMemory(struct MemoryBlock* head) {
    printf("Memory Blocks:\n");
    while (head != NULL) {
        printf("Block ID: %d, Size: %d, Status: %s\n", head->blockID, head->size, head->isOccupied ? "Occupied" : "Free");
        head = head->next;
    }
    printf("\n");
}
void firstFit(struct MemoryBlock* head, int processID, int size) {
    struct MemoryBlock* current = head;

    while (current != NULL) {
        if (!current->isOccupied && current->size >= size) {
            current->isOccupied = 1;
            printf("Process %d allocated to Block %d using First Fit.\n", processID, current->blockID);
            return;
        }
        current = current->next;
    }
    printf("Process %d cannot be allocated using First Fit. No suitable block found.\n", processID);
}
void bestFit(struct MemoryBlock* head, int processID, int size) {
    struct MemoryBlock* current = head;
    struct MemoryBlock* bestFitBlock = NULL;

    while (current != NULL) {
        if (!current->isOccupied && current->size >= size) {
            if (bestFitBlock == NULL || current->size < bestFitBlock->size) {
                bestFitBlock = current;
            }
        }
        current = current->next;
    }
    if (bestFitBlock != NULL) {
        bestFitBlock->isOccupied = 1;
        printf("Process %d allocated to Block %d using Best Fit.\n", processID, bestFitBlock->blockID);
    } else {
        printf("Process %d cannot be allocated using Best Fit. No suitable block found.\n", processID);
    }
}
void worstFit(struct MemoryBlock* head, int processID, int size) {
    struct MemoryBlock* current = head;
    struct MemoryBlock* worstFitBlock = NULL;
    while (current != NULL) {
        if (!current->isOccupied && current->size >= size) {
            if (worstFitBlock == NULL || current->size > worstFitBlock->size) {
                worstFitBlock = current;
            }
        }
        current = current->next;
    }

    if (worstFitBlock != NULL) {
        worstFitBlock->isOccupied = 1;
        printf("Process %d allocated to Block %d using Worst Fit.\n", processID, worstFitBlock->blockID);
    } else {
        printf("Process %d cannot be allocated using Worst Fit. No suitable block found.\n", processID);
    }
}
void deallocateMemory(struct MemoryBlock* head, int processID) {
    struct MemoryBlock* current = head;
    while (current != NULL) {
        if (current->isOccupied && current->blockID == processID) {
            current->isOccupied = 0;
            printf("Process %d deallocated from Block %d.\n", processID, current->blockID);
            return;
        }
        current = current->next;
    }
    printf("Process %d not found. Deallocation failed.\n", processID);
}
void freeMemory(struct MemoryBlock* head) {
    struct MemoryBlock* current = head;
    struct MemoryBlock* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}
int main() {
    struct MemoryBlock* memoryHead = createMemoryBlock(1, 100);
    memoryHead->next = createMemoryBlock(2, 50);
    memoryHead->next->next = createMemoryBlock(3, 75);
    memoryHead->next->next->next = createMemoryBlock(4, 30);

    int choice, processID, size;

    do {
        printf("1. First Fit Allocation\n");
        printf("2. Best Fit Allocation\n");
        printf("3. Worst Fit Allocation\n");
        printf("4. Deallocate Memory\n");
        printf("5. Display Memory\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
            case 2:
            case 3:
                printf("Enter Process ID: ");
                scanf("%d", &processID);
                printf("Enter Size: ");
                scanf("%d", &size);
                if (choice == 1)
                    firstFit(memoryHead, processID, size);
                else if (choice == 2)
                    bestFit(memoryHead, processID, size);
                else
                    worstFit(memoryHead, processID, size);
                break;
            case 4:
                printf("Enter Process ID to deallocate: ");
                scanf("%d", &processID);
                deallocateMemory(memoryHead, processID);
                break;
            case 5:
                displayMemory(memoryHead);
                break;
            case 6:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 6);
    freeMemory(memoryHead);

    return 0;
}

