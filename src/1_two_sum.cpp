/*
给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。
你可以假设每种输入只会对应一个答案。但是，数组中同一个元素不能使用两遍。

示例:

给定 nums = [2, 7, 11, 15], target = 9
因为 nums[0] + nums[1] = 2 + 7 = 9
所以返回 [0, 1]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/two-sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*
    思路：
    1. 带index排序 O(nlogn)
    2. 双指针扫描 O(n)
*/

#include <vector>
#include <iostream>
using namespace std;

template <class T>
class Stack
{
public:
    Stack(int n);
    ~Stack();
    void push(const T &t);
    T top();
    T pop();
    int size();
    int isEmpty();

private:
    T *arr;
    int count;
};

template <class T>
Stack<T>::Stack(int n)
{
    arr = new T[n];
    count = 0;
    if (!arr)
    {
        cout << "arr malloc error!" << endl;
    }
}
template <class T>
Stack<T>::~Stack()
{
    if (arr)
    {
        delete[] arr;
        arr = NULL;
    }
}

template <class T>
void Stack<T>::push(const T &t)
{
    arr[count] = t;
    count++;
}

template <class T>
T Stack<T>::top()
{
    return arr[count - 1];
}

template <class T>
T Stack<T>::pop()
{
    int ret = arr[count - 1];
    count--;
    return ret;
}

template <class T>
int Stack<T>::size()
{
    return count;
}

template <class T>
int Stack<T>::isEmpty()
{
    return size() == 0;
}

class Solution
{
public:
    struct pair
    {
        int num;
        int index;
    };

    vector<int> twoSum(vector<int> &nums, int target)
    {
        pair *num_and_index = new pair[nums.size()];

        for (int i = 0; i < nums.size(); i++)
        {
            num_and_index[i].num = nums[i];
            num_and_index[i].index = i;
        }

        quickSortNonRecursive(num_and_index, 0, nums.size() - 1);

        for (int i = 0; i < nums.size(); i++)
        {
            cout << num_and_index[i].num << ' ';
        }

        int lo = 0;
        int hi = nums.size() - 1;

        while (lo < hi)
        {
            while (num_and_index[hi].num > target - num_and_index[lo].num && lo < hi)
            {
                hi--;
            }
            if (num_and_index[hi].num == target - num_and_index[lo].num)
            {
                return vector<int>({num_and_index[lo].index, num_and_index[hi].index});
            }
            while (num_and_index[lo].num < target - num_and_index[hi].num && lo < hi)
            {
                lo++;
            }
            if (num_and_index[hi].num == target - num_and_index[lo].num)
            {
                return vector<int>({num_and_index[lo].index, num_and_index[hi].index});
            }
        }
        return vector<int>({num_and_index[lo].index, num_and_index[hi].index});
    }

    int getPartition(pair *pairs, int lo, int hi)
    {
        pair keyVal = pairs[lo];
        while (lo < hi)
        {
            while (lo < hi && pairs[hi].num >= keyVal.num)
                hi--;
            pairs[lo] = pairs[hi];
            while (lo < hi && pairs[lo].num <= keyVal.num)
                lo++;
            pairs[hi] = pairs[lo];
        }
        pairs[lo] = keyVal;
        return lo;
    }

    void quickSortNonRecursive(pair *pairs, int lo, int hi)
    {
        Stack<int> s(hi + 1); //hi+1 is length.
        if (lo < hi)
        {
            int mid = getPartition(pairs, lo, hi);
            if (mid - 1 > lo)
            {
                s.push(lo);
                s.push(mid - 1);
            }
            if (mid + 1 < hi)
            {
                s.push(mid + 1);
                s.push(hi);
            }

            while (!s.isEmpty())
            {
                int qhi = s.top();
                s.pop();
                int plo = s.top();
                s.pop();
                int pqMid = getPartition(pairs, plo, qhi);
                if (pqMid - 1 > plo)
                {
                    s.push(plo);
                    s.push(pqMid - 1);
                }
                if (pqMid + 1 < qhi)
                {
                    s.push(pqMid + 1);
                    s.push(qhi);
                }
            }
        }
    }
};

int main()
{

    vector<int> nums = vector<int>({3, 2, 4});
    int target = 6;

    Solution solution;
    auto a = solution.twoSum(nums, target);

    cout << endl;
    cout << a[0] << a[1];
    return 0;
}
