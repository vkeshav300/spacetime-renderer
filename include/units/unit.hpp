#pragma once

class Unit {
protected:
  float m_value;

public:
  explicit Unit(const float value);

  float get_value() const;

  friend Unit operator+(const Unit &lhs, const Unit &rhs);
  friend Unit operator-(const Unit &lhs, const Unit &rhs);
  friend Unit operator*(const Unit &lhs, const float rhs);
  friend Unit operator/(const Unit &lhs, const float rhs);

  Unit &operator+=(const Unit &other);
  Unit &operator-=(const Unit &other);
  Unit &operator*=(const float scale);
  Unit &operator/=(const float scale);
};

template <typename Derived> Derived &unit_cast(Unit &unit) {
  Derived *derived_ptr = static_cast<Derived *>(&unit);
  return *derived_ptr;
}
