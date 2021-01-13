#ifndef BLOCKS_H_INCLUDED
#define BLOCKS_H_INCLUDED

#include <time.h>

#define AUX_COLOR YELLOW
#define BLOCK_COLOR GREEN
#define LINE_COLOR WHITE
#define IN_SMALL_BASE_DIFF 30
#define MATRIXX 700
#define MATRIXY 1200

float coef;
node * NODE_1 = new node;
node * NODE_2 = new node;
bool MOVE_IS_ON=0;

struct POINTXY
{
    int x,y;
} CURRENT_POINT, NEXT_POINT, LAST_GOOD_POINT, P, POINTS_ARRAY[300];

int DX[4]= {0, -1, 0, 1}, DY[4]= {1, 0, -1, 0};
int FOLLOWING_DIR[300];

void setColors(bool isColored)
{
    setlinestyle(0, 0, 3);

    if (isColored)
    {
        setcolor(AUX_COLOR);
        setfillstyle(SOLID_FILL, THEME[CURRENT_THEME].block_clr);
    }
    else
    {
        setcolor(THEME[CURRENT_THEME].bck_clr);
        setfillstyle(SOLID_FILL, THEME[CURRENT_THEME].bck_clr);
    }
}

void createRoundedRect(int x, int y, bool isColored)
{
    const int NR_POINTS = 15;
    const int RADIUS = 15;
    int i = 0;
    float X = 0;
    float Y = 0;
    float points[2][4 * NR_POINTS];
    setColors(isColored);

    for(; i < NR_POINTS; i++)
    {
        X += RADIUS / NR_POINTS;
        Y = sqrt(RADIUS * RADIUS - X * X);
        points[0][i] = X + x + START_WIDTH * coef - RADIUS;
        points[1][i] = y - Y + RADIUS;
    }
    Y=0;
    for(; i < NR_POINTS * 2; i++)
    {
        Y += RADIUS/NR_POINTS;
        X = sqrt(RADIUS * RADIUS - Y * Y);
        points[0][i] = x + START_WIDTH * coef + X - RADIUS;
        points[1][i] = y + START_HEIGHT * coef - RADIUS + Y;
    }
    X=0;
    for(; i < NR_POINTS * 3; i++)
    {
        X += RADIUS/NR_POINTS;
        Y = sqrt(RADIUS * RADIUS - X * X);
        points[0][i] = x + RADIUS - X;
        points[1][i] = y + START_HEIGHT * coef - RADIUS + Y;
    }
    Y=0;
    for(; i < NR_POINTS * 4; i++)
    {
        Y += RADIUS/NR_POINTS;
        X = sqrt(RADIUS * RADIUS - Y * Y);
        points[0][i] = x - X + RADIUS;
        points[1][i] = y + RADIUS - Y;
    }

    for (i = 0; i < NR_POINTS * 4 - 1; i++)
        line(points[0][i], points[1][i], points[0][i+1], points[1][i + 1]);
    line(points[0][NR_POINTS * 4 - 1], points[1][NR_POINTS * 4 - 1], points[0][0], points[1][0]);

    if (isColored)
    {
        floodfill(x + START_WIDTH * coef / 2, y + START_HEIGHT * coef / 2, AUX_COLOR);
        setcolor(LINE_COLOR);
        for (i = 0; i < NR_POINTS * 4 - 1; i++)
            line(points[0][i], points[1][i], points[0][i+1], points[1][i + 1]);
        line(points[0][NR_POINTS * 4 - 1], points[1][NR_POINTS * 4 - 1], points[0][0], points[1][0]);
    }
    else
    {
        floodfill(x + START_WIDTH * coef / 2, y + START_HEIGHT * coef / 2, THEME[CURRENT_THEME].bck_clr);
    }
}

