#ifndef BLOCKS_H_INCLUDED
#define BLOCKS_H_INCLUDED

#define POINTS 15
#define RADIUS 15
#define CIRCLE_RADIUS 6
#define COLOR GREEN
#define x 30
void createRoundedRect(int width, int height, int y)
{
    setlinestyle(0, 0, 3);
	float X=0,Y=0;
	int i = 0;
	float points[2][4*POINTS];
	for(; i<POINTS; i++)
	{
		X += RADIUS/POINTS;
		Y = sqrt(RADIUS*RADIUS-X*X);
		points[0][i] = X+x+width-RADIUS;
		points[1][i] = y-Y+RADIUS;
	}
	Y=0;
	for(; i<POINTS*2; i++)
	{
		Y += RADIUS/POINTS;
		X = sqrt(RADIUS*RADIUS-Y*Y);
		points[0][i] = x+width+X-RADIUS;
		points[1][i] = y+height-RADIUS+Y;
	}
	X=0;
	for(; i<POINTS*3; i++)
	{
		X += RADIUS/POINTS;
		Y = sqrt(RADIUS*RADIUS-X*X);
		points[0][i] = x+RADIUS-X;
		points[1][i] = y+height-RADIUS+Y;
	}
	Y=0;
	for(; i < POINTS*4; i++)
	{
		Y += RADIUS/POINTS;
		X = sqrt(RADIUS*RADIUS-Y*Y);
		points[0][i] = x-X+RADIUS;
		points[1][i] = y+RADIUS-Y;
	}
	for (i = 0; i < POINTS*4-1; i++)
        line(points[0][i], points[1][i], points[0][i+1], points[1][i+1]);
    line(points[0][POINTS*4-1], points[1][POINTS*4-1], points[0][0], points[1][0]);
    setfillstyle(SOLID_FILL, COLOR);
    floodfill(x+width/2, y+height/2, WHITE);
}

void createStart()
{
    const int width = 150;
    const int height = 70;
    const int y = 30;
    createRoundedRect(width, height, y);
    int textWidth = textwidth("Start");
    int textHeight = textheight("Start");
    outtextxy(x+(width-textWidth)/2, y+(height-textHeight)/2 - 5, "Start");
    circle(x+width/2, y+height-CIRCLE_RADIUS, CIRCLE_RADIUS);
}

void createStop()
{
    const int width = 150;
    const int height = 70;
    const int y = 130;
    createRoundedRect(width, height, y);
    int textWidth = textwidth("Stop");
    int textHeight = textheight("Stop");
    outtextxy(x + (width-textWidth)/2, y + (height-textHeight)/2, "Stop");
}
void createIn()
{
    setlinestyle(0, 0, 3);
    const int y = 230;
    const int smallPart = 30;
    const int bigPart = 120;
    const int lateralPart = 50;
	line(x, y, x+bigPart, y);
	line(x+bigPart, y, x+bigPart-smallPart, y+lateralPart);
	line(x+bigPart-smallPart, y+lateralPart, x+smallPart, y+lateralPart);
	line(x+smallPart, y+lateralPart, x, y);
	setfillstyle(SOLID_FILL, COLOR);
    floodfill(x+bigPart/2, y+lateralPart/2, WHITE);
    int textWidth = textwidth("<var>");
    int textHeight = textheight("<var>");
    outtextxy(x + (bigPart-textWidth)/2, y + (lateralPart-textHeight)/2, "<var>");
    circle(x+bigPart/2, y+lateralPart-CIRCLE_RADIUS, CIRCLE_RADIUS);
}

void createOut()
{
    setlinestyle(0, 0, 3);
    const int y = 310;
    const int smallPart = 30;
    const int bigPart = 120;
    const int lateralPart = 50;
	line(x+smallPart, y, x+bigPart-smallPart, y);
	line(x+bigPart-smallPart, y, x+bigPart, y+lateralPart);
	line(x+bigPart, y+lateralPart, x, y+lateralPart);
	line(x, y+lateralPart, x+smallPart, y);
	setfillstyle(SOLID_FILL, COLOR);
    floodfill(x+bigPart/2, y+lateralPart/2, WHITE);
    int textWidth = textwidth("<var>");
    int textHeight = textheight("<var>");
    outtextxy(x + (bigPart-textWidth)/2, y + (lateralPart-textHeight)/2, "<var>");
    circle(x+bigPart/2, y+lateralPart-CIRCLE_RADIUS, CIRCLE_RADIUS);
}

void createAssign()
{
    const int width = 200;
    const int height = 60;
    const int y = 390;
    rectangle(x, y, x+width, y+height);
    setfillstyle(SOLID_FILL, COLOR);
    floodfill(x+width/2, y+height/2, WHITE);
    int textWidth = textwidth("<var> <- exp");
    int textHeight = textheight("<var> <- exp");
    outtextxy(x + (width-textWidth)/2, y + (height - textHeight)/2, "<var> <- exp");
    circle(x+width/2, y+height-CIRCLE_RADIUS, CIRCLE_RADIUS);
}

void createDecision()
{
    int TWidth = textwidth("T");
    const int equalPart = 80;
    const int base = 150;
    const int X = x + CIRCLE_RADIUS*2 + TWidth + 15;
    const int y = 480;
    line(X+base/2, y, X+base, y+equalPart);
    line(X+base, y+equalPart, X, y+equalPart);
    line(X, y+equalPart, X+base/2, y);
    setfillstyle(SOLID_FILL, COLOR);
    floodfill(X+base/2, y+equalPart/2, WHITE);
    int textWidth = textwidth("<var> ? <var>");
    int textHeight = textheight("<var> ? <var>");
    int FWidth = textwidth("F");
    outtextxy(X + (base-textWidth)/2, y + (equalPart - textHeight)/2 + 15, "<var> ? <var>");
    outtextxy(30+TWidth/2, y + equalPart - 10, "T");
    outtextxy(X+base+CIRCLE_RADIUS*2+5+FWidth/2, y + equalPart - 10, "F");
    circle(X-CIRCLE_RADIUS, y+equalPart-CIRCLE_RADIUS/2, CIRCLE_RADIUS);
    circle(X+base+CIRCLE_RADIUS, y+equalPart-CIRCLE_RADIUS/2, CIRCLE_RADIUS);
}

#endif // BLOCKS_H_INCLUDED

