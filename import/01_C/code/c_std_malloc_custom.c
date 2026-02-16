#include <stdio.h>
#include <stddef.h>  // For size_t

#define MEMORY_POOL_SIZE 1024  // Total pool size (e.g., 1024 bytes)
#define BLOCK_SIZE sizeof(Block)

typedef struct Block {
    size_t size;           // Size of the memory block
    struct Block *next;    // Pointer to the next free block
} Block;

static char memoryPool[MEMORY_POOL_SIZE];  // Static memory pool
static Block *freeList = NULL;             // Pointer to the list of free blocks

void *my_malloc(size_t size) {
    Block *current, *previous;

    // Ensure the requested size is non-zero and align to a multiple of sizeof(Block)
    if (size == 0) {
        return NULL;
    }
    size = (size + sizeof(Block) - 1) & ~(sizeof(Block) - 1);  // Align to the next multiple of Block size

    // Initialize the memory pool on the first call
    if (!freeList) {
        freeList = (Block *)memoryPool;
        freeList->size = MEMORY_POOL_SIZE;
        freeList->next = NULL;
    }

    previous = NULL;
    current = freeList;

    // Find a free block with enough space
    while (current != NULL) {
        if (current->size >= size) {
            // Found a suitable block
            if (current->size > size + BLOCK_SIZE) {
                // Split the block if it's large enough to have leftover space
                Block *newBlock = (Block *)((char *)current + size);
                newBlock->size = current->size - size;
                newBlock->next = current->next;

                current->size = size;
                current->next = newBlock;
            }

            // Remove the block from the free list and return the allocated memory
            if (previous) {
                previous->next = current->next;
            } else {
                freeList = current->next;
            }

            return (char *)current + BLOCK_SIZE;
        }

        previous = current;
        current = current->next;
    }

    // If no suitable block is found, return NULL (out of memory)
    return NULL;
}

void my_free(void *ptr) {
    Block *block = (Block *)((char *)ptr - BLOCK_SIZE);

    // Insert the block back into the free list (simple insertion at the beginning)
    block->next = freeList;
    freeList = block;
}

int main() {
    // Test our custom malloc implementation
    int *arr = (int *)my_malloc(5 * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Use the allocated memory
    for (int i = 0; i < 5; i++) {
        arr[i] = i * 2;
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Free the memory
    my_free(arr);

    return 0;
}