void createStart(int x, int y, bool isSmall, bool isColored)
{
    if (!isSmall)
        coef = 1;
    else
        coef = 0.7;

    createRoundedRect(x, y, isColored);

    if (isColored)
    {
        int textWidth = textwidth("Start");
        int textHeight = textheight("Start");
        setbkcolor(THEME[CURRENT_THEME].block_clr);
        outtextxy(x + (START_WIDTH * coef - textWidth) / 2, y + (START_HEIGHT * coef - textHeight) / 2, "Start");
        setbkcolor(THEME[CURRENT_THEME].bck_clr);
    }
}

void createStop(int x, int y, bool isSmall, bool isColored)
{
    if (!isSmall)
        coef = 1;
    else
        coef = 0.7;

    createRoundedRect(x, y, isColored);

    if (isColored)
    {
        int textWidth = textwidth("Stop");
        int textHeight = textheight("Stop");
        setbkcolor(THEME[CURRENT_THEME].block_clr);
        setcolor(LINE_COLOR);
        outtextxy(x + (STOP_WIDTH * coef - textWidth)/2, y + (STOP_HEIGHT * coef - textHeight)/2, "Stop");
        setbkcolor(THEME[CURRENT_THEME].bck_clr);
    }
}

void createIn(int x, int y, bool isSmall, bool isColored, char expression[50])
{
    const int LATERAL_PART = 50;
    char text[50];

    if (!isSmall)
        coef = 1;

    setColors(isColored);

    line(x, y, x + IN_BIG_BASE * coef, y);
    line(x + IN_BIG_BASE * coef, y, x + IN_BIG_BASE * coef - IN_SMALL_BASE_DIFF * coef, y + LATERAL_PART * coef);
    line(x + IN_BIG_BASE * coef - IN_SMALL_BASE_DIFF * coef, y + LATERAL_PART * coef, x + IN_SMALL_BASE_DIFF * coef, y + LATERAL_PART * coef);
    line(x + IN_SMALL_BASE_DIFF * coef, y + LATERAL_PART * coef, x, y);

    if (isColored)
    {
        floodfill(x + IN_BIG_BASE * coef / 2, y + LATERAL_PART * coef / 2, AUX_COLOR);
        setcolor(LINE_COLOR);

        line(x, y, x + IN_BIG_BASE * coef, y);
        line(x + IN_BIG_BASE * coef, y, x + IN_BIG_BASE * coef - IN_SMALL_BASE_DIFF * coef, y + LATERAL_PART * coef);
        line(x + IN_BIG_BASE * coef - IN_SMALL_BASE_DIFF * coef, y + LATERAL_PART * coef, x + IN_SMALL_BASE_DIFF * coef, y + LATERAL_PART * coef);
        line(x + IN_SMALL_BASE_DIFF * coef, y + LATERAL_PART * coef, x, y);

        if (!isSmall)
        {
            if (strcmp(expression, "no expression"))
                strcpy(text, expression);
            else
                strcpy(text, "<var>");
        }
        else
            strcpy(text, "Input");

        int textWidth = textwidth(text);
        int textHeight = textheight(text);
        setbkcolor(THEME[CURRENT_THEME].block_clr);
        setcolor(LINE_COLOR);
        outtextxy(x + (IN_BIG_BASE * coef - textWidth) / 2, y + (LATERAL_PART * coef - textHeight) / 2, text);
        setbkcolor(THEME[CURRENT_THEME].bck_clr);
    }
    else
        floodfill(x + IN_BIG_BASE * coef / 2, y + LATERAL_PART * coef / 2, THEME[CURRENT_THEME].bck_clr);
}

