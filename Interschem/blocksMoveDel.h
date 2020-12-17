#ifndef BLOCKSMOVEDEL_H_INCLUDED
#define BLOCKSMOVEDEL_H_INCLUDED

#include "blocks.h"


node *findNodeByTimeInStart(int time, node * head)
{
    int visited[ALL_NODES_TIME_SIZE];
    int j = 0;
    bool isVisited;
    if (head->timePriority)
    {
        if (ALL_NODES_TIME.arraySize != 0)
        {
            for (int i = 0; i < ALL_NODES_TIME_SIZE; ++i)
            {
                if (visited[i] == head->timePriority)
                {
                    isVisited = true;
                    break;
                }
                isVisited = false;
            }
        }
        if (!isVisited)
        {
            visited[j] = head->timePriority;
            if (head->timePriority == time)
                return head;
            findNodeByTimeInStart(time, head->next);
            if (head->isDecision == true)
                findNodeByTimeInStart(time, head->nextElse);
        }
    }
    return NULL;
}

//to implement for rests
node *findNodeByTime(int time)
{
    node *found;
    if (START)
    {
        if (START->timePriority == time)
            return START;
        if (START->next)
        {
            found = findNodeByTimeInStart(time, START->next);
            if (found)
                return found;
        }
    }
    for (int j = 0; j < FREE_NODES_SIZE; ++j)
        if (FREE_NODES->n[j] != NULL && FREE_NODES->n[j]->timePriority == time)
            return FREE_NODES->n[j];
    return NULL;

}

void addBlocksFromList(node *head, int &i)
{
    int visited[ALL_NODES_TIME_SIZE];
    int j = 0;
    bool isVisited;
    if (head->timePriority)
    {
        if (ALL_NODES_TIME.arraySize != 0)
        {
            for (int i = 0; i < ALL_NODES_TIME_SIZE; ++i)
            {
                if (visited[i] == head->timePriority)
                {
                    isVisited = true;
                    break;
                }
                isVisited = false;
            }
        }
        if (!isVisited)
        {
            ALL_NODES_TIME.n[i++] = head->timePriority;
            visited[j] = head->timePriority;
            addBlocksFromList(head->next, i);
            if (head->isDecision == true)
                addBlocksFromList(head->nextElse, i);
        }
    }
}

//to implement rest nodes
void createArrayWithAllBlocks()
{
    int i = 0;
    int j;
    if (START)
    {
        ALL_NODES_TIME.n[i++] = START->timePriority;
        if (START->next)
            addBlocksFromList(START->next, i);
    }

    for (j = 0; j < FREE_NODES_SIZE; ++j)
        if (FREE_NODES->n[j] != NULL)
            ALL_NODES_TIME.n[i++] = FREE_NODES->n[j]->timePriority;

    ALL_NODES_TIME.arraySize = i;
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

void drawAll()
{
    createArrayWithAllBlocks();
    sortArrayByTime(0, ALL_NODES_TIME.arraySize - 1);
    for (int i = 0; i < ALL_NODES_TIME.arraySize; ++i)
    {
        createBlock(findNodeByTime(ALL_NODES_TIME.n[i]), true);
    }
}

void moveBlock(int x, int y, node *p)
{
    POINT cursorPos1, cursorPos2;
    cursorPos1.x = x;
    cursorPos1.y = y;
    bool isFirstTime = true;

    while (!ismouseclick(WM_LBUTTONUP))
    {
        GetCursorPos(&cursorPos2);
        if (cursorPos1.x != cursorPos2.x || cursorPos1.y != cursorPos2.y)
        {
            if (isFirstTime)
            {
                isFirstTime = false;
            }
            else
            {
                createBlock(p, false);
                p->coordX = cursorPos1.x;
                p->coordY = cursorPos1.y;
                createBlock(p, true);
                updateTimePriority(p);
            }
        }
        GetCursorPos(&cursorPos1);
    }
    drawAll();
    clearmouseclick(WM_LBUTTONUP);
}

#endif // BLOCKSMOVEDEL_H_INCLUDED
