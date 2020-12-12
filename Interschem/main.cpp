#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <cmath>
#include "blocks.h"

int main()
{
  initwindow(800,600);
  createStart();
  createStop();
  createIn();
  createOut();
  createAssign();
  createDecision();
  getch();
  closegraph();
  return 0;
}
