#include <vector>
#include <iostream>

using namespace std;

/*
@풀이
    100*100이니까 그냥 브루트포스로 풀음
    모든 조합 중 제일 작은 값을 저장하면 됨
    실행 결과, 4ms(over 64.75%), 92MB(over 60.66%)
    
*/

class Solution {
public:
    int earliestFinishTime(vector<int>& landStartTime, vector<int>& landDuration, vector<int>& waterStartTime, vector<int>& waterDuration) {
        int minTime = 100'000;

        for (int i=0; i<landStartTime.size(); ++i)
        {
            int start0 = landStartTime[i];
            int dur0 = landDuration[i];

            for (int j=0; j<waterStartTime.size(); ++j)
            {
                int temp = 0;
                int start1 = waterStartTime[j];
                int dur1 = waterDuration[j];

                if (start0 < start1)
                    temp = start0 + dur0 + max(0,start1-start0-dur0) + dur1;
                else
                    temp = start1 + dur1 + max(0,start0-start1-dur1) + dur0;
                
                minTime = min(minTime, temp);
            }
        }

        return minTime;
    }
};

int main()
{
    Solution s;

    return 0;
}