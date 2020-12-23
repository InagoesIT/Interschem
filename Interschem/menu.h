#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "list.h"
#include "blocksMoveDel.h"

#define START_X 50
#define START_Y 110
#define STOP_X 50
#define STOP_Y 200
#define IN_X 50
#define IN_Y 300
#define OUT_X 50
#define OUT_Y 380
#define ASSIGN_X 50
#define ASSIGN_Y 480
#define DECISION_X 50
#define DECISION_Y 570

#define MENUY 70
#define WINDOWX 1200
#define WINDOWY 700

void moveBlock(int x, int y, node *p, bool isNew);

const int tileX = WINDOWX / 3;
const int smallTileX = 170;//width Background Color + 50 ?? textwidth("Background Color") + 50 won't work))))
const int smallTileY = MENUY * 0.8;
const int firstSchemeX = (tileX - smallTileX) / 2;
const int lastSchemeX = smallTileX + firstSchemeX;
const int lastSchemeY = MENUY + smallTileY * 2;
const int firstCustomizeX = tileX + (tileX - smallTileX) / 2;
const int lastCustomizeX = smallTileX + firstCustomizeX;
const int lastCustomizeY = MENUY + smallTileY * 4;

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
    moveBlock(x, y, createNode(blockType, !strcmp(blockType, "DECISION"), x, y), true);
}

void drawPage()
{
    setlinestyle(0, 0, 3);
    //drag and drop blocks
    createStart(START_X, START_Y, true, true);
    createStop(STOP_X, STOP_Y, true, true);
    createIn(IN_X, IN_Y, true, true);
    createOut(OUT_X, OUT_Y, true, true);
    createAssign(ASSIGN_X, ASSIGN_Y, true, true);
    createDecision(DECISION_X, DECISION_Y, true, true);

    line(0, MENUY, WINDOWX, MENUY); // orizontala
    line(DRAG_SIZE_X, MENUY, DRAG_SIZE_X, WINDOWY); //verticala
}

void drawMenu()
{
    setfillstyle(LTSLASH_FILL , LIGHTCYAN);

    line(tileX, 0, tileX, MENUY);
    floodfill(tileX / 2, MENUY / 2, WHITE);
    line(tileX * 2, 0, tileX * 2, MENUY);
    floodfill(tileX * 1.5, MENUY / 2, WHITE);
    floodfill(tileX * 2.5, MENUY / 2, WHITE);

    outtextxy((tileX - textwidth("SCHEME")) / 2, (MENUY - textheight("SCHEME")) / 2, "SCHEME");
    outtextxy((tileX - textwidth("CUSTOMIZE")) / 2 + tileX, (MENUY - textheight("CUSTOMIZE")) / 2, "CUSTOMIZE");
    outtextxy((tileX - textwidth("HELP")) / 2 + tileX * 2, (MENUY - textheight("HELP")) / 2, "HELP");
}

void drawSubmenuScheme(bool isColored)
{
    setlinestyle(0, 0 , 3);
    setcolor(DARKGRAY);

    line(firstSchemeX, MENUY, firstSchemeX, lastSchemeY); // |
    line(firstSchemeX, lastSchemeY, lastSchemeX, lastSchemeY); // -
    line(lastSchemeX, MENUY, lastSchemeX, lastSchemeY); // |
    line(firstSchemeX, MENUY, lastSchemeX, MENUY); // -

    if (isColored)
    {
        setfillstyle(LTSLASH_FILL , LIGHTBLUE);
        setcolor(WHITE);
    }

    else
    {
        setfillstyle(LTSLASH_FILL , BLACK);
        setcolor(BLACK);
    }

    floodfill(firstSchemeX + smallTileX / 2, lastSchemeY / 2 , DARKGRAY);

    line(firstSchemeX, MENUY, firstSchemeX, lastSchemeY); // |
    line(firstSchemeX, lastSchemeY, lastSchemeX, lastSchemeY); // -
    line(lastSchemeX, MENUY, lastSchemeX, lastSchemeY); // |
    line(firstSchemeX, MENUY, lastSchemeX, MENUY); // -

    line(firstSchemeX, MENUY + smallTileY, lastSchemeX, MENUY + smallTileY);

    if (isColored)
    {
        outtextxy(firstSchemeX + (smallTileX - textwidth("Open")) / 2, MENUY + (smallTileY - textheight("Open")) / 2, "Open");
        outtextxy(firstSchemeX + (smallTileX - textwidth("Empty Scheme")) / 2, MENUY + smallTileY + (smallTileY - textheight("Empty Scheme")) / 2, "Empty Scheme");
    }
}

