# Shell script to generate an avl header file
# Author: drs
# Modified: Barnaby Stewart (add find function to allow key searching)
# Usage: ./avl_header.sh int
#        creates an int avl header file:  avl_int.h

item=$1
avl=avl_${item}
target=${avl}.h

echo "#ifndef AVL_${item}_H"                                                       > ${target}
echo "#define AVL_${item}_H"                                                      >> ${target}
echo                                                                              >> ${target}
echo "// Auto-generated header file for an avl of ${item}"                        >> ${target}
echo "// values.  This avl has no exception handling but"                         >> ${target}
echo "// prints a message on stdout and calls exit(1)."                           >> ${target}
echo "// Author: drs."                                                            >> ${target}
echo                                                                              >> ${target}
echo "typedef struct ${avl}_implementation ${avl};"                               >> ${target}
if [ "$item" = "any" ]; then                                                     
    echo "#include \"any.h\""                                                     >> ${target}
    echo "typedef int (*rel_fun)(any a, any b);"                                  >> ${target}
    echo                                                                          >> ${target}
    echo "${avl} * new_${avl}(rel_fun lt);"                                       >> ${target}
	echo "any  ${avl}_find(${avl} *t, any key);"                                  >> ${target}
else                                                                             
    echo                                                                          >> ${target}
    echo "${avl} * new_${avl}();"                                                 >> ${target}
fi                                                                               
echo "int  ${avl}_isempty(${avl} *t);"                                            >> ${target}
echo "int  ${avl}_isfull(${avl} *t);"                                             >> ${target}
echo "int  ${avl}_size(${avl} *t);"                                               >> ${target}
echo "int  ${avl}_depth(${avl} *t);"                                              >> ${target}
echo "void ${avl}_insert(${avl} *t, ${item} x);"                                  >> ${target}
echo "void ${avl}_delete(${avl} *t, ${item} x);"                                  >> ${target}
echo "int  ${avl}_contains(${avl} *t, ${item} x);"                                >> ${target}
echo "void ${avl}_preorder_print(${avl} *t, void (* item_print)(${item} item));"  >> ${target}
echo "void ${avl}_inorder_print(${avl} *t, void (* item_print)(${item} item));"   >> ${target}
echo "void ${avl}_postorder_print(${avl} *t, void (* item_print)(${item} item));" >> ${target}
echo "void ${avl}_simple_print(${avl} *t, void (* item_print)(${item} item));"    >> ${target}
if [ "$item" = "char" ]; then
    echo "void ${avl}_pretty_print(${avl} *t);"                                   >> ${target}
    echo                                                                          >> ${target}
else
    echo                                                                          >> ${target}
fi
echo "void ${avl}_release(${avl} *t);"                                            >> ${target}
echo "#endif"                                                                     >> ${target}
