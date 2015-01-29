# Shell script to generate an avl implementation file
# Author: drs
# Usage: ./avl.sh int
#        creates an int avl implementation file:  avl_int.c

item=$1
avl=avl_${item}
target=${avl}.c

echo "// Auto-generated impl. file for an avl of ${item}"  > ${target}
echo "// values.  This avl has no exception handling but" >> ${target}
echo "// prints a message on stdout and calls exit(1)."   >> ${target} 
echo "// Author: drs."                                    >> ${target} 

cat << EOI >>${target}

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "${avl}.h"

struct node
{
    char height;
    ${item} item;
    struct node * left;
    struct node * right;
};

struct ${avl}_implementation
{
    struct node * root;
    int size;
EOI

if [ "$item" = "any" ]; then  
    echo "    rel_fun lt;"                                       >> ${target}
    echo "};"                                                    >> ${target}
    echo                                                         >> ${target}
    echo "${avl} * new_${avl}(rel_fun lt)"                       >> ${target}
    echo "{"                                                     >> ${target}
    echo "    ${avl} * t = (${avl}*)malloc(sizeof(${avl}));"     >> ${target}
    echo "    t->root = NULL;"                                   >> ${target}
    echo "    t->size = 0;"                                      >> ${target}
    echo "    t->lt = lt;"                                       >> ${target}
    echo "    return t;"                                         >> ${target}
    echo "}"                                                     >> ${target}
    echo                                                         >> ${target}
    echo "#define LT(A,B) t->lt(A,B)"                            >> ${target}
    echo                                                         >> ${target}
    echo "any findin(${avl} *t, any x, struct node *p)"          >> ${target}          
	echo "{"                                                     >> ${target}
    echo "	if (p==NULL)"                                        >> ${target}
    echo "		return 0;"                                       >> ${target}
    echo                                                         >> ${target}
    echo "	else if (LT(x,p->item))"                             >> ${target}
    echo "		return findin(t, x, p->left);"                   >> ${target}
    echo                                                         >> ${target}
    echo "	else if (LT(p->item,x))"                             >> ${target}
    echo "		return findin(t, x, p->right);"                  >> ${target}
    echo                                                         >> ${target}
    echo "	else"                                                >> ${target}
    echo "		return p->item;"                                 >> ${target}
    echo "}"                                                     >> ${target}
    echo                                                         >> ${target}
    echo "any ${avl}_find(${avl} *t, ${item} x)"                 >> ${target}
    echo "{"                                                     >> ${target}
    echo "	assert(t!=NULL);"                                    >> ${target}
    echo "	return findin (t,x,t->root);"                        >> ${target}
    echo "}"                                                     >> ${target}
    echo                                                         >> ${target}
else                                                
    echo "};"                                                    >> ${target}
    echo                                                         >> ${target}
    echo "${avl} * new_${avl}()"                                 >> ${target}
    echo "{"                                                     >> ${target}
    echo "    ${avl} * t = (${avl}*)malloc(sizeof(${avl}));"     >> ${target}
    echo "    t->root = NULL;"                                   >> ${target} 
    echo "    t->size = 0;"                                      >> ${target}
    echo "    return t;"                                         >> ${target}
    echo "}"                                                     >> ${target}
    echo                                                         >> ${target}
    echo "#define LT(A,B)   A < B"                               >> ${target}
    echo                                                         >> ${target}
fi                                                                               


cat << EOI >>${target}

#define ABS(X)    ((X<0) ? -(X) : X)
#define MAX(X,Y)  ((X>Y) ? X : Y)
#define HEIGHT(P) ((P == NULL) ? 0 : P->height)


int  ${avl}_isempty(${avl} *t)
{
    assert(t!=NULL);
    return (t->size == 0);
}
    
int  ${avl}_isfull(${avl} *t)
{
    return 0;
}
    
int  ${avl}_size(${avl} *t)
{
    assert(t!=NULL);
    return t->size;
}
    
int  get_depth(struct node *p)
{
    int l,r;
    if (p==NULL)
       return 0;
    else {
       l = 1 + get_depth(p->left);
       r = 1 + get_depth(p->right);
       return (l>r) ? l : r;
    }
}

int ${avl}_depth(${avl} *t)
{
    assert(t!=NULL);
    return get_depth(t->root);
}

struct node* rotate_left(struct node *p)
{
    struct node *q;
    assert(p!=NULL);
    assert(p->right!=NULL);
    q = p->right;
    p->right = q->left;
    q->left = p;
    p->height = 1 + MAX(HEIGHT(p->left),HEIGHT(p->right));
    q->height = 1 + MAX(HEIGHT(q->left),HEIGHT(q->right));
    return q;
}

struct node* rotate_right(struct node *p)
{
    struct node *q;
    assert(p!=NULL);
    assert(p->left!=NULL);
    q = p->left;
    p->left = q->right;
    q->right = p;
    p->height = 1 + MAX(HEIGHT(p->left),HEIGHT(p->right));
    q->height = 1 + MAX(HEIGHT(q->left),HEIGHT(q->right));
    return q;
}

struct node* ensure_balance(struct node *p)
{
    if (p==NULL)
        return p;                                   // trivially balanced - return now

