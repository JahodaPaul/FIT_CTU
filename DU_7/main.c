#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define min(a, b) ((a) < (b)) ? (a): (b)

int data[51];
int expectedResult;
int numberCount;
char op[50];
char expr[100];
int ind;
int previous;

int Read()
{
    char character;
    int bracket = 0, atLeastOneNumber = 0,secondBracket=0;
    while (1)
    {
        int loadedNumber = 0;
        while (!bracket)
        {
            character = getchar();
            if (character == '\n')
            {
                return 0;
            }
            else if (character != ' ' && character != '[')
            {
                return 0;
            }
            else if (character == '[')
            {
                bracket = 1;
            }
        }
        if (scanf("%d", &loadedNumber) != 1)
        {
            character = getchar();
            if (character == '\n' || character == ']')
            {
                if (!atLeastOneNumber)
                    return 0;
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            if(loadedNumber>=10 || loadedNumber<0)
            {
                return 0;
            }
            atLeastOneNumber = 1;
            int comma = 0;
            data[ind] = loadedNumber;
            ind++;
            while (!secondBracket && !comma)
            {
                character = getchar();
                if (character == '\n')
                    return 0;
                else if (character != ' ' && character != ',' && character != ']')
                    return 0;
                else if (character == ',')
                    comma += 1;
                else if (character == ']')
                {
                    secondBracket += 1;
                    return 1;
                }
            }
        }
    }
    return 1;
}

int calcNum(int *i)
{
  int n = data[*i];
  while (op[*i] == 's')
  {
    (*i)++;
    n = n * 10 + data[*i];
  }
  return n;
}

int calcMult(int *i, double *res)
{
  double a = calcNum(i);
  do
  {
    char c = op[*i];
    if (c == '*')
    {
      (*i)++;
      double b = calcNum(i);
      a = a*b;
    }
    else if (c == '/')
    {
      (*i)++;
      double b = calcNum(i);
      if (b == 0)
      {
        return 0;
      }
      a = a / b;
    }
    else
    {
      break;
    }
  } while (1);
  *res = a;
  return 1;
}

double calcSum(int *i, double *res)
{
  double a, b;
  if (calcMult(i, &a) == 0)
  {
    return 0;
  }
  do
  {
    char c = op[*i];
    if (c == '+')
    {
      (*i)++;
      if (calcMult(i, &b) == 0)
      {
        return 0;
      }
      a = a + b;
    }
    else if (c == '-')
    {
      (*i)++;
      if (calcMult(i, &b) == 0)
      {
        return 0;
      }
      a = a - b;
    }
    else
    {
      break;
    }
  } while (1);
  *res = a;
  return 1;
}

int calc()
{
  int i = 0;
  op[numberCount - 1] = 'e';
  double result;
  if (calcSum(&i, &result) == 0)
  {
    return 0;
  }
  if (fabs(result - expectedResult) < DBL_EPSILON * 1000000.0)
  {
    expr[0] = '0' + data[0];
    int c = numberCount;
    int t = 1;
    for (i = 0; i < c - 1; ++i)
    {
      if (op[i] != 's')
      {
        expr[t++] = op[i];
      }
      expr[t++] = '0' + data[i + 1];
    }
    expr[t] = 0;
    printf("%d = %s\n", expectedResult, expr);
    return 1;
  }
  return 0;
}

int gener(int depth)
{
  if (depth == 0)
  {
    return calc();
  }
  int i = numberCount - depth - 1;
  op[i] = 's';
  int n = gener(depth - 1);
  op[i] = '+';
  n += gener(depth - 1);
  op[i] = '-';
  n += gener(depth - 1);
  op[i] = '*';
  n += gener(depth - 1);
  op[i] = '/';
  n += gener(depth - 1);
  return n;
}

int main()
{
  printf("Cislice:\n");
  int s = Read();
  if(s)
  {
    printf("Dotazy:\n");
    numberCount=ind;

    if((scanf("%d",&previous))==1)
    {
        expectedResult = previous;
    }
    else
    {
        printf("Nespravny vstup.\n");
        return 0;
    }
    while(!feof(stdin))
    {
        if((scanf("%d",&previous))==1)
        {
            if(numberCount>10)
            {
                printf("Nespravny vstup.\n");
                return 0;
            }
            int n = gener(numberCount - 1);
            printf("Celkem: %d\n", n);
            expectedResult = previous;
        }
        else
        {
            break;
        }
    }
    if(!feof(stdin))
    {
        printf("Nespravny vstup.\n");
        return 0;
    }
    expectedResult = previous;
    int n = gener(numberCount - 1);
    printf("Celkem: %d\n", n);
  }
  else
  {
      printf("Nespravny vstup.\n");
  }
  return 0;
/*Pavel Jahoda*/
}
