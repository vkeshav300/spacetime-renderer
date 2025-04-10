#include "unit.hpp"

Unit::Unit(const float value) : m_value(value) {}

float Unit::get_value() const { return m_value; }

Unit Unit::operator+(const Unit &other) {
  return Unit(m_value + other.m_value);
}

Unit Unit::operator-(const Unit &other) {
  return Unit(m_value - other.m_value);
}

Unit Unit::operator*(const float scale) { return Unit(m_value * scale); }

Unit Unit::operator/(const float scale) { return Unit(m_value * scale); }

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

bool Unit::operator==(const Unit &other) {
    return m_value == other.m_value;
}

bool Unit::operator!=(const Unit &other) {
    return m_value != other.m_value;
}

bool Unit::operator>(const Unit &other) {
    return m_value > other.m_value;
}

bool Unit::operator>=(const Unit &other) {
    return m_value >= other.m_value;
}

bool Unit::operator<(const Unit &other) {
    return m_value < other.m_value;
}

bool Unit::operator<=(const Unit &other) {
    return m_value <= other.m_value;
}

/* Wavelength */
Unit operator""_nm(const long double wavelength) {
  return Unit(static_cast<float>(wavelength));
}

Unit operator""_ang(const long double wavelength) {
  return Unit(static_cast<float>(wavelength) / 10.0f);
}

Unit operator""_nm(const unsigned long long wavelength) {
  return Unit(static_cast<float>(wavelength));
}

Unit operator""_ang(const unsigned long long wavelength) {
  return Unit(static_cast<float>(wavelength) / 10.0f);
}

/* Temperature */
Unit operator""_K(const long double temperature) {
  return Unit(static_cast<float>(temperature));
}

Unit operator""_K(const unsigned long long temperature) {
  return Unit(static_cast<float>(temperature));
}

