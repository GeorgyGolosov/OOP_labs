#include "../include/functions.h"

int main()
{
    std::cout << "Type count of figures: ";
    size_t cnt;
    std::cin >> cnt;

    Figure **arr = new Figure *[cnt];
    input(arr, cnt);

    print(std::cout, arr, cnt);
    geomcenter(std::cout, arr, cnt);
    separate_areas(std::cout, arr, cnt);

    std::cout << "Summary area is " << all_area(arr, cnt) << '\n';

    del(arr, cnt);
    return 0;
}
