#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
@풀이
    간단하게 정리하면 max(prevAttFinish, nextAttStart) + nextAttDur로 계산됨
    즉, 이전 기구의 종료시간이 이를수록 최소한 손해는 아님
    따라서 각 기구의 제일 빠른 종료시간을 계산해두고, 각 기구에 대해 위 식을 계산
     ㄴ 각 놀이 기구 중 제일 빨리 끝나는 것을 탄다면, 다음 놀이 기구는 어떤 것을 타야 될까? 라는 문제
    각 배열을 2번씩 순회하므로 O(m+n)임
     ㄴ 2*(m+n)
    실행결과, 0ms(over 100%), 238MB(over 90.02%)

    이것이 성립하는 이유는 prevAttFinish가 작을수록 적어도 값이 커지진 않는다는 성질 덕분임
     ㄴ 다음 기구를 고정하고, 앞의 기구를 더 일찍 끝나는 것으로 바꾼다고 생각해보면, 값이 유지되거나 작아짐
     ㄴ 따라서 제일 작은 것을 고르는 것이 항상 이득임
    
    힌트에선 prefix/suffix 개념으로 접근할 것을 제시함
     ㄴ prefix가 duration, suffix는 start+duration라고 생각하면 됨
    앞의 놀이기구를 고정하면 1) 대기없이 바로 타기 2) 대기하고 타기로 나뉨
    대기없이 바로 타는 경우엔 finish + duration이므로, duration이 최소여야 최소값임
    대기하고 타는 경우엔 suffix가 그 결과값이 되므로, suffix의 최소값을 찾아야함
    따라서 finish 이후의 suffix 중 제일 작은 것을 찾아야 함
    그리고 넘지않는 것들 중 duration이 제일 작은 것을 찾아야 함
    이를 위해 prefixMin 배열과 suffixMin 배열을 만들어야 함
     ㄴ 놀이기구를 시작시간을 기준으로 정렬했다고 치면,
     ㄴ 0~i번 놀이기구 중 duration의 최소, 그리고 i~n번 놀이기구 중 start+duration의 최소를 저장

    그러나 이 방법은 복잡성에 비해 그렇게 효과적이지 않음
    우선 정렬에 nlogn이 소요되며, 각 놀이기구마다 만들어야 하는 배열 2개씩 있음
    또한 매번 시작시간에 대해 이분탐색을 수행하여 인덱스를 얻어야 함
    즉, mlogm + nlogn + 2*(m+n) + m*logn + n*logm가 걸릴것
     ㄴ 정리하면 (m+n)(logm+logn) + 2*(m+n)
*/

class Solution {
public:
    int earliestFinishTime(vector<int>& landStartTime, vector<int>& landDuration, vector<int>& waterStartTime, vector<int>& waterDuration) {
        const int m = landStartTime.size();
        const int n = waterStartTime.size();
        int minTime = 1e6;
        int minLandFinish = 1e6;
        int minWaterFinish = 1e6;

        for (int i=0; i<m; ++i)
            minLandFinish = min(minLandFinish, landStartTime[i]+landDuration[i]);

        for (int i=0; i<n; ++i)
            minWaterFinish = min(minWaterFinish, waterStartTime[i]+waterDuration[i]);
        
        for (int i=0; i<m; ++i)
            minTime = min(minTime, max(minWaterFinish,landStartTime[i]) + landDuration[i]);

        for (int i=0; i<n; ++i)
            minTime = min(minTime, max(minLandFinish,waterStartTime[i]) + waterDuration[i]);

        return minTime;
    }
};

int main()
{
    Solution s;

    return 0;
}