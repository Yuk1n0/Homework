#include <iostream>
#include <fstream>
#include "Compress.h"
#include "Huffman.h"
#include "Menu.h"
using namespace std;

int main(void)
{
    
    OutMenu();
    int nSelet;
    cin >> nSelet;
    MenuSelect(nSelet);
    return 0;
    
}
