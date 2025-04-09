#include "units/unit.hpp"

Unit::Unit(const float value) : m_value(value) {}

float Unit::get_value() const {
    return m_value;
}

Unit operator+(const Unit &lhs, const Unit &rhs) {
  return Unit(lhs.m_value + rhs.m_value);
}

Unit operator-(const Unit &lhs, const Unit &rhs) {
  return Unit(lhs.m_value - rhs.m_value);
}

Unit operator*(const Unit &lhs, const float rhs) {
  return Unit(lhs.m_value * rhs);
}

Unit operator/(const Unit &lhs, const float rhs) {
  return Unit(lhs.m_value / rhs);
}

Unit &Unit::operator+=(const Unit &other) {
  m_value += other.m_value;
  return *this;
}

Unit &Unit::operator-=(const Unit &other) {
  m_value -= other.m_value;
  return *this;
}

Unit &Unit::operator*=(const float scale) {
  m_value *= scale;
  return *this;
}

Unit &Unit::operator/=(const float scale) {
  m_value /= scale;
  return *this;
}
