#ifndef INTERPRETATION_H_INCLUDED
#define INTERPRETATION_H_INCLUDED

struct VarSub
{
    int value;
    char name[EXPRESSION_LENGTH];
    bool isUsed;
} VARIABLES[10];

void getVariableFromIN(node * k, char var[EXPRESSION_LENGTH], int & value)
{
    strcpy(var, k->expression);
    value=100; //implement right click to get value for IN blocks in menu
}

void getVariableFromAssign(node * k, char var[EXPRESSION_LENGTH])
{
    char s[EXPRESSION_LENGTH];
    strcpy(s, k->expression);
    char *p =strtok(s, "=");
    strcpy(var, p);
}

void getExpressionAfterEqualSign(node * k, char exp[EXPRESSION_LENGTH])
{
    char s[EXPRESSION_LENGTH];
    strcpy(s, k->expression);
    char *p =strtok(s, "=");
    p=strtok(NULL, "=");
    strcpy(exp, p);
}

void getInfix(char s[EXPRESSION_LENGTH], char infix[EXPRESSION_LENGTH][EXPRESSION_LENGTH], int & infixElements)
{
    int i=0, j=0, poz=0;
    while(s[i])
    {
        if(strchr("+-*/()", s[i]))
            infix[poz][0]=s[i], infix[poz][1]=NULL, ++poz;
        else
        {
            char var[EXPRESSION_LENGTH];
            j=0;
            while(s[i] and strchr("+-*/()", s[i])==0)
                var[j]=s[i], ++j, ++i;
            var[j]=NULL;
            strcpy(infix[poz], var);
            ++poz;
            --i;
        }
        ++i;
    }
    infixElements=poz;
}

int operatorPriority(char x, char y) // 0 for equal priority, 1 for first argument bigger priority, 2 for second argument bigger priority
{
    if(x=='+' or x=='-')
    {
        if(y=='+' or y=='-')
            return 0;
        if(y=='*' or y=='/')
            return 2;
    }
    if(x=='*' or x=='/')
    {
        if(y=='+' or y=='-')
            return 1;
        if(y=='*' or y=='/')
            return 0;
    }
}

void infixToPostfix(char infix[EXPRESSION_LENGTH][EXPRESSION_LENGTH], char postfix[EXPRESSION_LENGTH][EXPRESSION_LENGTH], int & infixElements, int & postfixElements)
{
    char stackS[EXPRESSION_LENGTH]= {' '};
    int i=0, poz=0, j=-1;
    while(infixElements>i)
    {
        if(strchr("+-*/()", infix[i][0])==0)
            strcpy(postfix[poz], infix[i]), ++poz;
        else if(infix[i][0]==')')
        {
            while(j>=0 and stackS[j]!='(')
            {
                postfix[poz][0]=stackS[j];
                postfix[poz][1]=NULL;
                stackS[j]=' ';
                ++poz;
                --j;
            }
            stackS[j]=' ';
            --j;
        }
        else
        {
            while(j>=0 and stackS[j]!='(' and operatorPriority(stackS[j], infix[i][0])<=1)
            {
                postfix[poz][0]=stackS[j];
                postfix[poz][1]=NULL;
                stackS[j]=' ';
                --j;
                ++poz;
            }
            ++j;
            stackS[j]=infix[i][0];
        }
        ++i;
    }
    while(j>=0)
    {
        postfix[poz][0]=stackS[j];
        postfix[poz][1]=NULL;
        stackS[j]=' ';
        ++poz;
        --j;
    }
    postfixElements=poz;
}

bool isInt(char x[EXPRESSION_LENGTH])
{
    if(x[0]=='0' and x[1]==NULL)
        return 1;
    int i=0;
    if(strchr("123456789-", x[0])==0)
        return 0;
    ++i;
    while(x[i])
    {
        if(strchr("1234567890", x[i])==0)
            return 0;
        ++i;
    }
    return 1;
}

void convertStringToInt(char op1[EXPRESSION_LENGTH], int & value1)
{
    int negative=1, i=0;
    value1=0;
    if(op1[0]=='-')
        negative=-1, i=1;
    while(op1[i])
    {
        value1=value1*10+op1[i]-48;
        ++i;
    }
    value1=value1*negative;
}

int getVariablePosition(char var[EXPRESSION_LENGTH], int & state)//state=0 no more places, state=1 found, state=2  not found but can be put on pozition poz
{
    int sum=0;
    for(int i=0; i<=10; ++i)
    {
        if(strcmp(VARIABLES[i].name, var)==0)
        {
            state=1;
            return i;
        }
        sum+=VARIABLES[i].isUsed;
    }
    if(sum==10)
    {
        state=0;
        return -1;
    }
    for(int i=0; i<=10; ++i)
    {
        if(VARIABLES[i].isUsed==0)
        {
            state=2;
            return i;
        }
    }
}

