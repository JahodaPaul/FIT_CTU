#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <time.h>

int wrongInput = 0, pipes, lines;
long long int arr[50000], arr2[50000], result;
int powerOfTwo[26] = {1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216,33554432};

int badData(int x)
{
	//NELZE SYNCHRONIZOVAT
	if (x == 0)
	{
		int i, boolean = 0, odd = 0, even = 0;
		//BUDOU STEJNE DLOUHE ALE JINAK POSUNUTE
		for (i = 0; i<lines - 1; i++)
		{
			if (arr[i] != arr[i + 1])
				boolean = -1;
		}
		if (boolean == 0)
		{
			for (i = 0; i<lines - 1; i++)
			{
				if (arr2[i] != arr2[i + 1])
					return 1;
			}
		}
		boolean = 0;
		//NEBUDOU VSECHNY POSUNUTE O SUDY NEBO LICHY POCET ALE BUDOU VSECHNY DLOUHY SUDY POCET
		for (i = 0; i<lines; i++)
		{
			if (arr[i] % 2 == 0)
				even++;
		}
		if (even != lines)
		{
			boolean = -1;
		}
		even = 0;
		for (i = 0; i<lines; i++)
		{
			if (arr2[i] % 2 == 0)
				even++;
			else
				odd++;
		}
		if (boolean==0 && even>0 && odd>0)
        {
			return 1;
        }
		else
		{
			if (arr[0] > arr[1])
			{
				if (arr[0] % arr[1] == 0)
				boolean = 1;
			}
			else
			{
				if (arr[1] % arr[0] == 0)
				boolean = 1;
			}
			if (boolean == 1 && even > 0 && odd > 0)
				return 1;
		}
		return 0;
	}
	else {//na zacatku pipe nebo na konci pipe
		int i;
		for (i = 0; i<lines; i++)
		{
			if (arr2[i] != arr[i] && arr2[i] != 0)
				return 0;
		}
		return 1;
	}
}

int allSameValue()
{
    int i;
    for(i=0;i<lines-1;i++)
    {
        if(arr2[i] != arr2[i+1])
        return 0;
    }
    return 1;
}

void Synchronization()
{
	register int c=0;
	if(lines==2)
    {
        long long int one = 0, two = 0;
        one = arr2[0];
        two = arr2[1];
        while (one != two)
        {
            if (one<two){
                one += arr[0];
                ++c;
                if(c>10000000){
                wrongInput=1;
                return;}
                }
            else {
                two += arr[1];
            }
        }
        result = one;
    }
    else{
        int i;
        int compare = 170000000/(lines*2);
        while(allSameValue()==0)
        {
            long long int maximum = 0;
            ++c;
            for(i=0;i<lines;i++)
            {
                if(arr2[i] > maximum)
                maximum = arr2[i];
            }
            for(i=0;i<lines;i++)
            {
                if(arr2[i] < maximum)
                arr2[i] += arr[i];
            }
            if(c > compare)
            {
                wrongInput=1;
                return;
            }
        }
        result=arr2[0];
    }
}

int main()
{
	register int character;
	long long int value;
	printf("Zpravy:\n");
	while (1)
	{
		character = getchar();
		if ((character >= 97 && character <= 122))
		{
			value = powerOfTwo[character - 97];
			arr[lines] += value;
			if (pipes == 0)
			{
				arr2[lines] += value;
			}
		}
		else if (character == 124)
		{
			pipes += 1;
		}
		else if (character == 10)
		{
			if (pipes != 1)
			{
				wrongInput = 1;
				break;
			}
			lines += 1;
			pipes = 0;
		}
		else if (character == EOF)
		{
			if (pipes == 1)
			{
				lines += 1;
				pipes = 0;
			}
			if (lines < 2 || arr[lines - 1] == 0)
				wrongInput = 1;
			break;
		}
		else
		{
			wrongInput = 1;
			break;
		}
	}
	if (wrongInput == 1)
	{
		printf("Nespravny vstup.\n");
	}
	else if (badData(1) == 1)
	{
		printf("Synchronizace za: 0\n");
	}
	else if (badData(0) == 1)
	{
		printf("Nelze dosahnout.\n");
	}
	else
	{
		Synchronization();
		if(wrongInput==1)
        {
            printf("Nelze dosahnout.\n");
        }
        else{
		printf("Synchronizace za: %lld\n", result);
        }
	}
	return 0;
/*Pavel Jahoda*/
}
