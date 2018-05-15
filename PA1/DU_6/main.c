#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char numbers[200000];
int originalNumberOfNumbers, numberOfNumbers = 0, name = 0, surname = 0;
char *nameArr = NULL, *surnameArr = NULL;
char **CollectedPeople = NULL;
int NCollectedPeople = 0;
int LimitCollected = 4;
int space = 1;

struct tree
{
	struct tree *sons[10];
	int numberOfPeople;
	char **arr;
};

struct tree *root;

void AddPerson(struct tree *node, int numberOfNumbers)
{
	if (numberOfNumbers == 0)
	{
		if (node->numberOfPeople == 0)
		{
			int j;
			node->numberOfPeople = 1;
			node->arr = (char**)realloc(node->arr, (sizeof(node->arr[0]))*node->numberOfPeople);
			node->arr[0] = NULL;
			if (surname == 0)
			{
				node->arr[(node->numberOfPeople) - 1] = (char*)realloc(node->arr[(node->numberOfPeople) - 1], sizeof(node->arr[(node->numberOfPeople) - 1][0]) * (originalNumberOfNumbers + 1 + name + 1));
			}
			else
			{
				node->arr[(node->numberOfPeople) - 1] = (char*)realloc(node->arr[(node->numberOfPeople) - 1], sizeof(node->arr[(node->numberOfPeople) - 1][0]) * (originalNumberOfNumbers + 1 + name + 1 + surname + 1));
			}
			for (j = 0; j < originalNumberOfNumbers; j++)
			{
				node->arr[(node->numberOfPeople) - 1][j] = numbers[j];
			}
			node->arr[(node->numberOfPeople) - 1][originalNumberOfNumbers] = ' ';
			for (j = 0; j < name; j++)
			{
				node->arr[(node->numberOfPeople) - 1][j + originalNumberOfNumbers + 1] = nameArr[j];
			}
			if (surname != 0)
			{
				node->arr[(node->numberOfPeople) - 1][name + originalNumberOfNumbers + 1] = ' ';
			}
			else
			{
				node->arr[(node->numberOfPeople) - 1][name + originalNumberOfNumbers + 1] = 0;
			}
			for (j = 0; j < surname; j++)
			{
				node->arr[(node->numberOfPeople) - 1][j + originalNumberOfNumbers + name + 2] = surnameArr[j];
			}
			if (surname != 0)
			{
				node->arr[(node->numberOfPeople) - 1][surname + originalNumberOfNumbers + name + 2] = 0;
			}
			printf("OK\n");
		}
		else
		{
			int i, j, alreadyExist = 0;
			for (i = 0; i < node->numberOfPeople; i++)
			{
				int l = strlen(node->arr[i]);
				if ((surname > 1 && l == (surname + originalNumberOfNumbers + name + 2)) || (surname == 0 && l == (surname + originalNumberOfNumbers + name + 1)))
				{
					for (j = 0; j < originalNumberOfNumbers; j++)
					{
						if (node->arr[i][j] != numbers[j])
						{
							alreadyExist = 0;
							break;
						}
						alreadyExist = 1;
					}
					if (!alreadyExist)
					{
						continue;
					}
					for (j = 0; j < name; j++)
					{
						if (node->arr[i][j + originalNumberOfNumbers + 1] != nameArr[j])
						{
							alreadyExist = 0;
							break;
						}
						alreadyExist = 1;
					}
					if (!alreadyExist)
					{
						continue;
					}
					for (j = 0; j < surname; j++)
					{
						if (node->arr[i][j + originalNumberOfNumbers + name + 2] != surnameArr[j])
						{
							alreadyExist = 0;
							break;
						}
						alreadyExist = 1;
					}
					if (!alreadyExist)
					{
						continue;
					}

					if (alreadyExist)
					{
						break;
					}
				}
			}
			if (alreadyExist)
			{
				printf("Kontakt jiz existuje.\n");
			}
			else
			{
				node->numberOfPeople += 1;

				node->arr = (char**)realloc(node->arr, (sizeof(node->arr[(node->numberOfPeople) - 1])) * node->numberOfPeople);
				node->arr[(node->numberOfPeople) - 1] = NULL;
				if (surname == 0)
				{
					node->arr[(node->numberOfPeople) - 1] = (char*)realloc(node->arr[(node->numberOfPeople) - 1], sizeof(node->arr[(node->numberOfPeople) - 1][0]) * (originalNumberOfNumbers + 1 + name + 1));
				}
				else
				{
					node->arr[(node->numberOfPeople) - 1] = (char*)realloc(node->arr[(node->numberOfPeople) - 1], sizeof(node->arr[(node->numberOfPeople) - 1][0]) * (originalNumberOfNumbers + 1 + name + 1 + surname + 1));
				}

				for (j = 0; j < originalNumberOfNumbers; j++)
				{
					node->arr[(node->numberOfPeople) - 1][j] = numbers[j];
				}
				node->arr[(node->numberOfPeople) - 1][originalNumberOfNumbers] = ' ';
				for (j = 0; j < name; j++)
				{
					node->arr[(node->numberOfPeople) - 1][j + originalNumberOfNumbers + 1] = nameArr[j];
				}
				if (surname != 0)
					node->arr[(node->numberOfPeople) - 1][name + originalNumberOfNumbers + 1] = ' ';
				else
				{
					node->arr[(node->numberOfPeople) - 1][name + originalNumberOfNumbers + 1] = 0;
				}
				for (j = 0; j < surname; j++)
				{
					node->arr[(node->numberOfPeople) - 1][j + originalNumberOfNumbers + name + 2] = surnameArr[j];
				}
				if (surname != 0)
					node->arr[(node->numberOfPeople) - 1][surname + originalNumberOfNumbers + name + 2] = 0;
				printf("OK\n");
			}
		}
		return;
	}
	int index = (numbers[originalNumberOfNumbers - numberOfNumbers]-'0');
	if (node->sons[index] == 0)
	{
		node->sons[index] = (struct tree*)calloc(1, sizeof(struct tree));
	}
	AddPerson(node->sons[index], numberOfNumbers - 1);
}

