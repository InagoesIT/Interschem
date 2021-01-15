#ifndef BLOCKOPTIONS_H_INCLUDED
#define BLOCKOPTIONS_H_INCLUDED

#include <iostream>

#define NEW_BLOCKS_SIZE 6

#define DECISION_WIDTH 150+textwidth("T")+textwidth("F")+20

#define OPTIONS_WIDTH 150
#define ONE_OPTION_HEIGHT 30

#define WINDOWX GetSystemMetrics(SM_CXSCREEN)
#define WINDOWY GetSystemMetrics(SM_CYSCREEN)
#define MENUY 70
#define DRAG_SIZE_X 250


void getOptionsXY(node * p, int & opx, int & opy)
{
    opy=p->coordY;
    if(p==START or strcmp(p->type, "START")==0)
    {
        opx=p->coordX+START_WIDTH;
    }
    else if(strcmp(p->type, "ASSIGN")==0)
    {
        opx=p->coordX+ASSIGN_WIDTH;
    }
    else if(strcmp(p->type, "STOP")==0)
    {
        opx=p->coordX+STOP_WIDTH;
    }
    else if(strcmp(p->type, "IN")==0)
    {
        opx=p->coordX+IN_BIG_BASE;
    }
    else if(strcmp(p->type, "OUT")==0)
    {
        opx=p->coordX+IN_BIG_BASE;
    }
    else if(strcmp(p->type, "DECISION")==0)
    {
        opx=p->coordX+DECISION_WIDTH;
    }
    opx+=5;
}

