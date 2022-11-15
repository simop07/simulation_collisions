#include "particleType.hpp"

ParticleType::ParticleType(std::string const& name, double mass, int charge)
    : fName{name}, fMass{mass}, fCharge{charge} {}

std::string const ParticleType::GetName() const { return fName; }

double ParticleType::GetMass() const { return fMass; }

int ParticleType::GetCharge() const { return fCharge; }

double ParticleType::GetWidth() const { return 0; }

void ParticleType::Print() const {
  using namespace std;

  // Printing data with same spacing
  cout << left << setw(9) << "\nName:" << fName << left << setw(9)
       << "\nMass:" << fMass << left << setw(9) << "\nCharge:" << fCharge
       << '\n';
}