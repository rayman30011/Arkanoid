#include "utils.hpp"

float len(sf::Vector2f& vec) {
    return sqrt(pow(vec.x, 2) + pow(vec.y, 2));
}

void normilize(sf::Vector2f& vec) {
    float lenght = len(vec);
    vec.x /= lenght;
    vec.y /= lenght;
}