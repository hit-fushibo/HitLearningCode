#include"BinTree.h"

#include"BinTree.c"

int main (void)
{
    int depth=0;
    scanf("%d",&depth);
    BTreeNode * root=(BTreeNode * )malloc(sizeof(BTreeNode));
    root=TestCreatBT(depth);
    return 0;
}