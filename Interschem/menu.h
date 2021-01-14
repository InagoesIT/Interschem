#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "list.h"
#include "blocksMoveDel.h"
#include "openSaveScheme.h"

#define SPACE_BETWEEN 55
#define START_X 70
#define STOP_X 70
#define IN_X 80
#define OUT_X 80
#define ASSIGN_X 50
#define DECISION_X 50

#define MENUY 70
#define WINDOWX GetSystemMetrics(SM_CXSCREEN)
#define WINDOWY GetSystemMetrics(SM_CYSCREEN)

void refresh();
void moveBlock(int x, int y, node *p, bool isNew);
void isSchemeCorrect(node * k, bool & isCorrect);
void analyzeScheme(node * k);
void generateCode(bool &isGenCode);

const int START_Y = (WINDOWY - MENUY - SPACE_BETWEEN * 5 - 290) / 2 + MENUY - 15;
const int STOP_Y = START_Y + SPACE_BETWEEN + START_HEIGHT;
const int IN_Y = STOP_Y + SPACE_BETWEEN + STOP_HEIGHT;
const int OUT_Y = IN_Y + SPACE_BETWEEN + IN_HEIGHT;
const int ASSIGN_Y = OUT_Y + SPACE_BETWEEN + IN_HEIGHT;
const int DECISION_Y = ASSIGN_Y + SPACE_BETWEEN + ASSIGN_HEIGHT;

const int tileX = WINDOWX / 3;
const int smallTileX = 170;// textwidth("Background Color") + 50
const int smallTileY = MENUY * 0.8;
const int firstSchemeX = (tileX - smallTileX) / 2;
const int lastSchemeX = smallTileX + firstSchemeX;
const int lastSchemeY = MENUY + smallTileY * 4;
const int firstCustomizeX = tileX + (tileX - smallTileX) / 2;
const int lastCustomizeX = smallTileX + firstCustomizeX;
const int lastCustomizeY = MENUY + smallTileY * 5;
const int spaceGenCodeY = 10;
const int sizeGenCodeY = MENUY * 0.6;
const int sizeGenCodeX = 146; // textwidth("Generate Code")-96 + 50
const int spaceGenCodeX = (OUTPUT_SIZE_X  - sizeGenCodeX) / 2;
const int firstGenCodeX = WINDOWX - OUTPUT_SIZE_X + spaceGenCodeX;
const int lastGenCodeX = WINDOWX - spaceGenCodeX;
const int textGenCodeX = firstGenCodeX + 25; // 50/2
const int textGenCodeY = (sizeGenCodeY - 16)/2 + MENUY + spaceGenCodeY; // 16-- textheight
const int firstOthersX = tileX*2 + (tileX - smallTileX) / 2;
const int lastOthersX = smallTileX + firstOthersX;
const int lastOthersY = MENUY + smallTileY * 3;

bool IS_INSIDE_SCHEME;
bool IS_INSIDE_CUSTOMIZE;
bool IS_INSIDE_OTHERS;

bool m[630][950];

char *selectedNewBlock(int x, int y)
{
    node *newBlock = new node;
    newBlock->coordX = START_X;
    newBlock->coordY = START_Y;
    strcpy(newBlock->type, "START");
    if (isInsideNode(x, y, newBlock))
        return newBlock->type;

    newBlock->coordX = STOP_X;
    newBlock->coordY = STOP_Y;
    strcpy(newBlock->type, "STOP");
    if (isInsideNode(x, y, newBlock))
        return newBlock->type;

    newBlock->coordX = IN_X;
    newBlock->coordY = IN_Y;
    strcpy(newBlock->type, "IN");
    if (isInsideNode(x, y, newBlock))
        return newBlock->type;

    newBlock->coordX = OUT_X;
    newBlock->coordY = OUT_Y;
    strcpy(newBlock->type, "OUT");
    if (isInsideNode(x, y, newBlock))
        return newBlock->type;

    newBlock->coordX = ASSIGN_X;
    newBlock->coordY = ASSIGN_Y;
    strcpy(newBlock->type, "ASSIGN");
    if (isInsideNode(x, y, newBlock))
        return newBlock->type;

    newBlock->coordX = DECISION_X;
    newBlock->coordY = DECISION_Y;
    strcpy(newBlock->type, "DECISION");
    if (isInsideNode(x, y, newBlock))
        return newBlock->type;

    return "NO";
}

