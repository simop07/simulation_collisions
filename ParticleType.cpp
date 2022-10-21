#include "ParticleType.hpp"
using namespace std;

ParticleType::ParticleType(string const& name, double mass, int charge)
    : fName{name}, fMass{mass}, fCharge{charge} {}

string const ParticleType::GetName() const { return fName; }

double ParticleType::GetMass() const { return fMass; }

int ParticleType::GetCharge() const { return fCharge; }

void ParticleType::Print() const {
  cout << left << setw(10) << "\nName:" << fName << left << setw(10)
       << "\nMass:" << fMass << left << setw(10) << "\nCharge:" << left
       << setw(10) << fCharge << '\n';
}