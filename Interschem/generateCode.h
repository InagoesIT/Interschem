#ifndef GENERATECODE_H_INCLUDED
#define GENERATECODE_H_INCLUDED

#include "menu.h"

#define TEXT_X WINDOWX - OUTPUT_SIZE_X + 30
#define OUTPUT_MIDDLE_X OUTPUT_SIZE_X/2 + (WINDOWX - OUTPUT_SIZE_X)
#define OUTPUT_MIDDLE_Y (WINDOWY - MENUY) / 2 + MENUY
#define LINE_SPACE 25
#define TAB_SIZE textwidth("    ")

void getVariableFromAssign(node *k, char var[EXPRESSION_LENGTH]);
void drawGenCodeButton();

struct declaredVars
{
    char name[10][EXPRESSION_LENGTH];
    int newElemIndex = 0;

}DECLARED_VARS;

void clearOutput()
{
    if(babab==1)
        babab=1;
    setcolor(THEME[CURRENT_THEME].button_clr);
    line(WINDOWX-tileX, MENUY, WINDOWX, MENUY);
    setfillstyle(SOLID_FILL, THEME[CURRENT_THEME].bck_clr);
    floodfill(WINDOWX-5, WINDOWY-5, THEME[CURRENT_THEME].button_clr);
    drawGenCodeButton();
}

void writeWhile(char condition[EXPRESSION_LENGTH], int &y, int level)
{
    char text[EXPRESSION_LENGTH + 20] = "";
    strcat(text, "while (");
    strcat(text, condition);
    strcat(text, ")");
    int x = TEXT_X;
    if (level)
        x = TEXT_X + TAB_SIZE * level;
    outtextxy(x, y += LINE_SPACE, text);
    outtextxy(x, y += LINE_SPACE, "{");
}

void writeIf(char condition[EXPRESSION_LENGTH], int &y, int level)
{
    char text[EXPRESSION_LENGTH + 20] = "";
    strcat(text, "if (");
    strcat(text, condition);
    strcat(text, ")");
    int x = TEXT_X;
    if (level)
        x = TEXT_X + TAB_SIZE * level;
    outtextxy(x, y += LINE_SPACE, text);
    outtextxy(x, y += LINE_SPACE, "{");
}

void writeElse(int &y, int level)
{
    int x = TEXT_X;
    if (level)
        x = TEXT_X + TAB_SIZE * level;
    outtextxy(x, y += LINE_SPACE, "else");
    outtextxy(x, y += LINE_SPACE, "{");
}

void writeEnd(int &y)
{
    outtextxy(TEXT_X + TAB_SIZE, y += LINE_SPACE, "return 0;");
    outtextxy(TEXT_X, y += LINE_SPACE, "}");
}

void writeIn(char expression[EXPRESSION_LENGTH], int &y, int level)
{
    char text[EXPRESSION_LENGTH + 1] = "";
    strcpy(text, "cin >> ");
    strcat(text, expression);
    text[strlen(text)] = ';';
    int x = TEXT_X;
    if (level)
        x = TEXT_X + TAB_SIZE * level;
    outtextxy(x, y += LINE_SPACE, text);
}

void writeOut(char expression[EXPRESSION_LENGTH], int &y, int level)
{
    char text[EXPRESSION_LENGTH + 1] = "";
    strcpy(text, "cout << ");
    strcat(text, expression);
    text[strlen(text)] = ';';
    int x = TEXT_X;
    if (level)
        x = TEXT_X + TAB_SIZE * level;
    outtextxy(x, y += LINE_SPACE, text);
}

void writeAssign(char expression[EXPRESSION_LENGTH], int &y, int level)
{
    char text[EXPRESSION_LENGTH + 1] = "";
    char expAux[EXPRESSION_LENGTH] = "";
    strcpy(expAux, expression);
    char *token = strtok(expAux, "=");
    strcpy(text, token);
    strcat(text, " = ");
    token = strtok(NULL, "=");
    strcat(text, token);
    text[strlen(text)] = ';';
    int x = TEXT_X;
    if (level)
        x = TEXT_X + TAB_SIZE * level;
    outtextxy(x, y += LINE_SPACE, text);
}

void writeStart(int &y)
{
    outtextxy(TEXT_X, y, "#include <iostream>");
    outtextxy(TEXT_X, y += LINE_SPACE, "using namespace std;");
    outtextxy(TEXT_X, y += LINE_SPACE, "int main( )"); // ( )
    outtextxy(TEXT_X, y += LINE_SPACE, "{");
}

