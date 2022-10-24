#include "resonanceType.hpp"

ResonanceType::ResonanceType(std::string const& name, double mass, int charge,
                             double width)
    : ParticleType{name, mass, charge}, fWidth{width} {}

double ResonanceType::GetWidth() const { return fWidth; }

void ResonanceType::Print() const {
  using namespace std;

  ParticleType::Print();
  cout << left << setw(9) << "Width:" << setw(6) << fWidth << '\n';
}