void dragNewBlock(int x, int y, char *blockType)
{
    node * v = new node;
    v=createNode(blockType, !strcmp(blockType, "DECISION"), x, y, 0);
    int difX=x-v->coordX;
    int difY=y-v->coordY;
    moveBlock(x, y, v, true, difX, difY);
}

void drawGenCodeButton()
{
    setcolor(DARKGRAY);
    line(firstGenCodeX, MENUY + spaceGenCodeY + sizeGenCodeY, firstGenCodeX, MENUY + spaceGenCodeY); // |
    line(firstGenCodeX, MENUY + spaceGenCodeY, lastGenCodeX, MENUY + spaceGenCodeY); // --
    line(lastGenCodeX, MENUY + spaceGenCodeY, lastGenCodeX, MENUY + spaceGenCodeY + sizeGenCodeY); // |
    line(lastGenCodeX, MENUY + spaceGenCodeY + sizeGenCodeY, firstGenCodeX, MENUY + spaceGenCodeY + sizeGenCodeY); // --

    setfillstyle(SOLID_FILL, THEME[CURRENT_THEME].option_clr);
    floodfill(firstGenCodeX + sizeGenCodeX / 2, MENUY + spaceGenCodeY + sizeGenCodeY / 2, DARKGRAY);

    setcolor(WHITE);
    setbkcolor(THEME[CURRENT_THEME].option_clr);
    outtextxy(textGenCodeX, textGenCodeY, "Generate Code");
    setbkcolor(THEME[CURRENT_THEME].bck_clr);
}

void drawPage()
{
    setbkcolor(THEME[CURRENT_THEME].bck_clr);
    //drag and drop blocks
    setlinestyle(0, 0, 3);
    createStart(START_X, START_Y, true);
    createStop(STOP_X, STOP_Y, true);
    createIn(IN_X, IN_Y, true, true, "no expression");
    createOut(OUT_X, OUT_Y, true, true, "no expression");
    createAssign(ASSIGN_X, ASSIGN_Y, true, true, "no expression");
    createDecision(DECISION_X, DECISION_Y, true, true, "no expression");

    setcolor(THEME[CURRENT_THEME].button_clr);
    line(0, MENUY, WINDOWX, MENUY); // menu
    line(DRAG_SIZE_X, MENUY, DRAG_SIZE_X, WINDOWY); //drag
    line(WINDOWX - OUTPUT_SIZE_X, MENUY, WINDOWX - OUTPUT_SIZE_X, WINDOWY); //output
    drawGenCodeButton();
}

void hoverEffect(int x, int y, char a[20], bool hoverOn)
{
    int color;
    if(hoverOn==1)
        color=THEME[CURRENT_THEME].option_clr;
    else
        color=THEME[CURRENT_THEME].button_clr;

    setlinestyle(SOLID_LINE, 0, 3);
    setcolor(RED);
    line(x, y, x+tileX, y);
    line(x, y+MENUY, x+tileX, y+MENUY);
    line(x, y, x, y+MENUY);
    line(x+tileX, y, x+tileX, y+MENUY);

    setfillstyle(SOLID_FILL, color);
    setcolor(color);
    floodfill(x+5, y+5, RED);

    setcolor(color);
    line(x, y, x+tileX, y);
    line(x, y+MENUY, x+tileX, y+MENUY);

    setcolor(THEME[CURRENT_THEME].bck_clr);
    line(x, y, x, y+MENUY);
    line(x+tileX, y, x+tileX, y+MENUY);

    setcolor(WHITE);
    setbkcolor(color);
    outtextxy(x+tileX/2-textwidth(a)/2, y+MENUY/2-textheight(a)/2, a);
    setbkcolor(THEME[CURRENT_THEME].bck_clr);

}

