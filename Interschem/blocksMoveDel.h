#ifndef BLOCKSMOVEDEL_H_INCLUDED
#define BLOCKSMOVEDEL_H_INCLUDED

#include "blocks.h"
#include "menu.h"
#include "list.h"

#define DRAG_SIZE_X 250
#define OUTPUT_SIZE_X 400
#define MENUY 70
#define WINDOWX GetSystemMetrics(SM_CXSCREEN)
#define WINDOWY GetSystemMetrics(SM_CYSCREEN)

void drawPage();


void makeAllVizEqualTo2(node *head)
{
    if (head && (head->viz==1 or head->viz==0))
    {
        head->viz = 2;
        if (head->next && (head->next->viz==0 or head->next->viz==1))
            makeAllVizEqualTo2(head->next);
        if (head->nextElse && (head->nextElse->viz==0 or head->nextElse->viz==1))
            makeAllVizEqualTo2(head->nextElse);
    }
}

void makeAllVizFrom2To0(node * head)
{
    if (head)
    {
        if (head->viz==2)
        {
            head->viz = 0;
            if (head->next && head->next->viz==2)
                makeAllVizFrom2To0(head->next);
            if (head->nextElse && head->nextElse->viz==2)
                makeAllVizFrom2To0(head->nextElse);
        }
    }
}

void reinitializeListViz(node * head)
{
    makeAllVizEqualTo2(head);
    makeAllVizFrom2To0(head);
}

void reinitializeAllViz()
{
    int j;
    if (START->wasCreated)
    {
        reinitializeListViz(START);

        for (j = 0; j < FREE_NODES_SIZE; ++j)
            if (FREE_NODES->n[j] != NULL && FREE_NODES->n[j]->viz)
                FREE_NODES->n[j]->viz = 0;


        for (j = 0; j < FREE_NODES_SIZE; ++j)
            if (RESTS->n[j] != NULL)
                reinitializeListViz(RESTS->n[j]);
    }
}

void findNodeByTimeInList(int time, node * head, node * & nodeFound, bool & nodeWasFound)
{
    if(nodeWasFound==0)
    {
        bool wasViz;
        if (head->timePriority)
        {
            if (head->viz)
                wasViz = true;
            else
            {
                wasViz = false;
                head->viz = 1;
            }

            if (head->timePriority == time && wasViz == false)
            {
                nodeFound=head;
                nodeWasFound=1;
            }

            if (head->next && !head->next->viz)
                findNodeByTimeInList(time, head->next, nodeFound, nodeWasFound);
            if (head->nextElse && !head->nextElse->viz)
                findNodeByTimeInList(time, head->nextElse, nodeFound, nodeWasFound);
        }
    }
}

node *findNodeByTime(int time)
{
    node *found = new node;
    found=NULL;
    int j;
    if (START->wasCreated)
    {
        if (START->timePriority == time)
            return START;
        if (START->next)
        {
            bool nodeWasFound=0;
            findNodeByTimeInList(time, START->next, found, nodeWasFound);
            if(nodeWasFound==1)
                return found;
        }
    }

    for (j = 0; j < FREE_NODES_SIZE; ++j)
        if (FREE_NODES->n[j] != NULL && FREE_NODES->n[j]->timePriority == time)
            return FREE_NODES->n[j];

    for (j = 0; j < FREE_NODES_SIZE; ++j)
    {
        if (RESTS->n[j] != NULL && RESTS->n[j]->timePriority == time)
            return RESTS->n[j];
        bool nodeWasFound=0;
        if (RESTS->n[j])
            findNodeByTimeInList(time, RESTS->n[j], found, nodeWasFound);
        if (nodeWasFound==1)
            return found;
    }
    return NULL;
}

void addBlocksFromList(node *head, int &i)
{
    bool wasViz;
    if (head)
    {
        if (head->viz)
            wasViz = true;
        else
        {
            wasViz = false;
            head->viz = 1;
        }

        if (!wasViz)
            ALL_NODES_TIME.n[i++] = head->timePriority;
        if (head->next && !head->next->viz)
            addBlocksFromList(head->next, i);
        if (head->nextElse && !head->nextElse->viz)
            addBlocksFromList(head->nextElse, i);
    }
}

