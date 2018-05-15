#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int n,m,arr[2000][2000],numberQ,ans,previous,arr2[2000][2000],done=0;
char query[10000];

void checkEveryRectangleOrSquare(int i,int j,int listOneCountZero)
{
    if(j==0&&i==0&&done==0){
    int k,l,o,p;
    for(k=i;k<m;k++)
    {
        for(l=j;l<n;l++)
        {
            int sum = 0;
            for(o=i;o<=k;o++)
            {
                for(p=j;p<=l;p++)
                {
                    sum += arr[o][p];
                }
            }
            arr2[k][l] = sum;
            if(arr2[k][l]==numberQ)
            {
                ans++;
                if(listOneCountZero)
                {
                    printf("%d @ (%d,%d) - (%d,%d)\n",numberQ,j,i,l,k);
                }
            }
        }
    }
    }
    else
    {
        int k,l;
        for(k=i;k<m;k++)
        {
            for(l=j;l<n;l++)
            {
                int tmp=0;
                if(i!=0 && j!=0)
                {
                    tmp = arr2[i-1][l];
                    tmp += arr2[k][j-1]-arr2[i-1][j-1];
                    tmp = arr2[k][l] - tmp;
                    if(tmp==numberQ)
                    {
                        ans++;
                        if(listOneCountZero)
                        {
                            printf("%d @ (%d,%d) - (%d,%d)\n",numberQ,j,i,l,k);
                        }
                    }
                }
                else if(i==0)
                {
                    tmp=arr2[k][l]-arr2[k][j-1];
                    if(tmp==numberQ)
                    {
                        ans++;
                        if(listOneCountZero)
                        {
                            printf("%d @ (%d,%d) - (%d,%d)\n",numberQ,j,i,l,k);
                        }
                    }
                }
                else if(j==0)
                {
                    tmp=arr2[k][l]-arr2[i-1][l];
                    if(tmp==numberQ)
                    {
                        ans++;
                        if(listOneCountZero)
                        {
                            printf("%d @ (%d,%d) - (%d,%d)\n",numberQ,j,i,l,k);
                        }
                    }
                }
                else if(j==0 && i==0)
                {
                    if(arr2[k][l]==numberQ)
                    {
                        ans++;
                        if(listOneCountZero)
                        {
                            printf("%d @ (%d,%d) - (%d,%d)\n",numberQ,j,i,l,k);
                        }
                    }
                }

            }
        }
    }
    done=1;
}

void DarkMagicForJirkaKukackaAndRomanSvoboda(int listOneCountZero)
{
    int i,j;
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            checkEveryRectangleOrSquare(i,j,listOneCountZero);
        }
    }
}

int read()
{
    int s=0;
    while((int)(query[s]=getchar())!= 10 && s<=3)
    {
        if((s==0 && query[s] != 'l' && query[s] != 'c') || (s==1 && query[s] != 'i' && query[s] != 'o') || (s==2 && query[s] != 's' && query[s] != 'u'))
        return 0;
        if(s==3 && query[s]=='t')
        break;
        if(s==3 && query[s]=='n')
        {
            s++;
            query[s]=getchar();
            break;
        }
        s++;
    }
    return 1;
}

int main()
{
    int i,j;
    printf("Velikost mapy:\n");
    if ( scanf ( "%d %d", &n, &m ) != 2 || n <= 0 || m <= 0 || n > 2000 || m > 2000)
    {
        printf("Nespravny vstup.\n");
        return 0;
    }
    printf("Cenova mapa:\n");
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            if ( scanf ( "%d ", &arr[i][j] ) != 1)
            {
                printf("Nespravny vstup.\n");
                return 0;
            }
        }
    }
    printf("Dotazy:\n");
    while(read() && scanf("%d", &numberQ) == 1)
    {
        if(query[0]=='c' && query[1]=='o' && query[2]=='u' && query[3]=='n' && query[4]=='t')
        {
            DarkMagicForJirkaKukackaAndRomanSvoboda(0);
            printf("Celkem: %d\n",ans);
            ans=0;
        }
        else if(query[0]=='l' && query[1]=='i' && query[2]=='s' && query[3]=='t')
        {
            DarkMagicForJirkaKukackaAndRomanSvoboda(1);
            printf("Celkem: %d\n",ans);
            ans=0;
        }
        else{
            printf("Nespravny vstup.\n");
            return 0;
        }
        int o = getchar();
        if(o != 10)
        {
            break;
        }
    }
    if(!feof(stdin))
    {
        printf("Nespravny vstup.\n");
        return 0;
    }

    return 0;
/*Pavel Jahoda*/
}
