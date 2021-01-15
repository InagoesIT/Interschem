#ifndef OPENSAVESCHEME_H_INCLUDED
#define OPENSAVESCHEME_H_INCLUDED

#define SCHEME_SIZE 30
#include "blocks.h"
#include "blocksMoveDel.h"
#include "menu.h"

void drawPage();
void drawMenu();
void isSchemeCorrect(node * k, bool & isCorrect);
void popUpMessage(char a[200]);
void waitForClickToRefresh();
void generateCode(bool &isGenCode);

int VIZITED_NODES[SCHEME_SIZE];

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

void writeSchemeToFile(char path[500], node *head, bool &isFirstTime)
{
    if (head && !head->viz)
    {
        ofstream File;
        if (!isFirstTime)
            File.open(path, ios::app);
        else
        {
            isFirstTime = 0;
            File.open(path, ios::trunc);
        }
        File << head->type << ",";
        File << head->timePriority << ",";
        File << head->coordX << ",";
        File << head->coordY << ",";
        if (!strcmp(head->expression, "no expression") || !strlen(head->expression))
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

        writeSchemeToFile(path, head->next, isFirstTime);
        if (head->isDecision)
            writeSchemeToFile(path, head->nextElse, isFirstTime);

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

void getPathName(char path[500], bool fromOpen)
{
    char b[150];
    if(fromOpen==1)
        strcpy(b, "Enter the path of the scheme you want to open");
    else
        strcpy(b, "Enter path name");

    int textboxWidth=600, textboxHeight=100;
    setlinestyle(SOLID_LINE, 0, 1);
    setcolor(RED);
    line(WINDOWX/2-textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2-textboxWidth/2, WINDOWY/2+textboxHeight/2);
    line(WINDOWX/2-textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2+textboxWidth/2, WINDOWY/2-textboxHeight/2);
    line(WINDOWX/2+textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2+textboxWidth/2, WINDOWY/2+textboxHeight/2);
    line(WINDOWX/2+textboxWidth/2, WINDOWY/2+textboxHeight/2, WINDOWX/2-textboxWidth/2, WINDOWY/2+textboxHeight/2);

    setfillstyle(SOLID_FILL, THEME[CURRENT_THEME].option_clr);
    floodfill(WINDOWX/2, WINDOWY/2, RED);

    setlinestyle(SOLID_LINE, 0, 1);
    setcolor(THEME[CURRENT_THEME].option_clr);
    line(WINDOWX/2-textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2-textboxWidth/2, WINDOWY/2+textboxHeight/2);
    line(WINDOWX/2-textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2+textboxWidth/2, WINDOWY/2-textboxHeight/2);
    line(WINDOWX/2+textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2+textboxWidth/2, WINDOWY/2+textboxHeight/2);
    line(WINDOWX/2+textboxWidth/2, WINDOWY/2+textboxHeight/2, WINDOWX/2-textboxWidth/2, WINDOWY/2+textboxHeight/2);

    setcolor(THEME[CURRENT_THEME].bck_clr);
    line(WINDOWX/2-textboxWidth/2, WINDOWY/2, WINDOWX/2+textboxWidth/2, WINDOWY/2);

    setbkcolor(THEME[CURRENT_THEME].option_clr);
    setcolor(WHITE);
    outtextxy(WINDOWX/2-textwidth(b)/2, WINDOWY/2-textheight(b)/2-textboxHeight/4, b);
    setbkcolor(THEME[CURRENT_THEME].bck_clr);

    bool finished=0;
    char cc[500] = "";
    int i=strlen(cc);
    do
    {
        char c=getch();
        if(c==13) //enter
            finished=1;
        else
        {
            if(c==8) //backspace
            {
                if(strlen(cc)>=1)
                {
                    cc[strlen(cc)-1]=NULL;
                    --i;
                }
            }
            else
            {
                cc[i]=c;
                ++i;
                cc[i]=NULL;
            }
            setlinestyle(SOLID_LINE, 0, 1);
            setcolor(RED);
            line(WINDOWX/2-textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2-textboxWidth/2, WINDOWY/2+textboxHeight/2);
            line(WINDOWX/2-textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2+textboxWidth/2, WINDOWY/2-textboxHeight/2);
            line(WINDOWX/2+textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2+textboxWidth/2, WINDOWY/2+textboxHeight/2);
            line(WINDOWX/2+textboxWidth/2, WINDOWY/2+textboxHeight/2, WINDOWX/2-textboxWidth/2, WINDOWY/2+textboxHeight/2);

            setfillstyle(SOLID_FILL, THEME[CURRENT_THEME].option_clr);
            floodfill(WINDOWX/2, WINDOWY/2, RED);

            setlinestyle(SOLID_LINE, 0, 1);
            setcolor(THEME[CURRENT_THEME].option_clr);
            line(WINDOWX/2-textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2-textboxWidth/2, WINDOWY/2+textboxHeight/2);
            line(WINDOWX/2-textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2+textboxWidth/2, WINDOWY/2-textboxHeight/2);
            line(WINDOWX/2+textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2+textboxWidth/2, WINDOWY/2+textboxHeight/2);
            line(WINDOWX/2+textboxWidth/2, WINDOWY/2+textboxHeight/2, WINDOWX/2-textboxWidth/2, WINDOWY/2+textboxHeight/2);

            setcolor(THEME[CURRENT_THEME].bck_clr);
            line(WINDOWX/2-textboxWidth/2, WINDOWY/2, WINDOWX/2+textboxWidth/2, WINDOWY/2);

            setbkcolor(THEME[CURRENT_THEME].option_clr);
            setcolor(WHITE);
            outtextxy(WINDOWX/2-textwidth(b)/2, WINDOWY/2-textheight(b)/2-textboxHeight/4, b);
            outtextxy(WINDOWX/2-textwidth(cc)/2, WINDOWY/2-textheight(cc)/2+textboxHeight/4, cc);
            setbkcolor(THEME[CURRENT_THEME].bck_clr);
        }
    }
    while(finished==0 and i<EXPRESSION_LENGTH-2);
    strcpy(path, cc);
    refresh();
}

void saveScheme(bool isGenCode)
{
    char path[500];
    bool isCorrect=1;
    restoreVariables();
    isSchemeCorrect(START, isCorrect);
    restoreVariables();
    if (isCorrect && isFreeNull() && isRestsNull())
    {
        getPathName(path, 0);
        if (ispathForOut(path))
        {
            if (strcmp(path, "Generated Code.txt") && strcmp(path, "Generated Code"))
            {
                bool isFirstTime = 1;
                reinitializeAllViz();
                writeSchemeToFile(path, START, isFirstTime);
                reinitializeAllViz();
                popUpMessage("The scheme was saved succesfully!");
            }
            else
            {
                popUpMessage("Can't save the scheme in the file destined for generated code!");
            }
        }
        else
        {
            popUpMessage("The path choosen doesn't permit creating a new file.");
        }
    }
    else
    {
        popUpMessage("The scheme is incorrect!");
    }
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
        nodesInfo[i].viz = 0;
        strcpy(nodesInfo[i].expression, "no expression");
        nodesInfo[i].isDecision = 0;
        nodesInfo[i].next = 0;
        nodesInfo[i].nextElse = 0;
        i++;
    }
}

void writeNodesInfoInArr(char path[500])
{
    fstream File;
    File.open(path, ios::in);
    char info[300];
    char *token;
    int i = 0;
    if (nodesInfo[0].timePriority)
        reinitializeArr();
    while(File.get(info,300))
    {
//        File.getline(info, 300);
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
        else
            strcpy(nodesInfo[i].expression, "no expression");
        token = strtok(NULL, ",");
        nodesInfo[i].isDecision = !strcmp(token, "1");
        token = strtok(NULL, ",");
        nodesInfo[i].next = atoi(token);
        token = strtok(NULL, ",");
        nodesInfo[i].nextElse = atoi(token);

        i++;
        File.ignore();
    }
    File.close();
}

readNode findNodeInArr(int time, int &i)
{
    i = 0;
    while (nodesInfo[i].timePriority)
    {
        if (nodesInfo[i].timePriority == time)
            return nodesInfo[i];
        else
            i++;
    }
}

void rememberAllViz(node *head, int &i)
{
    if (head && head->viz != 2)
    {
        if (head->viz == 1)
        {
            VIZITED_NODES[i] = head->timePriority;
            i++;
        }

        head->viz = 2;

        if (head->next)
            rememberAllViz(head->next, i);
        if (head->nextElse)
            rememberAllViz(head->nextElse, i);
    }
}

bool wasViz(int nodeTime, int arrSize)
{
    for (int i = 0; i < arrSize; i++)
        if (VIZITED_NODES[i] == nodeTime)
            return 1;
    return 0;
}

void recoverVizInScheme(node *head, int arrSize)
{
    if (head->viz == 2)
    {
        if (wasViz(head->timePriority, arrSize))
            head->viz = 1;
        else
            head->viz = 0;

        if(head->next and head->next->viz==2)
            recoverVizInScheme(head->next, arrSize);
        if(head->nextElse and head->nextElse->viz==2)
            recoverVizInScheme(head->nextElse, arrSize);
    }
}

void addNextNodesToScheme(readNode headArr, node *head)
{
    node *next;
    readNode nextArr;
    node *nextElse;
    readNode nextElseArr;
    int i;

    if (headArr.next && !head->next)
    {
        nextArr = findNodeInArr(headArr.next, i);
        if (!nodesInfo[i].viz)
        {
            next = createNode(nextArr.type, nextArr.isDecision, nextArr.coordX, nextArr.coordY, nextArr.timePriority);
                strcpy(next->expression, nextArr.expression);
                nodesInfo[i].viz = 1;
                head->next = next;
                addNextNodesToScheme(nextArr, next);
            }
            else
            {
                int arrSize = 0;
                rememberAllViz(START, arrSize);
                makeAllVizFrom2To0(START);
                next = findNodeByTime(headArr.next);
                makeAllVizEqualTo2(START);
                recoverVizInScheme(START, arrSize);
                head->next = next;
            }
        }
        if (headArr.isDecision && !head->nextElse && headArr.nextElse)
        {
            nextElseArr = findNodeInArr(headArr.nextElse, i);
            if (!nodesInfo[i].viz)
            {
                nextElse = createNode(nextElseArr.type, nextElseArr.isDecision, nextElseArr.coordX, nextElseArr.coordY, nextElseArr.timePriority);
                strcpy(nextElse->expression, nextElseArr.expression);
                nodesInfo[i].viz = 1;
                head->nextElse = nextElse;
                addNextNodesToScheme(nextElseArr, nextElse);
            }
            else
            {
                int arrSize = 0;
                rememberAllViz(START, arrSize);
                makeAllVizFrom2To0(START);
                nextElse = findNodeByTime(headArr.nextElse);
                makeAllVizEqualTo2(START);
                recoverVizInScheme(START, arrSize);
                head->nextElse = nextElse;
            }
        }
}

void convertArrToScheme()
{
    node *head;
    if (nodesInfo[0].timePriority)
    {
        if (START->wasCreated)
        {
            delete START;
            START = new node;
            for(int i=0; i<FREE_NODES_SIZE; ++i)
                RESTS->n[i]=NULL;
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
    getPathName(path, 1);
    if (pathExists(path))
    {
        if (strcmp(path, "Generated Code.txt") && strcmp(path, "Generated Code"))
        {
            reinitializeAllViz();
            writeNodesInfoInArr(path);
            makePriorityMax();
            convertArrToScheme();
            reinitializeAllViz();
            cleardevice();
            drawPage();
            drawMenu();
            drawAllBlocks();
            popUpMessage("Scheme opened with succes!");
        }
        else
        {
            popUpMessage("Can't open the the file destined for generated code, because it's not a scheme!");
        }
    }
    else
    {
        popUpMessage("There is no such path.");
    }
}

#endif // OPENSAVESCHEME_H_INCLUDED
