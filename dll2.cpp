#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

typedef struct Stack {
    char items[MAX][MAX];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, char *item) {
    if (s->top < MAX - 1) {
        strcpy(s->items[++s->top], item);
    }
}

char *pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->items[s->top--];
    }
    return "";
}

char *peek(Stack *s) {
    if (!isEmpty(s)) {
        return s->items[s->top];
    }
    return "";
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

void infixToPostfix(char *exp, char *result) {
    Stack stack;
    initStack(&stack);
    char output[MAX] = "";
    int k = 0;

    for (int i = 0; exp[i]; i++) {
        if (isalnum(exp[i])) {
            output[k++] = exp[i];
        } else if (exp[i] == '(') {
            char str[2] = {exp[i], '\0'};
            push(&stack, str);
        } else if (exp[i] == ')') {
            while (!isEmpty(&stack) && peek(&stack)[0] != '(') {
                output[k++] = pop(&stack)[0];
            }
            pop(&stack);
        } else {
            while (!isEmpty(&stack) && precedence(peek(&stack)[0]) >= precedence(exp[i])) {
                output[k++] = pop(&stack)[0];
            }
            char str[2] = {exp[i], '\0'};
            push(&stack, str);
        }
    }
    
    while (!isEmpty(&stack)) {
        output[k++] = pop(&stack)[0];
    }
    output[k] = '\0';
    strcpy(result, output);
}

void postfixToInfix(char *exp, char *result) {
    Stack stack;
    initStack(&stack);
    
    for (int i = 0; exp[i]; i++) {
        if (isalnum(exp[i])) {
            char str[2] = {exp[i], '\0'};
            push(&stack, str);
        } else {
            char op2[MAX], op1[MAX], newExpr[MAX];
            strcpy(op2, pop(&stack));
            strcpy(op1, pop(&stack));
            snprintf(newExpr, MAX, "(%s%c%s)", op1, exp[i], op2);
            push(&stack, newExpr);
        }
    }
    strcpy(result, pop(&stack));
}

int main() {
    char infix[] = "A+B*C";
    char postfix[MAX];
    char infixResult[MAX];
    
    infixToPostfix(infix, postfix);
    printf("Infix ke Postfix: %s\n", postfix);
    
    postfixToInfix(postfix, infixResult);
    printf("Postfix ke Infix: %s\n", infixResult);
    
    return 0;
}
