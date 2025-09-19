#include <stdio.h>
#include <stack>

/*
    1918번 후위표기법 문제.
    언제 연산자를 출력할지를 인지하는 것이 핵심
    
    처음엔 level이라는 변수에 연산대기중인 문자를 세는 방법으로 했음
    괄호 들어가면 level를 별도 스택에 넣고, 괄호 나올때 다시 빼고...
    근데 너무 복잡하고 제대로 작동하지 않았음

    해법은 괄호도 opr 스택에 넣는거였음
    그리고 우선순위에 따라 어떻게 출력할지만 정하면 됐음
    +,-는 (이 나오거나 스택이 빌때까지 출력시키고, *,/는 *,/이 스택 맨위면 출력시키면 됐음
    그리고 괄호는 (는 opr 스택에 넣고, )이 입력될때 (이 나올때까지 계속 출력시키면 됐음

    너무 복잡하게 생각한 것이 화근이었음...
*/

using namespace std;

void outputOne(stack<char>& _opr)
{
    putchar(_opr.top());
    _opr.pop();
}

int main()
{
    stack<char> opr;

    char input;
    while(1)
    {
        input = getchar();

        // Store input
        if (input >= 65 && input <=90)
        {
            putchar(input);
        }
        else if (input == '+' || input == '-')
        {
            if (!opr.empty() && opr.top() != '(')
            {
                while(!opr.empty() && opr.top() != '(')
                    outputOne(opr);
            }
            opr.push(input);
        }
        else if (input == '*' || input == '/')
        {
            if (!opr.empty() && (opr.top() == '*' || opr.top() == '/'))
                outputOne(opr);
            opr.push(input);
        }
        else if (input == '(')
        {
            opr.push(input);
        }
        else if (input == ')')
        {
            while(opr.top() != '(')
                outputOne(opr);
            opr.pop();
        }
        else if (input == '\n')
        {
            const int ITER = opr.size();
            for (int i=0; i<ITER; i++)
                outputOne(opr);
            break;
        }
    }

    return 0;
}