void drawRightClickOptions(node * p, int opx, int opy, int nrOfOptions)
{
    if(strcmp(p->type, "START")==0)
    {
        setcolor(RED);
        line(opx, opy, opx + OPTIONS_WIDTH, opy);
        line(opx, opy, opx, opy + nrOfOptions * ONE_OPTION_HEIGHT);
        line(opx + OPTIONS_WIDTH, opy, opx + OPTIONS_WIDTH, opy + nrOfOptions * ONE_OPTION_HEIGHT);
        line(opx, opy + nrOfOptions * ONE_OPTION_HEIGHT, opx + OPTIONS_WIDTH, opy + nrOfOptions * ONE_OPTION_HEIGHT);

        char x[20];
        setfillstyle(SOLID_FILL, THEME[CURRENT_THEME].option_clr);
        floodfill(opx+5, opy+5, RED);

        setcolor(THEME[CURRENT_THEME].option_clr);
        line(opx, opy, opx + OPTIONS_WIDTH, opy);
        line(opx, opy, opx, opy + nrOfOptions * ONE_OPTION_HEIGHT);
        line(opx + OPTIONS_WIDTH, opy, opx + OPTIONS_WIDTH, opy + nrOfOptions * ONE_OPTION_HEIGHT);
        line(opx, opy + nrOfOptions * ONE_OPTION_HEIGHT, opx + OPTIONS_WIDTH, opy + nrOfOptions * ONE_OPTION_HEIGHT);

        line(opx, opy + ONE_OPTION_HEIGHT, opx + OPTIONS_WIDTH, opy + ONE_OPTION_HEIGHT);

        setbkcolor(THEME[CURRENT_THEME].option_clr);
        setcolor(WHITE);
        outtextxy(opx + OPTIONS_WIDTH/2 - textwidth("Make binding")/2, opy + ONE_OPTION_HEIGHT/2 - textheight("Make binding")/2, "Make binding");
        setbkcolor(THEME[CURRENT_THEME].bck_clr);
    }
    else if(strcmp(p->type, "ASSIGN")==0)
    {
        setlinestyle(SOLID_LINE, 0, 1);
        setcolor(RED);
        line(opx, opy, opx + OPTIONS_WIDTH, opy);
        line(opx, opy, opx, opy + nrOfOptions * ONE_OPTION_HEIGHT);
        line(opx + OPTIONS_WIDTH, opy, opx + OPTIONS_WIDTH, opy + nrOfOptions * ONE_OPTION_HEIGHT);
        line(opx, opy + nrOfOptions * ONE_OPTION_HEIGHT, opx + OPTIONS_WIDTH, opy + nrOfOptions * ONE_OPTION_HEIGHT);

        setfillstyle(SOLID_FILL, THEME[CURRENT_THEME].option_clr);
        floodfill(opx+5, opy+5, RED);

        setlinestyle(SOLID_LINE, 0, 1);
        setcolor(THEME[CURRENT_THEME].option_clr);
        line(opx, opy, opx + OPTIONS_WIDTH, opy);
        line(opx, opy, opx, opy + nrOfOptions * ONE_OPTION_HEIGHT);
        line(opx + OPTIONS_WIDTH, opy, opx + OPTIONS_WIDTH, opy + nrOfOptions * ONE_OPTION_HEIGHT);
        line(opx, opy + nrOfOptions * ONE_OPTION_HEIGHT, opx + OPTIONS_WIDTH, opy + nrOfOptions * ONE_OPTION_HEIGHT);

        setlinestyle(SOLID_LINE, 0, 1);
        setcolor(THEME[CURRENT_THEME].bck_clr);
        line(opx, opy + ONE_OPTION_HEIGHT, opx + OPTIONS_WIDTH, opy + ONE_OPTION_HEIGHT);
        line(opx, opy + ONE_OPTION_HEIGHT*2, opx + OPTIONS_WIDTH, opy + ONE_OPTION_HEIGHT*2);

        setbkcolor(THEME[CURRENT_THEME].option_clr);
        setcolor(WHITE);
        outtextxy(opx + OPTIONS_WIDTH/2 - textwidth("Make binding")/2, opy + ONE_OPTION_HEIGHT/2 - textheight("Make binding")/2, "Make binding");
        outtextxy(opx + OPTIONS_WIDTH/2 - textwidth("Expression")/2, opy + ONE_OPTION_HEIGHT + ONE_OPTION_HEIGHT/2 - textheight("Expression")/2, "Expression");
        outtextxy(opx + OPTIONS_WIDTH/2 - textwidth("Delete")/2, opy + ONE_OPTION_HEIGHT*2 + ONE_OPTION_HEIGHT/2 - textheight("Delete")/2, "Delete");
        setbkcolor(THEME[CURRENT_THEME].bck_clr);
    }
    else if(strcmp(p->type, "STOP")==0)
    {
        setlinestyle(SOLID_LINE, 0, 1);
        setcolor(RED);
        line(opx, opy, opx + OPTIONS_WIDTH, opy);
        line(opx, opy, opx, opy + nrOfOptions * ONE_OPTION_HEIGHT);
        line(opx + OPTIONS_WIDTH, opy, opx + OPTIONS_WIDTH, opy + nrOfOptions * ONE_OPTION_HEIGHT);
        line(opx, opy + nrOfOptions * ONE_OPTION_HEIGHT, opx + OPTIONS_WIDTH, opy + nrOfOptions * ONE_OPTION_HEIGHT);

        setfillstyle(SOLID_FILL, THEME[CURRENT_THEME].option_clr);
        floodfill(opx+5, opy+5, RED);

        setlinestyle(SOLID_LINE, 0, 1);
        setcolor(THEME[CURRENT_THEME].option_clr);
        line(opx, opy, opx + OPTIONS_WIDTH, opy);
        line(opx, opy, opx, opy + nrOfOptions * ONE_OPTION_HEIGHT);
        line(opx + OPTIONS_WIDTH, opy, opx + OPTIONS_WIDTH, opy + nrOfOptions * ONE_OPTION_HEIGHT);
        line(opx, opy + nrOfOptions * ONE_OPTION_HEIGHT, opx + OPTIONS_WIDTH, opy + nrOfOptions * ONE_OPTION_HEIGHT);

        setbkcolor(THEME[CURRENT_THEME].option_clr);
        setcolor(WHITE);
        outtextxy(opx + OPTIONS_WIDTH/2 - textwidth("Delete")/2, opy + ONE_OPTION_HEIGHT/2 - textheight("Delete")/2, "Delete");
        setbkcolor(THEME[CURRENT_THEME].bck_clr);
    }
    else if(strcmp(p->type, "IN")==0)
    {
        setlinestyle(SOLID_LINE, 0, 1);
        setcolor(RED);
        line(opx, opy, opx + OPTIONS_WIDTH, opy);
        line(opx, opy, opx, opy + nrOfOptions * ONE_OPTION_HEIGHT);
        line(opx + OPTIONS_WIDTH, opy, opx + OPTIONS_WIDTH, opy + nrOfOptions * ONE_OPTION_HEIGHT);
        line(opx, opy + nrOfOptions * ONE_OPTION_HEIGHT, opx + OPTIONS_WIDTH, opy + nrOfOptions * ONE_OPTION_HEIGHT);

        setfillstyle(SOLID_FILL, THEME[CURRENT_THEME].option_clr);
        floodfill(opx+5, opy+5, RED);

        setcolor(THEME[CURRENT_THEME].option_clr);
        line(opx, opy, opx + OPTIONS_WIDTH, opy);
        line(opx, opy, opx, opy + nrOfOptions * ONE_OPTION_HEIGHT);
        line(opx + OPTIONS_WIDTH, opy, opx + OPTIONS_WIDTH, opy + nrOfOptions * ONE_OPTION_HEIGHT);
        line(opx, opy + nrOfOptions * ONE_OPTION_HEIGHT, opx + OPTIONS_WIDTH, opy + nrOfOptions * ONE_OPTION_HEIGHT);

        setcolor(THEME[CURRENT_THEME].bck_clr);
        line(opx, opy + ONE_OPTION_HEIGHT, opx + OPTIONS_WIDTH, opy + ONE_OPTION_HEIGHT);
        line(opx, opy + ONE_OPTION_HEIGHT*2, opx + OPTIONS_WIDTH, opy + ONE_OPTION_HEIGHT*2);

        setbkcolor(THEME[CURRENT_THEME].option_clr);
        setcolor(WHITE);
        outtextxy(opx + OPTIONS_WIDTH/2 - textwidth("Make binding")/2, opy + ONE_OPTION_HEIGHT/2 - textheight("Make binding")/2, "Make binding");
        outtextxy(opx + OPTIONS_WIDTH/2 - textwidth("Variable name")/2, opy + ONE_OPTION_HEIGHT + ONE_OPTION_HEIGHT/2 - textheight("Variable name")/2, "Variable name");
        outtextxy(opx + OPTIONS_WIDTH/2 - textwidth("Delete")/2, opy + ONE_OPTION_HEIGHT*2 + ONE_OPTION_HEIGHT/2 - textheight("Delete")/2, "Delete");
        setbkcolor(THEME[CURRENT_THEME].bck_clr);
    }
    else if(strcmp(p->type, "OUT")==0)
    {
        setlinestyle(SOLID_LINE, 0, 1);
        setcolor(RED);
        line(opx, opy, opx + OPTIONS_WIDTH, opy);
        line(opx, opy, opx, opy + nrOfOptions * ONE_OPTION_HEIGHT);
        line(opx + OPTIONS_WIDTH, opy, opx + OPTIONS_WIDTH, opy + nrOfOptions * ONE_OPTION_HEIGHT);
        line(opx, opy + nrOfOptions * ONE_OPTION_HEIGHT, opx + OPTIONS_WIDTH, opy + nrOfOptions * ONE_OPTION_HEIGHT);

        setfillstyle(SOLID_FILL, THEME[CURRENT_THEME].option_clr);
        floodfill(opx+5, opy+5, RED);

        setcolor(THEME[CURRENT_THEME].option_clr);
        line(opx, opy, opx + OPTIONS_WIDTH, opy);
        line(opx, opy, opx, opy + nrOfOptions * ONE_OPTION_HEIGHT);
        line(opx + OPTIONS_WIDTH, opy, opx + OPTIONS_WIDTH, opy + nrOfOptions * ONE_OPTION_HEIGHT);
        line(opx, opy + nrOfOptions * ONE_OPTION_HEIGHT, opx + OPTIONS_WIDTH, opy + nrOfOptions * ONE_OPTION_HEIGHT);

        setcolor(THEME[CURRENT_THEME].bck_clr);
        line(opx, opy + ONE_OPTION_HEIGHT, opx + OPTIONS_WIDTH, opy + ONE_OPTION_HEIGHT);
        line(opx, opy + ONE_OPTION_HEIGHT*2, opx + OPTIONS_WIDTH, opy + ONE_OPTION_HEIGHT*2);

        setbkcolor(THEME[CURRENT_THEME].option_clr);
        setcolor(WHITE);
        outtextxy(opx + OPTIONS_WIDTH/2 - textwidth("Make binding")/2, opy + ONE_OPTION_HEIGHT/2 - textheight("Make binding")/2, "Make binding");
        outtextxy(opx + OPTIONS_WIDTH/2 - textwidth("Variable name")/2, opy + ONE_OPTION_HEIGHT + ONE_OPTION_HEIGHT/2 - textheight("Variable name")/2, "Variable name");
        outtextxy(opx + OPTIONS_WIDTH/2 - textwidth("Delete")/2, opy + ONE_OPTION_HEIGHT*2 + ONE_OPTION_HEIGHT/2 - textheight("Delete")/2, "Delete");
        setbkcolor(THEME[CURRENT_THEME].bck_clr);
    }
    else if(strcmp(p->type, "DECISION")==0)
    {
        setlinestyle(SOLID_LINE, 0, 1);
        setcolor(RED);
        line(opx, opy, opx + OPTIONS_WIDTH, opy);
        line(opx, opy, opx, opy + nrOfOptions * ONE_OPTION_HEIGHT);
        line(opx + OPTIONS_WIDTH, opy, opx + OPTIONS_WIDTH, opy + nrOfOptions * ONE_OPTION_HEIGHT);
        line(opx, opy + nrOfOptions * ONE_OPTION_HEIGHT, opx + OPTIONS_WIDTH, opy + nrOfOptions * ONE_OPTION_HEIGHT);

        setfillstyle(SOLID_FILL, THEME[CURRENT_THEME].option_clr);
        floodfill(opx+5, opy+5, RED);

        setcolor(THEME[CURRENT_THEME].option_clr);
        line(opx, opy, opx + OPTIONS_WIDTH, opy);
        line(opx, opy, opx, opy + nrOfOptions * ONE_OPTION_HEIGHT);
        line(opx + OPTIONS_WIDTH, opy, opx + OPTIONS_WIDTH, opy + nrOfOptions * ONE_OPTION_HEIGHT);
        line(opx, opy + nrOfOptions * ONE_OPTION_HEIGHT, opx + OPTIONS_WIDTH, opy + nrOfOptions * ONE_OPTION_HEIGHT);

        setcolor(THEME[CURRENT_THEME].bck_clr);
        line(opx, opy + ONE_OPTION_HEIGHT, opx + OPTIONS_WIDTH, opy + ONE_OPTION_HEIGHT);
        line(opx, opy + ONE_OPTION_HEIGHT*2, opx + OPTIONS_WIDTH, opy + ONE_OPTION_HEIGHT*2);
        line(opx, opy + ONE_OPTION_HEIGHT*3, opx + OPTIONS_WIDTH, opy + ONE_OPTION_HEIGHT*3);

        setbkcolor(THEME[CURRENT_THEME].option_clr);
        setcolor(WHITE);
        outtextxy(opx + OPTIONS_WIDTH/2 - textwidth("Make binding T")/2, opy + ONE_OPTION_HEIGHT/2 - textheight("Make binding T")/2, "Make binding T");
        outtextxy(opx + OPTIONS_WIDTH/2 - textwidth("Make binding F")/2, opy + ONE_OPTION_HEIGHT + ONE_OPTION_HEIGHT/2 - textheight("Make binding F")/2, "Make binding F");
        outtextxy(opx + OPTIONS_WIDTH/2 - textwidth("Expression")/2, opy + ONE_OPTION_HEIGHT*2 + ONE_OPTION_HEIGHT/2 - textheight("Expression")/2, "Expression");
        outtextxy(opx + OPTIONS_WIDTH/2 - textwidth("Delete")/2, opy + ONE_OPTION_HEIGHT*3 + ONE_OPTION_HEIGHT/2 - textheight("Delete")/2, "Delete");
        setbkcolor(THEME[CURRENT_THEME].bck_clr);
    }
}