void createOut(int x, int y, bool isSmall, bool isColored, char expression[50])
{
    const int LATERAL_PART = 50;
    char text[50];

    if (!isSmall)
        coef = 1;

    setColors(isColored);

    line(x + IN_SMALL_BASE_DIFF * coef, y, x + IN_BIG_BASE * coef - IN_SMALL_BASE_DIFF * coef, y);
    line(x + IN_BIG_BASE * coef - IN_SMALL_BASE_DIFF * coef, y, x + IN_BIG_BASE * coef, y + LATERAL_PART * coef);
    line(x + IN_BIG_BASE * coef, y + LATERAL_PART * coef, x, y + LATERAL_PART * coef);
    line(x, y + LATERAL_PART * coef, x + IN_SMALL_BASE_DIFF * coef, y);

    if (isColored)
    {
        floodfill(x + IN_BIG_BASE * coef / 2, y + LATERAL_PART * coef / 2, AUX_COLOR);

        setcolor(LINE_COLOR);
        line(x + IN_SMALL_BASE_DIFF * coef, y, x + IN_BIG_BASE * coef - IN_SMALL_BASE_DIFF * coef, y);
        line(x + IN_BIG_BASE * coef - IN_SMALL_BASE_DIFF * coef, y, x + IN_BIG_BASE * coef, y + LATERAL_PART * coef);
        line(x + IN_BIG_BASE * coef, y + LATERAL_PART * coef, x, y + LATERAL_PART * coef);
        line(x, y + LATERAL_PART * coef, x + IN_SMALL_BASE_DIFF * coef, y);

        if (!isSmall)
        {
            if (strcmp(expression, "no expression"))
                strcpy(text, expression);
            else
                strcpy(text, "<var>");
        }
        else
            strcpy(text, "Output");

        int textWidth = textwidth(text);
        int textHeight = textheight(text);
        setbkcolor(THEME[CURRENT_THEME].block_clr);
        setcolor(LINE_COLOR);
        outtextxy(x + (IN_BIG_BASE * coef - textWidth) / 2, y + (LATERAL_PART * coef - textHeight) / 2, text);
        setbkcolor(THEME[CURRENT_THEME].bck_clr);
    }
    else
        floodfill(x + IN_BIG_BASE * coef / 2, y + LATERAL_PART * coef / 2, THEME[CURRENT_THEME].bck_clr);
}

void createAssign(int x, int y, bool isSmall, bool isColored, char expression[50])
{
    char text[50];

    if (!isSmall)
        coef = 1;
    else
        coef = 0.7;

    setColors(isColored);

    rectangle(x, y, x + ASSIGN_WIDTH * coef, y + ASSIGN_HEIGHT * coef);

    if (isColored)
    {
        floodfill(x + ASSIGN_WIDTH * coef / 2, y + ASSIGN_HEIGHT * coef / 2, AUX_COLOR);
        setcolor(LINE_COLOR);
        rectangle(x, y, x + ASSIGN_WIDTH * coef, y + ASSIGN_HEIGHT * coef);

        if (!isSmall)
        {
            if (strcmp(expression, "no expression"))
                strcpy(text, expression);
            else
                strcpy(text, "<var> <- exp");
        }
        else
            strcpy(text, "Assign");

        int textWidth = textwidth(text);
        int textHeight = textheight(text);
        setbkcolor(THEME[CURRENT_THEME].block_clr);
        setcolor(LINE_COLOR);
        outtextxy(x + (ASSIGN_WIDTH * coef - textWidth) / 2, y + (ASSIGN_HEIGHT * coef - textHeight) / 2, text);
        setbkcolor(THEME[CURRENT_THEME].bck_clr);
    }
    else
        floodfill(x + ASSIGN_WIDTH * coef / 2, y + ASSIGN_HEIGHT * coef / 2, THEME[CURRENT_THEME].bck_clr);
}

