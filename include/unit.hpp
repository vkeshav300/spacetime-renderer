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

/* Wavelength (same as distance, different base unit) */
Unit operator""_nm(const long double wavelength);  // Nanometers
Unit operator""_ang(const long double wavelength); // Angstroms

Unit operator""_nm(const unsigned long long wavelength);
Unit operator""_ang(const unsigned long long wavelength);

/* Temperature */
Unit operator""_K(const long double temperature); // Kelvin

Unit operator""_K(const unsigned long long temperature);