int getNrOfOptions(node * p)
{
    if(strcmp(p->type, "START")==0)
    {
        return 1;
    }
    else if(strcmp(p->type, "ASSIGN")==0)
    {
        return 3;
    }
    else if(strcmp(p->type, "STOP")==0)
    {
        return 1;
    }
    else if(strcmp(p->type, "IN")==0)
    {
        return 3;
    }
    else if(strcmp(p->type, "OUT")==0)
    {
        return 3;
    }
    else if(strcmp(p->type, "DECISION")==0)
    {
        return 4;
    }
}

void refresh()
{
    cleardevice();
    drawPage();
    drawMenu();
    drawAllBlocks();
    clearmouseclick(WM_LBUTTONDOWN);
}

void closeOptions(int opx, int opy, int nrOfOptions, int & finished)
{
    refresh();
    finished=true;
}

bool insideOptions(int xx, int yy, int opx, int opy, int nrOfOptions)
{
    if(xx < opx or xx > opx + OPTIONS_WIDTH)
        return 0;
    if(yy< opy or yy > opy + ONE_OPTION_HEIGHT * nrOfOptions)
        return 0;
    return 1;
}

void deleteWasPressed(node * & p)
{
    deleteNode(p);
    refresh();
}

void getAssignOrDecisionExpression(node * & p)
{
    int textboxWidth=500, textboxHeight=100;
    setlinestyle(SOLID_LINE, 0, 1);
    setcolor(RED);
    line(WINDOWX/2-textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2-textboxWidth/2, WINDOWY/2+textboxHeight/2);
    line(WINDOWX/2-textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2+textboxWidth/2, WINDOWY/2-textboxHeight/2);
    line(WINDOWX/2+textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2+textboxWidth/2, WINDOWY/2+textboxHeight/2);
    line(WINDOWX/2+textboxWidth/2, WINDOWY/2+textboxHeight/2, WINDOWX/2-textboxWidth/2, WINDOWY/2+textboxHeight/2);

    setfillstyle(SOLID_FILL, THEME[CURRENT_THEME].option_clr);
    floodfill(WINDOWX/2, WINDOWY/2, RED);

    setcolor(THEME[CURRENT_THEME].option_clr);
    line(WINDOWX/2-textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2-textboxWidth/2, WINDOWY/2+textboxHeight/2);
    line(WINDOWX/2-textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2+textboxWidth/2, WINDOWY/2-textboxHeight/2);
    line(WINDOWX/2+textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2+textboxWidth/2, WINDOWY/2+textboxHeight/2);
    line(WINDOWX/2+textboxWidth/2, WINDOWY/2+textboxHeight/2, WINDOWX/2-textboxWidth/2, WINDOWY/2+textboxHeight/2);

    setcolor(THEME[CURRENT_THEME].bck_clr);
    line(WINDOWX/2-textboxWidth/2, WINDOWY/2, WINDOWX/2+textboxWidth/2, WINDOWY/2);

    setbkcolor(THEME[CURRENT_THEME].option_clr);
    setcolor(WHITE);
    outtextxy(WINDOWX/2-textwidth("Insert Expression")/2, WINDOWY/2-textheight("Insert Expression")/2-textboxHeight/4, "Insert Expression");
    if (strcmp(p->expression, "no expression"))
        outtextxy(WINDOWX/2-textwidth(p->expression)/2, WINDOWY/2-textheight(p->expression)/2+textboxHeight/4, p->expression);
    setbkcolor(THEME[CURRENT_THEME].bck_clr);

    bool finished=0;
    char cc[EXPRESSION_LENGTH] = "";
    if (strcmp(p->expression, "no expression"))
        strcpy(cc, p->expression);
    int i=strlen(cc);
    do
    {
        char c=getch();
        if(i==EXPRESSION_LENGTH-2)
            c=getch();
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

            setcolor(THEME[CURRENT_THEME].option_clr);
            line(WINDOWX/2-textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2-textboxWidth/2, WINDOWY/2+textboxHeight/2);
            line(WINDOWX/2-textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2+textboxWidth/2, WINDOWY/2-textboxHeight/2);
            line(WINDOWX/2+textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2+textboxWidth/2, WINDOWY/2+textboxHeight/2);
            line(WINDOWX/2+textboxWidth/2, WINDOWY/2+textboxHeight/2, WINDOWX/2-textboxWidth/2, WINDOWY/2+textboxHeight/2);

            setcolor(THEME[CURRENT_THEME].bck_clr);
            line(WINDOWX/2-textboxWidth/2, WINDOWY/2, WINDOWX/2+textboxWidth/2, WINDOWY/2);

            setbkcolor(THEME[CURRENT_THEME].option_clr);
            setcolor(WHITE);
            outtextxy(WINDOWX/2-textwidth("Insert Expression")/2, WINDOWY/2-textheight("Insert Expression")/2-textboxHeight/4, "Insert Expression");
            outtextxy(WINDOWX/2-textwidth(cc)/2, WINDOWY/2-textheight(cc)/2+textboxHeight/4, cc);
            setbkcolor(THEME[CURRENT_THEME].bck_clr);
        }
    }
    while(finished==0 and i<EXPRESSION_LENGTH-2);

    strcpy(p->expression, cc);
    refresh();
}