void createDecision(int x, int y, bool isSmall, bool isColored, char expression[50])
{
    int TWidth = textwidth("T");
    int FWidth = textwidth("F");
    const int EQUAL_PART = 80;
    const int X = x + TWidth + 10;
    char text[50];

    if (!isSmall)
        coef = 1;
    else
        coef = 0.7;

    setColors(isColored);

    line(X + DECISION_BASE * coef / 2, y, X + DECISION_BASE * coef, y + EQUAL_PART * coef);
    line(X + DECISION_BASE * coef, y + EQUAL_PART * coef, X, y + EQUAL_PART * coef);
    line(X, y + EQUAL_PART * coef, X + DECISION_BASE * coef / 2, y);

    if (isColored)
    {
        floodfill(X + DECISION_BASE * coef / 2, y + EQUAL_PART * coef / 2, AUX_COLOR);
        setcolor(LINE_COLOR);
        line(X + DECISION_BASE * coef / 2, y, X + DECISION_BASE * coef, y + EQUAL_PART * coef);
        line(X + DECISION_BASE * coef, y + EQUAL_PART * coef, X, y + EQUAL_PART * coef);
        line(X, y + EQUAL_PART * coef, X + DECISION_BASE * coef / 2, y);


        if (!isSmall)
        {
            if (strcmp(expression, "no expression"))
                strcpy(text, expression);
            else
                strcpy(text, "<var> ? <var>");
        }
        else
            strcpy(text, "Decision");

        int textWidth = textwidth(text);
        int textHeight = textheight(text);

        setbkcolor(THEME[CURRENT_THEME].block_clr);
        setcolor(LINE_COLOR);
        outtextxy(X + (DECISION_BASE * coef - textWidth) / 2, y + (EQUAL_PART * coef - textHeight) / 2 + 20 * coef, text);

        setbkcolor(THEME[CURRENT_THEME].bck_clr);
        outtextxy(x + TWidth / 2, y + EQUAL_PART * coef - 10, "T");
        outtextxy(X + DECISION_BASE * coef + 5 + FWidth / 2, y + EQUAL_PART * coef - 10, "F");
    }
    else
    {
        floodfill(X + DECISION_BASE * coef / 2, y + EQUAL_PART * coef / 2, THEME[CURRENT_THEME].bck_clr);

        setbkcolor(THEME[CURRENT_THEME].bck_clr);
        setcolor(THEME[CURRENT_THEME].bck_clr);
        outtextxy(x + TWidth / 2, y + EQUAL_PART * coef - 10, "T");
        outtextxy(X + DECISION_BASE * coef + 5 + FWidth / 2, y + EQUAL_PART * coef - 10, "F");
    }
}
void getConnectionPointFromA(int & xa, int & ya, node * a, bool fromElse) //get connection point from father block
{
    if(strcmp(a->type, "START")==0 or strcmp(a->type, "STOP")==0)
    {
        xa=a->coordX+START_WIDTH/2;
        ya=a->coordY+START_HEIGHT;
    }
    else if(strcmp(a->type, "IN")==0 or strcmp(a->type, "OUT")==0)
    {
        xa=a->coordX+IN_BIG_BASE/2;
        ya=a->coordY+IN_HEIGHT;
    }
    else if(strcmp(a->type, "ASSIGN")==0)
    {
        xa=a->coordX+ASSIGN_WIDTH/2;
        ya=a->coordY+ASSIGN_HEIGHT;
    }
    else if(strcmp(a->type, "DECISION")==0)
    {
        if(fromElse==0)
            xa=a->coordX+10+textwidth("T");
        else
            xa=a->coordX+DECISION_BASE+10+textwidth("T");
        ya=a->coordY+DECISION_HEIGHT;
    }
}

void getConnectionPointFromB(int & xb, int & yb, node * b) //get connection point from son block
{
    if(strcmp(b->type, "START")==0 or strcmp(b->type, "STOP")==0)
    {
        xb=b->coordX+START_WIDTH/2;
        yb=b->coordY;
    }
    else if(strcmp(b->type, "IN")==0 or strcmp(b->type, "OUT")==0)
    {
        xb=b->coordX+IN_BIG_BASE/2;
        yb=b->coordY;
    }
    else if(strcmp(b->type, "ASSIGN")==0)
    {
        xb=b->coordX+ASSIGN_WIDTH/2;
        yb=b->coordY;
    }
    else if(strcmp(b->type, "DECISION")==0)
    {
        xb=b->coordX+DECISION_BASE/2+10+textwidth("T");
        yb=b->coordY;
    }
}

