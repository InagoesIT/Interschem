#ifndef BLOCKS_H_INCLUDED
#define BLOCKS_H_INCLUDED

#define AUX_COLOR YELLOW
#define BLOCK_COLOR GREEN
#define LINE_COLOR WHITE
#define IN_SMALL_BASE_DIFF 30

float coef;

void setColors(bool isColored)
{
    setlinestyle(0, 0, 3);

    if (isColored)
    {
        setcolor(AUX_COLOR);
        setfillstyle(SOLID_FILL, BLOCK_COLOR);
    }
    else
    {
        setcolor(BLACK);
        setfillstyle(SOLID_FILL, BLACK);
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
        floodfill(x + START_WIDTH * coef / 2, y + START_HEIGHT * coef / 2, BLACK);
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
        setbkcolor(BLOCK_COLOR);
        outtextxy(x + (START_WIDTH * coef - textWidth) / 2, y + (START_HEIGHT * coef - textHeight) / 2 - 5, "Start");
        setbkcolor(BLACK);
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
        setbkcolor(BLOCK_COLOR);
        outtextxy(x + (STOP_WIDTH * coef - textWidth)/2, y + (STOP_HEIGHT * coef - textHeight)/2, "Stop");
        setbkcolor(BLACK);
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
        setbkcolor(BLOCK_COLOR);
        outtextxy(x + (IN_BIG_BASE * coef - textWidth) / 2, y + (LATERAL_PART * coef - textHeight) / 2, text);
        setbkcolor(BLACK);
	}
    else
        floodfill(x + IN_BIG_BASE * coef / 2, y + LATERAL_PART * coef / 2, BLACK);
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

        setcolor(WHITE);
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
        setbkcolor(BLOCK_COLOR);
        outtextxy(x + (IN_BIG_BASE * coef - textWidth) / 2, y + (LATERAL_PART * coef - textHeight) / 2, text);
        setbkcolor(BLACK);
    }
    else
        floodfill(x + IN_BIG_BASE * coef / 2, y + LATERAL_PART * coef / 2, BLACK);
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
        setbkcolor(BLOCK_COLOR);
        outtextxy(x + (ASSIGN_WIDTH * coef - textWidth) / 2, y + (ASSIGN_HEIGHT * coef - textHeight) / 2, text);
        setbkcolor(BLACK);
    }
    else
        floodfill(x + ASSIGN_WIDTH * coef / 2, y + ASSIGN_HEIGHT * coef / 2, BLACK);
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

        setbkcolor(BLOCK_COLOR);
        outtextxy(X + (DECISION_BASE * coef - textWidth) / 2, y + (EQUAL_PART * coef - textHeight) / 2 + 20 * coef, text);
        setbkcolor(BLACK);
        outtextxy(x + TWidth / 2, y + EQUAL_PART * coef - 10, "T");
        outtextxy(X + DECISION_BASE * coef + 5 + FWidth / 2, y + EQUAL_PART * coef - 10, "F");
    }
    else
    {
        floodfill(X + DECISION_BASE * coef / 2, y + EQUAL_PART * coef / 2, BLACK);

        setbkcolor(BLACK);
        setcolor(BLACK);
        outtextxy(x + TWidth / 2, y + EQUAL_PART * coef - 10, "T");
        outtextxy(X + DECISION_BASE * coef + 5 + FWidth / 2, y + EQUAL_PART * coef - 10, "F");
    }
}

void createBlock(node *p, bool isColored)
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
    if(p->next!=NULL)
        line(p->coordX, p->coordY, p->next->coordX, p->next->coordY);
    if(p->nextElse!=NULL)
        line(p->coordX, p->coordY, p->nextElse->coordX, p->nextElse->coordY);
    node * parent = new node;
    bool fromElse, found=0;
    createLineFromParents(p);
}

#endif // BLOCKS_H_INCLUDED