void drawMenu()
{
    hoverEffect(0, 0, "SCHEME", IS_INSIDE_SCHEME); //IS_SCHEME_INSIDE acts like an on/off
    hoverEffect(tileX, 0, "CUSTOMIZE", IS_INSIDE_CUSTOMIZE);
    hoverEffect(tileX*2, 0, "OTHERS", IS_INSIDE_OTHERS);
}

void drawSubmenuScheme(bool isColored)
{
    setlinestyle(0, 0, 1);
    setcolor(DARKGRAY);

    line(firstSchemeX, MENUY, firstSchemeX, lastSchemeY); // |
    line(firstSchemeX, lastSchemeY, lastSchemeX, lastSchemeY); // -
    line(lastSchemeX, MENUY, lastSchemeX, lastSchemeY); // |
    line(firstSchemeX, MENUY, lastSchemeX, MENUY); // -

    if (isColored)
    {
        setfillstyle(SOLID_FILL, THEME[CURRENT_THEME].option_clr);
        setcolor(THEME[CURRENT_THEME].option_clr);
    }
    else
    {
        setfillstyle(SOLID_FILL, THEME[CURRENT_THEME].bck_clr);
        setcolor(THEME[CURRENT_THEME].bck_clr);
    }

    floodfill(firstSchemeX + smallTileX / 2, lastSchemeY / 2, DARKGRAY);

    line(firstSchemeX, MENUY, firstSchemeX, lastSchemeY); // |
    line(firstSchemeX, lastSchemeY, lastSchemeX, lastSchemeY); // -
    line(lastSchemeX, MENUY, lastSchemeX, lastSchemeY); // |
    line(firstSchemeX, MENUY, lastSchemeX, MENUY); // -

    if (isColored)
    {
        setcolor(THEME[CURRENT_THEME].bck_clr);
        line(firstSchemeX, MENUY + smallTileY, lastSchemeX, MENUY + smallTileY);
        line(firstSchemeX, MENUY + smallTileY * 2, lastSchemeX, MENUY + smallTileY * 2);
        line(firstSchemeX, MENUY + smallTileY * 3, lastSchemeX, MENUY + smallTileY * 3);

        setbkcolor(THEME[CURRENT_THEME].option_clr);
        setcolor(WHITE);
        outtextxy(firstSchemeX + (smallTileX - textwidth("Save")) / 2, MENUY + (smallTileY - textheight("Save")) / 2, "Save");
        outtextxy(firstSchemeX + (smallTileX - textwidth("Open")) / 2, MENUY + smallTileY + (smallTileY - textheight("Open")) / 2, "Open");
        outtextxy(firstSchemeX + (smallTileX - textwidth("Clear")) / 2, MENUY + smallTileY * 2 + (smallTileY - textheight("Clear")) / 2, "Clear");
        outtextxy(firstSchemeX + (smallTileX - textwidth("Run")) / 2, MENUY + smallTileY * 3 + (smallTileY - textheight("Run")) / 2, "Run");
        setbkcolor(THEME[CURRENT_THEME].bck_clr);
    }
}