void createLineFromAToB(int xa, int ya, int xb, int yb, int color) //create simple line even if it goes over blocks
{
    setlinestyle(SOLID_LINE, 0, 3);
    setcolor(color);
    line(xa, ya, xa, (ya+yb)/2);
    line(xb, yb, xb, (ya+yb)/2);
    line(xa, (ya+yb)/2, xb, (ya+yb)/2);
}

bool spaceIsEmpty(int x, int y)//empty AND inside scheme zone
{
    NODE_2=NODE_1;
    selectCorrectNode(x, y, NODE_1, NODE_2);
    if(NODE_1==NULL)
        return 1;//wait for the updated scheme zone to finish this
    return 0;
}

int calculateWantedDirectionX(int xa, int xb) //you are in xa and want to go xb
{
    if(xa<=xb)
        return 3;
    return 1;
}

int calculateWantedDirectionY(int ya, int yb) //you are in ya and want to go yb
{
    if(ya<=yb)
        return 0;
    return 2;
}

bool allignedWithBOrFurther(int x, int y, int xb, int yb, int dir) //is curent point alligned with the destination?
{
    if(dir==0)
    {
        if(y>=yb-2)
            return 1;
        return 0;
    }
    else if(dir==1)
    {
        if(x<=xb)
            return 1;
        return 0;
    }
    else if(dir==2)
    {
        if(y<=yb-2)
            return 1;
        return 0;
    }
    else
    {
        if(x>=xb)
            return 1;
        return 0;
    }
}

bool dir2CanBeUsed(int x, int y, int dir) //we can now use dir
{
    if(dir==0)
    {
        if(spaceIsEmpty(x, y+1))
            return 1;
        return 0;
    }
    else if(dir==1)
    {
        if(spaceIsEmpty(x-1, y))
            return 1;
        return 0;
    }
    else if(dir==2)
    {
        if(spaceIsEmpty(x, y-1))
            return 1;
        return 0;
    }
    else
    {
        if(spaceIsEmpty(x+1, y))
            return 1;
        return 0;
    }
}

bool isAEqualToB(int x, int y, int xb, int yb) //are points equal
{
    if(x==xb and y==yb)
        return 1;
    return 0;
}

void drawLinesFromArray(int nrPoints, int color) //draw lines from the points memorised
{
    for(int i=1; i<nrPoints; ++i)
    {
        setcolor(color);
        line(POINTS_ARRAY[i-1].x, POINTS_ARRAY[i-1].y, POINTS_ARRAY[i].x, POINTS_ARRAY[i].y);
    }
}

bool repeatingContext(int x, int y, int dir1, int nrPoints) //are we in an infinite loop?
{
    for(int i=0; i<nrPoints; ++i)
        if(POINTS_ARRAY[i].x==x and POINTS_ARRAY[i].y==y and dir1==FOLLOWING_DIR[i])
            return 1;
    return 0;
}

