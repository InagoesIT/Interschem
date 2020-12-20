#include <iostream>

#define START_HEIGHT 70
#define START_WIDTH 150
#define STOP_HEIGHT 70
#define STOP_WIDTH 150
#define IN_HEIGHT 50
#define IN_BIG_BASE 120
#define IN_SMALL_BASE 60
#define ASSIGN_HEIGHT 60
#define ASSIGN_WIDTH 200
#define DECISION_BASE 150
#define DECISION_HEIGHT 80
#define FREE_NODES_SIZE 10
#define ALL_NODES_TIME_SIZE 100

using namespace std;

struct node
{
    char type[20];
    bool isDecision;
    char expression[50];
    node * next;
    node * nextElse;
    double coordX;
    double coordY;
    int timePriority;
    int location; //0 for main scheme, 1 for free node, 2 for rests
    bool viz;
    bool wasCreated;
};

struct freeNodesStruct
{
    node * n[FREE_NODES_SIZE];
};

struct allNodesTimeStruct
{
    int n[ALL_NODES_TIME_SIZE];
    int arraySize = 0;
};

struct restNodesStruct
{
    node * n[FREE_NODES_SIZE];
};

restNodesStruct * RESTS = new restNodesStruct;
allNodesTimeStruct ALL_NODES_TIME;
freeNodesStruct * FREE_NODES = new freeNodesStruct;
node * START = new node;
node * LAST_DELETED= new node;
int PRIORITY=1;

void updateTimePriority(node *p)
{
    p->timePriority = PRIORITY;
    PRIORITY++;
}

void createNode(char type[20], bool isDecision, int x, int y) //creates free node
{
    if(strcmp(type, "START")==0)
    {
        START->isDecision=0;
        strcpy(START->type, "START");
        START->next=START->nextElse=NULL;
        updateTimePriority(START);
        START->location=0;
        START->coordX=x;
        START->coordY=y;
        START->viz=0;
        START->wasCreated=1;
        for(int i=0; i<=FREE_NODES_SIZE; ++i)
            FREE_NODES->n[i]=NULL;
    }
    else
    {
        node * k = new node;
        k->isDecision=isDecision;
        strcpy(k->type, type);
        k->next=k->nextElse=NULL;
        updateTimePriority(k);
        k->location=1;
        k->coordX=x;
        k->coordY=y;
        k->viz=0;
        for(int i=0; i<=FREE_NODES_SIZE; ++i)
            if(FREE_NODES->n[i]==NULL)
            {
                FREE_NODES->n[i]=k;
                break;
            }
    }
}

void calculateVertices(double & xa, double & ya, double & xb, double & yb, double & xc, double & yc, node * p)
{
    xa=p->coordX+DECISION_BASE/2;
    ya=p->coordY;
    xb=p->coordX;
    yb=p->coordY+DECISION_HEIGHT;
    xc=p->coordX+DECISION_BASE;
    yc=p->coordY+DECISION_HEIGHT;
}

double calculateSlope(double xa, double ya, double xb, double yb)
{
    double m, a, b;
    a=xa-xb;
    b=ya-yb;
    m=a/b;
    return m;
}

double calculateConstant(double slope, double xa, double ya)
{
    double c;
    c=ya-slope*xa;
    return c;
}

