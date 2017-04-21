#include "Frontend.h"

int main()
{
    Connection c;
    Frontend frontend;
    Data backendData;

    frontend.Run(c,backendData);

    return 0;
}