void connectBlocks(node * a, node * b, bool fromElse, int color) //create graphic line for binding
{
    int xa, ya, xb, yb;
    bool finished=0, forcedFinish=0;

    getConnectionPointFromA(xa, ya, a, fromElse);
    getConnectionPointFromB(xb, yb, b);

    //createLineFromAToB(xa, ya, xb, yb, color);

    int dir2=calculateWantedDirectionX(xa, xb);
    int dir1=calculateWantedDirectionY(ya+1, yb-2);

    if(!spaceIsEmpty(xa, ya+1) or !spaceIsEmpty(xb, yb-2))
    {
        createLineFromAToB(xa, ya, xb, yb, color);
        finished=1;
        forcedFinish=1;
    }

    CURRENT_POINT.x=xa;
    CURRENT_POINT.y=ya+1;
    LAST_GOOD_POINT.x=xa;
    LAST_GOOD_POINT.y=ya+1;
    NEXT_POINT.x=CURRENT_POINT.x+DX[dir1];
    NEXT_POINT.y=CURRENT_POINT.y+DY[dir1];
    P.x=xa;
    P.y=ya+1;
    POINTS_ARRAY[0]=P;
    FOLLOWING_DIR[0]=dir1;
    int nrPoints=1;
    time_t t1=time(NULL);
    int sasa=0;
    while(!finished)
    {
        time_t t2=time(NULL);
        if(t1!=t2)
        {
            t2=t2;
            ++sasa;
        }
        if(CURRENT_POINT.x==b->coordX and CURRENT_POINT.y==b->coordY-2)
        {
            finished=0;
        }
        while(spaceIsEmpty(NEXT_POINT.x, NEXT_POINT.y) and
                !(allignedWithBOrFurther(CURRENT_POINT.x, CURRENT_POINT.y, xb, yb, dir1) and
                  (dir2CanBeUsed(CURRENT_POINT.x, CURRENT_POINT.y, dir2) or isAEqualToB(CURRENT_POINT.x, CURRENT_POINT.y, xb, yb-2))))
        {
            if(dir2CanBeUsed(CURRENT_POINT.x, CURRENT_POINT.y, dir2))
            {
                LAST_GOOD_POINT.x=CURRENT_POINT.x;
                LAST_GOOD_POINT.y=CURRENT_POINT.y;
            }
            CURRENT_POINT.x=NEXT_POINT.x;
            CURRENT_POINT.y=NEXT_POINT.y;
            NEXT_POINT.x=CURRENT_POINT.x+DX[dir1];
            NEXT_POINT.y=CURRENT_POINT.y+DY[dir1];
        }
        if(!spaceIsEmpty(NEXT_POINT.x,NEXT_POINT.y))
        {
//            if(!spaceIsEmpty(CURRENT_POINT.x, CURRENT_POINT.y+1) and !spaceIsEmpty(CURRENT_POINT.x+1, CURRENT_POINT.y) and dir1==0)
//                dir1=2;
//            else if(!spaceIsEmpty(CURRENT_POINT.x, CURRENT_POINT.y+1) and !spaceIsEmpty(CURRENT_POINT.x-1, CURRENT_POINT.y) and dir1==0 and CURRENT_POINT.y==yb)
//                dir1=2;
//            else
            {
                if(!dir2CanBeUsed(CURRENT_POINT.x, CURRENT_POINT.y, dir2))
                {
                    if(dir2==0 or dir2==1)
                        dir2+=2;
                    else
                        dir2-=2;
                }
                dir1=dir2;
                if(dir2==0 or dir2==2)//on y axis
                    dir2=calculateWantedDirectionX(CURRENT_POINT.x, xb);
                else
                    dir2=calculateWantedDirectionY(CURRENT_POINT.y, yb-2);
            }
        }
        else if((allignedWithBOrFurther(CURRENT_POINT.x, CURRENT_POINT.y, xb, yb, dir1) and dir2CanBeUsed(CURRENT_POINT.x, CURRENT_POINT.y, dir2)))
        {
            dir1=dir2;
            if(dir2==0 or dir2==2)//on y axis
                dir2=calculateWantedDirectionX(CURRENT_POINT.x, xb);
            else
                dir2=calculateWantedDirectionY(CURRENT_POINT.y, yb-2);
        }
        if(isAEqualToB(CURRENT_POINT.x, CURRENT_POINT.y, xb, yb-2) or isAEqualToB(CURRENT_POINT.x, CURRENT_POINT.y, xb, yb-3))
            finished=1;
        int dir1Copy=dir1;
        if((CURRENT_POINT.x!=POINTS_ARRAY[nrPoints-1].x or CURRENT_POINT.y!=POINTS_ARRAY[nrPoints-1].y) and repeatingContext(CURRENT_POINT.x, CURRENT_POINT.y, dir1, nrPoints))
        {
            if(dir1==0)
            {
                dir1+=2;
                dir2=calculateWantedDirectionX(CURRENT_POINT.x, xb);
            }
            else if(dir1==1)
            {
                dir1+=2;
                dir2=calculateWantedDirectionY(CURRENT_POINT.y, yb-2);
            }
            else if(dir1==2)
            {
                dir1-=2;
                dir2=calculateWantedDirectionX(CURRENT_POINT.x, xb);
            }
            else
            {
                dir1-=2;
                dir2=calculateWantedDirectionY(CURRENT_POINT.y, yb-2);
            }
        }
        NEXT_POINT.x=CURRENT_POINT.x+DX[dir1];
        NEXT_POINT.y=CURRENT_POINT.y+DY[dir1];
        if(CURRENT_POINT.x!=POINTS_ARRAY[nrPoints-1].x or CURRENT_POINT.y!=POINTS_ARRAY[nrPoints-1].y)
        {
            P.x=CURRENT_POINT.x;
            P.y=CURRENT_POINT.y;

            POINTS_ARRAY[nrPoints]=P;
            FOLLOWING_DIR[nrPoints]=dir1Copy;
            ++nrPoints;
        }
    }
    if(forcedFinish==0)
        drawLinesFromArray(nrPoints, color);
    else
        createLineFromAToB(xa, ya, xb, yb, color);
}

