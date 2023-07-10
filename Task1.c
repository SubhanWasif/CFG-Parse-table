

#include <string.h>
#include <stdio.h>
#include <ctype.h>

int main(int arg, char *argv[])
{

  printf("\nProgram finds following tokens in the expression:");
  printf("\nExpression received: %s", argv[1]);

  for (int i = 0; i < sizeof(argv[1]); i++)
  {
    char a = (char)argv[1][i];
    if (a == '$')
    {
      break;
    }
    else if (a == '+' || a == '-' || a == '*' || a == '/')
    {
      printf("\nArithmetic operator: %c", a);
    }
    else if (isalpha(a) || isdigit(a))
    {
      printf("\nint literal found: %c", a);
    }
    else
    {
      printf("\nInvalid token encountered. Program terminated prematurely");
      break;
    }
  }
  printf("\n\n");
}