#include "Frontend/Frontend.h"

int main()
{
    Connection c;
    Data backendData;
    Frontend frontend;


    frontend.Run(c,backendData);

    return 0;
}