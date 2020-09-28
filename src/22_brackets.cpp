/*
22. 括号生成

数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。

示例：

输入：n = 3
输出：[
       "((()))",
       "(()())",
       "(())()",
       "()(())",
       "()()()"
     ]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/generate-parentheses
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*
    思路：
    等效成二维平面上等腰直角三角形内的曼哈顿寻路问题
    用一个栈辅助，做深度优先搜索，遍历所有可能路径。
*/

#include <vector>
#include <iostream>
#include <stdexcept>
using namespace std;

struct State
{
    int x;
    int y;
    char *path;
    int p; //pointer

    State(int _x, int _y)
    {
        x = _x;
        y = _y;
        path = nullptr;
        p = 0;
    }

    bool operator==(State &s)
    {
        return (this->x == s.x) && (this->y == s.y);
    }
};

template <typename T>
class Stack
{
public:
    T *b; //base
    T *t; //top
    int count;

    Stack(int capacity)
    {
        b = new T[capacity];
        t = b;
        count = 0;
    }

    ~Stack()
    {
        delete[] b;
    }

    void push(T &a)
    {
        *t = a;
        t++;
        count++;
    }

    T pop()
    {
        if (count > 0)
        {
            t--;
            count--;
            return *t;
        }
        else
        {
            throw out_of_range("Stack reached bottom");
        }
    }

    int size()
    {
        return count;
    }
};

class Solution
{
public:
    vector<string> generateParenthesis(int n)
    {
        vector<string> *results = new vector<string>();
        Stack<State *> st(n);

        State *cur_state = new State(0, 0);
        cur_state->path = new char[2 * n];

        State final_state = State(n, n);
        int cur_x;
        int cur_y;

        while (true)
        {
            cur_x = cur_state->x;
            cur_y = cur_state->y;

            if (cur_x == n)
            {
                if (*cur_state == final_state)
                {
                    if (cur_state->p != 2 * n)
                    {
                        throw logic_error("path should be n characters.");
                    }
                    string s = string(cur_state->path, 2 * n);
                    //cout << s << endl;
                    results->push_back(s);

                    delete[] cur_state->path;
                    cur_state->path = nullptr;
                    delete cur_state;

                    if (st.size() > 0)
                    {
                        cur_state = st.pop();
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    for (int i = cur_state->p; i < 2 * n; i++)
                    {
                        cur_state->path[i] = ')';
                    }
                    cur_state->p = 2 * n;
                    cur_state->y = n;
                }
            }
            else if (cur_x == cur_y)
            {
                cur_state->x += 1;
                cur_state->path[cur_state->p] = '(';
                cur_state->p++;
            }
            else
            {
                State *new_state = new State(cur_x, cur_y + 1);
                new_state->path = new char[2 * n];

                memcpy(new_state->path, cur_state->path, cur_state->p);
                new_state->path[cur_state->p] = ')';
                new_state->p = cur_state->p;
                new_state->p += 1;
                st.push(new_state);

                cur_state->x += 1;
                cur_state->path[cur_state->p] = '(';
                cur_state->p++;
            }
        }

        return *results;
    }
};

int main()
{
    try
    {
        Solution s;
        s.generateParenthesis(10);
    }
    catch (exception e)
    {
        cout << e.what() << endl;
    }

    return 0;
}
