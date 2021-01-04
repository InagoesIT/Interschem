#ifndef BLOCKSMOVEDEL_H_INCLUDED
#define BLOCKSMOVEDEL_H_INCLUDED

#include "blocks.h"
#include "menu.h"
#include "list.h"

#define DRAG_SIZE_X 250
#define MENUY 70
#define WINDOWX 1200
#define WINDOWY 700

void drawPage();

void reinitializeListViz(node *head)
{
    if (head)
    {
        bool wasViz;
        if (head->viz)
        {
            wasViz = true;
            head->viz = 0;
        }
        else
            wasViz = false;

        if (head->next && head->next->viz)
            reinitializeListViz(head->next);
        if (head->nextElse && head->nextElse->viz)
            reinitializeListViz(head->nextElse);
    }
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

node *findNodeByTimeInList(int time, node * head)
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
            return head;
        if (head->next && !head->next->viz)
            findNodeByTimeInList(time, head->next);
        if (head->nextElse && !head->nextElse->viz)
            findNodeByTimeInList(time, head->nextElse);
    }
    return NULL;
}

node *findNodeByTime(int time)
{
    node *found;
    int j;
    if (START->wasCreated)
    {
        if (START->timePriority == time)
            return START;
        if (START->next)
        {
            found = findNodeByTimeInList(time, START->next);
            if (found)
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
        found = findNodeByTimeInList(time, RESTS->n[j]);
        if (found)
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

//quick sort
void sortArrayByTime(int low, int high)
{
    if (low < high)
    {
        int mid = partitionNodes(low, high);

        sortArrayByTime(low, mid - 1);
        sortArrayByTime(mid + 1, high);
    }
}

void drawAllBlocks()
{
    reinitializeAllViz();
    createArrayWithAllBlocks();
    reinitializeAllViz();
    sortArrayByTime(0, ALL_NODES_TIME.arraySize - 1);
    for (int i = 0; i < ALL_NODES_TIME.arraySize; ++i)
        createBlock(findNodeByTime(ALL_NODES_TIME.n[i]), true);
}

void moveBlock(int x, int y, node *p, bool isNew)
{
    POINT cursorPos1, cursorPos2;
    cursorPos1.x = x;
    cursorPos1.y = y;
    bool isFirstTime = true;

    clearmouseclick(WM_LBUTTONUP);

    while (!ismouseclick(WM_LBUTTONUP))
    {
        GetCursorPos(&cursorPos2);
        if (cursorPos1.x != cursorPos2.x || cursorPos1.y != cursorPos2.y)
        {
            if (isFirstTime)
                isFirstTime = false;
            else
            {
                if (isNew && cursorPos1.y > MENUY + 10 && cursorPos1.y < WINDOWY - 100 && cursorPos1.x < WINDOWX - 200)
                {
                    createBlock(p, false);
                    drawPage();
                    p->coordX = cursorPos1.x;
                    p->coordY = cursorPos1.y;
                    createBlock(p, true);
                }
                else if (!isNew && cursorPos1.y > MENUY + 10 && cursorPos1.x > DRAG_SIZE_X + 10 && cursorPos1.y < WINDOWY - 100 && cursorPos1.x < WINDOWX - 200)
                {
                    createBlock(p, false);
                    p->coordX = cursorPos1.x;
                    p->coordY = cursorPos1.y;
                    createBlock(p, true);
                }
            }
        }
        GetCursorPos(&cursorPos1);
    }
    if (!isNew)
        updateTimePriority(p);
    if ((isNew && strcmp(p->type, "START")) || !isNew)
    {
         line(DRAG_SIZE_X, MENUY, DRAG_SIZE_X, WINDOWY);
         drawAllBlocks();
    }

    clearmouseclick(WM_LBUTTONUP);
}

#endif // BLOCKSMOVEDEL_H_INCLUDED
