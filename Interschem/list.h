struct node
{
    char type[20];
    bool isDecision;
    char expression[50];
    node * next;
    node * nextElse;
    int coordX;
    int coordY;

};

struct freeNodesStruct
{
    node * n[10];
};

freeNodesStruct * freeNodes = new freeNodesStruct;

node * start = new node;

void createNode(char type[20], bool isDecision)
{
    if(strcmp(type, "START")==0)
    {

        start->isDecision=0;
        strcpy(start->type, "START");
        start->next=start->nextElse=NULL;
        for(int i=1;i<=10;++i)
            freeNodes->n[i]=NULL;
    }
    else
    {
        node * k = new node;
        k->isDecision=isDecision;
        strcpy(k->type, type);
        k->next=k->nextElse=NULL;

        for(int i=1;i<=10;++i)
            if(freeNodes->n[i]==NULL)
            {
                freeNodes->n[i]=k;
                break;
            }

    }
}
