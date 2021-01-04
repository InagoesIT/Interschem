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
    char expression[50];
    int next = 0;
    int nextElse = 0;
    double coordX;
    double coordY;
    int timePriority = 0;
    int location; //0 for main scheme, 1 for free node, 2 for rests
    bool viz = 0;
    bool wasCreated = 0;
};

readNode nodesInfo[SCHEME_SIZE];

bool isFreeNull()
{
    for (int i = 0; i < FREE_NODES_SIZE; ++i)
        if (FREE_NODES->n[i] != NULL)
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

void writeSchemeToFile(char path[500], node *head)
{
    if (head)
    {
        ofstream File;
        File.open(path, ios::app);

        if (File)
        {
            File << head->type << ",";
            File << head->timePriority << ",";
            File << head->coordX << ",";
            File << head->coordY << ",";
            if (strlen(head->expression))
                File << head->expression << ",";
            else
                File << "0,";
            File << head->isDecision << ",";
            if (head->next && head->next->timePriority)
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

            writeSchemeToFile(path, head->next);
            if (head->isDecision)
                writeSchemeToFile(path, head->nextElse);
            File.close();
        }
        else
            cout << "The path choosen doesn't permit creating a new file.";

    }
}

void saveScheme()
{
    char path[500];
    if (START->wasCreated && isFreeNull() && isRestsNull())
    {
        cout << "Give the path of the file you want to save your scheme into." << endl;
        cin >> path;
        reinitializeAllViz();
        writeSchemeToFile(path, START);
        cout << "The scheme was saved successfully!" << endl;
    }
    else
        cout << "The scheme isn't correct." << endl;
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
        if (token)
            strcpy(nodesInfo[i].expression, token);
        token = strtok(NULL, ",");
        nodesInfo[i].isDecision = !strcmp(token, "1");
        token = strtok(NULL, ",");
        nodesInfo[i].next = atoi(token);
        token = strtok(NULL, ",");
        nodesInfo[i].nextElse = atoi(token);
        nodesInfo[i].location = 0;

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
                next = createNode(nextArr.type, nextArr.isDecision, nextArr.coordX, nextArr.coordY, nextArr.timePriority);
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
                next = createNode(nextElseArr.type, nextElseArr.isDecision, nextElseArr.coordX, nextElseArr.coordY, nextElseArr.timePriority);
            else
                next = findNodeByTime(headArr.nextElse);
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
            head = START;
            initialize();
        }
        head = createNode(nodesInfo[0].type, nodesInfo[0].isDecision, nodesInfo[0].coordX, nodesInfo[0].coordY, nodesInfo[0].timePriority);
        nodesInfo[0].viz = 1;
        addNextNodesToScheme(nodesInfo[0], head);
    }
}

void openScheme()
{
    char path[500];
    cout << "Give the path of the file you want to open." << endl;
    cin >> path;
    if (pathExists(path))
    {
        writeNodesInfoInArr(path);
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