bool isInsideNode(double x, double y, node * k)
{
    if(strcmp(k->type, "START")==0 or strcmp(k->type, "STOP")==0)
    {
        if(x >= k->coordX and x <= k->coordX+START_WIDTH and y >= k->coordY and y <= k->coordY+START_HEIGHT)
            return 1;
        return 0;
    }
    if(strcmp(k->type, "ASSIGN")==0)
    {
        if(x >= k->coordX and x <= k->coordX+ASSIGN_WIDTH and y >= k->coordY and y <= k->coordY+ASSIGN_HEIGHT)
            return 1;
        return 0;
    }
    if(strcmp(k->type, "DECISION")==0)
    {
        double xa, ya, xb, yb, xc, yc; //vertices coord
        double mAB, mBC, mAC; //slopes
        double constantAB, constantAC, constantBC; //constants form lines
        double currentConstant;

        calculateVertices(xa, ya, xb, yb, xc, yc, k);

        mAB = calculateSlope(xa, ya, xb, yb);
        constantAB = calculateConstant(mAB, xa, ya);
        currentConstant = calculateConstant(mAB, x, y);
        if(currentConstant<constantAB)
            return 0;

        mAC = calculateSlope(xa, ya, xc, yc);
        constantAC = calculateConstant(mAC, xa, ya);
        currentConstant = calculateConstant(mAC, x, y);
        if(currentConstant<constantAC)
            return 0;

        mBC = 0;
        constantBC = yb;
        currentConstant = y;
        if(currentConstant>constantBC)
            return 0;

        return 1;
    }
    if(strcmp(k->type, "IN")==0)
    {
        if(y<k->coordY or y>k->coordY+IN_HEIGHT)
            return 0;

        double xa, ya, xb, yb, m, constant, currentConstant;
        xa=k->coordX;
        ya=k->coordY;
        xb=xa+(IN_BIG_BASE-IN_SMALL_BASE)/2;
        yb=ya+IN_HEIGHT;

        m = calculateSlope(xa, ya, xb, yb);
        constant = calculateConstant(m, xa, ya);
        currentConstant = calculateConstant(m, x, y);
        if(currentConstant>constant)
            return 0;

        xa=k->coordX+IN_BIG_BASE;
        ya=k->coordY;
        xb=xa-(IN_BIG_BASE-IN_SMALL_BASE)/2;
        yb=ya+IN_HEIGHT;

        m = calculateSlope(xa, ya, xb, yb);
        constant = calculateConstant(m, xa, ya);
        currentConstant = calculateConstant(m, x, y);
        if(currentConstant>constant)
            return 0;

        return 1;
    }
    if(strcmp(k->type, "OUT")==0)
    {
        if(y<k->coordY or y>k->coordY+IN_HEIGHT)
            return 0;

        double xa, ya, xb, yb, m, constant, currentConstant;
        xa=k->coordX+(IN_BIG_BASE-IN_SMALL_BASE)/2;
        ya=k->coordY;
        xb=k->coordX;
        yb=ya+IN_HEIGHT;

        m = calculateSlope(xa, ya, xb, yb);
        constant = calculateConstant(m, xa, ya);
        currentConstant = calculateConstant(m, x, y);
        if(currentConstant<constant)
            return 0;

        xa=k->coordX+(IN_BIG_BASE-IN_SMALL_BASE)/2+IN_SMALL_BASE;
        ya=k->coordY;
        xb=xa+(IN_BIG_BASE-IN_SMALL_BASE)/2;
        yb=ya+IN_HEIGHT;

        m = calculateSlope(xa, ya, xb, yb);
        constant = calculateConstant(m, xa, ya);
        currentConstant = calculateConstant(m, x, y);
        if(currentConstant<constant)
            return 0;

        return 1;
    }
}

void selectCorrectNodeFromStart(int x, int y, int & maxPriority, node * & selectedNode, node * & currentNode, bool &selected, node * & underSelectedNode, bool & selectedAtLeastTwice) //goes through all main scheme nodes to see if selected now
{
    currentNode->viz=1;
    if(currentNode)
    {
        if(isInsideNode(x, y, currentNode)==1)
        {
            if(maxPriority<currentNode->timePriority)
            {
                maxPriority=currentNode->timePriority;
                if(selected==1)
                    selectedAtLeastTwice=1;
                if(selectedAtLeastTwice==1)
                    underSelectedNode=selectedNode;
                selectedNode=currentNode;
                selected=1;
            }
        }
        if(currentNode->next and currentNode->next->viz==0)
            selectCorrectNodeFromStart(x, y, maxPriority, selectedNode, currentNode->next, selected, underSelectedNode, selectedAtLeastTwice);
        if(currentNode->nextElse and currentNode->nextElse->viz==0)
            selectCorrectNodeFromStart(x, y, maxPriority, selectedNode, currentNode->nextElse, selected, underSelectedNode, selectedAtLeastTwice);
    }
}

bool isSchemeCorrect(node * k)
{
    if(!(START->wasCreated))
        return 0;
    k->viz=1;
    if(!(k->next) and !(k->nextElse) and strcmp(k->type, "STOP")!=0)
        return 0;
    if(k->next and k->next->viz==0)
        isSchemeCorrect(k->next);
    if(k->nextElse and k->nextElse->viz==0)
        isSchemeCorrect(k->nextElse);
    return 1;
}

void restoreViz(node * k)
{
    if(!(START->wasCreated))
        return;
    k->viz=0;
    if(k->next and k->next->viz==1)
        isSchemeCorrect(k->next);
    if(k->nextElse and k->nextElse->viz==1)
        isSchemeCorrect(k->nextElse);
}

void selectCorrectNodeFromFreeNodes(int x, int y, int & maxPriority, node * & selectedNode, bool & selected, node * & underSelectedNode, bool & selectedAtLeastTwice) //goes through all free nodes to see if selected now
{
    for (int i=0; i<=FREE_NODES_SIZE; ++i)
    {
        if(FREE_NODES->n[i])
        {
            if(isInsideNode(x, y, FREE_NODES->n[i])==1)
            {
                if(maxPriority<FREE_NODES->n[i]->timePriority)
                {
                    maxPriority=FREE_NODES->n[i]->timePriority;
                    if(selected==1)
                        selectedAtLeastTwice=1;
                    if(selectedAtLeastTwice==1)
                        underSelectedNode=selectedNode;
                    selectedNode=FREE_NODES->n[i];
                    selected=1;
                }
            }
        }
    }
}

