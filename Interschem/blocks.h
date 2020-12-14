#ifndef BLOCKS_H_INCLUDED
#define BLOCKS_H_INCLUDED

#include "list.h"

#define AUX_COLOR YELLOW
#define BLOCK_COLOR GREEN
#define LINE_COLOR WHITE
#define IN_SMALL_BASE_DIFF 30

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
        points[0][i] = X + x + START_WIDTH - RADIUS;
        points[1][i] = y - Y + RADIUS;
    }
    Y=0;
    for(; i < NR_POINTS * 2; i++)
    {
        Y += RADIUS/NR_POINTS;
        X = sqrt(RADIUS * RADIUS - Y * Y);
        points[0][i] = x + START_WIDTH + X - RADIUS;
        points[1][i] = y + START_HEIGHT - RADIUS + Y;
    }
    X=0;
    for(; i < NR_POINTS * 3; i++)
    {
        X += RADIUS/NR_POINTS;
        Y = sqrt(RADIUS * RADIUS - X * X);
        points[0][i] = x + RADIUS - X;
        points[1][i] = y + START_HEIGHT - RADIUS + Y;
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
        floodfill(x + START_WIDTH / 2, y + START_HEIGHT / 2, AUX_COLOR);
        setcolor(LINE_COLOR);
        for (i = 0; i < NR_POINTS * 4 - 1; i++)
            line(points[0][i], points[1][i], points[0][i+1], points[1][i + 1]);
        line(points[0][NR_POINTS * 4 - 1], points[1][NR_POINTS * 4 - 1], points[0][0], points[1][0]);
    }
    else
    {
        floodfill(x + START_WIDTH / 2, y + START_HEIGHT / 2, BLACK);
    }
}

void createStart(int x, int y, bool isColored)
{
    createRoundedRect(x, y, isColored);

    int textWidth = textwidth("Start");
    int textHeight = textheight("Start");
    outtextxy(x + (START_WIDTH - textWidth) / 2, y + (START_HEIGHT - textHeight) / 2 - 5, "Start");
}

void createStop(int x, int y, bool isColored)
{
    createRoundedRect(x, y, isColored);

    int textWidth = textwidth("Stop");
    int textHeight = textheight("Stop");
    outtextxy(x + (STOP_WIDTH - textWidth)/2, y + (STOP_HEIGHT - textHeight)/2, "Stop");
}

void createIn(int x, int y, bool isColored)
{
    const int LATERAL_PART = 50;

    setColors(isColored);

	line(x, y, x + IN_BIG_BASE, y);
	line(x + IN_BIG_BASE, y, x + IN_BIG_BASE - IN_SMALL_BASE_DIFF, y + LATERAL_PART);
	line(x + IN_BIG_BASE - IN_SMALL_BASE_DIFF, y + LATERAL_PART, x + IN_SMALL_BASE_DIFF, y + LATERAL_PART);
	line(x + IN_SMALL_BASE_DIFF, y + LATERAL_PART, x, y);

	if (isColored)
	{
	    floodfill(x + IN_BIG_BASE / 2, y + LATERAL_PART / 2, AUX_COLOR);
	    setcolor(LINE_COLOR);

	    line(x, y, x + IN_BIG_BASE, y);
        line(x + IN_BIG_BASE, y, x + IN_BIG_BASE - IN_SMALL_BASE_DIFF, y + LATERAL_PART);
        line(x + IN_BIG_BASE - IN_SMALL_BASE_DIFF, y + LATERAL_PART, x + IN_SMALL_BASE_DIFF, y + LATERAL_PART);
        line(x + IN_SMALL_BASE_DIFF, y + LATERAL_PART, x, y);

        int textWidth = textwidth("<var>");
        int textHeight = textheight("<var>");
        outtextxy(x + (IN_BIG_BASE - textWidth) / 2, y + (LATERAL_PART - textHeight) / 2, "<var>");
	}
    else
    {
        floodfill(x + IN_BIG_BASE / 2, y + LATERAL_PART / 2, BLACK);
    }
}