void getVariableName(node * & p)
{
    int textboxWidth=500, textboxHeight=100;
    setlinestyle(SOLID_LINE, 0, 1);
    setcolor(RED);
    line(WINDOWX/2-textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2-textboxWidth/2, WINDOWY/2+textboxHeight/2);
    line(WINDOWX/2-textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2+textboxWidth/2, WINDOWY/2-textboxHeight/2);
    line(WINDOWX/2+textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2+textboxWidth/2, WINDOWY/2+textboxHeight/2);
    line(WINDOWX/2+textboxWidth/2, WINDOWY/2+textboxHeight/2, WINDOWX/2-textboxWidth/2, WINDOWY/2+textboxHeight/2);

    setfillstyle(SOLID_FILL, THEME[CURRENT_THEME].option_clr);
    floodfill(WINDOWX/2, WINDOWY/2, RED);

    setcolor(THEME[CURRENT_THEME].option_clr);
    line(WINDOWX/2-textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2-textboxWidth/2, WINDOWY/2+textboxHeight/2);
    line(WINDOWX/2-textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2+textboxWidth/2, WINDOWY/2-textboxHeight/2);
    line(WINDOWX/2+textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2+textboxWidth/2, WINDOWY/2+textboxHeight/2);
    line(WINDOWX/2+textboxWidth/2, WINDOWY/2+textboxHeight/2, WINDOWX/2-textboxWidth/2, WINDOWY/2+textboxHeight/2);

    setcolor(THEME[CURRENT_THEME].bck_clr);
    line(WINDOWX/2-textboxWidth/2, WINDOWY/2, WINDOWX/2+textboxWidth/2, WINDOWY/2);

    setbkcolor(THEME[CURRENT_THEME].option_clr);
    setcolor(WHITE);
    outtextxy(WINDOWX/2-textwidth("Insert variable name")/2, WINDOWY/2-textheight("Insert variable name")/2-textboxHeight/4, "Insert variable name");
    if (strcmp(p->expression, "no expression"))
        outtextxy(WINDOWX/2-textwidth(p->expression)/2, WINDOWY/2-textheight(p->expression)/2+textboxHeight/4, p->expression);
    setbkcolor(THEME[CURRENT_THEME].bck_clr);

    bool finished=0;
    char cc[EXPRESSION_LENGTH] = "";
    if (strcmp(p->expression, "no expression"))
        strcpy(cc, p->expression);
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

            setcolor(THEME[CURRENT_THEME].option_clr);
            line(WINDOWX/2-textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2-textboxWidth/2, WINDOWY/2+textboxHeight/2);
            line(WINDOWX/2-textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2+textboxWidth/2, WINDOWY/2-textboxHeight/2);
            line(WINDOWX/2+textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2+textboxWidth/2, WINDOWY/2+textboxHeight/2);
            line(WINDOWX/2+textboxWidth/2, WINDOWY/2+textboxHeight/2, WINDOWX/2-textboxWidth/2, WINDOWY/2+textboxHeight/2);

            setcolor(THEME[CURRENT_THEME].bck_clr);
            line(WINDOWX/2-textboxWidth/2, WINDOWY/2, WINDOWX/2+textboxWidth/2, WINDOWY/2);

            setbkcolor(THEME[CURRENT_THEME].option_clr);
            setcolor(WHITE);
            outtextxy(WINDOWX/2-textwidth("Insert variable name")/2, WINDOWY/2-textheight("Insert variable name")/2-textboxHeight/4, "Insert variable name");
            outtextxy(WINDOWX/2-textwidth(cc)/2, WINDOWY/2-textheight(cc)/2+textboxHeight/4, cc);
            setbkcolor(THEME[CURRENT_THEME].bck_clr);
        }
    }
    while(finished==0 and i<EXPRESSION_LENGTH-2);

    strcpy(p->expression, cc);
    refresh();
}

