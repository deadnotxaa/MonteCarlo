#include "hit.h"
#include <cmath>

bool hit_test(float x, float y, float z) {
    // f(x; y; z) = 4 * y^2 + 4 * z^2 - 2 * x^3 + x^4
    return (4 * y * y + 4 * z * z - 2 * x * x * x + x * x * x * x) <= 0;
}

const float* get_axis_range() {
    static float range[] = {0.0, 2.0,
                            (float)(-3 * std::sqrt(3) / 8), (float)(3 * std::sqrt(3) / 8),
                            (float)(-3 * std::sqrt(3) / 8),(float)(3 * std::sqrt(3) / 8)};
    return range;
}
