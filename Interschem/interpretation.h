#ifndef INTERPRETATION_H_INCLUDED
#define INTERPRETATION_H_INCLUDED

void convertStringToInt(char op1[EXPRESSION_LENGTH], int & value1);
void refresh();

void getVariableFromIn(node * k, char var[EXPRESSION_LENGTH], int & value)
{
    strcpy(var, k->expression);
    value=100;
    int textboxWidth=500, textboxHeight=100;
    setcolor(RED);
    line(WINDOWX/2-textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2-textboxWidth/2, WINDOWY/2+textboxHeight/2);
    line(WINDOWX/2-textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2+textboxWidth/2, WINDOWY/2-textboxHeight/2);
    line(WINDOWX/2+textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2+textboxWidth/2, WINDOWY/2+textboxHeight/2);
    line(WINDOWX/2+textboxWidth/2, WINDOWY/2+textboxHeight/2, WINDOWX/2-textboxWidth/2, WINDOWY/2+textboxHeight/2);

    setfillstyle(SOLID_FILL, LIGHTBLUE);
    floodfill(WINDOWX/2, WINDOWY/2, RED);

    setcolor(WHITE);
    line(WINDOWX/2-textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2-textboxWidth/2, WINDOWY/2+textboxHeight/2);
    line(WINDOWX/2-textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2+textboxWidth/2, WINDOWY/2-textboxHeight/2);
    line(WINDOWX/2+textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2+textboxWidth/2, WINDOWY/2+textboxHeight/2);
    line(WINDOWX/2+textboxWidth/2, WINDOWY/2+textboxHeight/2, WINDOWX/2-textboxWidth/2, WINDOWY/2+textboxHeight/2);

    line(WINDOWX/2-textboxWidth/2, WINDOWY/2, WINDOWX/2+textboxWidth/2, WINDOWY/2);

    outtextxy(WINDOWX/2-textwidth("Insert input value")/2, WINDOWY/2-textheight("Insert input value")/2-textboxHeight/4, "Insert input value");

    bool finished=0;
    char cc[EXPRESSION_LENGTH] = "";
    int i=strlen(cc);
    do
    {
        char c=getch();
        if(c==32) //space
            finished=1;
        else
        {
            if(c==8) //backspace
            {
                if(strlen(cc)>=1)
                {
                    cc[strlen(cc)-1]=NULL;
                    --i;
                }
            }
            else
            {
                cc[i]=c;
                ++i;
                cc[i]=NULL;
            }
            setcolor(RED);
            line(WINDOWX/2-textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2-textboxWidth/2, WINDOWY/2+textboxHeight/2);
            line(WINDOWX/2-textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2+textboxWidth/2, WINDOWY/2-textboxHeight/2);
            line(WINDOWX/2+textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2+textboxWidth/2, WINDOWY/2+textboxHeight/2);
            line(WINDOWX/2+textboxWidth/2, WINDOWY/2+textboxHeight/2, WINDOWX/2-textboxWidth/2, WINDOWY/2+textboxHeight/2);

            setfillstyle(SOLID_FILL, LIGHTBLUE);
            floodfill(WINDOWX/2, WINDOWY/2, RED);

            setcolor(WHITE);
            line(WINDOWX/2-textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2-textboxWidth/2, WINDOWY/2+textboxHeight/2);
            line(WINDOWX/2-textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2+textboxWidth/2, WINDOWY/2-textboxHeight/2);
            line(WINDOWX/2+textboxWidth/2, WINDOWY/2-textboxHeight/2, WINDOWX/2+textboxWidth/2, WINDOWY/2+textboxHeight/2);
            line(WINDOWX/2+textboxWidth/2, WINDOWY/2+textboxHeight/2, WINDOWX/2-textboxWidth/2, WINDOWY/2+textboxHeight/2);

            line(WINDOWX/2-textboxWidth/2, WINDOWY/2, WINDOWX/2+textboxWidth/2, WINDOWY/2);

            outtextxy(WINDOWX/2-textwidth("Insert input value")/2, WINDOWY/2-textheight("Insert input value")/2-textboxHeight/4, "Insert input value");
            outtextxy(WINDOWX/2-textwidth(cc)/2, WINDOWY/2-textheight(cc)/2+textboxHeight/4, cc);
        }
    }
    while(finished==0 and i<EXPRESSION_LENGTH-2);
    convertStringToInt(cc, value);
    refresh();
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
    for(int i=0; i<10; ++i)
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
    for(int i=0; i<10; ++i)
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
                    cout<<"There are variables in this expression that are not defined!!!!!!!!"; // continue code for menu
                else
                    value1=VARIABLES[poz1].value;
            }
            if(isInt(op2))
                convertStringToInt(op2, value2);
            else
            {
                poz2=getVariablePosition(op2, state2);
                if(state2==0 or state2==2)
                    cout<<"There are variables in this expression that are not defined!!!!!!!!!"; // continue code for menu
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
void getSecondExpressionFromCondition(node * k, char exp2[EXPRESSION_LENGTH], bool & notCorrect)
{
    notCorrect=0;
    char s[EXPRESSION_LENGTH];
    strcpy(s, k->expression);
    char * p=strtok(s, "!=<>");
    p=strtok(NULL, "!=<>");
    if(p)
        strcpy(exp2, p);
    else
        notCorrect=1;
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
    reinitializeAllViz();
    if(k==START)
        analyzeScheme(k->next);
    else if(strcmp(k->type, "IN")==0)
    {
        int state=0, value=0;
        char var[EXPRESSION_LENGTH];
        int poz=0;

        getVariableFromIn(k, var, value); // implement popup
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
        bool notCorrect=0;

        getFirstExpresionFromCondition(k, exp1);
        getSecondExpressionFromCondition(k, exp2, notCorrect);
        getRelationOperator(k, oper);
        getExpressionValue(exp1, value1);
        getExpressionValue(exp2, value2);
        if(conditionIsMet(value1, value2, oper))
            analyzeScheme(k->next);
        else
            analyzeScheme(k->nextElse);
    }
}


bool isLetter(char x)
{
    if((x>=65 and x<=90) or (x>=97 and x<=122))
        return 1;
    return 0;
}

bool isLetterOrDigit(char x)
{
    if((x>=65 and x<=90) or (x>=97 and x<=122) or (x>=48 and x<=57))
        return 1;
    return 0;
}

bool variableNameCorrect(char exp[EXPRESSION_LENGTH])
{
    if(!isLetter(exp[0]))
        return 0;
    for(int i=0; exp[i]; ++i)
        if(!isLetterOrDigit(exp[i]))
            return 0;
    return 1;
}

bool isADigit(char x)
{
    if(strchr("0123456789", x))
        return 1;
    return 0;
}

bool numberCorrect(char exp[EXPRESSION_LENGTH])
{
    for(int i=0; exp[i]; ++i)
        if(!isADigit(exp[i]))
            return 0;
    return 1;
}

bool isSymbol(char x)
{
    if(strchr("()*+-/", x))
        return 1;
    return 0;
}

bool variablePlacedCorrect(int i, char infix[EXPRESSION_LENGTH][EXPRESSION_LENGTH], int lgInfix)
{
    if(i==0)
        return 1;
    if(isADigit(infix[i-1][0]))
        return 0;
    return 1;
}

bool isSymbolNextToSymbolOk(char x, char y)
{
    if(x=='+' and y=='(')
        return 1;
    if(x=='-' and y=='(')
        return 1;
    if(x=='*' and (y=='-' or y=='+' or y=='('))
        return 1;
    if(x=='/' and (y=='-' or y=='+' or y=='('))
        return 1;
    if(x=='(' and (y=='-' or y=='+'))
        return 1;
    if(x==')' and (y=='-' or y=='+' or y=='*' or y=='/'))
        return 1;
    return 0;
}

bool symbolPlacedCorrect(int i, char infix[EXPRESSION_LENGTH][EXPRESSION_LENGTH], int lgInfix)
{
    char b=infix[i][0];
    if(i==0)
    {
        if(i!=lgInfix-1) //position i+1 exists
        {
            char c=infix[i+1][0];
            if(isSymbol(c))
            {
                bool ok=isSymbolNextToSymbolOk(b, c);
                if(ok==0)
                    return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    else if(i!=lgInfix-1) //positions i-1 and i+1 exist
    {
        char a=infix[i-1][0];
        if(isSymbol(a))
        {
            bool ok=isSymbolNextToSymbolOk(a, b);
            if(ok==0)
                return 0;
        }
        else
        {
            if(isLetterOrDigit(a))
                if(b=='(')
                    return 0;
        }
        char c=infix[i+1][0];
        if(isSymbol(c))
        {
            bool ok=isSymbolNextToSymbolOk(b, c);
            if(ok==0)
                return 0;
        }
    }
    else
    {
        if(b!=')')
            return 0;
    }
    return 1;
}

bool isExpressionCorrect(char exp[EXPRESSION_LENGTH])
{
    if(strlen(exp)==0)
        return 0;
    char s[EXPRESSION_LENGTH], infix[EXPRESSION_LENGTH][EXPRESSION_LENGTH];
    int lgInfix=0;
    strcpy(s, exp);
    getInfix(s, infix, lgInfix);
    for(int i=0; i<lgInfix; ++i)
    {
        if(isLetter(infix[i][0]))
        {
            if(!variableNameCorrect(infix[i]))
                return 0;
            int state=0;
            int poz=getVariablePosition(infix[i], state);
            if(state!=1)
                return 0;
            if(!variablePlacedCorrect(i, infix, lgInfix))
                return 0;
        }
        else if(isADigit(infix[i][0]))
        {
            if(!numberCorrect(infix[i]))
                return 0;
        }
        else if(isSymbol(infix[i][0]))
        {
            if(!symbolPlacedCorrect(i, infix, lgInfix))
                return 0;
        }
        else
            return 0;
    }
    return 1;
}

bool isOperatorCorrect(char exp[EXPRESSION_LENGTH])
{
    char s[EXPRESSION_LENGTH];
    strcpy(s, exp);
    int howMany=0;
    for(int i=0; s[i]; ++i)
    {
        if(s[i]=='!')
        {
            ++howMany;
            if(s[i+1] and s[i+1]!='=')
                return 0;
            if(s[i+2] and (s[i+2]=='=' or s[i+2]=='<' or s[i+2]=='>' or s[i+2]=='!'))
                return 0;
            ++i; //jump over = form !=
        }
        else if(s[i]=='=')
        {
            ++howMany;
            if(s[i+1] and (s[i+1]=='<' or s[i+1]=='>' or s[i+1]=='!'))
                return 0;
            if(s[i+2] and s[i+1]=='=' and (s[i+2]=='<' or s[i+2]=='>' or s[i+2]=='!'))
                return 0;
            if(s[i+1]=='=')
                ++i; //jump over = form ==
        }
        else if(s[i]=='<')
        {
            ++howMany;
            if(s[i+1] and (s[i+1]=='<' or s[i+1]=='>' or s[i+1]=='!'))
                return 0;
            if(s[i+2] and s[i+1]=='=' and (s[i+2]=='<' or s[i+2]=='>' or s[i+2]=='!'))
                return 0;
            if(s[i+1]=='=')
                ++i; //jump over = form <=
        }
        else if(s[i]=='>')
        {
            ++howMany;
            if(s[i+1] and (s[i+1]=='<' or s[i+1]=='>' or s[i+1]=='!'))
                return 0;
            if(s[i+2] and s[i+1]=='=' and (s[i+2]=='<' or s[i+2]=='>' or s[i+2]=='!'))
                return 0;
            if(s[i+1]=='=')
                ++i; //jump over = form >=
        }
    }
    if(howMany==1)
        return 1;
    return 0;
}

void isSchemeCorrect(node * k, bool & isCorrect) //has to be called like this: a=1; isSchemeCorrect(START, a);
{
    if(!(START->wasCreated))
    {
        isCorrect=0;
        return;
    }
    k->viz=1;
    if(!(k->next) and !(k->nextElse) and strcmp(k->type, "STOP")!=0)
    {
        isCorrect=0;
        return;
    }
    else
    {
        if(strcmp(k->type, "IN")==0)
        {
            if(!variableNameCorrect(k->expression))
            {
                isCorrect=0;
                return;
            }
            else
            {
                int state=0, value=0;
                char var[EXPRESSION_LENGTH];
                int poz=0;
                strcpy(var, k->expression);
                poz=getVariablePosition(var, state);
                if(state==0)
                {
                    cout<<"No more places for new variables!!!!!"; //continue code for menu
                    isCorrect=0;
                    return;
                }
                else
                {
                    strcpy(VARIABLES[poz].name, var);
                    VARIABLES[poz].isUsed=1;
                }
            }
        }
        else if(strcmp(k->type, "OUT")==0)
        {
            int state=0;
            char var[EXPRESSION_LENGTH];
            int poz=0;
            getVariableFromOut(k, var);
            poz=getVariablePosition(var, state);
            if(state==0 or state==2)
            {
                cout<<"Variable not known!!!!!";   //continue code for menu
                isCorrect=0;
                return;
            }
        }
        else if(strcmp(k->type, "ASSIGN")==0)
        {
            char var[EXPRESSION_LENGTH];
            int state=0, poz=0;
            if(k->expression[0]==NULL)
            {
                cout<<"Assign empty!!!"; //continue code for menu
                isCorrect=0;
                return;
            }
            getVariableFromAssign(k, var);
            if(!variableNameCorrect(var))
            {
                cout<<"Assign variable incorrect!!!"; //continue code for menu
                isCorrect=0;
                return;
            }
            poz=getVariablePosition(var, state);
            if(state==0)
            {
                cout<<"No more places for this new variable!!!"; //continue code for menu
                isCorrect=0;
                return;
            }
            else
            {
                char exp[EXPRESSION_LENGTH];
                char s[EXPRESSION_LENGTH];
                strcpy(s, k->expression);
                if(strtok(s, "=")==NULL)
                {
                    cout<<"Assign expression has no ="; //continue code for menu
                    isCorrect=0;
                    return;
                }
                getExpressionAfterEqualSign(k, exp);
                if(!isExpressionCorrect(exp))
                {
                    cout<<"Assign expression is not correct!!!"; //continue code for menu
                    isCorrect=0;
                    return;
                }
                else {
                        strcpy(VARIABLES[poz].name, var);
                        VARIABLES[poz].isUsed=1;
                }
            }
        }
        else if(strcmp(k->type, "DECISION")==0)
        {
            char exp1[EXPRESSION_LENGTH], exp2[EXPRESSION_LENGTH], oper[3];
            int value1=0, value2=0;
            if(!k->next or !k->nextElse)
            {
                cout<<"Decision does not have 2 bindings!!!"; //continue code for menu
                isCorrect=0;
                return;
            }
            if(k->expression[0]==NULL)
            {
                cout<<"Decision empty!!!"; //continue code for menu
                isCorrect=0;
                return;
            }
            getFirstExpresionFromCondition(k, exp1);
            char s[EXPRESSION_LENGTH];
            strcpy(s, k->expression);
            if(strtok(s, "!<=>")==NULL)
            {
                cout<<"Decision expression has wrong operator!!!"; //continue code for menu
                isCorrect=0;
                return;
            }
            if(!isOperatorCorrect(k->expression))
            {
                cout<<"Decision expression has wrong operator!!!"; //continue code for menu
                isCorrect=0;
                return;
            }
            bool notCorrect=0;
            getSecondExpressionFromCondition(k, exp2, notCorrect);
            if(notCorrect==1)
            {
                cout<<"Decision expression 2 is empty!!!"; //continue code for menu
                isCorrect=0;
                return;
            }
            getRelationOperator(k, oper);
            if(!isExpressionCorrect(exp1))
            {
                cout<<"Decision expression 1 is not correct!"; //continue code for menu
                isCorrect=0;
                return;
            }
            else if(!isExpressionCorrect(exp2))
            {
                cout<<"Decision expression 2 is not correct!"; //continue code for menu
                isCorrect=0;
                return;
            }
        }
        if((k->next and k->next->viz==0))
        {
            isSchemeCorrect(k->next, isCorrect);
            if(isCorrect==0)
                return;
        }
        if(k->nextElse and k->nextElse->viz==0)
        {
            isSchemeCorrect(k->nextElse, isCorrect);
            if(isCorrect==0)
                return;
        }
    }
}
#endif // INTERPRETATION_H_INCLUDED