void makeBinding(int xx, int yy, int opx, int opy, node * & p, int & finished, bool fromElse)
{
    int newBinding=0;
    int secondNodeSelected=0;
    node * q = new node;
    node * otherNode = new node;
    q=NULL;
    if(fromElse==0)
    {
        setlinestyle(SOLID_LINE, 0, 1);
        setcolor(RED);
        line(opx, opy, opx + OPTIONS_WIDTH, opy);
        line(opx, opy, opx, opy + ONE_OPTION_HEIGHT);
        line(opx + OPTIONS_WIDTH, opy, opx + OPTIONS_WIDTH, opy + ONE_OPTION_HEIGHT);
        line(opx, opy + ONE_OPTION_HEIGHT, opx + OPTIONS_WIDTH, opy + ONE_OPTION_HEIGHT);

        setfillstyle(SOLID_FILL, THEME[CURRENT_THEME].option_clr);
        floodfill(opx+5, opy+5, RED);

        setcolor(THEME[CURRENT_THEME].option_clr);
        line(opx, opy, opx + OPTIONS_WIDTH, opy);
        line(opx, opy, opx, opy + ONE_OPTION_HEIGHT);
        line(opx + OPTIONS_WIDTH, opy, opx + OPTIONS_WIDTH, opy + ONE_OPTION_HEIGHT);
        line(opx, opy + ONE_OPTION_HEIGHT, opx + OPTIONS_WIDTH, opy + ONE_OPTION_HEIGHT);

        if(strcmp(p->type, "START"))
        {
            setcolor(THEME[CURRENT_THEME].bck_clr);
            line(opx, opy + ONE_OPTION_HEIGHT, opx + OPTIONS_WIDTH, opy + ONE_OPTION_HEIGHT);
        }


        setbkcolor(THEME[CURRENT_THEME].option_clr);
        setcolor(WHITE);
        outtextxy(opx + OPTIONS_WIDTH/2 - textwidth("Select second node")/2, opy + ONE_OPTION_HEIGHT/2 - textheight("Select second node")/2, "Select second node");
        setbkcolor(THEME[CURRENT_THEME].bck_clr);
    }
    else
    {
        setlinestyle(SOLID_LINE, 0, 1);
        setcolor(RED);
        line(opx, opy+ONE_OPTION_HEIGHT, opx + OPTIONS_WIDTH, opy+ONE_OPTION_HEIGHT);
        line(opx, opy+ONE_OPTION_HEIGHT, opx, opy + ONE_OPTION_HEIGHT*2);
        line(opx + OPTIONS_WIDTH, opy+ONE_OPTION_HEIGHT, opx + OPTIONS_WIDTH, opy + ONE_OPTION_HEIGHT*2);
        line(opx, opy + ONE_OPTION_HEIGHT*2, opx + OPTIONS_WIDTH, opy + ONE_OPTION_HEIGHT*2);

        setfillstyle(SOLID_FILL, THEME[CURRENT_THEME].option_clr);
        floodfill(opx+5, opy+ONE_OPTION_HEIGHT+5, RED);

        setcolor(THEME[CURRENT_THEME].option_clr);
        line(opx, opy+ONE_OPTION_HEIGHT, opx + OPTIONS_WIDTH, opy+ONE_OPTION_HEIGHT);
        line(opx, opy+ONE_OPTION_HEIGHT, opx, opy + ONE_OPTION_HEIGHT*2);
        line(opx + OPTIONS_WIDTH, opy+ONE_OPTION_HEIGHT, opx + OPTIONS_WIDTH, opy + ONE_OPTION_HEIGHT*2);
        line(opx, opy + ONE_OPTION_HEIGHT*2, opx + OPTIONS_WIDTH, opy + ONE_OPTION_HEIGHT*2);

        setcolor(THEME[CURRENT_THEME].bck_clr);
        line(opx, opy + ONE_OPTION_HEIGHT*2, opx + OPTIONS_WIDTH, opy + ONE_OPTION_HEIGHT*2);
        line(opx, opy + ONE_OPTION_HEIGHT, opx + OPTIONS_WIDTH, opy + ONE_OPTION_HEIGHT);

        setbkcolor(THEME[CURRENT_THEME].option_clr);
        setcolor(WHITE);
        outtextxy(opx + OPTIONS_WIDTH/2 - textwidth("Select second node")/2, opy + ONE_OPTION_HEIGHT+ONE_OPTION_HEIGHT/2 - textheight("Select second node")/2, "Select second node");
        setbkcolor(THEME[CURRENT_THEME].bck_clr);
    }

    while(!secondNodeSelected)
    {
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN, xx, yy);
            clearmouseclick(WM_LBUTTONDOWN);
            if(!(xx<=opx+OPTIONS_WIDTH and xx>=opx and yy>=opy and yy<=opy+ONE_OPTION_HEIGHT))
            {
                selectCorrectNode(xx, yy, q, otherNode);
                if(q and q!=p and q!=START)
                {
//                    if(strcmp(q->type, "IN")==0)
//                        newBinding=1;
                    if(strcmp(p->type, "IN")==0)
                        bool fafa=0;
                    makeBindingAB(p, q, fromElse);
                    secondNodeSelected=1;
                    finished=true;
                    newBinding=1;
                }
            }
            setlinestyle(SOLID_LINE, 0, 1);
            setcolor(RED);
            line(opx, opy, opx + OPTIONS_WIDTH, opy);
            line(opx, opy, opx, opy + ONE_OPTION_HEIGHT);
            line(opx + OPTIONS_WIDTH, opy, opx + OPTIONS_WIDTH, opy + ONE_OPTION_HEIGHT);
            line(opx, opy + ONE_OPTION_HEIGHT, opx + OPTIONS_WIDTH, opy + ONE_OPTION_HEIGHT);

            setfillstyle(SOLID_FILL, THEME[CURRENT_THEME].option_clr);
            floodfill(opx+5, opy+5, RED);

            setcolor(THEME[CURRENT_THEME].option_clr);
            line(opx, opy, opx + OPTIONS_WIDTH, opy);
            line(opx, opy, opx, opy + ONE_OPTION_HEIGHT);
            line(opx + OPTIONS_WIDTH, opy, opx + OPTIONS_WIDTH, opy + ONE_OPTION_HEIGHT);
            line(opx, opy + ONE_OPTION_HEIGHT, opx + OPTIONS_WIDTH, opy + ONE_OPTION_HEIGHT);

            setcolor(THEME[CURRENT_THEME].bck_clr);
            line(opx, opy + ONE_OPTION_HEIGHT, opx + OPTIONS_WIDTH, opy + ONE_OPTION_HEIGHT);

            setbkcolor(THEME[CURRENT_THEME].option_clr);
            setcolor(WHITE);
            outtextxy(opx + OPTIONS_WIDTH/2 - textwidth("Make binding")/2, opy + ONE_OPTION_HEIGHT/2 - textheight("Make binding")/2, "Make binding");
            secondNodeSelected=1;
            finished=true;
            setbkcolor(THEME[CURRENT_THEME].bck_clr);
        }
    }
    if(strcmp(p->type, "IN")==0)
        bool fafa=0;
}

