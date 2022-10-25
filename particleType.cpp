#include "particleType.hpp"

ParticleType::ParticleType(std::string const& name, double mass, int charge)
    : fName{name}, fMass{mass}, fCharge{charge} {}

std::string const ParticleType::GetName() const { return fName; }

double ParticleType::GetMass() const { return fMass; }

int ParticleType::GetCharge() const { return fCharge; }

double ParticleType::GetWidth() const { return 0; }

// Printing data with same spacing
void ParticleType::Print() const {
  using namespace std;

  cout << left << setw(10) << "\nName:" << fName << left << setw(10)
       << "\nMass:" << fMass << left << setw(10) << "\nCharge:" << left
       << setw(10) << fCharge << '\n';
}