void createLineFromList(node * k, node * currentNode, int color) //create graphic lines from all the blocks that have k as son from this list
{
    if(START->wasCreated)
    {
        currentNode->viz=1;
        if(currentNode->next and currentNode->next==k)
            connectBlocks(currentNode, k, 0, color);
        if(currentNode->nextElse and currentNode->nextElse==k)
            connectBlocks(currentNode, k, 1, color);
        if(currentNode->next and currentNode->next->viz==0)
            createLineFromList(k, currentNode->next, color);
        if(currentNode->nextElse and currentNode->nextElse->viz==0)
            createLineFromList(k, currentNode->nextElse, color);
    }
}

void createLineFromParents(node * k, int color) //create graphic lines from all the blocks that have k as son
{
    reinitializeAllViz();
    createLineFromList(k, START, color);
    reinitializeAllViz();
    for(int i=0; i<FREE_NODES_SIZE; ++i)
        if(RESTS->n[i])
            createLineFromList(k, RESTS->n[i], color);
    reinitializeAllViz();
}
void createBlock(node *p, bool isColored) //creates block and his lines
{
    if (strcmp(p->type, "START") == 0)
        createStart(p->coordX, p->coordY, false, isColored);
    else if (strcmp(p->type, "STOP") == 0)
        createStop(p->coordX, p->coordY, false, isColored);
    else if (strcmp(p->type, "IN") == 0)
        createIn(p->coordX, p->coordY, false, isColored, p->expression);
    else if (strcmp(p->type, "OUT") == 0)
        createOut(p->coordX, p->coordY, false, isColored, p->expression);
    else if (strcmp(p->type, "ASSIGN") == 0)
        createAssign(p->coordX, p->coordY, false, isColored, p->expression);
    else
        createDecision(p->coordX, p->coordY, false, isColored, p->expression);
    if(isColored==1)
    {
        if(p->next!=NULL)
            connectBlocks(p, p->next, 0, LINE_COLOR);
        if(p->nextElse!=NULL)
            connectBlocks(p, p->nextElse, 1, LINE_COLOR);
        createLineFromParents(p, LINE_COLOR);
    }
    else
    {
        if(p->next!=NULL)
            connectBlocks(p, p->next, 0, THEME[CURRENT_THEME].bck_clr);
        if(p->nextElse!=NULL)
            connectBlocks(p, p->nextElse, 1, THEME[CURRENT_THEME].bck_clr);
        createLineFromParents(p, THEME[CURRENT_THEME].bck_clr);
    }
}

#endif // BLOCKS_H_INCLUDED