void AddPersonByName(struct tree *node, int numberOfNumbers)
{
	if (numberOfNumbers == 0)
	{
		if (node->numberOfPeople == 0)
		{
			int j;
			node->numberOfPeople = 1;
			node->arr = (char**)realloc(node->arr, (sizeof(node->arr[0]))*node->numberOfPeople);
			node->arr[0] = NULL;
			if (surname == 0)
			{
				node->arr[(node->numberOfPeople) - 1] = (char*)realloc(node->arr[(node->numberOfPeople) - 1], sizeof(node->arr[(node->numberOfPeople) - 1][0]) * (originalNumberOfNumbers + 1 + name + 1));
			}
			else
			{
				node->arr[(node->numberOfPeople) - 1] = (char*)realloc(node->arr[(node->numberOfPeople) - 1], sizeof(node->arr[(node->numberOfPeople) - 1][0]) * (originalNumberOfNumbers + 1 + name + 1 + surname + 1));
			}
			for (j = 0; j < originalNumberOfNumbers; j++)
			{
				node->arr[(node->numberOfPeople) - 1][j] = numbers[j];
			}
			node->arr[(node->numberOfPeople) - 1][originalNumberOfNumbers] = ' ';
			for (j = 0; j < name; j++)
			{
				node->arr[(node->numberOfPeople) - 1][j + originalNumberOfNumbers + 1] = nameArr[j];
			}
			if (surname != 0)
				node->arr[(node->numberOfPeople) - 1][name + originalNumberOfNumbers + 1] = ' ';
			else
			{
				node->arr[(node->numberOfPeople) - 1][name + originalNumberOfNumbers + 1] = 0;
			}
			for (j = 0; j < surname; j++)
			{
				node->arr[(node->numberOfPeople) - 1][j + originalNumberOfNumbers + name + 2] = surnameArr[j];
			}
			if (surname != 0)
				node->arr[(node->numberOfPeople) - 1][surname + originalNumberOfNumbers + name + 2] = 0;
		}
		else
		{
			int i, j, alreadyExist = 0;
			for (i = 0; i < node->numberOfPeople; i++)
			{
				int l = strlen(node->arr[i]);
				if ((surname > 1 && l == (surname + originalNumberOfNumbers + name + 2)) || (surname == 0 && l == (surname + originalNumberOfNumbers + name + 1)))
				{
					for (j = 0; j < originalNumberOfNumbers; j++)
					{
						if (node->arr[i][j] != numbers[j])
						{
							alreadyExist = 0;
							break;
						}
						alreadyExist = 1;
					}
					if (!alreadyExist)
					{
						continue;
					}
					for (j = 0; j < name; j++)
					{
						if (node->arr[i][j + originalNumberOfNumbers + 1] != nameArr[j])
						{
							alreadyExist = 0;
							break;
						}
						alreadyExist = 1;
					}
					if (!alreadyExist)
					{
						continue;
					}
					for (j = 0; j < surname; j++)
					{
						if (node->arr[i][j + originalNumberOfNumbers + name + 2] != surnameArr[j])
						{
							alreadyExist = 0;
							break;
						}
						alreadyExist = 1;
					}
					if (!alreadyExist)
					{
						continue;
					}
					alreadyExist = 1;
					if (alreadyExist)
					{
						break;
					}
				}
			}
			if (alreadyExist)
			{
			}
			else
			{
				node->numberOfPeople += 1;

				node->arr = (char**)realloc(node->arr, (sizeof(node->arr[(node->numberOfPeople) - 1])) * node->numberOfPeople);
				node->arr[(node->numberOfPeople) - 1] = NULL;
				if (surname == 0)
				{
					node->arr[(node->numberOfPeople) - 1] = (char*)realloc(node->arr[(node->numberOfPeople) - 1], sizeof(node->arr[(node->numberOfPeople) - 1][0]) * (originalNumberOfNumbers + 1 + name + 1));
				}
				else
				{
					node->arr[(node->numberOfPeople) - 1] = (char*)realloc(node->arr[(node->numberOfPeople) - 1], sizeof(node->arr[(node->numberOfPeople) - 1][0]) * (originalNumberOfNumbers + 1 + name + 1 + surname + 1));
				}

				for (j = 0; j < originalNumberOfNumbers; j++)
				{
					node->arr[(node->numberOfPeople) - 1][j] = numbers[j];
				}
				node->arr[(node->numberOfPeople) - 1][originalNumberOfNumbers] = ' ';
				for (j = 0; j < name; j++)
				{
					node->arr[(node->numberOfPeople) - 1][j + originalNumberOfNumbers + 1] = nameArr[j];
				}
				if (surname != 0)
					node->arr[(node->numberOfPeople) - 1][name + originalNumberOfNumbers + 1] = ' ';
				else
				{
					node->arr[(node->numberOfPeople) - 1][name + originalNumberOfNumbers + 1] = 0;
				}
				for (j = 0; j < surname; j++)
				{
					node->arr[(node->numberOfPeople) - 1][j + originalNumberOfNumbers + name + 2] = surnameArr[j];
				}
				if (surname != 0)
					node->arr[(node->numberOfPeople) - 1][surname + originalNumberOfNumbers + name + 2] = 0;
			}
		}
		return;
	}
	int index = 0;
	if (numberOfNumbers > surname)
	{
		char tmp = tolower(nameArr[name + surname - numberOfNumbers]);
		if (tmp == 'a' || tmp == 'b' || tmp == 'c')
		{
			index = 2;
		}
		else if (tmp == 'd' || tmp == 'e' || tmp == 'f')
		{
			index = 3;
		}
		else if (tmp == 'g' || tmp == 'h' || tmp == 'i')
		{
			index = 4;
		}
		else if (tmp == 'j' || tmp == 'k' || tmp == 'l')
		{
			index = 5;
		}
		else if (tmp == 'm' || tmp == 'n' || tmp == 'o')
		{
			index = 6;
		}
		else if (tmp == 'p' || tmp == 'q' || tmp == 'r' || tmp == 's')
		{
			index = 7;
		}
		else if (tmp == 't' || tmp == 'u' || tmp == 'v')
		{
			index = 8;
		}
		else if (tmp == 'w' || tmp == 'x' || tmp == 'y' || tmp == 'z')
		{
			index = 9;
		}
	}
	else if (surname != 0 && numberOfNumbers == surname && space)
	{
		numberOfNumbers++;
		index = 1;
		space = 0;
	}
	else if (surname != 0 && numberOfNumbers <= surname)
	{
		char tmp = tolower(surnameArr[surname - numberOfNumbers]);
		if (tmp == 'a' || tmp == 'b' || tmp == 'c')
		{
			index = 2;
		}
		else if (tmp == 'd' || tmp == 'e' || tmp == 'f')
		{
			index = 3;
		}
		else if (tmp == 'g' || tmp == 'h' || tmp == 'i')
		{
			index = 4;
		}
		else if (tmp == 'j' || tmp == 'k' || tmp == 'l')
		{
			index = 5;
		}
		else if (tmp == 'm' || tmp == 'n' || tmp == 'o')
		{
			index = 6;
		}
		else if (tmp == 'p' || tmp == 'q' || tmp == 'r' || tmp == 's')
		{
			index = 7;
		}
		else if (tmp == 't' || tmp == 'u' || tmp == 'v')
		{
			index = 8;
		}
		else if (tmp == 'w' || tmp == 'x' || tmp == 'y' || tmp == 'z')
		{
			index = 9;
		}
	}
	if (node->sons[index] == 0)
	{
		node->sons[index] = (struct tree*)calloc(1, sizeof(struct tree));
	}
	AddPersonByName(node->sons[index], numberOfNumbers - 1);
}