int calculateResult(int a, int b, char operand)
{
    if(operand=='+')
        return a+b;
    if(operand=='-')
        return b-a;
    if(operand=='*')
        return a*b;
    if(operand=='/')
        return b/a;
}

void convertIntToString(int a, char s[EXPRESSION_LENGTH])
{
    int i=0, nrDigits=0;
    char aux[EXPRESSION_LENGTH];
    if(a<0)
        s[0]='-', ++i, a=a*(-1);
    while(a)
    {
        aux[nrDigits]=(a%10)+48;
        ++nrDigits;
        a=a/10;
    }
    i=i+nrDigits-1;
    for(int j=0; j<nrDigits; ++j)
        s[i]=aux[j], --i;
    if(s[0]=='-')
        s[nrDigits+1]=NULL;
    else
        s[nrDigits]=NULL;
}

void evaluate(char postfix[EXPRESSION_LENGTH][EXPRESSION_LENGTH], int & postfixElements, int & value)
{
    char stackS[EXPRESSION_LENGTH][EXPRESSION_LENGTH];
    int j=0;
    for(int i=0; i<postfixElements; ++i)
    {
        if(strchr("+-*/()", postfix[i][0])==0)
        {
            strcpy(stackS[j], postfix[i]);
            ++j;
        }
        else
        {
            char op1[EXPRESSION_LENGTH], op2[EXPRESSION_LENGTH], textResult[EXPRESSION_LENGTH];
            int poz1=0, poz2=0, state1=0, state2=0, result=0, value1=0, value2=0;

            strcpy(op1, stackS[j-1]);
            strcpy(op2, stackS[j-2]);
            if(isInt(op1))
                convertStringToInt(op1, value1);
            else
            {
                poz1=getVariablePosition(op1, state1);
                if(state1==0 or state1==2)
                    cout<<"There are variables in this expression that are not defined!!!!!!!!1"; // continue code for menu
                else
                    value1=VARIABLES[poz1].value;
            }
            if(isInt(op2))
                convertStringToInt(op2, value2);
            else
            {
                poz2=getVariablePosition(op2, state2);
                if(state2==0 or state2==2)
                    cout<<"There are variables in this expression that are not defined!!!!!!!!"; // continue code for menu
                value2=VARIABLES[poz2].value;
            }
            result=calculateResult(value1, value2, postfix[i][0]);
            convertIntToString(result, textResult);
            strcpy(stackS[j-2], textResult);
            j=j-1;
        }
    }
    if(isInt(stackS[0]))
        convertStringToInt(stackS[0], value);
    else
    {
        int poz1=0, state1=0;
        poz1=getVariablePosition(stackS[0], state1);
        if(state1==0 or state1==2)
            cout<<"There are variables in this expression that are not defined!!!!!!!!"; // continue code for menu
        else
            value=VARIABLES[poz1].value;
    }
}

void makeZeroFirst(char infix[EXPRESSION_LENGTH][EXPRESSION_LENGTH], int & infixElements)
{
    for(int i=infixElements-1; i>=0; --i)
    {
        strcpy(infix[i+1], infix[i]);
    }
    infix[0][0]='0';
    infix[0][1]=NULL;
    ++infixElements;
}

void getExpressionValue(char exp[EXPRESSION_LENGTH], int & value)
{
    char s[EXPRESSION_LENGTH], infix[EXPRESSION_LENGTH][EXPRESSION_LENGTH],  postfix[EXPRESSION_LENGTH][EXPRESSION_LENGTH];
    int infixElements=0, postfixElements=0;
    strcpy(s, exp);
    getInfix(s, infix, infixElements);
    if(infix[0][0]=='+' or infix[0][0]=='-')
        makeZeroFirst(infix, infixElements);
    infixToPostfix(infix, postfix, infixElements, postfixElements);
    evaluate(postfix, postfixElements, value);
}

void getVariableFromOut(node * k, char var[EXPRESSION_LENGTH])
{
    strcpy(var, k->expression);
}

void getFirstExpresionFromCondition(node * k, char exp1[EXPRESSION_LENGTH])
{
    char s[EXPRESSION_LENGTH];
    strcpy(s, k->expression);
    char * p=strtok(s, "=<>");
    strcpy(exp1, p);
}
void getSecondExpressionFromCondition(node * k, char exp2[EXPRESSION_LENGTH])
{
    char s[EXPRESSION_LENGTH];
    strcpy(s, k->expression);
    char * p=strtok(s, "=<>");
    p=strtok(NULL, "=<>");
    strcpy(exp2, p);
}

