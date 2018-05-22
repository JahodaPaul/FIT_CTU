#include <iostream>

using namespace std;

#define ll long long int

struct Object{
    int nOfItemsNeededToComplete;
    int * arr;
    int limit;
    int counter;
    void Init(){
        limit = 2;
        nOfItemsNeededToComplete = 0;
        arr = NULL;
        arr = (int*)realloc(arr,sizeof(int) * limit);
        counter = 0;
    }
    void Add(int n)
    {
        if(counter == limit){
            limit *= 2;
            arr = (int*)realloc(arr,sizeof(int) * limit);
        }
        arr[counter] = n;
        counter++;
    }
    void Free()
    {
        free(arr);
    }
};


Object * arrOfObjects = NULL;
ll * howLongItTakes = NULL;
ll * when = NULL;
int n;
int * zeros = NULL;
int zerosCNT,zerosLIMIT;
int * zerosTMP = NULL;
int zerosTMPCNT,zerosTMPLIMIT;
int done = 0;

int main() {
    cin>>n;
    arrOfObjects = (Object*)realloc(arrOfObjects,sizeof(Object) * n);
    howLongItTakes = (ll*)realloc(howLongItTakes,sizeof(ll) * n);
    when = (ll*)realloc(when,sizeof(ll) * n);

    int tmp;
    for(int i=0;i<n;i++) {
        arrOfObjects[i].Init();
        cin>>tmp;
        howLongItTakes[i] = tmp;
        when[i] = 0;
    }
    int howMany = 0;
    for(int i=0;i<n;i++){
        cin>>howMany;
        arrOfObjects[i].nOfItemsNeededToComplete = howMany;
        int number;
        for(int j=0;j<howMany;j++){
            cin>>number;
            arrOfObjects[number].Add(i);
        }
    }

    for(int i=0;i<n;i++){
        if(arrOfObjects[i].nOfItemsNeededToComplete == 0){
            if(zerosLIMIT == 0){
                zerosLIMIT = 2;
                zeros = (int*)realloc(zeros,sizeof(int) * zerosLIMIT);
            }
            else if(zerosLIMIT == zerosCNT) {
                zerosLIMIT *= 2;
                zeros = (int*)realloc(zeros,sizeof(int) * zerosLIMIT);
            }
            zeros[zerosCNT] = i;
            zerosCNT++;
        }
    }

    while(zerosCNT != 0){
        for(int i=0;i<zerosCNT;i++)
        {
            for(int j=0;j<arrOfObjects[zeros[i]].counter;j++)
            {
                arrOfObjects[arrOfObjects[zeros[i]].arr[j]].nOfItemsNeededToComplete -= 1;
                if(when[arrOfObjects[zeros[i]].arr[j]] < (howLongItTakes[zeros[i]] + when[zeros[i]]) ){
                    when[arrOfObjects[zeros[i]].arr[j]] = (howLongItTakes[zeros[i]] + when[zeros[i]]);
                }
                if(arrOfObjects[arrOfObjects[zeros[i]].arr[j]].nOfItemsNeededToComplete == 0){
                    //NEW array
                    if(zerosTMPLIMIT == 0){
                        zerosTMPLIMIT = 2;
                        zerosTMP = (int*)realloc(zerosTMP,sizeof(int) * zerosTMPLIMIT);
                    }
                    else if(zerosTMPLIMIT == zerosTMPCNT) {
                        zerosTMPLIMIT *= 2;
                        zerosTMP = (int*)realloc(zerosTMP,sizeof(int) * zerosTMPLIMIT);
                    }
                    zerosTMP[zerosTMPCNT] = arrOfObjects[zeros[i]].arr[j];
                    zerosTMPCNT++;
                }
            }
        }


        free(zeros);
        done += zerosCNT;
        zerosCNT = zerosTMPCNT;
        zerosLIMIT = zerosTMPLIMIT;
        zeros=NULL;zeros = zerosTMP;
        zerosTMP = NULL;
        zerosTMPLIMIT = 0;
        zerosTMPCNT = 0;

    }

    if(done != n)
    {
        cout << "No solution." << endl;
    }
    else{
        ll max = 0;
        for(int i=0;i<n;i++){
            if(when[i]+howLongItTakes[i] > max){
                max = when[i]+howLongItTakes[i];
            }
        }
        cout << max << endl;
        for(int i=0;i<n;i++){
            cout << when[i] << " ";
        }
        cout << endl;
    }

    //cleaning
    for(int i=0;i<n;i++){
        if(arrOfObjects[i].arr != NULL) {
            arrOfObjects[i].Free();
        }
    }
    if(n!=0) {
        free(when);
        free(howLongItTakes);
        if(zerosTMP != NULL) {
            free(zerosTMP);
        }
        free(arrOfObjects);
    }

    return 0;
}