void triggerOption(int xx, int yy, int opx, int opy, int nrOfOptions, node * & p, int &finished)
{
    Beep(400, 100);
    if(strcmp(p->type, "START")==0)
    {
        makeBinding(xx, yy, opx, opy, p, finished, 0);
        refresh();
        restoreOutput();

    }
    else if(strcmp(p->type, "ASSIGN")==0)
    {
        if(yy<=opy+ONE_OPTION_HEIGHT)
        {
            makeBinding(xx, yy, opx, opy, p, finished, 0);
            restoreOutput();
        }
        else
        {
            if(yy<=opy+ONE_OPTION_HEIGHT*2)
            {
                getAssignOrDecisionExpression(p);
                restoreOutput();
            }
            else
            {
                deleteWasPressed(p);
                finished=true;
                restoreOutput();
            }
        }
        refresh();
    }
    else if(strcmp(p->type, "STOP")==0)
    {
        deleteWasPressed(p);
        finished=true;
        restoreOutput();
        refresh();
    }
    else if(strcmp(p->type, "IN")==0)
    {
        if(yy<opy+ONE_OPTION_HEIGHT)
        {
            makeBinding(xx, yy, opx, opy, p, finished, 0);
            restoreOutput();
        }
        else if(yy>=opy+ONE_OPTION_HEIGHT and yy<opy+2*ONE_OPTION_HEIGHT)
        {
            getVariableName(p);
            restoreOutput();
            finished=true;
        }
        else
        {
            deleteWasPressed(p);
            restoreOutput();
            finished=true;
        }
        refresh();
    }
    else if(strcmp(p->type, "OUT")==0)
    {
        if(yy<opy+ONE_OPTION_HEIGHT)
        {
            makeBinding(xx, yy, opx, opy, p, finished, 0);
            restoreOutput();
        }
        else if(yy>=opy+ONE_OPTION_HEIGHT and yy<opy+2*ONE_OPTION_HEIGHT)
        {
            getVariableName(p);
            finished=true;
            restoreOutput();
        }
        else
        {
            deleteWasPressed(p);
            finished=true;
            restoreOutput();
        }
        refresh();
    }
    else if(strcmp(p->type, "DECISION")==0)
    {
        if(yy<=opy+ONE_OPTION_HEIGHT)
        {
            makeBinding(xx, yy, opx, opy, p, finished, 0);
            restoreOutput();
        }
        else
        {
            if(yy<=opy+ONE_OPTION_HEIGHT*2)
            {
                makeBinding(xx, yy, opx, opy, p, finished, 1);
                restoreOutput();
            }
            else
            {
                if(yy<=opy+ONE_OPTION_HEIGHT*3)
                {
                    getAssignOrDecisionExpression(p);
                    restoreOutput();
                }
                else
                {
                    deleteWasPressed(p);
                    finished=true;
                    restoreOutput();
                }
            }
        }
        refresh();
    }
}

#endif // BLOCKOPTIONS_H_INCLUDED