void getRelationOperator(node * k, char oper[3])
{
    char s[EXPRESSION_LENGTH], c[EXPRESSION_LENGTH];
    strcpy(s, k->expression);
    if(strchr(s, '!'))
    {
        oper[0]='!';
        oper[1]='=';
        oper[2]=NULL;
        return;
    }
    if(strchr(s, '<'))
    {
        if(strchr(s, '='))
        {
            oper[0]='<';
            oper[1]='=';
            oper[2]=NULL;
            return;
        }
        else
        {
            oper[0]='<';
            oper[1]=NULL;
            return;
        }
    }
    if(strchr(s, '>'))
    {
        if(strchr(s, '='))
        {
            oper[0]='>';
            oper[1]='=';
            oper[2]=NULL;
            return;
        }
        else
        {
            oper[0]='>';
            oper[1]=NULL;
            return;
        }
    }
    if(strstr(s, "=="))
    {
        oper[0]='=';
        oper[1]='=';
        oper[2]=NULL;
        return;
    }
}

bool conditionIsMet(int a, int b, char oper[3])
{
    if(oper[0]=='!')
    {
        if(a!=b)
            return 1;
        return 0;
    }
    if(oper[0]=='>' and oper[1]=='=')
    {
        if(a>=b)
            return 1;
        return 0;
    }
    if(oper[0]=='<' and oper[1]=='=')
    {
        if(a<=b)
            return 1;
        return 0;
    }
    if(oper[0]=='=' and oper[1]=='=')
    {
        if(a==b)
            return 1;
        return 0;
    }
    if(oper[0]=='<')
    {
        if(a<b)
            return 1;
        return 0;
    }
    if(oper[0]=='>')
    {
        if(a>b)
            return 1;
        return 0;
    }
}

void analyzeScheme(node * k)
{
    bool isCorrect=1;
    isSchemeCorrect(START, isCorrect);
    if(isCorrect==0)
        return;
    restoreViz(START);
    if(k==START)
        analyzeScheme(k->next);
    else if(strcmp(k->type, "IN")==0)
    {
        int state=0, value=0;
        char var[EXPRESSION_LENGTH];
        int poz=0;

        getVariableFromIN(k, var, value);
        poz=getVariablePosition(var, state);
        if(state==0)
            cout<<"No more places for new variables!!!!!"; //continue code for menu
        else
        {
            VARIABLES[poz].value=value;
            strcpy(VARIABLES[poz].name, var);
            VARIABLES[poz].isUsed=1;
        }
        analyzeScheme(k->next);
    }
    else if(strcmp(k->type, "OUT")==0)
    {
        int state=0;
        char var[EXPRESSION_LENGTH];
        int poz=0;

        getVariableFromOut(k, var);
        poz=getVariablePosition(var, state);
        if(state==0 or state==2)
            cout<<"Variable not known!!!!!";   //continue code for menu
        else
        {
            cout<<VARIABLES[poz].name<<"="<<VARIABLES[poz].value<<' ';   //implement procedure for menu
        }
        analyzeScheme(k->next);
    }
    else if(strcmp(k->type, "STOP")==0)
        cout<<"End of algorithm :)";
    else if(strcmp(k->type, "ASSIGN")==0)
    {
        char var[EXPRESSION_LENGTH];
        int state=0, poz=0;

        getVariableFromAssign(k, var);
        poz=getVariablePosition(var, state);
        if(state==0)
            cout<<"No more places for this new variable!!!"; //continue code for menu
        else
        {
            int value=0;
            char exp[EXPRESSION_LENGTH];
            getExpressionAfterEqualSign(k, exp);
            getExpressionValue(exp, value);
            VARIABLES[poz].value=value;
            VARIABLES[poz].isUsed=1;
        }
        analyzeScheme(k->next);
    }
    else if(strcmp(k->type, "DECISION")==0)
    {
        char exp1[EXPRESSION_LENGTH], exp2[EXPRESSION_LENGTH], oper[3];
        int value1=0, value2=0;

        getFirstExpresionFromCondition(k, exp1);
        getSecondExpressionFromCondition(k, exp2);
        getRelationOperator(k, oper);
        getExpressionValue(exp1, value1);
        getExpressionValue(exp2, value2);
        if(conditionIsMet(value1, value2, oper))
            analyzeScheme(k->next);
        else
            analyzeScheme(k->nextElse);
    }
}

#endif // INTERPRETATION_H_INCLUDED