void selectCorrectNodeFromRests(int x, int y, node * k, int & maxPriority, bool & selected, bool & selectedAtLeastTwice, node * & selectedNode, node * & underSelectedNode)
{
    if(k)
    {
        k->viz=1;
        if(isInsideNode(x, y, k)==1)
        {
            if(maxPriority<k->timePriority)
            {
                maxPriority=k->timePriority;
                if(selected==1)
                    selectedAtLeastTwice=1;
                if(selectedAtLeastTwice==1)
                    underSelectedNode=selectedNode;
                selectedNode=k;
                selected=1;
            }
        }
        if(k->next and k->next->viz==0)
            selectCorrectNodeFromRests(x, y, k->next, maxPriority, selected, selectedAtLeastTwice, selectedNode, underSelectedNode);
        if(k->nextElse and k->next->viz==0)
            selectCorrectNodeFromRests(x, y, k->nextElse, maxPriority, selected, selectedAtLeastTwice, selectedNode, underSelectedNode);
    }
}

void selectCorrectNode(int x, int y, node * & selectedNode, node * & underSelectedNode)  //select the correct node from (x,y)
{
    int maxPriority=0;
    bool selected=0, selectedAtLeastTwice=0;
    if(START->wasCreated)
    {
        node * currentNode = new node;
        currentNode=START;
        selectCorrectNodeFromStart(x, y, maxPriority, selectedNode, currentNode, selected, underSelectedNode, selectedAtLeastTwice);
    }
    restoreViz(START);
    selectCorrectNodeFromFreeNodes(x, y, maxPriority, selectedNode, selected, underSelectedNode, selectedAtLeastTwice);
    for(int i=0; i<=FREE_NODES_SIZE; ++i)
    {
        if(RESTS->n[i]!=NULL)
        {
            selectCorrectNodeFromRests(x, y, RESTS->n[i], maxPriority, selected, selectedAtLeastTwice, selectedNode, underSelectedNode);
            restoreViz(RESTS->n[i]);
        }
    }
    if(!selected)
        selectedNode=NULL, underSelectedNode=NULL;
    if(selected and !selectedAtLeastTwice)
        underSelectedNode=NULL;
}

void writeNode(node * n)
{
    if(n)
    {
        cout<<n->type;
        cout<<'\n';
        cout<<n->location;
        cout<<'\n';
        cout<<n->timePriority;
        cout<<'\n';
        cout<<n->coordX;
        cout<<'\n';
        cout<<n->coordY;
        cout<<'\n';
        cout<<n->isDecision;
        cout<<'\n';
        cout<<'\n';
    }
    else
        cout<<"There is no selected node";
}
void deleteNode(node * & k)
{
    LAST_DELETED = k;
    k->wasCreated=0;
    if(k->next)
        for(int i=0; i<=FREE_NODES_SIZE; ++i)
            if(RESTS->n[i]==NULL)
            {
                RESTS->n[i]=k->next;
                RESTS->n[i]->wasCreated=1;
                break;
            }
    if(k->nextElse)
        for(int i=0; i<=FREE_NODES_SIZE; ++i)
            if(RESTS->n[i]==NULL)
            {
                RESTS->n[i]=k->nextElse;
                RESTS->n[i]->wasCreated=1;
                break;
            }
    if(!START)
    {
        for(int i=0; i<=FREE_NODES_SIZE; ++i)
        {
            if(RESTS->n[i]==k)
                RESTS->n[i]=NULL;
        }
        delete k;
    }
}

void makeBindingAB(node * & a, node * & b, bool fromElse)
{
    if(fromElse==0)
        a->next=b;
    else
        a->nextElse=b;
    for(int i=0; i<=FREE_NODES_SIZE; ++i)
    {
        if(FREE_NODES->n[i]==b)
            FREE_NODES->n[i]=NULL;
    }
    for(int i=0; i<=FREE_NODES_SIZE; ++i)
    {
        if(RESTS->n[i]==b)
            RESTS->n[i]=NULL;
    }
    for(int i=0; i<=FREE_NODES_SIZE; ++i)
    {
        if(FREE_NODES->n[i]==a)
            FREE_NODES->n[i]=NULL;
        for(int j=0; j<=FREE_NODES_SIZE; ++j)
            if(RESTS->n[j]==NULL)
            {
                RESTS->n[j]=a;
                a->location=3;
            }
    }
    b->location=a->location;
}

void initialize()
{
    for(int i=0; i<=FREE_NODES_SIZE; ++i)
        RESTS->n[i]=NULL;
}



