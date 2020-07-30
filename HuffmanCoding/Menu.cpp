#include "Compress.h"
#include "Menu.h"

void OutMenu()
{
    cout << "================Huffman文件压缩================\n"
         << "选择功能："
         << "1.压缩文件\t"
         << "2.解压文件\t"
         << "0.退出\n";
    cout << "选择: ";
}

void MenuSelect(int k)
{
    switch (k)
    {
    case (1):
        CompFile();
        break;
    case (2):
        DeCompFile();
        break;
    case (0):
        cout << "退出" << endl;
        break;
    default:
        cout << "输入错误" << endl;
    }
}

void CompFile()
{
    int root = 256 * 2 - 1;
    char filename[SIZE];
    cout << "\n=========Huffman文件压缩=========" << endl;
    cout << "请输入文件名： ";
    cin >> filename;
    if (!Compress(filename))
    {
        cout << "压缩失败" << endl;
    }
}

void DeCompFile()
{
    char filename[SIZE];
    cout << "\n=========Huffman文件解压=========" << endl;
    cout << "请输入文件名： ";
    cin >> filename;
    cout << "解压成功" << endl;
}
