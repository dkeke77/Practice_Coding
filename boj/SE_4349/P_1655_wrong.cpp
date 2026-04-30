#include <iostream>
#include <vector>

using namespace std;

/*
    2개 힙을 구성하고 두 힙간 개수의 균형을 유지하는 문제
    중간값 아래 힙(최대 힙), 중간값 위 힙(최소 힙)으로 구성

    직접 힙을 구현해봤음
    그런데 push만 있으면 될줄 알았는데 pop도 있어야됨....
    왜냐면 균형을 맞추기 위해 힙의 루트가 다른 힙으로 옮겨야할 때도 있기 때문....

    그런데 힙과 main 둘다 구현에 문제가 존재했음
     - main
        풀이자체엔 에러가 없었지만 시간이 오래 걸리는 부분들이 많았음
        우선 sync_with_stdio, cin.tie(0), cout.tie(0)가 없는 점
        몰랐지만 해당 코드가 있어야 입출력이 더 빨라진다고 함
        그리고 endl을 썼던 점
        endl은 '\n'과 flush()의 같이 하기 때문에 불필요한 동작을 하게 되는 셈
        따라서 flush()가 따로 필요없는 상황이라면 '\n'을 쓰는 것이 맞음
        결국 입출력 관련한 시간소요가 컸던 셈
     - heap
        pop에서 if (rightChildIdx < count) 내부에서 왼쪽 자식에 대한 처리가 없었음
        즉, 오른쪽 자식이 있는 상황에서 왼쪽만 자식만 작거나/클 때 swap이 일어나지 않은 것
*/

struct MinHeap
{
    vector<int> elements;
    int count = 0;

    void push(int newElem)
    {
        elements.push_back(newElem);
        count++;
        
        int newElemIdx = count-1;
        while(newElemIdx > 0)
        {
            if (elements[newElemIdx] < elements[(newElemIdx-1)/2])
            {
                swap(elements[newElemIdx], elements[(newElemIdx-1)/2]);
                newElemIdx = (newElemIdx-1)/2;
            }
            else
                break;
        }
    }

    int pop()
    {
        int root = elements.front();
        swap(elements.front(),elements.back());
        elements.pop_back();
        count--;

        int curIndex = 0;
        int smallestIdx = 0;

        while(curIndex < count)
        {
            smallestIdx = curIndex;
            int leftChildIdx = curIndex*2 + 1;
            int rightChildIdx = curIndex*2 + 2;

            if (leftChildIdx >= count)
                break;
            
            bool isLeftSmall = elements[curIndex] > elements[leftChildIdx];

            if (rightChildIdx < count)
            {
                bool isRightSmall = elements[curIndex] > elements[rightChildIdx];

                if(isLeftSmall && isRightSmall)
                {
                    if(elements[leftChildIdx] < elements[rightChildIdx])
                        smallestIdx = leftChildIdx;
                    else
                        smallestIdx = rightChildIdx;
                }
                else if(isRightSmall)
                    smallestIdx = rightChildIdx;
            }
            else
            {
                if(isLeftSmall)
                    smallestIdx = leftChildIdx;
            }

            if (smallestIdx == curIndex)
                break;
                
            swap(elements[smallestIdx],elements[curIndex]);
            curIndex = smallestIdx;
        }
        
        return root;
    }
};

struct MaxHeap
{
    vector<int> elements;
    int count = 0;

    void push(int newElem)
    {
        elements.push_back(newElem);
        count++;
        
        int newElemIdx = count-1;
        while(newElemIdx > 0)
        {
            if (elements[newElemIdx] > elements[(newElemIdx-1)/2])
            {
                swap(elements[newElemIdx], elements[(newElemIdx-1)/2]);
                newElemIdx = (newElemIdx-1)/2;
            }
            else
                break;
        }
    }

    int pop()
    {
        int root = elements.front();
        swap(elements.front(),elements.back());
        elements.pop_back();
        count--;

        int curIndex = 0;
        int largestIdx = 0;

        while(curIndex < count)
        {
            largestIdx = curIndex;
            int leftChildIdx = curIndex*2 + 1;
            int rightChildIdx = curIndex*2 + 2;

            if (leftChildIdx >= count)
                break;
            
            bool isLeftBig = elements[curIndex] < elements[leftChildIdx];

            if (rightChildIdx < count)
            {
                bool isRightBig = elements[curIndex] < elements[rightChildIdx];

                if(isLeftBig && isRightBig)
                {
                    if(elements[leftChildIdx] > elements[rightChildIdx])
                        largestIdx = leftChildIdx;
                    else
                        largestIdx = rightChildIdx;
                }
                else if(isLeftBig)
                    largestIdx = leftChildIdx;
                else if(isRightBig)
                    largestIdx = rightChildIdx;
            }
            else
            {
                if(isLeftBig)
                    largestIdx = leftChildIdx;
            }

            if (largestIdx == curIndex)
                break;

            swap(elements[largestIdx],elements[curIndex]);
            curIndex = largestIdx;
        }
        
        return root;
    }
};

int main()
{
    int iter, input;
    MaxHeap lowerMid;
    MinHeap higherMid;

    cin >> iter;

    for (int i=0; i<iter; i++)
    {
        cin >> input;

        if (lowerMid.count == 0)
            lowerMid.push(input);
        else if (higherMid.count == 0)
        {
            if (lowerMid.elements.front() > input)
            {
                higherMid.push(lowerMid.pop());
                lowerMid.push(input);
            }
            else
                higherMid.push(input);
        }
        else if(higherMid.elements.front() > input)
            lowerMid.push(input);
        else
            higherMid.push(input);

        if (lowerMid.count - higherMid.count > 1)
            higherMid.push(lowerMid.pop());
        else if(lowerMid.count - higherMid.count < -1)
            lowerMid.push(higherMid.pop());

        if (lowerMid.count < higherMid.count)
            cout << higherMid.elements.front() << '\n';
        else
            cout << lowerMid.elements.front() << '\n';
    }
}