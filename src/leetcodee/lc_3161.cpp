#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <stack>
#include <algorithm>

using namespace std;

/*
@접근1
    쿼리 1에 대해 가용한 제일 넓은 공간을 추적하는 것이 좋다고 생각함
     ㄴ 넓은 공간은 2가지 타입이 있음
     ㄴ 제일 마지막 장애물 너머인 경우, 그리고 장애물 사이 간격이 넓은 경우
     ㄴ 이 2가지를 별도로 생각해야함
    하지만 제일 넓은 장애물 사이 간격만으론 안될 수도 있음
     ㄴ 주어지는 범위가 해당 간격을 완전히 포함하지 않을 수 있음
    아무래도 set와 lowerBound, upperBound를 이용해야 할 것...
     ㄴ 시작점에 대해 upper, 끝점에 lower
        ㄴ * upper/lower 잘못 알고 있음!!!!
     ㄴ 추가만 해도 nlogn보다 낮을거라고 평가됨
    그러나 탐색은 생각만큼 단순하게 수행할 수 없음
     ㄴ 블럭의 배치는 자유롭기 때문임
     ㄴ 그렇다면 연쇄적으로 공간을 탐색하는 것은 어떨까?
        ㄴ 우선 끝점에 대해 lower 수행, 그것을 임시 시작점으로 삼음
        ㄴ 임시 시작점과 끝점의 공간이 충분한지 확인
        ㄴ 충분하지 않다면 임시 시작점을 새로운 끝점으로 삼고 다시 lower 수행...
     ㄴ 이 방식은 장애물이 촘촘하다면 이익이지만, sparse하다면 손해일것
        ㄴ 그러나 역설적으로 sparse하면 전체 탐색 수는 줄으므로 큰 손해까진 아닐 것으로 생각됨
    여기에 더해 기존 탐색 결과를 캐시로써 활용하는 것도 좋을듯
     ㄴ 0~x 범위에 최대 몇칸 블럭이 들어갔었다는 정보 정도
     ㄴ 범위별로 최대 길이를 저장/갱신하는 것이 좋을듯
        ㄴ 만약 범위를 합병할 수 있다고 합병하는 것도 생각해볼만 함
        ㄴ 0~10 범위의 캐시된 길이가 5이고, 0~14 범위는 5 미만이라면 0~14 범위의 캐시를 5로 바꿔도 된다는 것
     ㄴ 그리고 해당 구간에 장애물이 설치된다면 해당 캐시는 무효화...
        ㄴ 그렇다면 무작정 범위를 합병하면 캐시가 무효화될 가능성을 높일 수도 있음

    그런데 임시 시작점과 정확히 동일한 장애물이 있다면, 제대로 된 lower가 나오지 않을 수 있음
     ㄴ 그 사이 장애물이 있더라도 이를 판별하지 못할 수 있음
     ㄴ 때문에 upper를 사용해야 함

@실패1
    우려대로 TLE 발생
    다른 접근이나 캐싱 등이 필요할 것으로 생각됨
    우선 캐싱을 적용해보자
     ㄴ 통과된 시작점과 구간의 너비를 저장
     ㄴ 그리고 캐시 탐색 시, 해당 구간이 사용 가능한지 체크
        ㄴ 모든 장애물 추가마다 이를 체크하는 것은 비효율적이며 불필요함
     ㄴ 사용 가능하면 유지, 아니라면 업데이트
     ㄴ 맞는 캐시가 없다면.. 전체 탐색 개시
    그런데 어떻게 저장해야 필요한 캐시를 빠르게 검색할 수 있을까?
     ㄴ 시작점 기준으로 하면, 길이에 맞는 캐시를 찾기위해 탐색하는 시간이 걸림
     ㄴ 이는 반대로 하여도 유사한 문제가 발생함
    캐시는 너비를 키로, 각 끝점(혹은 시작점)을 값으로 설정
     ㄴ 그런데 너비 이상의 모든 키에 대해 확인할 의무가 발생함
     ㄴ 때문에 캐시 본연의 목적을 달성하기 어려워보임
     ㄴ 따라서 반대로 끝점-너비로 하는 것이 좋다고 판단됨
    하지만 여전히 TLE 발생

@실패2
    구간은 트리라고 볼 수 있음
    어떤 구간에 장애물이 생기면, 그것은 2개의 구간으로 나뉜 것으로 생각할 수 있음
     ㄴ 즉, 이진트리임
    아래 규칙에 따라 트리를 구성하면 될 것으로 생각됨
     ㄴ 장애물 추가는 장애물 좌표가 포함되는 노드를 찾되, 그 노드는 반드시 리프여야함
     ㄴ 검색은 2단계로 나눠서 진행해야될 것으로 보임
     ㄴ 먼저 쿼리 구간을 감싸는 최소 구간을 찾아야 함
        ㄴ child[0]을 계속 참조하며, end보다 작거나 nullptr인 경우를 찾는다
     ㄴ 해당 구간 식별 후, 각 노드들을 탐색해야됨
     ㄴ 근데 어케 탐색함?????
        ㄴ 사실상 완전 탐색을 해야됨
    여기서 재밌는 아이디어 : 자식의 개수를 세자
     ㄴ 자식의 개수를 통해 가능한 최소 길이와 최대 길이를 유추할 수 있음
     ㄴ 가능한 최소 길이는 len / count이며, 최대 길이는 len - count임
     ㄴ 이를 이용하면 유망하지 않은 쪽을 빠르게 걷어낼 수 있을 것
     ㄴ 또한 좌우 중 어느 구간을 먼저 탐색할지에 대해, 확률적으로 정답인 방향으로 유도할 수 있음
    위 설계에 사소한 오류가 있었는데, 쿼리 구간을 감싸는 최소 구간이지만 child[0]가 유망하지 않은 경우가 존재함
     ㄴ child[0]가 좁고, child[1]가 넓은 상황 or 두 구간 모두 유망한 상황
    따라서 양쪽 구간을 너비만 충족한다면 탐색 스택에 넣는 것이 맞음
    풀까지 적용했으나, 결국 TLE을 해결하지 못함
    동일한 테스트케이스를 적용해본 결과, 접근1의 방식이 훨씬 빨랐음
     ㄴ 600ms vs 8ms 정도...
    이는 부분 트리의 완전 탐색을 강제하기 때문으로 보임
    그리고 최대한 유망하지 않은 가지를 잘라낸다 하더라도, 충분히 개선할 수 없었음

    완전 탐색을 방지하기 위해선 해당 구간의 최대 간격을 부모 노드도 알고 있어야 함
    그러나 이를 전파하는 것은 정수가 아닌 포인터여야 함
     ㄴ 기존 간격과 동일한 간격을 가지는 구간이 여러 개면, 이를 덮어쓸지 판단이 불가능함

@실패3
    map을 이용해서 간격을 계산하고, 최대 길이를 후방으로 전파하는 방법을 생각함
    하지만 이 방법은 최대 길이가 수정됐음에도 이 사실을 뒤의 원소가 알 수 없는 경우가 있음
    당장 떠오르는 아이디어는 포인터를 이용해서 동일한 데이터를 바라보도록 하는 것
     ㄴ 굳이 포인터는 아니여도 길이 벡터의 인덱스여도 충분
    어느 정도는 돌아가지만, 불안정한 모습이 많이 보임
    무엇보다, 최대 길이 수정으로 인한 영향을 처리하는 데 있어서 생각보다 많은 비용이 들것으로 예상됨
     ㄴ 단순히 최대 길이만 비교하여 될 일이 아니었음
     ㄴ 최대 길이가 구간 자체의 길이보다 짧아지는 경우, 구간보다 짧은 길이만 넣을 수 있는 것으로 평가됨
     ㄴ 따라서 반드시 뒤의 모든 원소들을 순회하며 해당 상황이 발생하는지 체크해야함

@실패4
    지금 세그먼트 트리의 문제점은 어느 값을 찾기 위해 완전 탐색을 해야 한다는 점임
    하지만 최대길이를 미리 계산해두는 것은 그렇게 효율적이지만은 않음
    또한 한쪽 구간에만 계속 divide가 발생하면, O(n)이 되어버릴 수 있음
    지금 필요한 것 : 최대 값을 빠르게 알 수 있는 방식
    최대길이를 계산하면 부모가 아닌 노드들에게도 전달해야된다고 생각했지만, 무조건 그렇지만은 않음!!
    부모 노드들이 최대 길이를 알고 있으면, 탐색 과정에서 알아서 걸러지게 되어있음
    또한 최대 길이 업데이트 시에도 형제 노드들의 자식까지 안 뒤져봐도 됨
    단순히 부모로 올라가는 과정에서, 부모의 자식들의 최대 값을 비교하고 이를 갱신하면 됨
    하지만 여전히 한쪽 구간만 계속 divide되는 문제는 해결할 수 없긴 함
     ㄴ 테스트 결과, 다른 케이스들에선 빠른 실행이 보장됐으나, 한쪽 구간만 divide하는 문제에선 여전히 약했음
    따라서 삽입 전, 해당 삽입이 불균형을 해결하지 못한다고 판단되면 재구성하는 동작이 필수임

@성공
    추가는 자유롭게 할 수 있으면서, 동일한 키(혹은 값)를 통해 접근하면 이전과 동일한 곳에 도달할 수 있어야함
    그와 동시에 1회 접근 시, dpeth가 16번을 넘겨선 안됨 (<log(50,000))
     ㄴ 즉, 지금과 같은 BST는 최악의 경우 O(n)이 나올 수 있으므로 아래쪽 조건에 맞지 않음
    암시적인 트리가 있을까?
     ㄴ leaf만 실제로 존재하고, 부모는 실제로 존재하지 않는 형태
     ㄴ 새로운 원소를 추가하면 알아서 가까운 노드와 형제가 되어 부모를 만들고 최댓값을 루트로 전파
     ㄴ 이 방식에선 루트가 고정되어있지 않을것으로 생각됨
    우선 제대로 된 진짜 세그먼트 트리를 만들자
     ㄴ 지금까지 만든건 BST에 가까웠음
    이 경우, 정적이고 큰 배열을 사용해야 하므로, 최대값과 최소값에 따라 헤드를 동적으로 설정하는 것도 좋을듯
     ㄴ 모든 장애물이 0~256 구간 안에 들어간다면, 해당 구간을 바라보는 노드를 헤드로 삼는 것이 더 효율적일 것
     ㄴ 트리 방문 회수가 약간 줄어들기도 하겠지만 주 목적은 캐시 히트율을 높이는 것인데, 원본 배열이 너무 커서 큰 효용이 있을진 모르겠음
    하지만 일단 기본 구현만 하도록 하였음
    실행 결과, 2723ms(over 5.03%), 453MB(over 5.98%)
     ㄴ cout을 넣었기 때문에 많이 느렸던것
     ㄴ 제거 후, 720ms(over 5.03%), 453MB(over 5.98%)가 나옴
    다행히 통과는 하였으나, 케이스 크기에 상관없이 무조건 큰 배열을 사용하기 때문에 느린 것을 확인할 수 있음
    이에 벡터로 배열 크기를 적절하게 만들도록 하여봄
    그 결과, 645ms(over 27.69%), 455MB(over 5.98%)가 나옴
    여전히 불필요한 방문이 많이 일어나기 때문에 성능 제한이 있는 것으로 보여짐
    더불어 배열 크기에 비해 데이터들이 너무 sparse함
    이 때문에 지역성 또한 크게 떨어져 캐시 히트율에 악영향 끼친다고 보여짐

@개선
    사실 구간 탐색 도중, 0~target이 구간을 완전히 감싸는 경우엔 더 아래로 내려갈 필요가 없음
    이는 기존 dfs에서도 반영됐던 부분이었음
    하지만 dfs에서 방문하고 나서 평가하는 부분과 별도의 stack을 쓴 점이 성능을 하락시켰던 것으로 보였음
    dfs 없는 형태로 탐색을 진행하도록 함
    핵심은 왼쪽 구간이 target을 감싸고 있는가, 그리고 오른쪽 구간이 target의 일부와 겹치는가
     ㄴ 왼쪽 구간이 target을 감싸며 유망하다면 왼쪽 구간 탐색
     ㄴ 그렇지 않고 오른쪽 구간에 target이 있다면, 왼쪽 구간 유망성 평가(return) 후, 오른쪽 구간 방문
    실행 결과, 267ms(over 85.13%), 341MB(over 79.53%)
    확실히 방문 횟수가 줄어듦과 stack의 관리가 없어지면서 실행시간과 메모리 양쪽 모두 큰 향상이 있었음

    추가로, 가장 먼 장애물에 대해 특별히 별도 평가를 수행했던 것처럼, 가장 가까운 장애물에 대해서도 별도 평가를 추가함
    target이 가장 가까운 장애물보다 가깝다면, 단순히 target 구간이 블록보다 큰지만 평가하면 됨
    그리고 max값 전파 시, 부모와 새로운 max값이 동일하다면 더 전파하지 않고 break하도록 함
     ㄴ 동일한 경우에만 break 가능함
     ㄴ 큰 경우는 수정되기 전 구간의 값일 수도 있기 때문...
    개선 후, 252ms(over 91.17%), 341MB(over 79.53%)
*/

