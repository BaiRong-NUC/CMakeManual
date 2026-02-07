#include <iostream>
#include <cassert>

int main(int argc, char const *argv[])
{
    assert(1 + 2 == 3);
    assert(2 * 3 != 6); // 失败
    std::cout << "Test OK" << std::endl;
    return 0;
}
