#include "../include/functions.h"
#include "../include/array.h"
#include <iostream>
#include <memory>

int main() {
    // Используем тип double для координат.
    Array<std::shared_ptr<Figure<double>>> figures(2);

    input<double>(figures);
    print<double>(std::cout, figures);
    geomcenter<double>(std::cout, figures);
    separate_areas<double>(std::cout, figures);
    std::cout << "Summary area is " << all_area<double>(figures) << "\n";
    del<double>(figures);

    std::cout << "\nFigures after deletion:\n";
    print<double>(std::cout, figures);

    return 0;
}
