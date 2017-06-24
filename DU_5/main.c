#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int **arr = NULL;
int *indexes = NULL;
int *helpArray = NULL;
int *limitArray = NULL;
int *sums = NULL;

int IndexExist(int index, int number,int *positionOfIndex)
{
    int i;
    for (i = 0; i < number; i++)
    {
        if (index == indexes[i])
        {
            *positionOfIndex=i;
            return 1;
        }
    }
    return 0;
}

void GrowArrays(int *limit)
{
    if (*limit == 0)
    {
        *limit = 16;
    }
    else
    {
        *limit *= 2;
    }
    arr = (int **)realloc(arr, sizeof(arr[0]) * *limit);
    indexes = (int*)realloc(indexes, sizeof(indexes[0]) * *limit);
    helpArray = (int*)realloc(helpArray, sizeof(helpArray[0]) * *limit);
    limitArray = (int*)realloc(limitArray, sizeof(limitArray[0]) * *limit);
    sums = (int*)realloc(sums, sizeof(sums[0]) * *limit);
}

void AddNumber(int ind, int loadedNumber)
{
    if (helpArray[ind] >= limitArray[ind])
    {
        if (limitArray[ind] == 0)
            limitArray[ind] = 16;
        else
            limitArray[ind] *= 2;
        arr[ind] = (int *)realloc(arr[ind], sizeof(arr[ind][0])*limitArray[ind]);
    }
    arr[ind][helpArray[ind]] = loadedNumber;
    helpArray[ind] += 1;
    sums[ind] += loadedNumber;
}

int Read(int index, int *numberOfUniqueIndexes, int *limit, int *secondBracket)
{
    char character;
    int bracket = 0, ind = 0, colon = 0, atLeastOneNumber = 0,positionOfIndex=-1;
    if (!IndexExist(index, *numberOfUniqueIndexes,&positionOfIndex))
    {
        if (*numberOfUniqueIndexes >= *limit)
        {
            GrowArrays(limit);
        }
        indexes[*numberOfUniqueIndexes] = index;
        arr[*numberOfUniqueIndexes] = NULL;
        limitArray[*numberOfUniqueIndexes] = 0;
        helpArray[*numberOfUniqueIndexes] = 0;
        sums[*numberOfUniqueIndexes] = 0;
        *numberOfUniqueIndexes += 1;
    }
    if(positionOfIndex!=-1)
    {
        ind=positionOfIndex;
    }
    else
    {
        ind=*numberOfUniqueIndexes-1;
    }
    while (1)
    {
        int loadedNumber = 0;
        while (!bracket || !colon)
        {
            character = getchar();
            if (character == '\n')
            {
                return 0;
            }
            else if (character != ' ' && character != ':' && character != '[')
            {
                return 0;
            }
            else if (character == ':')
            {
                colon += 1;
                if (colon > 1)
                    return 0;
            }
            else if (character == '[')
            {
                bracket += 1;
                if (bracket > 1 || colon == 0)
                    return 0;
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
            atLeastOneNumber = 1;
            *secondBracket = 0;
            int comma = 0;
            AddNumber(ind, loadedNumber);
            while (!*secondBracket && !comma)
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
                    *secondBracket += 1;
                    return 1;
                }
            }
        }
    }
    return 1;
}

int NumbersMightBeSimilar(int firstIndex, int secondIndex, int firstNumberOfNumbers, int secondNumberOfNumbers, int *arrFirstIndex, int *arrSecondIndex)
{
    if (firstNumberOfNumbers != secondNumberOfNumbers || sums[firstIndex] != sums[secondIndex])
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int NumbersInTheSameOrder(int firstNumberOfNumbers, int secondNumberOfNumbers, int *arrFirstIndex, int *arrSecondIndex)
{
    int i = 0, j = 0, k = 0;
    if (firstNumberOfNumbers == 1 && arrFirstIndex[0] == arrSecondIndex[0])
    {
        return 1;
    }
    for (k = 0; k < secondNumberOfNumbers; k++)
    {
        int found = 0;
        if (arrFirstIndex[0] == arrSecondIndex[k])
        {
            j = k;
            for (i = 1; i < firstNumberOfNumbers; i++)
            {
                j++;
                if (j == secondNumberOfNumbers)
                {
                    j = 0;
                }
                if (arrFirstIndex[i] != arrSecondIndex[j])
                {
                    found = 0;
                    break;
                }
                found = 1;
            }
        }
        if (found)
        {
            return 1;
        }
    }
    return 0;
}

void FindUniqueMessages(int numberOfUniqueIndexes)
{
    int i, j;
    for (i = numberOfUniqueIndexes - 1; i > 0; i--)
    {
        if(indexes[i] == -1)
        {
            continue;
        }
        int foundAtLeastOne = 0;
        for (j = i - 1; j >= 0; j--)
        {
            if (indexes[j] != -1)
            {
                if (NumbersMightBeSimilar(i, j, helpArray[i], helpArray[j], arr[i], arr[j]))
                {
                    if (NumbersInTheSameOrder(helpArray[i], helpArray[j], arr[i], arr[j]))
                    {
                        if (!foundAtLeastOne)
                        {
                            printf("%d", indexes[j]);
                        }
                        else
                        {
                            printf(", %d", indexes[j]);
                        }
                        foundAtLeastOne = 1;
                        indexes[j] = -1;
                    }
                }
            }
        }
        if (!foundAtLeastOne && indexes[i] != -1)
        {
            printf("%d\n", indexes[i]);
        }
        else if (indexes[i] != -1)
        {
            printf(", %d\n", indexes[i]);
        }
    }
    if (indexes[0] != -1)
    {
        printf("%d\n", indexes[0]);
    }
}

int main()
{
    int index = 0, i = 0, numberOfUniqueIndexes = 0, limit = 0, secondBracket = 0;
    printf("Zpravy:\n");
    while (scanf("%d", &index) == 1 && index >= 0 && Read(index, &numberOfUniqueIndexes, &limit, &secondBracket))
    {

    }
    if (!feof(stdin) || secondBracket == 0)
    {
        printf("Nespravny vstup.\n");
    }
    else
    {
        printf("Unikatni zpravy:\n");
        FindUniqueMessages(numberOfUniqueIndexes);
    }
    for (i = 0; i < numberOfUniqueIndexes; i++)
    {
        free(arr[i]);
    }
    free(limitArray);
    free(sums);
    free(helpArray);
    free(indexes);
    free(arr);
    return 0;
    /*Pavel Jahoda*/
}