void drawSubmenuCustomize(bool isColored)
{
    setlinestyle(0, 0, 1);
    setcolor(DARKGRAY);

    line(firstCustomizeX, MENUY, firstCustomizeX, lastCustomizeY); // |
    line(firstCustomizeX, lastCustomizeY, lastCustomizeX, lastCustomizeY); // -
    line(lastCustomizeX, MENUY, lastCustomizeX, lastCustomizeY); // |
    line(firstCustomizeX, MENUY, lastCustomizeX, MENUY); // -

    if (isColored)
    {
        setfillstyle(SOLID_FILL, THEME[CURRENT_THEME].option_clr);
        setcolor(THEME[CURRENT_THEME].option_clr);
    }
    else
    {
        setfillstyle(SOLID_FILL, THEME[CURRENT_THEME].bck_clr);
        setcolor(THEME[CURRENT_THEME].bck_clr);
    }

    floodfill(firstCustomizeX + smallTileX / 2, lastCustomizeY / 2, DARKGRAY);

    line(firstCustomizeX, MENUY, firstCustomizeX, lastCustomizeY); // |
    line(firstCustomizeX, lastCustomizeY, lastCustomizeX, lastCustomizeY); // -
    line(lastCustomizeX, MENUY, lastCustomizeX, lastCustomizeY); // |
    line(firstCustomizeX, MENUY, lastCustomizeX, MENUY); // -

    setcolor(THEME[CURRENT_THEME].bck_clr);
    line(firstCustomizeX, MENUY + smallTileY, lastCustomizeX, MENUY + smallTileY);
    line(firstCustomizeX, MENUY + smallTileY*2, lastCustomizeX, MENUY + smallTileY*2);
    line(firstCustomizeX, MENUY + smallTileY*3, lastCustomizeX, MENUY + smallTileY*3);
    line(firstCustomizeX, MENUY + smallTileY*4, lastCustomizeX, MENUY + smallTileY*4);

    if (isColored)
    {
        setcolor(THEME[CURRENT_THEME].bck_clr);
        line(firstCustomizeX, MENUY + smallTileY, lastCustomizeX, MENUY + smallTileY);

        setbkcolor(THEME[CURRENT_THEME].option_clr);
        setcolor(WHITE);
        outtextxy(firstCustomizeX + (smallTileX - textwidth("Basic")) / 2, MENUY + (smallTileY - textheight("Basic")) / 2, "Basic");
        outtextxy(firstCustomizeX + (smallTileX - textwidth("Dark theme")) / 2, MENUY + smallTileY + (smallTileY - textheight("Dark theme")) / 2, "Dark theme");
        outtextxy(firstCustomizeX + (smallTileX - textwidth("Playful")) / 2, MENUY + smallTileY*2 + (smallTileY - textheight("Playful")) / 2, "Playful");
        outtextxy(firstCustomizeX + (smallTileX - textwidth("Black and white")) / 2, MENUY + smallTileY*3 + (smallTileY - textheight("Black and white")) / 2, "Black and white");
        outtextxy(firstCustomizeX + (smallTileX - textwidth("Monochrome cyan")) / 2, MENUY + smallTileY*4 + (smallTileY - textheight("Monochrome cyan")) / 2, "Monochrome cyan");
        setbkcolor(THEME[CURRENT_THEME].bck_clr);
    }
}

void popUpMessage(char a[200])
{
    int textboxWidth=350, textboxHeight=50;
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

    setbkcolor(THEME[CURRENT_THEME].option_clr);
    setcolor(WHITE);
    outtextxy(WINDOWX/2-textwidth(a)/2, WINDOWY/2-textheight(a)/2, a);
    setbkcolor(THEME[CURRENT_THEME].bck_clr);
}

void popUpCantUseRestore()
{
    popUpMessage("You can't use this option now!");
}

void waitForClickToRefresh()
{
    bool done=0;
    while(!done)
    {
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            done=1;
        }
    }
    refresh();
}

