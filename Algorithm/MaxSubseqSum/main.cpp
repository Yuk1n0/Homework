/*//蛮力法求解最大子段和
#include <iostream>
using namespace std;

int MaxSubsequenceSum(const int array[], int n)
{
	int tempSum, maxSum;
	maxSum = 0;
	for (int i = 0; i < n; i++) // 子序列起始位置
	{
		for (int j = i; j < n; j++) // 子序列终止位置
		{
			tempSum = 0;
			for (int k = i; k < j; k++) // 子序列遍历求和
				tempSum += array[k];
			if (tempSum > maxSum) // 更新最大和值
				maxSum = tempSum;
		}
	}
	return maxSum;
}

int main()
{
	const int a[] = {-20, 11, -4, 13, -5, -2};
	//const int a[] = { 4, -3, 5, -2, -1, 2, 6, -2 };
	int maxSubSum = MaxSubsequenceSum(a, 8);
	cout << "The max subsequence sum of a is: " << maxSubSum << endl;
	system("pause");
	return 0;
} //算法复杂度为O(n^3)

/*2. 改进的蛮力算法
思想：直接在划定子序列时累加元素值，减少一层循环*/
/*#include<iostream>
using namespace std;
int MaxSubsequenceSum(const int array[], int n)
{
	int tempSum, maxSum;
	maxSum = 0;
	for (int i = 0; i < n; i++)
	{
		tempSum = 0;
		for (int j = i; j < n; j++)
		{
			tempSum += array[j];//累加元素值
			if (tempSum > maxSum)
				maxSum = tempSum;
		}
	}
	return maxSum;
}

int main()
{
	const int a[] = { -20, 11, -4, 13, -5, -2 };
	int maxSubSum = MaxSubsequenceSum(a, 8);
	cout << "The max subsequence sum of a is: " << maxSubSum << endl;
	system("pause");
	return 0;
}
  //算法复杂度为O(n2)
*/

//3分治递归算法求解最大子段和问题
//思想：将序列划分为左右两部分，则最大子段和可能在三处出现：左半部、右半部以及跨越左右边界的部分。递归的终止条件是：left == right。*/
/*
#include<iostream>
using namespace std;
int max3(int a, int b, int c)           // 求三个数的最大值
{
	int max = a;
	if (b > max)
		max = b;
	if (c > max)
		max = c;
	return max;
}

int MaxSubsequenceSum(const int array[], int left, int right)
{
	if (left == right)          // 设置基准，即递归终止条件
		return array[left];

	int middle = (left + right) / 2;

	int leftMaxSubsequenceSum = MaxSubsequenceSum(array, left, middle);     // 求左半部分最大子序列和
	int rightMaxSubsequenceSum = MaxSubsequenceSum(array, middle + 1, right);    // 求右半部分最大子序列和

	// 处理左右边界问题：最大子序列跨越中间，包含左半部分最右一个数，同时包含右半部分最左一个数
	int maxLeftBorderSum = 0;
	int maxRightBorderSum = 0;
	int tempSum = 0;        // 临时求和变量
	for (int i = middle; i >= left; i--)
	{
		tempSum += array[i];
		if (tempSum > maxLeftBorderSum)
			maxLeftBorderSum = tempSum;     // 左边包含边界最大序列和
	}
	tempSum = 0;
	for (int i = middle + 1; i < right; i++)
	{
		tempSum += array[i];
		if (tempSum > maxRightBorderSum)
			maxRightBorderSum = tempSum;    // 右边包含边界最大序列和
	}

	int maxBorderSum = maxRightBorderSum + maxLeftBorderSum;        // 最大边界子序列和等于两部分边界之和
	return max3(leftMaxSubsequenceSum, maxBorderSum, rightMaxSubsequenceSum);         // 返回三个部分的最大子序列和
}

int main()
{
	const int a[] = {-20,11,-4,13,-5,-2};
	int maxSubSum = MaxSubsequenceSum(a, 0, 5);
	cout << "The max subsequence sum of a is: " << maxSubSum << endl;
	system("pause");
	return 0;
}//算法复杂度为O(NlogN)
*/

/*//动态规划法
#include<iostream>
using namespace std;

int MaxSubsequenceSum(const int a[], int n)
{
	int tempSum = 0;
	int maxSum = 0;
	for (int j = 0; j < n; j++)   //子问题后边界
	{
		tempSum = (tempSum + a[j]) > a[j] ? (tempSum + a[j]):a[j];
		if (tempSum > maxSum)   // 更新最大和
			maxSum = tempSum;
	}
	return maxSum;
}

int main()
{
	const int a[] = { 4, -3, 5, -2, -1, 2, 6, -2 };
	int maxSubSum = MaxSubsequenceSum(a, 8);
	cout << "The max subsequence sum of a is:" << maxSubSum << endl;
	system("pause");
	return 0;
}
//算法时间复杂度为O(n)*/

#include <time.h>
#include <Windows.h>
#include <vector>
#include <iostream>
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

int main()
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
    system("pause");
    return 0;
}