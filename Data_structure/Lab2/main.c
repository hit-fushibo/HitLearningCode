#include "Code.h"
#include "Decode.h"
#include "Fileop.h"

#include "Code.c"
#include "Decode.c"
#include "Fileop.c"

int main(void)
{
    CW *Weight;
    int kind = 0;
    char *input;
    GetData(&input);//get input
    if (strlen(input) == 0)
    {
        printf("error input NULL");
        return 0;
    }
    kind = GetWeights(input, &Weight);//get weight and kind
    if (kind == 1)
    {
        char **a = (char **)malloc(sizeof(char *));
        for (int i = 0; i < kind; i++)
        {
            a[i] = (char *)malloc(sizeof(char) * 4);
        }
        a[0][0] = input[0];
        a[0][1] = ' ';
        a[0][2] = '1';
        a[0][3] = '\0';
        OutputHufcode(a, kind);
        int len = strlen(input);
        char *code = (char *)malloc(sizeof(char) * len);
        CodeString(input, a, code);
        int ziplen = ZipCode(code);
        GetHufcode(a);
        char *decode;
        Unzip(&decode, ziplen);
        char *Dedata = (char *)malloc(sizeof(char) * 10000);
        Decode(Dedata, a, decode);
        OutputData(Dedata);
    }
    else
    {
        HuT *w = CreatNode(Weight, kind);//creat node
        HuT *root = CreatHuffman(w, kind);//creat huffmantree
        char **huffmacode = (char **)malloc(sizeof(char *) * kind);
        for (int i = 0; i < kind; i++)
        {
            huffmacode[i] = (char *)malloc(sizeof(char) * (kind));
        }
        char buffer[100] = {0};
        HuffmanCode(huffmacode, root, buffer, 0);//get huffmancode
        OutputHufcode(huffmacode, kind);//output 
        int len = strlen(input);
        char *code = (char *)malloc(sizeof(char) * len * strlen(huffmacode[kind - 1]));
        CodeString(input, huffmacode, code);//code input
        int ziplen = ZipCode(code);//oputput
        GetHufcode(huffmacode);
        char *decode;
        Unzip(&decode, ziplen);
        char *Dedata = (char *)malloc(sizeof(char) * 10000);
        Decode(Dedata, huffmacode, decode);
        OutputData(Dedata);//output decode
    }
    return 0;
}