void createOut(int x, int y, bool isColored)
{
    const int LATERAL_PART = 50;

    setColors(isColored);

	line(x + IN_SMALL_BASE_DIFF, y, x + IN_BIG_BASE - IN_SMALL_BASE_DIFF, y);
	line(x + IN_BIG_BASE - IN_SMALL_BASE_DIFF, y, x + IN_BIG_BASE, y + LATERAL_PART);
	line(x + IN_BIG_BASE, y + LATERAL_PART, x, y + LATERAL_PART);
	line(x, y + LATERAL_PART, x + IN_SMALL_BASE_DIFF, y);

    if (isColored)
    {
        floodfill(x + IN_BIG_BASE / 2, y + LATERAL_PART / 2, AUX_COLOR);

        setcolor(WHITE);
        line(x + IN_SMALL_BASE_DIFF, y, x + IN_BIG_BASE - IN_SMALL_BASE_DIFF, y);
        line(x + IN_BIG_BASE - IN_SMALL_BASE_DIFF, y, x + IN_BIG_BASE, y + LATERAL_PART);
        line(x + IN_BIG_BASE, y + LATERAL_PART, x, y + LATERAL_PART);
        line(x, y + LATERAL_PART, x + IN_SMALL_BASE_DIFF, y);

        int textWidth = textwidth("<var>");
        int textHeight = textheight("<var>");
        outtextxy(x + (IN_BIG_BASE - textWidth) / 2, y + (LATERAL_PART - textHeight) / 2, "<var>");
    }
    else
    {
        floodfill(x + IN_BIG_BASE / 2, y + LATERAL_PART / 2, BLACK);
    }
}

void createAssign(int x, int y, bool isColored)
{
    setColors(isColored);

    rectangle(x, y, x + ASSIGN_WIDTH, y + ASSIGN_HEIGHT);

    if (isColored)
    {
        floodfill(x + ASSIGN_WIDTH / 2, y + ASSIGN_HEIGHT / 2, AUX_COLOR);
        setcolor(LINE_COLOR);
        rectangle(x, y, x + ASSIGN_WIDTH, y + ASSIGN_HEIGHT);

        int textWidth = textwidth("<var> <- exp");
        int textHeight = textheight("<var> <- exp");
        outtextxy(x + (ASSIGN_WIDTH - textWidth) / 2, y + (ASSIGN_HEIGHT - textHeight) / 2, "<var> <- exp");
    }
    else
    {
        floodfill(x + ASSIGN_WIDTH / 2, y + ASSIGN_HEIGHT / 2, BLACK);
    }
}

void createDecision(int x, int y, bool isColored)
{
    int TWidth = textwidth("T");
    const int EQUAL_PART = 80;
    const int X = x + TWidth + 10;

    setColors(isColored);

    line(X + DECISION_BASE / 2, y, X + DECISION_BASE, y + EQUAL_PART);
    line(X + DECISION_BASE, y + EQUAL_PART, X, y + EQUAL_PART);
    line(X, y + EQUAL_PART, X + DECISION_BASE / 2, y);

    if (isColored)
    {
        floodfill(X + DECISION_BASE / 2, y + EQUAL_PART / 2, AUX_COLOR);
        setcolor(LINE_COLOR);
        line(X + DECISION_BASE / 2, y, X + DECISION_BASE, y + EQUAL_PART);
        line(X + DECISION_BASE, y + EQUAL_PART, X, y + EQUAL_PART);
        line(X, y + EQUAL_PART, X + DECISION_BASE / 2, y);

        int textWidth = textwidth("<var> ? <var>");
        int textHeight = textheight("<var> ? <var>");
        int FWidth = textwidth("F");

        outtextxy(X + (DECISION_BASE - textWidth)/2, y + (EQUAL_PART - textHeight)/2 + 15, "<var> ? <var>");
        outtextxy(30 + TWidth / 2, y + EQUAL_PART - 10, "T");
        outtextxy(X + DECISION_BASE + 5 + FWidth / 2, y + EQUAL_PART - 10, "F");
    }
    else
    {
        floodfill(X + DECISION_BASE / 2, y + EQUAL_PART / 2, BLACK);
    }
}

#endif // BLOCKS_H_INCLUDED