void CollectPerson(char *person)
{
	int i, j;
	int alreadyExist = 0;
	int length = strlen(person);
	for (i = 0; i < NCollectedPeople; i++)
	{
		int l = strlen(CollectedPeople[i]);
		if (l == length)
		{
			alreadyExist = 1;
			for (j = 0; j < l; j++)
			{
				if (person[j] != CollectedPeople[i][j])
				{
					alreadyExist = 0;
					break;
				}
			}
		}
		else
		{
			alreadyExist = 0;
		}
		if (alreadyExist)
		{
			break;
		}
	}
	if (!alreadyExist)
	{
		if (NCollectedPeople == LimitCollected)
		{
			LimitCollected *= 2;
			CollectedPeople = (char**)realloc(CollectedPeople, (sizeof(CollectedPeople[0]))*LimitCollected);
		}
		CollectedPeople[NCollectedPeople] = person;
		NCollectedPeople += 1;
	}
}

void CollectPeople(struct tree *node)
{
	int i, j;
	for (i = 0; i < 10; i++)
	{
		if (node->sons[i] != NULL)
		{
			CollectPeople(node->sons[i]);
		}
	}

	for (j = 0; j < node->numberOfPeople; j++)
	{
		CollectPerson(node->arr[j]);
	}
}

void FindPeople(struct tree *node, int numberOfNumbers)
{
	while (numberOfNumbers--)
	{
		if (node->sons[numbers[originalNumberOfNumbers - numberOfNumbers - 1] - '0'] == NULL)
		{
			return;
		}
		node = node->sons[numbers[originalNumberOfNumbers - numberOfNumbers - 1] - '0'];
	}
	CollectPeople(node);
}

