#pragma once

#include "unit.hpp"

class Wavelength : public Unit {
public:
  Wavelength(const float wavelength);
};

Wavelength operator""_nm(const long double wavelength);  // Nanometers
Wavelength operator""_ang(const long double wavelength); // Angstroms

Wavelength operator""_nm(const unsigned long long wavelength);
Wavelength operator""_ang(const unsigned long long wavelength);
