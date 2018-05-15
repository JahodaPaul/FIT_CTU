#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>

typedef struct TSoldier
 {
   struct TSoldier   * m_Next;
   int                 m_PersonalID;
   char                m_SecretRecord[64];
 } TSOLDIER;

#endif /* __PROGTEST__ */

TSOLDIER * mergePlatoons( TSOLDIER * p1,TSOLDIER * p2 )
{
    TSOLDIER *head = NULL;
    TSOLDIER *tmp = NULL;
    if(p1==NULL)
    {
        return p2;
    }
    if(p2==NULL)
    {
        return p1;
    }
    while(p1 && p2)
    {
        tmp = p1->m_Next;
        p1->m_Next=p2;
        p2=p2->m_Next;
        if(head==NULL)
        {
            head=p1;
            if(tmp!=NULL)
            {
                p1->m_Next->m_Next=tmp;
                p1=p1->m_Next->m_Next;
            }
            else
            {
                return head;
            }
        }
        else
        {
            if(tmp!=NULL)
            {
                p1->m_Next->m_Next=tmp;
                p1=p1->m_Next->m_Next;
            }
            else
            {
                return head;
            }
        }
    }

    if(head!=NULL)
    {
        return head;
    }
    return head;
}

void splitPlatoon( TSOLDIER * src, TSOLDIER ** p1, TSOLDIER ** p2 )
{
    int counter=0,oneGuyToKill=0;
    TSOLDIER *tmp = NULL;
    tmp = src;
    while(tmp!=NULL)
    {
        counter++;
        tmp=tmp->m_Next;
    }
    if(counter%2!=0)
    {
        oneGuyToKill=1;
        counter--;
    }
    if(counter==0)
    {
        if(oneGuyToKill)
        {
            free(src);
        }
        *p1 = NULL;
        *p2 = NULL;
        return;
    }
    else
    {
        int i,half=counter/2;
        *p1 = src;
        for(i=0;i<half;i++)
        {
            src = src->m_Next;
            p1 = &(*p1)->m_Next;
        }
        *p1 = NULL;
        *p2=src;
        for(i=0;i<half;i++)
        {
            src = src->m_Next;
            p2 = &(*p2)->m_Next;
        }
        *p2 = NULL;
        if(oneGuyToKill)
        {
            free(src);
        }
    }
}

void destroyPlatoon( TSOLDIER * src )
{
    TSOLDIER *tmp = NULL;
	while(src != NULL)
    {
		tmp = src;
		src = src->m_Next;
        free(tmp);
	}
}

/*Pavel Jahoda*/
#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
 {
   /* Vase testy */
 }
#endif /* __PROGTEST__ */
