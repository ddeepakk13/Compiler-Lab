#include "ASTLinkedList.h"
#include "ASTnode.h"
#include <stdlib.h>

extern struct ASTLinkedList *argHead;

struct ASTLinkedList *InstallArgument(struct ASTnode *node)    // installs argument node to argument list headed by argHead; returns newly added node
{
    struct ASTLinkedList *temp = malloc(sizeof(struct ASTLinkedList));
    temp->node = node;
    temp->previous = NULL;
    temp->next = NULL;

    if(argHead == NULL)
    {
        argHead = temp;
        return temp;
    }

    struct ASTLinkedList *iterator = argHead;
    while(1)
    {
        if(iterator->next == NULL)   break;
        iterator = iterator->next;
    }
    temp->previous = iterator;
    iterator->next = temp;
    return temp;
}

struct ASTLinkedList *Get_ArgumentList_Tail()                      // Returns tail of argument list
{
    struct ASTLinkedList *iterator = argHead;
    if(iterator == NULL) return iterator;
    while(1)
    {
        if(iterator->next == NULL)   break;
        iterator = iterator->next;
    }
    return iterator;
}