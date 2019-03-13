#ifndef ASTLINKEDLIST_H
#define ASTLINKEDLIST_H

#include "ASTnode.h"

struct ASTLinkedList
{
    struct ASTnode *node;
    struct ASTLinkedList *next;
    struct ASTLinkedList *previous;
};

struct ASTLinkedList *InstallArgument(struct ASTnode *node);        // installs argument node to argument list headed by argHead; returns newly added node
struct ASTLinkedList *Get_ArgumentList_Tail();                      // Returns tail of argument list

#endif