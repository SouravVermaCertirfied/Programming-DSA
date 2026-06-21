#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1000
#define MAX_HISTORY 10

typedef struct {
    char *history[MAX_HISTORY];
    int top;
} Stack;

// Push text onto stack
void push(Stack *s, const char *text) {
    if (s->top == MAX_HISTORY - 1) {
        // Remove oldest element
        free(s->history[0]);
        for (int i = 1; i <= s->top; i++) {
            s->history[i-1] = s->history[i];
        }
        s->top--;
    }
    s->top++;
    s->history[s->top] = strdup(text);
}

// Pop text from stack
char* pop(Stack *s) {
    if (s->top == -1) return NULL;
    char *text = s->history[s->top];
    s->top--;
    return text;
}

// Clear a stack
void clearStack(Stack *s) {
    while (s->top != -1) {
        free(s->history[s->top]);
        s->top--;
    }
}

int main() {
    char text[MAX_LEN] = "";
    Stack undo = {.top = -1};
    Stack redo = {.top = -1};
    char input[MAX_LEN];
    int choice;
    int deleteCount;

    while (1) {
        printf("\nCurrent Text: \"%s\"\n", text);
        printf("1. Append Text\n2. Delete Last N Characters\n3. Replace Text\n4. Undo\n5. Redo\n6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();  // consume newline

        switch (choice) {
            case 1: // Append
                printf("Enter text to append: ");
                fgets(input, MAX_LEN, stdin);
                input[strcspn(input, "\n")] = 0;

                push(&undo, text);      // save for undo
                clearStack(&redo);      // clear redo stack
                strcat(text, input);    // append
                break;

            case 2: // Delete last N characters
                printf("Enter number of characters to delete: ");
                scanf("%d", &deleteCount);
                getchar(); // consume newline

                if (deleteCount > (int)strlen(text)) deleteCount = strlen(text);
                push(&undo, text);      // save for undo
                clearStack(&redo);      // clear redo stack
                text[strlen(text) - deleteCount] = '\0';
                break;

            case 3: // Replace
                printf("Enter new text: ");
                fgets(input, MAX_LEN, stdin);
                input[strcspn(input, "\n")] = 0;

                push(&undo, text);      // save for undo
                clearStack(&redo);      // clear redo stack
                strcpy(text, input);    // replace
                break;

            case 4: { // Undo
                char *prev = pop(&undo);
                if (prev) {
                    push(&redo, text);  // save current for redo
                    strcpy(text, prev);
                    free(prev);
                } else {
                    printf("Nothing to undo.\n");
                }
                break;
            }

            case 5: { // Redo
                char *next = pop(&redo);
                if (next) {
                    push(&undo, text);  // save current for undo
                    strcpy(text, next);
                    free(next);
                } else {
                    printf("Nothing to redo.\n");
                }
                break;
            }

            case 6: // Exit
                clearStack(&undo);
                clearStack(&redo);
                printf("Exiting editor.\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}