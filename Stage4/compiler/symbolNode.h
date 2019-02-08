#ifndef SYMBOLNODE_H
#define SYMBOLNODE_H

/*
 *  <-------------------SYMBOLNODE_H------------------------>
 *  # The node that makes up symbol list containing variables
 *  # Nothing much else; just whatever I wrote at the top 
*/

struct symbolNode
{
    char* varName;              // carries the variable name or ID or whatever you like to call it
    int dataType;               // specifies the variable's dataType
    int size;                   // specifies the size of the variable
    int binding;                // holds the variable's address
    struct symbolNode* next;    // pointer to next variable entry
};

void Install(char *varName, int dataType, int size);    // adds a variable to the symbol table; raises error if variable is already present
struct symbolNode *Lookup(char * varName);              // lookup a particular variable and return its node address; returns NULL if not found

#endif