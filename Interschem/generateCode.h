#ifndef GENERATECODE_H_INCLUDED
#define GENERATECODE_H_INCLUDED

#include "menu.h"

#define TEXT_X WINDOWX - OUTPUT_SIZE_X + 30
#define OUTPUT_MIDDLE_X WINDOWX - OUTPUT_SIZE_X / 2
#define OUTPUT_MIDDLE_Y (WINDOWY - MENUY) / 2 + MENUY
#define LINE_SPACE 25

struct declaredVars
{
    char name[10][EXPRESSION_LENGTH];
    int newElemIndex = 0;

}DECLARED_VARS;

void clearOutput()
{
    setfillstyle(SOLID_FILL, THEME[CURRENT_THEME].bck_clr);
    floodfill(OUTPUT_MIDDLE_X, OUTPUT_MIDDLE_Y, THEME[CURRENT_THEME].button_clr);
    drawGenCodeButton();
}

void writeWhile(char condition[EXPRESSION_LENGTH], int &y)
{
    char text[EXPRESSION_LENGTH + 20] = "";
    strcat(text, "while (");
    strcat(text, condition);
    strcat(text, ")");
    outtextxy(TEXT_X, y += LINE_SPACE, text);
    outtextxy(TEXT_X, y += LINE_SPACE, "{");
}

void writeIf(char condition[EXPRESSION_LENGTH], int &y)
{
    char text[EXPRESSION_LENGTH + 20] = "";
    strcat(text, "if (");
    strcat(text, condition);
    strcat(text, ")");
    outtextxy(TEXT_X, y += LINE_SPACE, text);
    outtextxy(TEXT_X, y += LINE_SPACE, "{");
}

void writeElse(int &y)
{
    outtextxy(TEXT_X, y += LINE_SPACE, "else");
    outtextxy(TEXT_X, y += LINE_SPACE, "{");
}

void writeEnd(int &y)
{
    outtextxy(TEXT_X, y += LINE_SPACE, "return 0;");
    outtextxy(TEXT_X, y += LINE_SPACE, "}");
}

void writeIn(char expression[EXPRESSION_LENGTH], int &y)
{
    char text[EXPRESSION_LENGTH + 1] = "";
    strcpy(text, "cin >> ");
    strcat(text, expression);
    text[strlen(text)] = ';';
    outtextxy(TEXT_X, y += LINE_SPACE, text);
}

void writeOut(char expression[EXPRESSION_LENGTH], int &y)
{
    char text[EXPRESSION_LENGTH + 1] = "";
    strcpy(text, "cout << ");
    strcat(text, expression);
    text[strlen(text)] = ';';
    outtextxy(TEXT_X, y += LINE_SPACE, text);
}

void writeAssign(char expression[EXPRESSION_LENGTH], int &y)
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
    outtextxy(TEXT_X, y += LINE_SPACE, text);
}

void writeStart(int &y)
{
    outtextxy(TEXT_X, y, "#include <iostream>");
    outtextxy(TEXT_X, y += LINE_SPACE, "using namespace std;");
    outtextxy(TEXT_X, y += LINE_SPACE, "int main( )"); // ( )
    outtextxy(TEXT_X, y += LINE_SPACE, "{");
}

void writeInstruction(node *head, int &y)
{
    if (strcmp(head->type, "IN") == 0)
        writeIn(head->expression, y);
    else if (strcmp(head->type, "OUT") == 0)
        writeOut(head->expression, y);
    else if (strcmp(head->type, "ASSIGN") == 0)
        writeAssign(head->expression, y);
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


void parseScheme(node *head, int &y)
{
    if (head && !head->viz && strcmp(head->type, "STOP"))
    {
        head->viz = 1;
        if (!head->isDecision)
        {
            writeInstruction(head, y);
            parseScheme(head->next, y);
        }
        else
        {
             bool isWhile = 0;
             determineDecisionType(head, y, isWhile);

             if (isWhile)
                writeWhile(head->expression, y);
            else
                writeIf(head->expression, y);

             if (isWhile)
             {
                 parseScheme(head->next, y);
                 outtextxy(TEXT_X, y += LINE_SPACE, "}");
                 parseScheme(head->nextElse, y);
             }
             else
             {
                 parseScheme(head->next, y);
                 outtextxy(TEXT_X, y += LINE_SPACE, "}");
                 if (strcmp(head->nextElse->type, "STOP") || head->nextElse->viz)
                 {
                    writeElse(y);
                    parseScheme(head->nextElse, y);
                    outtextxy(TEXT_X, y += LINE_SPACE, "}");
                 }
             }
        }
    }
}

void generateCode()
{
    if (START->wasCreated) // put isSchemeCorrect
    {
        int y = MENUY + sizeGenCodeY + 30;
        int isFor = 0;
        bool isWhile = 0;
        char varText[EXPRESSION_LENGTH * 2] = "int ";
        clearOutput();
        reinitializeVarArr();
        writeStart(y);

        reinitializeAllViz();
        declareUsedVars(START->next, varText);
        reinitializeAllViz();
        strcat(varText, ";");
        outtextxy(TEXT_X, y += LINE_SPACE, varText);

        parseScheme(START, y);
        writeEnd(y);
    }
    else
        showerrorbox("The scheme isn't correct!");
}

#endif // GENERATECODE_H_INCLUDED
