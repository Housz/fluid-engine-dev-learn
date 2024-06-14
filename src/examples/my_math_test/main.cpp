#include <jet/jet.h>
#include <iostream>

int main() {
    jet::Vector3F axis(0, 0, 1);
    float angle = jet::kPiF / 4;
    jet::QuaternionF q(axis, angle);

    std::cout << q.w << " " << q.x << " " << q.y << " " << q.z << std::endl;

    auto m = q.matrix3();

    std::cout << m(0, 0) << " " << m(0, 1) << " " << m(0, 2) << std::endl;
    std::cout << m(1, 0) << " " << m(1, 1) << " " << m(1, 2) << std::endl;
    std::cout << m(2, 0) << " " << m(2, 1) << " " << m(2, 2) << std::endl;
    std::cout << std::endl;

    return 0;
}