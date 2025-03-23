#include "objects/primitives/square.hpp"

Square::Square() {}

Square::~Square() {
    delete m_texture;
}