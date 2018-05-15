#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double fabricWidth,fabricHeigth,sailWidth,sailHeigth,prekryv,temporary;
int result,i,finalResult;

double Pomocna(double fabric, double sail,double prekryv)
{
    if (sail <= fabric)
    {
        return 1.0;
    }
    if(((sail-prekryv)/(fabric-prekryv)) - 0.00001 < ceil(((sail-prekryv)/(fabric-prekryv))-1) )
    {
        return (int)((sail-prekryv)/(fabric-prekryv));
    }
    return ceil((sail-prekryv)/(fabric-prekryv));
}

static void Vypocet()
{
    result = (int)(Pomocna(fabricHeigth, sailHeigth, prekryv)) * (int)(Pomocna(fabricWidth, sailWidth, prekryv));
    if(finalResult == 0 || (result < finalResult))
    {
        finalResult = result;
    }
}

static int MocVelkyPrekryv()
{
    if((fabricHeigth<sailHeigth && fabricWidth < sailWidth) && (prekryv >= fabricWidth || prekryv >= fabricHeigth))
    {
        return 1;
    }
    else if((fabricHeigth<sailHeigth && fabricWidth >= sailWidth && prekryv >= fabricHeigth) ||
            (fabricWidth<sailWidth && fabricHeigth >= sailHeigth && prekryv >= fabricWidth))
    {
        return 1;
    }
    return 0;
}

int main()
{
    printf("Velikost latky:\n");
    if ( scanf ( "%lf %lf", &fabricWidth, &fabricHeigth ) != 2 || fabricWidth <= 0 || fabricHeigth <= 0)
    {
        printf("Nespravny vstup.\n");
        return 0;
    }
    printf("Velikost plachty:\n");
    if ( scanf ( "%lf %lf", &sailWidth, &sailHeigth ) != 2 || sailWidth <= 0 || sailHeigth <= 0)
    {
        printf("Nespravny vstup.\n");
        return 0;
    }

    if(!(fabricWidth >= sailWidth && fabricHeigth >= sailHeigth) && !(fabricWidth >= sailHeigth && fabricHeigth >= sailWidth))
    {
        printf("Prekryv:\n");
        if ( scanf ( "%lf", &prekryv ) != 1 || prekryv < 0)
        {
            printf("Nespravny vstup.\n");
            return 0;
        }
    }
    else{
        result = 1;
        printf("Pocet kusu latky: %d\n",result);
        return 0;
    }

    //moc velky prekryv
    if(MocVelkyPrekryv())
    {
        temporary = fabricWidth;
        fabricWidth = fabricHeigth;
        fabricHeigth = temporary;
        if(MocVelkyPrekryv())
        {
            printf("Nelze vyrobit.\n");
            return 0;
        }
        else
        {
            Vypocet();
        }
    }
    else
    {
        //vypocet - nejdriv pro neotoceny pak pro otoceny
        for(i=0;i<2;++i)
        {
            if(i==1 && MocVelkyPrekryv())
            {
                break;
            }
            Vypocet();
            temporary = fabricWidth;
            fabricWidth = fabricHeigth;
            fabricHeigth = temporary;
        }
    }
    printf("Pocet kusu latky: %d\n",finalResult);
    return 0;
    /*Pavel Jahoda*/
}