void drawSubmenuCustomize(bool isColored)
{
    setlinestyle(0, 0 , 3);
    setcolor(DARKGRAY);

    line(firstCustomizeX, MENUY, firstCustomizeX, lastCustomizeY); // |
    line(firstCustomizeX, lastCustomizeY, lastCustomizeX, lastCustomizeY); // -
    line(lastCustomizeX, MENUY, lastCustomizeX, lastCustomizeY); // |
    line(firstCustomizeX, MENUY, lastCustomizeX, MENUY); // -

    if (isColored)
    {
        setfillstyle(LTSLASH_FILL , LIGHTBLUE);
        setcolor(WHITE);
    }

    else
    {
        setfillstyle(LTSLASH_FILL , BLACK);
        setcolor(BLACK);
    }

    floodfill(firstCustomizeX + smallTileX / 2, lastCustomizeY / 2 , DARKGRAY);

    line(firstCustomizeX, MENUY, firstCustomizeX, lastCustomizeY); // |
    line(firstCustomizeX, lastCustomizeY, lastCustomizeX, lastCustomizeY); // -
    line(lastCustomizeX, MENUY, lastCustomizeX, lastCustomizeY); // |
    line(firstCustomizeX, MENUY, lastCustomizeX, MENUY); // -

    line(firstCustomizeX, MENUY + smallTileY, lastCustomizeX, MENUY + smallTileY);
    line(firstCustomizeX, MENUY + smallTileY * 2, lastCustomizeX, MENUY + smallTileY * 2);
    line(firstCustomizeX, MENUY + smallTileY * 3, lastCustomizeX, MENUY + smallTileY * 3);

    if (isColored)
    {
        outtextxy(firstCustomizeX + (smallTileX - textwidth("Block Color")) / 2, MENUY + (smallTileY - textheight("Block Color")) / 2, "Block Color");
        outtextxy(firstCustomizeX + (smallTileX - textwidth("Text Color")) / 2, MENUY + smallTileY + (smallTileY - textheight("Text Color")) / 2, "Text Color");
        outtextxy(firstCustomizeX + (smallTileX - textwidth("Background Color")) / 2, MENUY + smallTileY * 2 + (smallTileY - textheight("Background Color")) / 2, "Background Color");
        outtextxy(firstCustomizeX + (smallTileX - textwidth("Binding Color")) / 2, MENUY + smallTileY * 3 + (smallTileY - textheight("Binding Color")) / 2, "Binding Color");
    }
}

//to implement
void hoverMenu(int x, int y)
{

}

void handleMenuClick(int x, int y)
{
    int xx, yy;
    bool isDone = false;
//    hoverMenu(x, y);

    //scheme
    if (x < tileX)
    {
        drawSubmenuScheme(true);
        clearmouseclick(WM_LBUTTONDOWN);

        while (!isDone)
        {
            getmouseclick(WM_LBUTTONDOWN, xx, yy);
            if (xx != -1 && yy != -1)
            {
                if (xx > firstSchemeX && xx < lastSchemeX && yy > MENUY && yy < lastSchemeY)
                {
//                    if (yy < MENUY + smallTileY)
//                        saveScheme();
//                    else if (yy < MENUY + smallTileY * 2)
//                        openScheme();
//                    else if (yy < MENUY + smallTileY * 3)
//                        emptyScheme();
                }
                else
                {
                    cleardevice();
                    drawPage();
                    drawMenu();
                    drawAllBlocks();
                    clearmouseclick(WM_LBUTTONDOWN);
                    isDone = true;
                }
            }
        }
    }

    //customize
    else if (x > tileX && x < tileX * 2)
    {
        drawSubmenuCustomize(true);
        clearmouseclick(WM_LBUTTONDOWN);

        while (!isDone)
        {
            getmouseclick(WM_LBUTTONDOWN, xx, yy);
            if (xx != -1 && yy != -1)
            {
                if (xx > firstCustomizeX && xx < lastCustomizeX && yy > MENUY && yy < lastCustomizeY)
                {
//                    if (yy < MENUY + smallTileY)
//
//                    else if (yy < MENUY + smallTileY * 2)
//
//                    else if (yy < MENUY + smallTileY * 3)
//
                }
                else
                {
                    cleardevice();
                    drawPage();
                    drawMenu();
                    drawAllBlocks();
                    isDone = true;
                }
            }
        }
    }
//
//    //help
//    else if (x > tileX * 2)
//    {
//
//    }
}

#endif // MENU_H_INCLUDED
