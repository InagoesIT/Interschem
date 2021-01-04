#ifndef OPENSAVESCHEME_H_INCLUDED
#define OPENSAVESCHEME_H_INCLUDED

#define SCHEME_SIZE 30

#include "blocks.h"
#include "blocksMoveDel.h"
#include "menu.h"

void drawPage();
void drawMenu();

struct readNode
{
    char type[20];
    bool isDecision;
    char expression[EXPRESSION_LENGTH];
    int next = 0;
    int nextElse = 0;
    double coordX;
    double coordY;
    int timePriority = 0;
    bool viz = 0;
};

readNode nodesInfo[SCHEME_SIZE];

bool isFreeNull()
{
    for (int i = 0; i < FREE_NODES_SIZE; ++i)
        if (FREE_NODES->n[i])
            return false;
    return true;
}

bool isRestsNull()
{
    for (int i = 0; i < FREE_NODES_SIZE; i++)
        if (RESTS->n[i])
            return false;
    return true;
}

void writeSchemeToScreen(char path[500], node *head)
{
    if (head && !head->viz)
    {
        cout << head->type << ",";
        cout << head->timePriority << ",";
        cout << head->coordX << ",";
        cout << head->coordY << ",";
        if (!strcmp(head->expression, "no expression"))
            cout << "0,";
        else
            cout << head->expression << ",";
        cout << head->isDecision << ",";
        if (head->next)
            cout << head->next->timePriority << ",";
        else
            cout << "0,";
        if (head->next || head->nextElse)
        {
            if (head->isDecision && head->nextElse)
                cout << head->nextElse->timePriority << endl;
            else
                cout << "0" << endl;
        }

        else
        {
            if (head->isDecision && head->nextElse)
                cout << head->nextElse->timePriority;
            else
                cout << "0";
        }

        head->viz = 1;

        writeSchemeToScreen(path, head->next);
        if (head->isDecision)
            writeSchemeToScreen(path, head->nextElse);
    }
}

void writeSchemeToFile(char path[500], node *head)
{
    if (head && !head->viz)
    {
        ofstream File;
        File.open(path, ios::app);
        File << head->type << ",";
        File << head->timePriority << ",";
        File << head->coordX << ",";
        File << head->coordY << ",";
        if (!strcmp(head->expression, "no expression"))
            File << "0,";
        else
            File << head->expression << ",";
        File << head->isDecision << ",";
        if (head->next)
            File << head->next->timePriority << ",";
        else
            File << "0,";
        if (head->next || head->nextElse)
        {
            if (head->isDecision && head->nextElse)
                File << head->nextElse->timePriority << endl;
            else
                File << "0" << endl;
        }

        else
        {
            if (head->isDecision && head->nextElse)
                File << head->nextElse->timePriority;
            else
                File << "0";
        }

        head->viz = 1;

        writeSchemeToFile(path, head->next);
        if (head->isDecision)
            writeSchemeToFile(path, head->nextElse);

        File.close();
    }
}

bool pathExists(char path[500])
{
    fstream File;
    File.open(path, ios::in);
    if (!File)
		return false;
    else
    {
        File.close();
        return true;
    }
}

bool ispathForOut(char path[500])
{
    fstream File;
    File.open(path, ios::app);
    if (!File)
		return false;
    else
    {
        File.close();
        return true;
    }
}

void saveScheme()
{
    char path[500];
    if (START->wasCreated && isFreeNull() && isRestsNull())  //change to isSchemeCorrect() from START->wasCreated
    {
        cout << "Give the path of the file you want to save your scheme into." << endl;
        cin >> path;
        if (ispathForOut(path))
        {
            reinitializeAllViz();
            writeSchemeToFile(path, START);
            cout << "The scheme was saved successfully!" << endl;
        }
        else
            cout << "The path choosen doesn't permit creating a new file." << endl;
    }
    else
        cout << "The scheme isn't correct." << endl;
}

void reinitializeArr()
{
    int i = 0;
    while (nodesInfo[i].timePriority)
    {
        strcpy(nodesInfo[i].type, "");
        nodesInfo[i].timePriority = 0;
        nodesInfo[i].coordX = 0;
        nodesInfo[i].coordY = 0;
        strcpy(nodesInfo[i].expression, "no expression");
        nodesInfo[i].isDecision = 0;
        nodesInfo[i].next = 0;
        nodesInfo[i].nextElse = 0;
    }
}