void createArrayWithAllBlocks()
{
    int i = 0;
    int j;
    if (START->wasCreated)
    {
        addBlocksFromList(START, i);

        for (j = 0; j < FREE_NODES_SIZE; ++j)
            if (FREE_NODES->n[j] != NULL)
                ALL_NODES_TIME.n[i++] = FREE_NODES->n[j]->timePriority;

        for (j = 0; j < FREE_NODES_SIZE; ++j)
            if (RESTS->n[j] != NULL)
                addBlocksFromList(RESTS->n[j], i);

        ALL_NODES_TIME.arraySize = i;
    }
}

int partitionNodes(int low, int high)
{
    int pivot = ALL_NODES_TIME.n[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; ++j)
    {
        if (ALL_NODES_TIME.n[j] <= pivot)
        {
            ++i;
            swap(ALL_NODES_TIME.n[i], ALL_NODES_TIME.n[j]);
        }
    }
    swap(ALL_NODES_TIME.n[i + 1], ALL_NODES_TIME.n[high]);
    return (i + 1);
}

void sortArrayByTime(int low, int high)//quick sort
{
    if (low < high)
    {
        int mid = partitionNodes(low, high);

        sortArrayByTime(low, mid - 1);
        sortArrayByTime(mid + 1, high);
    }
}

void reinitializeAllNodesTime()
{
    for (int i = 0; i < ALL_NODES_TIME.arraySize; ++i)
        ALL_NODES_TIME.n[i]=0;
    ALL_NODES_TIME.arraySize=0;
}

void drawAllBlocks()
{
    reinitializeAllViz();
    reinitializeAllNodesTime();
    createArrayWithAllBlocks();
    reinitializeAllViz();
    sortArrayByTime(0, ALL_NODES_TIME.arraySize - 1);
    if(ALL_NODES_TIME.arraySize)
    {
        for (int i = 0; i < ALL_NODES_TIME.arraySize; ++i)
        {
            reinitializeAllViz();
            node * k = new node;
            k=findNodeByTime(ALL_NODES_TIME.n[i]);
            createBlock(k, true);
        }
    }
}

void moveBlock(int x, int y, node *p, bool isNew, int difX, int difY)
{
    POINT cursorPos1, cursorPos2;
    cursorPos1.x = x-difX;
    cursorPos1.y = y-difY;
    bool isFirstTime = true;

    clearmouseclick(WM_LBUTTONUP);

    while (!ismouseclick(WM_LBUTTONUP))
    {
        cursorPos2.x=mousex()-difX;
        cursorPos2.y=mousey()-difY;
        if (cursorPos1.x != cursorPos2.x || cursorPos1.y != cursorPos2.y)
        {
            if (isFirstTime)
                isFirstTime = false;
            else
            {
                if (isNew && cursorPos1.y > MENUY + 10 && cursorPos1.y < WINDOWY - 100 && cursorPos1.x < WINDOWX - OUTPUT_SIZE_X - 200)
                {
                    createBlock(p, false);
                    drawPage();
                    p->coordX = cursorPos2.x;
                    p->coordY = cursorPos2.y;
                    createBlock(p, true);
                }
                else if (!isNew && cursorPos1.y > MENUY + 10 && cursorPos1.x > DRAG_SIZE_X + 10 && cursorPos1.y < WINDOWY - 100 && cursorPos1.x < WINDOWX - OUTPUT_SIZE_X - 200)
                {
                    createBlock(p, false);
                    p->coordX = cursorPos2.x;
                    p->coordY = cursorPos2.y;
                    createBlock(p, true);
                }
            }
        }
        cursorPos1.x=mousex()-difX;
        cursorPos1.y=mousey()-difY;
    }
    if (!isNew)
        updateTimePriority(p);
    if (isNew && p->coordX < DRAG_SIZE_X)
    {
        createBlock(p, false);
        deleteNode(p);
    }
    drawAllBlocks();
    clearmouseclick(WM_LBUTTONUP);
    reinitializeAllViz();
}

#endif // BLOCKSMOVEDEL_H_INCLUDED
