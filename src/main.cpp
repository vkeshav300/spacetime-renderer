#include "renderer/engine.hpp"

int main() {
    Engine engine(800, 600);

    engine.stage();
    engine.render();
}