void writeNodesInfoInArr(char path[500])
{
    fstream File;
    File.open(path, ios::in);
    char info[200];
    char *token;
    int i = 0;
    while (!File.eof())
    {
        File >> info;

        token = strtok(info, ",");
        strcpy(nodesInfo[i].type, token);
        token = strtok(NULL, ",");
        nodesInfo[i].timePriority = atoi(token);
        token = strtok(NULL, ",");
        nodesInfo[i].coordX = atoi(token);
        token = strtok(NULL, ",");
        nodesInfo[i].coordY = atoi(token);
        token = strtok(NULL, ",");
        if (strcmp(token, "0") != 0)
            strcpy(nodesInfo[i].expression, token);
        token = strtok(NULL, ",");
        nodesInfo[i].isDecision = !strcmp(token, "1");
        token = strtok(NULL, ",");
        nodesInfo[i].next = atoi(token);
        token = strtok(NULL, ",");
        nodesInfo[i].nextElse = atoi(token);

        i++;
    }
    File.close();
}

readNode findNodeInArr(int time)
{
    int i = 0;
    while (nodesInfo[i].timePriority)
    {
        if (nodesInfo[i].timePriority == time)
            return nodesInfo[i];
        i++;
    }
}

void addNextNodesToScheme(readNode headArr, node *head)
{
    node *next = new node;
    readNode nextArr;
    node *nextElse = new node;
    readNode nextElseArr;

    if (headArr.timePriority)
    {
        if (headArr.next && !head->next)
        {
            nextArr = findNodeInArr(headArr.next);
            if (!nextArr.viz)
            {
                next = createNode(nextArr.type, nextArr.isDecision, nextArr.coordX, nextArr.coordY, nextArr.timePriority);
                strcpy(next->expression, nextArr.expression);
            }
            else
                next = findNodeByTime(headArr.next);
            head->next = next;
            nextArr.viz = 1;
            addNextNodesToScheme(nextArr, next);
        }
        if (headArr.isDecision && !head->nextElse && headArr.nextElse)
        {
            nextElseArr = findNodeInArr(headArr.nextElse);
            if (!nextElseArr.viz)
            {
                nextElse = createNode(nextElseArr.type, nextElseArr.isDecision, nextElseArr.coordX, nextElseArr.coordY, nextElseArr.timePriority);
                strcpy(nextElse->expression, nextElseArr.expression);
            }

            else
                nextElse = findNodeByTime(headArr.nextElse);
            head->nextElse = nextElse;
            nextElseArr.viz = 1;
            addNextNodesToScheme(nextElseArr, nextElse);
        }
    }
}

void convertArrToScheme()
{
    if (nodesInfo[0].timePriority)
    {
        node *head = new node;
        if (START->wasCreated)
        {
            delete START;
            START = new node;
            initialize();
        }
        head = createNode(nodesInfo[0].type, nodesInfo[0].isDecision, nodesInfo[0].coordX, nodesInfo[0].coordY, nodesInfo[0].timePriority);
        nodesInfo[0].viz = 1;
        addNextNodesToScheme(nodesInfo[0], head);
    }
}

void makePriorityMax()
{
    int i = 0;
    int maxTime = 0;
    while (nodesInfo[i].timePriority)
    {
        if (nodesInfo[i].timePriority > maxTime)
            maxTime = nodesInfo[i].timePriority;
        i++;
    }
    changePRIORITY(maxTime);
}

void openScheme()
{
    char path[500];
    cout << "Give the path of the file you want to open." << endl;
    cin >> path;
    if (pathExists(path))
    {
        writeNodesInfoInArr(path);
        makePriorityMax();
        convertArrToScheme();
        cleardevice();
        drawPage();
        drawMenu();
        drawAllBlocks();
        cout << "Scheme opened with succes!" << endl;
    }
    else
        cout << "There is no such path." << endl;
}


#endif // OPENSAVESCHEME_H_INCLUDED
