#ifndef NODESTRUCTURE_H
#define NODESTRUCTURE_H

struct tnode { 
	int nodeType;               // information about non-leaf nodes - read/write/connector/+/* etc.  
	int dataType;	                //type of variable
	int  val;	                // value of a number for NUM nodes.
	char *varName;	            //name of a variable for ID nodes  
	struct tnode *left,*right;	//left and right branches   
};

/*Create a node tnode*/
struct tnode* createNode(int nodeType, int dataType,int val, char *varName, struct tnode *l, struct tnode *r);

#endif