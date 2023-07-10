

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

char *Pop(char *);
char *Push(char *, char);
char precedence(char);
int evaluatePostfix(char *);
int performOperation(char, int, int);

int main(int arg, char *argv[])
{

  char *input = (char *)malloc(100);
  char *values = (char *)malloc(100);
  char *stackvalue = (char *)malloc(100);
  strcpy(input, argv[1]);

  char *stack = (char *)malloc(100);
  char *prefixExpression = (char *)malloc(100);

  printf("\nEnter integer values of the following identifiers: %s\n\n", input);
  int index = 0;
  for (int i = 0; i < strlen(argv[1]); i++)
  {

    if (argv[1][i] == '$')
    {
      break;
    }
    else if (argv[1][i] == '+' || argv[1][i] == '-' || argv[1][i] == '*' || argv[1][i] == '/')
    {

      values[i] = argv[1][i];
    }
    else if (isalpha(argv[1][i]) || isdigit(argv[1][i]))
    {
      printf("\nValue of %c: ", argv[1][i]);
      scanf("%hhd", &values[i]);
      index++;
    }
    else
    {
      printf("\nInvalid token encountered. Program terminated prematurely");
      break;
    }
  }
  printf("\n\n");
  printf("The stack implementation table for operator precedence parser for the given \nexpression is as follows:\n\n");

  int lastindex = strlen(input) - 1;
  input[lastindex] = '\0';
  char action[100];
  int i = 0;
  int act = 0;

  printf("\t\tStack\t\t\tInput\t\t\tAction\n\n");
  if (strlen(input) == 1 || !isalpha(input[0]))
  {
    printf("\n\n\t============================================================\n");
    printf("\t\tThis String does not satisfy the language!!\n");
    printf("\t============================================================\n\n");

    goto lastline;
  }

  char lastpopped;
  while (i < 20)
  {
    int input_element = 0;
    int stack_element = 0;
    if (strlen(input) != 0)
    {
      input_element = precedence(input[0]);
      // printf("precedence input is %d\n", input_element);
    }
    if (strlen((stack)) != 0)
    {
      stack_element = precedence(stack[0]);
      // printf("precedence stack is %d\n", stack_element);
    }

    printf("\t\t%s$\t\t\t%s$\t\t\t%s\n", stack, input, action);
    if (strlen(input) == 1 && !isalpha(input[0]))
    {
      printf("\n\n\t============================================================\n");
      printf("\t\tThis String does not satisfy the language!!\n");
      printf("\t============================================================\n\n");
      goto lastline;
    }
    if (act == 1)
    {

      break;
    }

    else if ((strlen(stack) == 0) && (strlen(input) == 0))
    {
      strcpy(action, "Accepted");
      act = 1;
    }

    else if (stack_element < input_element)
    {

      char popped = input[0];
      if (lastpopped == popped)
      {
        printf("\n\n\t============================================================\n");
        printf("\t\tThis String does not satisfy the language!!\n");
        printf("\t============================================================\n\n");
        goto lastline;
      }
      else
      {
        lastpopped = popped;
      }
      input = Pop(input);
      stack = Push(stack, popped);
      strcpy(action, "Push");
      ///////////////////////////////////////////////////////////////////////////////////////////////////
      //////////////////////////////////////////////////////////////////////////////////////////////////
      char stackpopped = values[0];
      values = Pop(values);
      stackvalue = Push(stackvalue, stackpopped);
    }
    else if (stack_element >= input_element)
    {
      char stackpop = stackvalue[0];
      prefixExpression[strlen(prefixExpression)] = stackpop;
      stackvalue = Pop(stackvalue);
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      stack = Pop(stack);
      strcpy(action, "Pop");
    }

    i++;
  }

  int result = evaluatePostfix(prefixExpression);
  printf("The output of the given expression is: %d\n", result);

  return 0;

lastline:
}

char precedence(char element)
{

  switch (element)
  {
  case '$':
    return 0;
  case '+':
    return 1;
  case '-':
    return 2;
  case '*':
    return 3;
  case '/':
    return 4;
  default:
    return 5;
  }
}

char *Pop(char *arr)
{
  int i;
  int length = strlen(arr);
  memmove(arr, arr + 1, length);
  return arr;
}
char *Push(char *arr, char element)
{
  int length = strlen(arr);
  memmove(arr + 1, arr, length + 1);
  arr[0] = element;
  return arr;
}

// Function to perform arithmetic operations
int performOperation(char operator, int operand1, int operand2)
{
  switch (operator)
  {
  case '+':
    return operand1 + operand2;
  case '-':
    return operand1 - operand2;
  case '*':
    return operand1 * operand2;
  case '/':
    return operand1 / operand2;
  }
  return 0;
}

int evaluatePostfix(char *expression)
{
  int len = strlen(expression);

  int *postfixStack = (int *)malloc(len * sizeof(int));
  int top = -1;
  for (int i = 0; i < (strlen(expression)); i++)
  {
    if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/' || expression[i] == '$')
    {
      int operand2 = postfixStack[top--];
      int operand1 = postfixStack[top--];
      int result = performOperation(expression[i], operand1, operand2);
      postfixStack[++top] = result;
    }
    else
    {
      postfixStack[++top] = expression[i];
    }
  }

  int result = postfixStack[top];

  return result;
}
