/*
LLD
    Design a text editor, that can read, and undo/redo 10 operations.

Approch:
    Making a simple, Menu Driven Text Editior.
    Operations allowed : Insert, Undo, Redo.

Limitation in this design:
    1. THIS IS MEMORY NON-EFFICIENT, stack keep full copy and not the differnce
    2. when undo / redo stacks are empty, then program fails if 
    operation is requested.
    3. stack push, when the stack is full, it shifts items to make space,
    instead of just replacing the oldest item. 

*/

// #include<string.h>
#include<stdio.h>
#include<string.h>

#define MAX_OP (10u)
#define MAX_TXT_LEN (100u)

typedef enum{
    insert = 1,
    undo,
    redo
} command_type;

typedef struct{
    char *valptr[MAX_OP];
    int top;
} DoStack;

DoStack undoStack;
DoStack redoStack;

void getCommand(command_type *command){
    printf("\n Please enter your choice : \n 1. Insert \n 2. Undo \n 3. Redo\n Input Now: ");
    scanf("%d", command);
    getchar();  // consume newline
}

void popStack(DoStack *stc){
    if(stc->top == -1)
        return;
    free(stc->valptr[stc->top]);
    stc->top -= 1;
}

void pushStack(DoStack *stc, char *newNote){
    if(stc->top + 1 == MAX_OP){ // stack full, make space
        int itr = 0;
        while(itr < MAX_OP-1){
            stc->valptr[itr] = stc->valptr[itr+1];
            itr++;
        }
    }
    else{
        stc->top += 1;
    }
    stc->valptr[stc->top] = (char *)malloc(strlen(newNote) + 1);
    strcpy(stc->valptr[stc->top], newNote);
    return;
}

void clearStack(DoStack *stc){
    if(stc->top == -1)
        return;
    while(stc->top > -1){
        free(stc->valptr[stc->top]);
        stc->top -= 1;
    }
    return;
}

void notepadApp(command_type *command, char *note){
    switch(*command){
        case insert:{
            char userinput[100];
            pushStack(&undoStack, note);
            printf("\n Enter the input text : ");
            fgets(userinput, 100, stdin);
            userinput[strcspn(userinput, "\n")] = 0;
            strcat(note, userinput); // (dest, src) dest = dest + src
            clearStack(&redoStack);
        }
            break;
        case undo:{
                pushStack(&redoStack, note);
                strcpy(note, undoStack.valptr[undoStack.top]);
                popStack(&undoStack);
            }
            break;
        case redo:{
                strcpy(note, redoStack.valptr[redoStack.top]);
                pushStack(&undoStack, note);
                popStack(&redoStack);
            }
            break;
        default:
            printf("Invalid Input Recived! \n");
            break;

    }
}

int main(){
    command_type command = insert;
    undoStack.top = -1;
    redoStack.top = -1;
    char note[10001]= "";
    while(command == insert || command == undo || command == redo){
        getCommand(&command);
        notepadApp(&command, note);
        printf("\nUpdated Node is  : %s\n", note);
    }
    clearStack(&undoStack);
    clearStack(&redoStack);

    return 0;
}