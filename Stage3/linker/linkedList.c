#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "linkedList.h"


struct linkedList* addLabel(struct linkedList *head, char* label, int address)
{
    struct linkedList *temp = malloc(sizeof(struct linkedList));
    temp->label = strdup(label);
    temp->address = address;
    temp->next = NULL;
    if(head == NULL) return temp;
    struct linkedList *iterator = head;
    while(1)                                                   
    {
        // if(!strcmp(label,iterator->label)) return head;             /*uncomment this line to avoid adding multiple copies of the same label*/
        if(iterator->next == NULL) break;                              /*Will probably come in handy for later stages*/
        iterator = iterator->next;
    }
    iterator->next = temp;
    return head;
}

int getLabelAddress(struct linkedList *head, char* label)
{
    struct linkedList *iterator = head;
    while(iterator != NULL)
    {
        if(!strcmp(label,iterator->label)) return iterator->address;
        iterator = iterator->next;
    }
    printf("ERROR: Undefined label encountered\n");
    exit(1);
}