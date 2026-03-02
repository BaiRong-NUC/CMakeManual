#include <iostream>
#include <math/math.h> // 自安装的数学库
#include <cassert>
using namespace std;

int main(int argc, char const *argv[])
{
    assert(add(2, 4) == 6);
    assert(sub(2, 4) == -2);

    cout << "Test End" << endl;
    return 0;
}
