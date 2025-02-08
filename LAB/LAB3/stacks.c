#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX 50

typedef struct {
    char items[MAX];
    int top;
} CharStack;

void initCharStack(CharStack *s) {
    s->top = -1;
}

int isCharStackEmpty(CharStack *s) {
    return s->top == -1;
}

void pushChar(CharStack *s, char item) {
    s->items[++s->top] = item;
}

char popChar(CharStack *s) {
    return s->items[s->top--];
}

char peekChar(CharStack *s) {
    return s->items[s->top];
}

typedef struct {
    int items[MAX];
    int top;
} IntStack;

void initIntStack(IntStack *s) {
    s->top = -1;
}

int isIntStackEmpty(IntStack *s) {
    return s->top == -1;
}

void pushInt(IntStack *s, int item) {
    s->items[++s->top] = item;
}

int popInt(IntStack *s) {
    return s->items[s->top--];
}
int precedence(char op) {
    switch(op) {
        
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '^': return 3;
        default: return 0;
    }
}

int isLeftAssociative(char op) {
    return (op != '^');  
}
void infixToPostfix(char* infix, char* postfix) {
    CharStack opStack;
    initCharStack(&opStack);
    int j = 0; 
    for (int i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        if (isalnum(ch)) { 
            postfix[j++] = ch;
        } 
        else if (ch == '(') {
            pushChar(&opStack, ch);
        } 
        else if (ch == ')') {
            while (!isCharStackEmpty(&opStack) && peekChar(&opStack) != '(') {
                postfix[j++] = popChar(&opStack);
            }
            popChar(&opStack);  
        } 
        else {  
            while (!isCharStackEmpty(&opStack) && 
                   precedence(peekChar(&opStack)) > precedence(ch) ||
                   (precedence(peekChar(&opStack)) == precedence(ch) && isLeftAssociative(ch))) {
                postfix[j++] = popChar(&opStack);
            }
            pushChar(&opStack, ch);
        }
    }

    while (!isCharStackEmpty(&opStack)) {
        postfix[j++] = popChar(&opStack);
    }
    postfix[j] = '\0';  
}
int evaluatePostfix(char* postfix) {
    IntStack valStack;
    initIntStack(&valStack);

    for (int i = 0; postfix[i] != '\0'; i++) {
        char ch = postfix[i];

        if (isdigit(ch)) {  
            pushInt(&valStack, ch - '0');  
        } else {  
            int val2 = popInt(&valStack);
            int val1 = popInt(&valStack);
            switch (ch) {
                case '+': pushInt(&valStack, val1 + val2); break;
                case '-': pushInt(&valStack, val1 - val2); break;
                case '*': pushInt(&valStack, val1 * val2); break;
                case '/': pushInt(&valStack, val1 / val2); break;
                case '^': pushInt(&valStack, (int)pow(val1, val2)); break;
            }
        }
    }
    return popInt(&valStack);  
}

int main() {
    char infix[MAX], postfix[MAX];
    printf("Enter infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    int result = evaluatePostfix(postfix);
    printf("Evaluation result: %d\n", result);

    return 0;
}


