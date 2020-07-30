#include <iostream>
#include <climits>
#include <cstdio>
#include <ctime>
#include <vector>
using namespace std;

int BF(vector<int> &vec, int &left, int &right) //蛮力法
{
    int maxsum = INT_MIN, sum = 0;
    for (int i = 0; i < vec.size(); i++)
        for (int k = i; k < vec.size(); k++)
        {
            sum = 0;
            for (int j = i; j <= k; j++)
                sum += vec[j];
            if (sum > maxsum)
            {
                maxsum = sum;
                left = i;
                right = k;
            }
        }
    return maxsum;
}

int DC(vector<int> &vec, const int start, const int end, int &left, int &right) //分治法
{
    if (start == end)
    {
        left = start;
        right = left;
        return vec[start];
    }
    int middle = start + ((end - start) >> 1);
    int lleft, lright, rleft, rright;
    int maxLeft = DC(vec, start, middle, lleft, lright);    //左半部分最大和
    int maxRight = DC(vec, middle + 1, end, rleft, rright); //右半部分最大和
    int maxLeftBoeder = vec[middle], maxRightBorder = vec[middle + 1], mleft = middle, mright = middle + 1;
    int tmp = vec[middle];
    for (int i = middle - 1; i >= start; i--)
    {
        tmp += vec[i];
        if (tmp > maxLeftBoeder)
        {
            maxLeftBoeder = tmp;
            mleft = i;
        }
    }
    tmp = vec[middle + 1];
    for (int i = middle + 2; i <= end; i++)
    {
        tmp += vec[i];
        if (tmp > maxRightBorder)
        {
            maxRightBorder = tmp;
            mright = i;
        }
    }
    int res = max(max(maxLeft, maxRight), maxLeftBoeder + maxRightBorder);
    if (res == maxLeft)
    {
        left = lleft;
        right = lright;
    }
    else if (res == maxLeftBoeder + maxRightBorder)
    {
        left = mleft;
        right = mright;
    }
    else
    {
        left = rleft;
        right = rright;
    }
    return res;
}

int DP(vector<int> &vec, int &left, int &right) //动态规划法
{
    int maxsum = INT_MIN, sum = 0;
    int begin = 0;
    for (int i = 0; i < vec.size(); i++)
    {
        if (sum >= 0)
        {
            sum += vec[i];
        }
        else
        {
            sum = vec[i];
            begin = i;
        }

        if (maxsum < sum)
        {
            maxsum = sum;
            left = begin;
            right = i;
        }
    }
    return maxsum;
}

int main(void)
{
    int n;
    printf("请输入数组的长度：");
    scanf("%d", &n);
    vector<int> vec(n);
    printf("请依次输入数组：");
    for (int i = 0; i < n; i++)
        scanf("%d", &vec[i]);
    int left, right;

    printf("\n**********蛮力法**********\n");
    int maxsum = BF(vec, left, right); //蛮力法
    if (maxsum >= 0)
    {
        printf("最大子段和为：");
        printf("%d", maxsum);
        printf("\n最大子段的段首及段尾元素为：");
        printf("%d %d", vec[left], vec[right]);
    }
    else
        printf("%d %d", vec[0], vec[n - 1]);

    printf("\n**********分治法**********\n");
    int start = 0;
    int end = vec.size() - 1;
    maxsum = DC(vec, start, end, left, right); //分治法
    if (maxsum >= 0)
    {
        printf("最大子段和为：");
        printf("%d", maxsum);
        printf("\n最大子段的段首及段尾元素为：");
        printf("%d %d", vec[left], vec[right]);
    }
    else
        printf("0 %d %d", vec[0], vec[n - 1]);

    printf("\n**********动态规划法**********\n");
    maxsum = DP(vec, left, right); //动态规划法
    if (maxsum >= 0)
    {
        printf("最大子段和为：");
        printf("%d", maxsum);
        printf("\n最大子段的段首及段尾元素为：");
        printf("%d %d", vec[left], vec[right]);
    }
    else
        printf("%d %d", vec[0], vec[n - 1]);
    printf("\n");
    return 0;
}