void restoreDeletedBlock()
{
    if(LAST_DELELED_NODE.canBeUsed==1)
    {
        for(int i=0; i<FREE_NODES_SIZE; ++i)
        {
            if(FREE_NODES->n[i]==NULL)
            {
                node * q = new node;
                FREE_NODES->n[i]=q;
                FREE_NODES->n[i]->coordX=LAST_DELELED_NODE.LAST_DELETED->coordX;
                FREE_NODES->n[i]->coordY=LAST_DELELED_NODE.LAST_DELETED->coordY;
                strcpy(FREE_NODES->n[i]->expression, LAST_DELELED_NODE.LAST_DELETED->expression);
                FREE_NODES->n[i]->isDecision=LAST_DELELED_NODE.LAST_DELETED->isDecision;
                FREE_NODES->n[i]->location=LAST_DELELED_NODE.LAST_DELETED->location;
                FREE_NODES->n[i]->next=LAST_DELELED_NODE.LAST_DELETED->next;
                FREE_NODES->n[i]->nextElse=LAST_DELELED_NODE.LAST_DELETED->nextElse;
                FREE_NODES->n[i]->timePriority=LAST_DELELED_NODE.LAST_DELETED->timePriority;
                strcpy(FREE_NODES->n[i]->type, LAST_DELELED_NODE.LAST_DELETED->type);
                FREE_NODES->n[i]->viz=LAST_DELELED_NODE.LAST_DELETED->viz;
                FREE_NODES->n[i]->wasCreated=LAST_DELELED_NODE.LAST_DELETED->wasCreated;
                i=FREE_NODES_SIZE+1;
                LAST_DELELED_NODE.canBeUsed=0;
            }
        }
        refresh();
    }
    else
        popUpCantUseRestore();
}

void popUpAgreeEmptyScheme(bool & continueEmptyScheme)
{
    int textboxWidth=250, textboxHeight=100;
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
    line(WINDOWX/2, WINDOWY/2, WINDOWX/2, WINDOWY/2+textboxHeight/2);

    setbkcolor(THEME[CURRENT_THEME].option_clr);
    setcolor(WHITE);
    outtextxy(WINDOWX/2-textwidth("Unsaved scheme will be lost!")/2, WINDOWY/2-textheight("Unsaved scheme will be lost!")/2-textboxHeight/4, "Unsaved scheme will be lost!");
    outtextxy(WINDOWX/2-textboxWidth/4-textwidth("Continue")/2, WINDOWY/2-textheight("Continue")/2+textboxHeight/4, "Continue");
    outtextxy(WINDOWX/2+textboxWidth/4-textwidth("Back")/2, WINDOWY/2-textheight("Back")/2+textboxHeight/4, "Back");
    setbkcolor(THEME[CURRENT_THEME].bck_clr);

    bool done=0;
    while(!done)
    {
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            int xx, yy;
            getmouseclick(WM_LBUTTONDOWN, xx, yy);
            clearmouseclick(WM_LBUTTONDOWN);
            if(xx<WINDOWX/2 and xx>WINDOWX/2-textboxWidth/2 and yy>WINDOWY/2 and yy<WINDOWY/2+textboxHeight/2)
                done=1;
            else
            {
                if(!(xx<WINDOWX/2+textboxWidth/2 and xx>WINDOWX/2-textboxWidth/2 and yy<WINDOWY/2 and yy>WINDOWY/2-textboxHeight/2))
                {
                    done=1;
                    continueEmptyScheme=0;
                }
            }
        }
    }
}

void emptyScheme()
{
    bool continueEmptyScheme=1;
    popUpAgreeEmptyScheme(continueEmptyScheme);
    if(continueEmptyScheme==1)
    {
        reinitializeAllViz();
        reinitializeAllNodesTime();
        createArrayWithAllBlocks();
        if(ALL_NODES_TIME.arraySize)
        {
            for (int i = 0; i < ALL_NODES_TIME.arraySize; ++i)
            {
                reinitializeAllViz();
                node * k = new node;
                k=findNodeByTime(ALL_NODES_TIME.n[i]);
                if(k!=START)
                    deleteNode(k);
            }
        }
        START->wasCreated=0;
    }
}

void popUpAnalyzedWithSucces()
{
    popUpMessage("Your scheme was analysed with succes!");
    waitForClickToRefresh();
}