    p->height = 1 + MAX(HEIGHT(p->left),HEIGHT(p->right));
    
    if ( HEIGHT(p->left) - HEIGHT(p->right) > 1) {  // left-heavy  - rebalance needed

       if (HEIGHT(p->left->left) > HEIGHT(p->left->right))
            p = rotate_right(p);
        else {
            p->left = rotate_left(p->left);
            p = rotate_right(p);
        }
    }
    else
    if ( HEIGHT(p->right) - HEIGHT(p->left) > 1) {  // right-heavy - rebalance needed

        if (HEIGHT(p->right->right) > HEIGHT(p->right->left))
           p = rotate_left(p);
        else {
           p->right = rotate_right(p->right);
           p = rotate_left(p);
        }
    }
    else                                            // balanced - no rebalance needed
        ;
        
    return p;
}


struct node * ins(${avl} *t, ${item} x, struct node *p)
{
    if (p==NULL) {
        p = (struct node *)malloc(sizeof(struct node));
        if (p==NULL) {
            printf("${avl}insert (ins): failed to allocate memory\n");
            exit(1);
        }
        p->left   = p->right = NULL;
        p->item   = x;
        (t->size)++;
    }
    else if (LT(x,p->item)) {                       // inserting into left sub-tree
        p->left = ins(t, x, p->left);
    }   
    else if (LT(p->item,x)) {                       // inserting into right sub-tree
        p->right = ins(t, x, p->right);
    }

    return ensure_balance(p);
}

void ${avl}_insert(${avl} *t, ${item} x)
{
    assert(t!=NULL);
    t->root = ins(t, x, t->root);
}

struct node * findmin(struct node *p)
{
    if (p==NULL)
        printf("error: ($avl) findmin: empty tree\n");
        
    else if (p->left == NULL)
        return p;
    
    else
        return findmin(p->left);
}

struct node * del(${avl} *t, ${item} x, struct node *p)
{
    struct node * n;
    
    if (p == NULL)
        ;                                       // do nothing - data not in tree
        
    else if (LT(x,p->item)) 
        p->left = del(t, x, p->left);
        
    else if (LT(p->item,x))
        p->right = del(t, x, p->right);
    
    else if (p->left!=NULL && p->right!=NULL) { // found and has two children
        n = findmin(p->right);                  // get smallest in right tree
        p->item = n->item;                      // overwrite the item to be deleted
        p->right = del(t, p->item, p->right);   // del the duplicate item in right tree
    }
    
    else {                                      // found and has at most one child
        n = p;
        if(p->left == NULL)
            p = p->right;                       // promote the right tree
            
        else if (p->right == NULL)              // or...
            p = p->left;                        // promote the left tree

        (t->size)--;                            // reduce the count
        free(n);                                // reclaim memory
    }
    
