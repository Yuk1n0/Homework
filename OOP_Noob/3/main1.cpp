#include <iostream>
using namespace std;

const int MaxSize = 100; // 栈中能保存的最多元素个数
template <class T>

class IStack
{
public:
    Istack() : Top(0){}; // 栈的构造函数
    void Push(int &n);   // 往栈顶增加元素
    {
    }
    void Pop();        // 从非空栈的栈顶删除一个元素
    T GetTop();        // 返回非空栈的栈顶元素
    bool Empty();      // 判断栈是否为空
    T Size();          // 返回栈中元素的个数
    void ClearStack(); // 将栈清空
    ~Istack();         // 栈的析构函数
private:
    T elem[MaxSize] ； // 保存栈中各元素的数组
        T Top;         // 保存栈顶的当前位置
};

int main(void)
{
    IStack a;
    return 0;
}
