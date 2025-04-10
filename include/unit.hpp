#pragma once

class Unit {
private:
  float m_value;

public:
  explicit Unit(const float value);

  float get_value() const;

  /* Basic math operators */
  Unit operator+(const Unit &other) const;
  Unit operator-(const Unit &other) const;
  Unit operator*(const float scale) const;
  Unit operator/(const float scale) const;

  /* Compound assignment math operators */
  Unit &operator+=(const Unit &other);
  Unit &operator-=(const Unit &other);
  Unit &operator*=(const float scale);
  Unit &operator/=(const float scale);

  /* Comparison operators */
  bool operator==(const Unit &other) const;
  bool operator!=(const Unit &other) const;
  bool operator>(const Unit &other) const;
  bool operator>=(const Unit &other) const;
  bool operator<(const Unit &other) const;
  bool operator<=(const Unit &other) const;
};

/* Wavelength (same as distance, different base unit) */
Unit operator""_nm(const long double wavelength);  // Nanometers (base)
Unit operator""_ang(const long double wavelength); // Angstroms

Unit operator""_nm(const unsigned long long wavelength);
Unit operator""_ang(const unsigned long long wavelength);

/* Temperature */
Unit operator""_K(const long double temperature); // Kelvin (base)

Unit operator""_K(const unsigned long long temperature);