void writeInstruction(node *head, int &y, int level)
{
    if (strcmp(head->type, "IN") == 0)
        writeIn(head->expression, y, level);
    else if (strcmp(head->type, "OUT") == 0)
        writeOut(head->expression, y, level);
    else if (strcmp(head->type, "ASSIGN") == 0)
        writeAssign(head->expression, y, level);
}

void reinitializeVarArr()
{
    if (DECLARED_VARS.newElemIndex != 0)
        for (int i = 0; i < DECLARED_VARS.newElemIndex; i++)
            if (strlen(DECLARED_VARS.name[i]))
                strcpy(DECLARED_VARS.name[i], "");
}

bool varIsNew(char var[EXPRESSION_LENGTH])
{
    for (int i = 0; i < DECLARED_VARS.newElemIndex; i++)
        if (!strcmp(DECLARED_VARS.name[i], var))
            return false;
    return true;
}

void addVarToArr(char var[EXPRESSION_LENGTH])
{
    strcpy(DECLARED_VARS.name[DECLARED_VARS.newElemIndex], var);
    DECLARED_VARS.newElemIndex++;
}

void declareUsedVars(node *head, char text[EXPRESSION_LENGTH])
{
    if (head && !head->viz)
    {
        if (!strcmp(head->type, "IN") || !strcmp(head->type, "ASSIGN"))
        {
            char var[EXPRESSION_LENGTH] = "";

            if (!strcmp(head->type, "ASSIGN"))
                getVariableFromAssign(head, var);
            else
                strcpy(var, head->expression);
            if (varIsNew(var))
            {
                addVarToArr(var);
                if (strlen(text) != 4) // 4 -- strlen("int ")
                    strcat(text, ", ");
                strcat(text, var);
            }
        }
        head->viz = 1;
        declareUsedVars(head->next, text);
        if (head->isDecision)
            declareUsedVars(head->nextElse, text);
    }
}

void determineDecisionType(node *head, int &y, bool &isWhile)
{
    node *aux = head->next;
    while (strcmp(aux->type, "STOP"))
    {
        if (aux->next == head)
        {
            isWhile = 1;
            break;
        }
        if (!aux->isDecision)
            aux = aux->next;
        else if (strcmp(aux->nextElse->type, "STOP"))
        {
            if (aux->nextElse == head)
            {
                isWhile = 1;
                break;
            }
            else
                aux = aux->nextElse;
        }
        else
            break;
    }
}

void parseScheme(node *head, int &y, int &level)
{
    if (head && !head->viz && strcmp(head->type, "STOP"))
    {
        head->viz = 1;
        if (!head->isDecision)
        {
            writeInstruction(head, y, level);
            parseScheme(head->next, y, level);
        }
        else
        {
             bool isWhile = 0;
             determineDecisionType(head, y, isWhile);

             if (isWhile)
                writeWhile(head->expression, y, level);
            else
                writeIf(head->expression, y, level);

             if (isWhile)
             {
                 parseScheme(head->next, y, ++level);
                 outtextxy(TEXT_X + TAB_SIZE * --level, y += LINE_SPACE, "}");
                 parseScheme(head->nextElse, y, level);
             }
             else
             {
                 parseScheme(head->next, y, ++level); // if
                 outtextxy(TEXT_X + TAB_SIZE * --level, y += LINE_SPACE, "}");
                 if (strcmp(head->nextElse->type, "STOP") || head->nextElse->viz)
                 {
                    writeElse(y, level);
                    parseScheme(head->nextElse, y, ++level);
                    outtextxy(TEXT_X + TAB_SIZE * --level, y += LINE_SPACE, "}");
                 }
             }
        }
    }
}

void generateCode(bool &isGenCode)
{
    restoreVariables();
    bool isCorrect = 1;
    isSchemeCorrect(START, isCorrect);
    if (isCorrect and isFreeNull() and isRestsNull())
    {
        int level = 1;
        isGenCode = 1;
        int y = MENUY + sizeGenCodeY + 30;
        char varText[EXPRESSION_LENGTH * 2] = "int ";
        clearOutput();
        reinitializeVarArr();
        writeStart(y);

        reinitializeAllViz();
        declareUsedVars(START->next, varText);
        reinitializeAllViz();
        if (strlen(varText) != 4)
        {
            strcat(varText, ";");
            outtextxy(TEXT_X + TAB_SIZE, y += LINE_SPACE, varText);
        }

        parseScheme(START, y, level);
        writeEnd(y);
        babab=1;
    }
    else
    {
        isGenCode = 0;
        popUpMessage("The scheme isn't correct and cannot be generated!");
    }
}

#endif // GENERATECODE_H_INCLUDED
