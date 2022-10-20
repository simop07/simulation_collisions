#include "ParticleType.hpp"

char const* ParticleType::GetName() const { return fName; }
double ParticleType::GetMass() const { return fMass; }
int ParticleType::GetCharge() const { return fCharge; }