#include <iostream>
using namespace std;

int main()
{
    int iteration;
    int storage[3] = {0,1,1};
    cin >> iteration;

    for(int idx = 2; idx < iteration; idx++)
            storage[(idx+1)%3] = storage[idx%3] + storage[(idx-1)%3];
    cout << storage[iteration%3];

    return 0;
}