#include "Particle.hpp"

Particle::Particle(std::string const& name, double px, double py, double pz)
    : fPx{px}, fPy{py}, fPz{pz} {
  auto index = FindParticle(name);

  // scrivere la possibilità di riprovare??
  // lasciare throw
  if (index < 0) {
    throw std::runtime_error{"Invalid input: no correspondence found.\n"};
  } else {
    fIndex = index;
  }

  assert(fIndex >= 0);
}

std::vector<ParticleType*> Particle::fParticleType{};

int Particle::FindParticle(std::string const& particleName) const {
  auto it = std::find_if(
      fParticleType.begin(), fParticleType.end(),
      [&](ParticleType* p) { return particleName == p->GetName(); });

  return it - fParticleType.begin();
}