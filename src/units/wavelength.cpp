#include "units/wavelength.hpp"

Wavelength::Wavelength(const float wavelength) : Unit(wavelength) {}

Wavelength operator""_nm(const long double wavelength) {
  return Wavelength(static_cast<float>(wavelength));
}

Wavelength operator""_ang(const long double wavelength) {
    return Wavelength(static_cast<float>(wavelength) / 10.0f);
}

Wavelength operator""_nm(const unsigned long long wavelength) {
    return Wavelength(static_cast<float>(wavelength));
}

Wavelength operator""_ang(const unsigned long long wavelength) {
    return Wavelength(static_cast<float>(wavelength) / 10.0f);
}