class Solution {
public:
    int maxValue = 0;

    void setValue(vector<int>& seg, int target, int value)
    {
        int start = 0;
        int end = maxValue;
        int index = 0;

        while(start != end)
        {
            int mid = (start+end) / 2;
            if (target <= mid)
            {
                end = mid;
                index = index*2 + 1;
            }
            else
            {
                start = mid+1;
                index = index*2 + 2;
            }
        }

        seg[index] = value;

        while(index != 0)
        {
            index = (index-1)/2;
            int newMax = max(seg[index*2 + 1], seg[index*2 + 2]);

            if (seg[index] == newMax)
                break;

            seg[index] = newMax;
        }
    }

    bool isAvailable(const vector<int>& seg, int target, int width)
    {
        int index = 0;
        int start = 0;
        int end = maxValue;
        bool flag = true;

        while(flag)
        {
            int mid = (start+end) / 2;

            if (target < mid && seg[index*2+1] >= width)
            {
                index = index*2+1;
                end = mid;
            }
            else if(target >= mid)
            {
                if (seg[index*2+1] >= width)
                    return true;
                else
                {
                    index = index*2+2;
                    start = mid+1;
                }
            }
            else
                flag = false;
        }

        return false;
    }

    vector<bool> getResults(vector<vector<int>>& queries) {
        const int n = queries.size();
        vector<bool> result;
        result.reserve(n);

        set<int> obstacle;
        maxValue = min(50'000, n*3);
        vector<int> seg(maxValue*4,0);

        int farestObs = 0;
        int nearestObs = maxValue;

        for (const auto& query : queries)
        {
            if (query[0] == 1)
            {
                int width = query[1];
                auto it = obstacle.upper_bound(query[1]);
                
                if (it != obstacle.end())
                {
                    setValue(seg, *it, *it - query[1]);
                }
                if (it != obstacle.begin())
                {
                    --it;
                    width -= *it;
                }
                obstacle.insert(query[1]);
                setValue(seg, query[1], width);

                farestObs = max(farestObs, query[1]);
                nearestObs = min(nearestObs, query[1]);
            }
            else if (query[0] == 2)
            {
                if (query[2] > query[1])
                {
                    result.push_back(false);
                }
                else if (farestObs <= query[1]-query[2])
                {
                    result.push_back(true);
                }
                else if (nearestObs >= query[1])
                {
                    result.push_back(true);
                }
                else
                {
                    bool available = false;
                    auto itFront = obstacle.upper_bound(query[1]-query[2]);
                    
                    if (query[1] - *itFront >= query[2])
                        result.push_back(true);
                    else
                        result.push_back(isAvailable(seg, *itFront, query[2]));                    
                }
                
            }
        }

        return result;
    }
};
int main()
{
    Solution s;

    set<int> v = {2,5,7,11,17};

    int tempEnd = 13;
    int width = 4;
    int startPoint = *v.lower_bound(tempEnd - width);
    cout << startPoint << " " << tempEnd << endl;
    while(startPoint - tempEnd < width && tempEnd != startPoint)
    {
        startPoint = tempEnd;
        tempEnd = *v.lower_bound(tempEnd - width);
        cout << startPoint << " " << tempEnd << endl;
    }

    cout << startPoint << " " << tempEnd << endl;

    return 0;
}