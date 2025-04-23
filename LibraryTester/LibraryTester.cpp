#include <iostream>
#include <TMM_PointerArray.h>

int main()
{
    int* a = new int(1);
    int* b = new int(2);
    int* c = new int(3);
    int* d = new int(4);

    TMM_PointerArray<int> arr(a, b, c, d);

    *a = 2;

    std::cout << "| ";
    for (int i = 0; i < arr.Size(); ++i) {
        std::cout << *arr[i] << " | ";
    }
    std::cout << std::endl;
}
