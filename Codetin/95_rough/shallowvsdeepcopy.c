#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Person {
    int rollno;
    char *name;
} Person;

// Properly performs a Deep Copy
void mydeepcpy(Person *dest, const Person *src) {
    dest->rollno = src->rollno;

    // 1. Calculate required length (+1 for null terminator)
    int len = strlen(src->name) + 1;

    // 2. Allocate WRITABLE memory on the heap
    dest->name = (char *)malloc(len);

    // 3. Copy the actual characters into the new memory
    if (dest->name != NULL) {
        strcpy(dest->name, src->name);
    }
}

int main() {
    // --- Step 1: Initialize P1 ---
    Person p1;
    p1.rollno = 10;
    // p1.name points to a read-only string literal
    p1.name = "verma"; 

    // --- Step 2: Deep Copy to P2 ---
    Person p2;
    mydeepcpy(&p2, &p1);

    printf("INITIAL STATE:\n");
    printf("P1: %d, %s (Points to Read-Only memory)\n", p1.rollno, p1.name);
    printf("P2: %d, %s (Points to Writable Heap memory)\n\n", p2.rollno, p2.name);

    // --- Step 3: Update P2 "In-Place" ---
    // Since p2.name was malloc'd, we can modify its contents.
    // NOTE: "sharma" is 6 chars + \0. "verma" was 5 chars + \0.
    // If the new name is longer, we should technically realloc, 
    // but for this example, let's just modify the characters we have.
    
    if (strlen(p2.name) >= 5) {
        p2.name[0] = 's'; // Change 'v' to 's'
        p2.name[1] = 'e'; // Change 'e' to 'e'
        p2.name[2] = 'r'; // Change 'r' to 'r' ... and so on.
        // Or simply:
        strcpy(p2.name, "serma"); 
    }

    printf("AFTER IN-PLACE MODIFICATION OF P2:\n");
    printf("P1 name: %s (Stays 'verma')\n", p1.name);
    printf("P2 name: %s (Changed to 'serma')\n\n", p2.name);

    // --- Step 4: Pointer Redirection vs In-Place ---
    // This doesn't change the memory; it just points p1 somewhere else.
    p1.name = "karma"; 
    
    printf("AFTER REDIRECTING P1 POINTER:\n");
    printf("P1 name: %s\n", p1.name);
    printf("P2 name: %s (Unchanged, independent copy)\n", p2.name);

    // Clean up heap memory
    free(p2.name);

    return 0;
}