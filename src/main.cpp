#include "Frontend/Frontend.h"

///Creates necessary Backend and Frontend instances and starts the program using Frontend Run method.
int main()
{
    Connection c;
    Data backendData;
    Frontend frontend;


    frontend.Run(c,backendData);

    return 0;
}