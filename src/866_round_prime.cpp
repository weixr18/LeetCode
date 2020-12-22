/*866. 回文素数

求出大于或等于 N 的最小回文素数。
回顾一下，如果一个数大于 1，且其因数只有 1 和它自身，那么这个数是素数。
例如，2，3，5，7，11 以及 13 是素数。
回顾一下，如果一个数从左往右读与从右往左读是一样的，那么这个数是回文数。
例如，12321 是回文数。

*/

#include <cmath>
#include <iostream>

bool isPrime(int num)
{
    if (num == 2 || num == 3 || num == 5)
        return true;
    unsigned long c = 7;
    if (num % 2 == 0 || num % 3 == 0 || num % 5 == 0 || num == 1)
        return false;
    int maxc = int(sqrt(num));
    while (c <= maxc)
    {
        if (num % c == 0)
            return false;
        c += 4;
        if (num % c == 0)
            return false;
        c += 2;
        if (num % c == 0)
            return false;
        c += 4;
        if (num % c == 0)
            return false;
        c += 2;
        if (num % c == 0)
            return false;
        c += 4;
        if (num % c == 0)
            return false;
        c += 6;
        if (num % c == 0)
            return false;
        c += 2;
        if (num % c == 0)
            return false;
        c += 6;
    }
    return true;
}

int my_pow10(int n)
{
    if (n == 0)
    {
        return 1;
    }
    else if (n == 1)
    {
        return 10;
    }
    else if (n == 2)
    {
        return 100;
    }
    else if (n == 3)
    {
        return 1000;
    }
    else if (n == 4)
    {
        return 10000;
    }
    else if (n == 5)
    {
        return 100000;
    }
    else if (n == 6)
    {
        return 1000000;
    }
    else if (n == 7)
    {
        return 10000000;
    }
    else if (n == 8)
    {
        return 100000000;
    }
    else if (n == 9)
    {
        return 1000000000;
    }
    return -1;
}

class Solution
{
public:
    int getRound(int base, int d)
    {
        int sum = 0;
        int N = base * my_pow10(d / 2);
        sum += N;
        for (int i = 0; i < d / 2; i++)
        {
            sum += ((N / my_pow10(d - 1 - i)) % 10) * (my_pow10(i));
        }
        return sum;
    }

    int primePalindrome(int N)
    {
        int n_copy = N;
        int d = 0;

        //int num[10] = {0};

        while (n_copy > 0)
        {
            //num[d] = n_copy % 10;
            n_copy = n_copy / 10;
            d++;
        }

        int base = (N / my_pow10(d / 2));

        int current = getRound(base, d);
        if (N > current)
        {
            if (base < (my_pow10((d + 1) / 2) - 1))
            {
                base++;
                current = getRound(base, d);
            }
            else
            {
                if (d % 2 == 0)
                {
                    base++;
                    d++;
                    current = getRound(base, d);
                }
                else
                {
                    base = (base++) / 10;
                    d++;
                    current = getRound(base, d);
                }
            }
        }

        while (!isPrime(current))
        {
            if (base < (my_pow10((d + 1) / 2) - 1))
            {
                base++;
                current = getRound(base, d);
            }
            else
            {
                if (d % 2 == 0)
                {
                    base++;
                    d++;
                    current = getRound(base, d);
                }
                else
                {
                    base = (base++) / 10;
                    d++;
                    current = getRound(base, d);
                }
            }
        }

        return current;
    }
};

/*
int main()
{
    Solution s;
    int n;

    //s.primePalindrome(456);

    while (true)
    {
        std::cin >> n;
        std::cout << s.primePalindrome(n) << std::endl;
    }

    return 0;
}
*/