void popUpIncorrectScheme()
{
    popUpMessage("The scheme is incorrect!");
    waitForClickToRefresh();
}

void run()
{
    bool isCorrect=1;
    restoreVariables();
    isSchemeCorrect(START, isCorrect);
    restoreVariables();
    if(!isCorrect)
    {
        popUpIncorrectScheme();
    }
    if(isCorrect)
    {
        restoreVariables();
        analyzeScheme(START);
        restoreVariables();
    }
}

void drawSubmenuOthers(bool isColored)
{
    setlinestyle(0, 0, 1);
    setcolor(LIGHTGRAY);

    line(firstOthersX, MENUY, firstOthersX, lastOthersY); // |
    line(firstOthersX, lastOthersY, lastOthersX, lastOthersY); // -
    line(lastOthersX, MENUY, lastOthersX, lastOthersY); // |
    line(firstOthersX, MENUY, lastOthersX, MENUY); // -

    if (isColored)
        setfillstyle(SOLID_FILL, THEME[CURRENT_THEME].option_clr);

    else
        setfillstyle(LTSLASH_FILL, BLACK);

    setcolor(THEME[CURRENT_THEME].option_clr);
    floodfill(firstOthersX + smallTileX / 2, lastOthersY / 2, LIGHTGRAY);

    line(firstOthersX, MENUY, firstOthersX, lastOthersY); // |
    line(firstOthersX, lastOthersY, lastOthersX, lastOthersY); // -
    line(lastOthersX, MENUY, lastOthersX, lastOthersY); // |
    line(firstOthersX, MENUY, lastOthersX, MENUY); // -

    setcolor(THEME[CURRENT_THEME].bck_clr);
    line(firstOthersX, MENUY + smallTileY, lastOthersX, MENUY + smallTileY);
    line(firstOthersX, MENUY + smallTileY*2, lastOthersX, MENUY + smallTileY*2);

    if (isColored)
    {
        setbkcolor(THEME[CURRENT_THEME].option_clr);
        setcolor(WHITE);
        outtextxy(firstOthersX + (smallTileX - textwidth("Last deleted block")) / 2, MENUY + (smallTileY - textheight("Last deleted block")) / 2, "Last deleted block");
        outtextxy(firstOthersX + (smallTileX - textwidth("Help")) / 2, MENUY + smallTileY + (smallTileY - textheight("Help")) / 2, "Help");
        outtextxy(firstOthersX + (smallTileX - textwidth("About us")) / 2, MENUY + smallTileY*2 + (smallTileY - textheight("About us")) / 2, "About us");
        setbkcolor(THEME[CURRENT_THEME].bck_clr);
    }
}

void help()
{
    int textboxWidth=560, textboxHeight=500;
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

    setbkcolor(THEME[CURRENT_THEME].option_clr);
    setcolor(WHITE);

    int height=WINDOWY/2-textboxHeight/2+30;
    char a[300];
    strcpy(a, "HELP & SUGGESTIONS");
    outtextxy(WINDOWX/2-textwidth(a)/2, height, a);
    height=height+textheight("A")+45;
    strcpy(a, "DRAG & DROP blocks in the Scheme Zone to create your own logical scheme.");
    int allignX=WINDOWX/2-textwidth(a)/2;
    outtextxy(allignX, height, a);
    height=height+textheight("A");
    strcpy(a, "Always start with the START block!");
    outtextxy(allignX, height, a);
    height=height+textheight("A")+20;
    strcpy(a, "Use the RIGHT-CLICK OPTIONS from blocks to create bindings, enter");
    outtextxy(allignX, height, a);
    height=height+textheight("A");
    strcpy(a, "variable names, expressions, or delete blocks.");
    outtextxy(allignX, height, a);
    height=height+textheight("A")+20;
    strcpy(a, "If your scheme is logically correct and there are no loose blocks you");
    outtextxy(allignX, height, a);
    height=height+textheight("A");
    strcpy(a, "can RUN your algorithm and see the output in the Output Zone.");
    outtextxy(allignX, height, a);
    height=height+textheight("A")+20;
    strcpy(a, "Save your scheme, open old ones, or erase your progress from the SCHEME ");
    outtextxy(allignX, height, a);
    height=height+textheight("A");
    strcpy(a, "button.");
    outtextxy(allignX, height, a);
    height=height+textheight("A")+20;
    strcpy(a, "Customize the interface and choose the THEME you like the most!");
    outtextxy(allignX, height, a);
    height=height+textheight("A")+20;
    strcpy(a, "GENERATE the C++ CODE equivalent to your scheme using the");
    outtextxy(allignX, height, a);
    height=height+textheight("A");
    strcpy(a, "<Generate code> button.");
    outtextxy(allignX, height, a);
    height=height+textheight("A")+20;
    strcpy(a, "RESTORE a DELETED BLOCK using the <Last deleted block> option.");
    outtextxy(allignX, height, a);
    height=height+textheight("A")+50;
    strcpy(a, "Have fun creating your own schemes!");
    outtextxy(allignX, height, a);
    height=height+textheight("A");


    setbkcolor(THEME[CURRENT_THEME].bck_clr);
    waitForClickToRefresh();
}

