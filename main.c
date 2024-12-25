#include <stdio.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];
int top = -1;

// Push an operator to the stack
void push(char c)
{
    stack[++top] = c;
}

// Pop an operator from the stack
char pop()
{
    return stack[top--];
}

// Return precedence of operators
int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/' || op == '%') 
        return 2;
    if (op == '^')
        return 3;
    return 0;
}

// Convert infix to postfix
void infixToPostfix(char *infix, char *postfix)
{
    int i = 0, j = 0;
    char c;

    while (infix[i] != '\0')
    {
        c = infix[i];

        if (isalnum(c))
        { // If operand, add to postfix
            postfix[j++] = c;
        }
        else if (c == '(')
        { // If '(', push to stack
            push(c);
        }
        else if (c == ')')
        { // If ')', pop until '('
            while (top != -1 && stack[top] != '(')
            {
                postfix[j++] = pop();
            }
            pop(); // Pop '('
        }
        else
        { // If operator, pop higher precedence operators
            while (top != -1 && precedence(stack[top]) >= precedence(c))
            {
                postfix[j++] = pop();
            }
            push(c);
        }
        i++;
    }

    while (top != -1)
    { // Pop remaining operators
        postfix[j++] = pop();
    }

    postfix[j] = '\0'; // Null-terminate the postfix expression
}

int main()
{
    char infix[MAX], postfix[MAX];

    printf("Enter infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);

    return 0;
}
