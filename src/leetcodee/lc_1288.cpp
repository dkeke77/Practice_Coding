#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@접근
    n이 1000이므로 n^2으로 접근하여도 됨
    따라서 너비 순으로 정렬하고 자기보다 너비가 큰 구간끼리 비교만 하여도 충분할듯
     ㄴ 각 구간은 유일하다고 하므로, 동일한 구간이 나올 가능성은 없음
    실행 결과, 0ms(over 100%), 15MB(over 60.13%)
    너비가 동일한 구간끼리는 포함되는 경우가 존재하지 않으므로, 이를 이용하여 검사하지 않아도 될 구간을 빠르게 넘기는 것도 가능할 것
     ㄴ 너비가 2인 구간이 k개 있다면, 해당 구간들에 대해선 그 이후 구간들부터 비교를 시행하는 방식

    혹은 O(n)으로 해결하는 방법도 있는데, 정렬을 시작점 기준 오름차순, 그리고 종점 기준 내림차순으로 정렬해야함
    이렇게 되면 다른 구간을 포함하는 구간은 늘 먼저 나오게 되며, 그 구간은 종점이 더 크게 나오게 됨
     ㄴ 뒤의 구간은 지금 구간보다 앞에 나올 수 없으므로, 종점이 더 작음은 어느 구간에 포함된다는 의미가 됨
    즉, 종점이 더 큰 경우만 따지면서 진행하면 포함되는 구간을 찾아낼 수 있음
    만약 n의 크기가 지금보다 10배 이상 더 커진다면 이러한 접근만 유효할 것으로 보임
*/

class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals)
    {
        const int n = intervals.size();
        int answer = 0;

        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b){
            return (a[1]-a[0]) < (b[1]-b[0]);
        });

        for (int i=0; i<n; i++)
        {
            bool isCovered = false;
            for (int j=i+1; j<n; j++)
            {
                bool flagL = intervals[j][0] <= intervals[i][0];
                bool flagR = intervals[i][1] <= intervals[j][1];

                if (flagL && flagR)
                {
                    isCovered = true;
                    break;
                }
            }

            if (!isCovered)
                answer++;
        }

        return answer;
    }
};

int main()
{
    Solution s;

    return 0;
}