#include <iostream>
#include <vector>

using namespace std;


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

    vector<int> dp0;
    vector<int> dp1;

    int iter, target;
    cin >> iter;

    while(iter--)
    {
        cin >> target;

        if (target == 0)
            cout << "1 0" << '\n';
        else if(target == 1)
            cout << "0 1" << '\n';
        else
        {
            dp0 = {1,0};
            dp1 = {0,1};

            for(int i=2; i<=target; i++)
            {
                dp0.push_back(dp0[i-2]+dp0[i-1]);
                dp1.push_back(dp1[i-2]+dp1[i-1]);
            }

            cout << dp0[target] << " " << dp1[target] << '\n';
        }
    }

    return 0;
}