    return ensure_balance(p);
}

void ${avl}_delete(${avl} *t, ${item} x)
{
    assert(t!=NULL);
    t->root = del(t, x, t->root);
}

int isin(${avl} *t, ${item} x, struct node *p)
{
    if (p==NULL)
        return 0;
        
    else if (LT(x,p->item))
        return isin(t, x, p->left);
        
    else if (LT(p->item,x))
        return isin(t, x, p->right);
        
    else 
        return 1;
}

int ${avl}_contains(${avl} *t, ${item} x)
{
    assert(t!=NULL);
    return isin(t,x,t->root);
}

void preorder(struct node *p, void (* item_print)(${item} item))
{
    if (p!=NULL) {
        item_print(p->item);
        preorder(p->left,item_print);
        preorder(p->right,item_print);
    }
}
void inorder(struct node *p, void (* item_print)(${item} item))
{
    if (p!=NULL) {
        inorder(p->left,item_print);
        item_print(p->item);
        inorder(p->right,item_print);
    }
}
void postorder(struct node *p, void (* item_print)(${item} item))
{
    if (p!=NULL) {
        postorder(p->left,item_print);
        postorder(p->right,item_print);
        item_print(p->item);
    }
}

void ${avl}_preorder_print(${avl} *t, void (* item_print)(${item} item))
{
    assert(t!=NULL);
    preorder(t->root, item_print);
}

void ${avl}_inorder_print(${avl} *t, void (* item_print)(${item} item))
{
    assert(t!=NULL);
    inorder(t->root, item_print);
}

void ${avl}_postorder_print(${avl} *t, void (* item_print)(${item} item))
{
    assert(t!=NULL);
    postorder(t->root, item_print);
}

void simple_print(struct node *p, int ind, void (* item_print)(${item} item))
{
    int i;
    
    if (p!=NULL) {
        simple_print(p->right,ind+4,item_print);
        for(i=0;i<ind;i++) putchar(' ');
        item_print(p->item);
        printf(" (h=%i).... %p", ((int)(p->height)), p);
        putchar('\n');
        simple_print(p->left,ind+4,item_print);
    }
    else {
       for(i=0;i<ind;i++) putchar(' ');
       printf("%p\n", p);
    }
}

void ${avl}_simple_print(${avl} *t, void (* item_print)(${item} item))
{
    assert(t!=NULL);
    simple_print(t->root,0,item_print);
}

void ${avl}_release(${avl} *t)
{
    assert(t!=NULL);
    free(t);
}
EOI

if [ "$item" = "char" ]; then
cat << EOI >>${target}

int tabwidth(int bot_up_level)
{
    return (int)pow(2,bot_up_level+1) - 1;
}

int indent(int bot_up_level)
{
    return tabwidth(bot_up_level) / 2;
}

int maxwidth(int bot_up_level, int depth)
{
    int tab = tabwidth(bot_up_level);
    int ind = indent(bot_up_level);
    int maxnodes = (int)pow(2,(depth - bot_up_level) );
    return (maxnodes *(tab + 1)) - ind - 1;
}

void populate(char * arraytree, int size, int index, struct node* p)
{
    if (p==NULL) {
       if (index < size)
          arraytree[index] = ' ';
    }
    else {
       arraytree[index] = p->item;
       populate(arraytree, size, index*2,   p->left);
       populate(arraytree, size, index*2+1, p->right);
    }
}

void spaces(int i)
{
    while (i>0) {
       printf(" ");
       i--;
    }
}

void putchars(int i, char c)
{
    while (i>0) {
       putchar(c);
       i--;
    }
}

void ${avl}_pretty_print(${avl} *t)
{
    char * arraytree;
    int k,r,n;
    int tab, ind;
    int space;
    int depth    = ${avl}_depth(t);
    int maxnodes = (int)pow(2,depth) - 1;
    int pictrows = depth * 2 - 1;
    
    arraytree = (char*)malloc((maxnodes+1) * sizeof(char));
    
    for (k=0; k<=maxnodes; k++)
        arraytree[k] = ' ';
      
    populate(arraytree, maxnodes+1, 1, t->root);
    
    k = 1;                   // index to the root of the tree within arraytree
    r = pictrows - 1;        // root level of the picture
    printf("BST {\n");
    while (r >=0) {
       int tab = tabwidth(r/2+1);
       int ind = indent(r/2+1);

       if (r % 2 == 0) {     // if r is an even row number then we are printing data...
          spaces(ind);
          for(n=k; n<2*k-1; n++) {
             putchar(arraytree[n]);
             spaces(tab);
          }
          putchar(arraytree[n]);  
          putchar('\n');
          k = k*2;                                // move index to left subtree
       }
       else {                // if r is an odd row number then we are drawing lines...
          spaces(ind);
          for(n=k; n<2*k; n++) {
             if ( n%2 == 0 ) {                    // must be a left node
                if (arraytree[n] == ' ')          // node is empty
                   spaces(tab/2+1);
                else {                            // node is not empty
                   putchar('.');
                   putchars(tab/2,'-');
                }
                if (arraytree[n] == ' ' && arraytree[n+1] == ' ')
                    putchar(' ');
                else
                    putchar('^');
                }
             else {                               // must be a right node
                if (arraytree[n] == ' ')          // node is empty
                   spaces(tab/2+1);
                else {                            // node is not empty
                   putchars(tab/2,'-');
                   putchar('.');
                }
             
                if (n == 2*k - 1)                 // only if we are at the end of the row...
                   putchar('\n');
                else                              // otherwise fill in the blanks
                     spaces(tab);
             }
          }
       }
       r--;                                       // move down to next row of picture
    }
    printf("}\n");
    free(arraytree);
}
EOI
else
  echo
fi