void DeleteTree(struct tree *node)
{
	int i, j;
	for (i = 0; i < 10; i++)
	{
		if (node->sons[i] != NULL)
		{
			DeleteTree(node->sons[i]);
		}
	}
	for (j = 0; j<node->numberOfPeople; j++)
	{
		free(node->arr[j]);
	}
	free(node->arr);
	free(node);
}


int Read()
{
	int numberOfWhiteSpaces = 0, limitS = 0, limitN = 0, correct = 1;
	numberOfNumbers = 0;
	name = 0;
	surname = 0;
	space = 1;
	char character;
	nameArr = NULL;
	surnameArr = NULL;
	character = getchar();
	if (character == '+')
	{
		character = getchar();
		while (character != '\n' && !feof(stdin))
		{
			if (character == ' ')
			{
				numberOfWhiteSpaces++;
			}
			else if ((character - '0') < 10 && (character - '0') >= 0)
			{
				if (numberOfWhiteSpaces != 1 || numberOfNumbers == 20 || correct == 0)
				{
					correct = 0;
				}
				else
				{
					numbers[numberOfNumbers] = character;
					numberOfNumbers++;
				}
			}
			else if (((character - 'a') >= 0 && (character - 'a') < 26) || ((character - 'A') >= 0 && (character - 'A') < 26))
			{
				if (numberOfNumbers == 0 || (numberOfWhiteSpaces == 3 && name == 0) || (numberOfWhiteSpaces != 2 && numberOfWhiteSpaces != 3) || correct == 0)
				{
					correct = 0;
				}
				if (numberOfWhiteSpaces == 2 && correct)
				{
					if (name == limitN)
					{
						if (limitN == 0)
						{
							limitN = 16;
						}
						else
						{
							limitN *= 2;
						}
						nameArr = (char*)realloc(nameArr, sizeof(nameArr[0])* limitN);
					}
					nameArr[name] = character;
					name += 1;
				}
				else if (numberOfWhiteSpaces == 3 && correct)
				{
					if (surname == limitS)
					{
						if (limitS == 0)
						{
							limitS = 16;
						}
						else
						{
							limitS *= 2;
						}
						surnameArr = (char*)realloc(surnameArr, sizeof(surnameArr[0])* limitS);
					}
					surnameArr[surname] = character;
					surname += 1;
				}
			}
			else
			{
				correct = 0;
			}
			character = getchar();
		}
		if (numberOfNumbers == 0 || name == 0 || numberOfWhiteSpaces < 2 || numberOfWhiteSpaces > 3 || correct == 0)
		{
			free(surnameArr);
			free(nameArr);
			return 0;
		}
		else
		{
			originalNumberOfNumbers = numberOfNumbers;
			AddPerson(root, numberOfNumbers);
			AddPersonByName(root, name + surname);
			free(surnameArr);
			free(nameArr);
			return 1;
		}
	}
	else if (character == '?')
	{
		character = getchar();
		while (character != '\n' && !feof(stdin))
		{
			if (character == ' ')
			{
				numberOfWhiteSpaces++;
			}
			else if ((character - '0') < 10 && (character - '0') >= 0)
			{
				if (numberOfWhiteSpaces != 1 || correct == 0)
				{
					correct = 0;
				}
				else
				{
				    if(numberOfNumbers<199999)
                    {
                        numbers[numberOfNumbers] = character;
                        numberOfNumbers++;
				    }
				}
			}
			else
			{
				correct = 0;
			}
			character = getchar();
		}
		if (correct && numberOfNumbers >= 1)
		{
			originalNumberOfNumbers = numberOfNumbers;
			FindPeople(root, numberOfNumbers);
			if (NCollectedPeople > 10)
			{
				printf("Celkem: %d\n", NCollectedPeople);
			}
			else
			{
				int i, j;
				for (i = 0; i < NCollectedPeople; i++)
				{
					int l = strlen(CollectedPeople[i]);
					for (j = 0; j < l; j++)
					{
						printf("%c", CollectedPeople[i][j]);
					}
					printf("\n");
				}
				printf("Celkem: %d\n", NCollectedPeople);
			}
			NCollectedPeople = 0;
			LimitCollected = 4;
			CollectedPeople = (char **)realloc(CollectedPeople, sizeof(CollectedPeople[0])*LimitCollected);
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		if (character == '\n')
		{
			return 0;
		}
		else
		{
			while (character != '\n' && !feof(stdin))
			{
				character = getchar();
			}
			return 0;
		}
	}
	return 0;
}

int main()
{
	root = (struct tree*)calloc(1, sizeof(struct tree));
	CollectedPeople = (char **)malloc(sizeof(CollectedPeople[0])*LimitCollected);
	while (1)
	{
		if (Read() == 0)
		{
			if (!feof(stdin))
			{
				printf("Nespravny vstup.\n");;
			}
			else
			{
				DeleteTree(root);
				free(CollectedPeople);
				return 0;
			}
		}
	}
	if (!feof(stdin))
	{
		printf("Nespravny vstup.\n");
	}
	DeleteTree(root);
	free(CollectedPeople);
	return 0;
	//*Pavel Jahoda*/
}
