#include <iostream>
#include "Tourism.h"
using namespace std;

int main(void)
{
    int sel = 1;
    cout << "====景区信息管理系统v3.1====\n";
    cout << "1.创建景区景点图\n";
    cout << "2.查询景点信息\n";
    cout << "3.旅游景点导航\n";
    cout << "4.搜索最短路径\n";
    cout << "5.预设电路规划\n";
    cout << "0.退出\n";
    while (sel)
    {
        cout << "请输入操作编号<0~5>：";
        cin >> sel;
        switch (sel)
        {
        case 1:
            CreateGraph();
            break;
        case 2:
            GetSpotInfo();
            break;
        case 3:
            TravelPaths();
            break;
        case 4:
            FindShortPath();
            break;
        case 5:
            DesignPath();
            break;
        case 0:
            cout << "退出系统" << endl;
            break;
        default:
            cout << "输入错误请重新输入！\n";
        }
    }
    return 0;
}