void aboutUs()
{
    int textboxWidth=450, textboxHeight=270;
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

    setbkcolor(THEME[CURRENT_THEME].option_clr);
    setcolor(WHITE);

    int height=WINDOWY/2-textboxHeight/2+30;
    char a[300];
    strcpy(a, "ABOUT US :)");
    outtextxy(WINDOWX/2-textwidth(a)/2, height, a);
    height=height+textheight("A")+45;
    strcpy(a, "We hope you enjoy your experience using Interschem!");
    int allignX=WINDOWX/2-textwidth(a)/2;
    strcpy(a, "We, Delia and Ina, are a team of 2 girls.");
    outtextxy(allignX, height, a);
    height=height+textheight("A");
    strcpy(a, "We are first-year students at FII, interested in ");
    outtextxy(allignX, height, a);
    height=height+textheight("A");
    strcpy(a, "everything about Computer Science.");
    outtextxy(allignX, height, a);
    height=height+textheight("A");
    strcpy(a, "This is our first-semester-project that we developed ");
    outtextxy(allignX, height, a);
    height=height+textheight("A");
    strcpy(a, "together while learning a lot of new things.");
    outtextxy(allignX, height, a);
    height=height+textheight("A")+45;
    strcpy(a, "We hope you enjoy your experience using Interschem!");
    outtextxy(allignX, height, a);


    setbkcolor(THEME[CURRENT_THEME].bck_clr);
    waitForClickToRefresh();
}

void handleMenuClick(int x, int y, bool &isGenCode)
{
    int xx, yy;
    bool isDone = false;

    //scheme
    if (x < tileX)
    {
        Beep(400, 100);
        drawSubmenuScheme(true);
        clearmouseclick(WM_LBUTTONDOWN);

        while (!isDone)
        {
            getmouseclick(WM_LBUTTONDOWN, xx, yy);
            if (xx != -1 && yy != -1)
            {
                if (xx > firstSchemeX && xx < lastSchemeX && yy > MENUY && yy < lastSchemeY)
                {
                    Beep(400, 100);
                    if (yy < MENUY + smallTileY)
                    {
                        saveScheme(isGenCode);
                        cleardevice();
                        drawPage();
                        drawMenu();
                        drawAllBlocks();
                        if (isGenCode)
                            generateCode(isGenCode);
                        isDone=1;
                    }
                    else if (yy < MENUY + smallTileY * 2)
                    {
                        openScheme();
                        cleardevice();
                        drawPage();
                        drawMenu();
                        drawAllBlocks();
                        if (isGenCode)
                            isGenCode = 0;
                        isDone=1;
                    }
                    else if (yy < MENUY + smallTileY * 3)
                    {
                        emptyScheme();
                        cleardevice();
                        drawPage();
                        drawMenu();
                        drawAllBlocks();
                        if (isGenCode)
                            isGenCode = 0;
                        isDone=1;
                    }
                    else if (yy < MENUY + smallTileY * 4)
                    {
                        run();
                        cleardevice();
                        drawPage();
                        drawMenu();
                        drawAllBlocks();
                        if (isGenCode)
                            isGenCode = 0;
                        isDone=1;
                    }
                }
                else
                {
                    cleardevice();
                    drawPage();
                    drawMenu();
                    drawAllBlocks();
                    if (isGenCode)
                        generateCode(isGenCode);
                    clearmouseclick(WM_LBUTTONDOWN);
                    isDone = true;
                }
            }
        }
    }

    //customize
    else if (x > tileX && x < tileX * 2)
    {
        Beep(400, 100);
        drawSubmenuCustomize(true);
        clearmouseclick(WM_LBUTTONDOWN);

        while (!isDone)
        {
            getmouseclick(WM_LBUTTONDOWN, xx, yy);
            if (xx != -1 && yy != -1)
            {
                if (xx > firstCustomizeX && xx < lastCustomizeX && yy > MENUY && yy < lastCustomizeY)
                {
                    Beep(400, 100);
                    if (yy < MENUY + smallTileY)
                    {
                        CURRENT_THEME=0;
                        refresh();
                        if (isGenCode)
                            generateCode(isGenCode);
                    }
                    else if (yy < MENUY + smallTileY * 2)
                    {
                        CURRENT_THEME=1;
                        refresh();
                        if (isGenCode)
                            generateCode(isGenCode);
                    }
                    else if (yy < MENUY + smallTileY * 3)
                    {
                        CURRENT_THEME=2;
                        refresh();
                        if (isGenCode)
                            generateCode(isGenCode);
                    }
                    else if (yy < MENUY + smallTileY * 4)
                    {
                        CURRENT_THEME=3;
                        refresh();
                        if (isGenCode)
                            generateCode(isGenCode);
                    }
                    else if (yy < MENUY + smallTileY * 5)
                    {
                        CURRENT_THEME=4;
                        refresh();
                        if (isGenCode)
                            generateCode(isGenCode);
                    }
                }
                cleardevice();
                drawPage();
                drawMenu();
                drawAllBlocks();
                if (isGenCode)
                    generateCode(isGenCode);
                isDone = true;
            }
        }
    }
    else if (x > tileX * 2) //others
    {
        Beep(400, 100);
        drawSubmenuOthers(true);
        clearmouseclick(WM_LBUTTONDOWN);

        while (!isDone)
        {
            getmouseclick(WM_LBUTTONDOWN, xx, yy);
            if (xx != -1 && yy != -1)
            {
                if (xx > firstOthersX && xx < lastOthersX && yy > MENUY && yy < lastOthersY)
                {
                    Beep(400, 100);
                    if (yy < MENUY + smallTileY)
                    {
                        restoreDeletedBlock();
                    }
                    else if (yy < MENUY + smallTileY * 2)
                    {
                        help();
                    }
                    else if (yy < MENUY + smallTileY * 3)
                    {
                        aboutUs();
                    }
                }
                cleardevice();
                drawPage();
                drawMenu();
                drawAllBlocks();
                if (isGenCode)
                    generateCode(isGenCode);
                isDone = true;
            }
        }
    }
}

bool isInsideMenu(POINT a)
{
    return a.y<=MENUY;
}

bool isInsideScheme(POINT a)
{
    return (a.x<=tileX and isInsideMenu(a));
}

bool isInsideCustomize(POINT a)
{
    return (a.x>tileX and a.x<=tileX*2 and isInsideMenu(a));
}

bool isInsideOthers(POINT a)
{
    return (a.x>tileX*2 and isInsideMenu(a));
}


#endif // MENU_H_INCLUDED
