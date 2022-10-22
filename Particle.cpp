#include "Particle.hpp"

Particle::Particle(std::string const& name, double px, double py, double pz)
    : fPx{px}, fPy{py}, fPz{pz} {
  auto index = FindParticle(name);

  // Converting unsigned in signed
  int size = fParticleType.size();

  // scrivere la possibilità di riprovare??
  // lasciare throw
  if (index == size) {
    throw std::runtime_error{"Invalid input: no correspondence found.\n"};
  } else {
    fIndex = index;
  }

  assert(fIndex != size);
}

std::vector<ParticleType*> Particle::fParticleType{};

int Particle::FindParticle(std::string const& particleName) {
  auto it = std::find_if(
      fParticleType.begin(), fParticleType.end(),
      [&](ParticleType* p) { return particleName == p->GetName(); });

  // Findng position of iterator
  return it - fParticleType.begin();
}

int Particle::GetIndex() const { return fIndex; }

void Particle::AddParticleType(std::string const& name, double mass, int charge,
                               double width) {
  auto index = FindParticle(name);
  int size = fParticleType.size();

  if (index == size) {
    std::cerr << "Particle already inserted.\n";
  } else {
    ResonanceType resT{name, mass, charge, width};

    std::transform(fParticleType.begin(), fParticleType.end(),
                   std::back_inserter(fParticleType), [&](ParticleType* p) {
                     p = &resT;
                     return p;
                   });
  }
}

// inserire un cout che avverta della scelta??
void Particle::SetIndex(int index) { fIndex = index; }

void Particle::SetIndex(std::string const& name) {
  auto index = FindParticle(name);
  int size = fParticleType.size();

  if (index == size) {
    std::cerr << "Particle already inserted.\n";
  } else {
    fIndex = index;
  }
}

/* double Particle::GetPx() const { return fPx; }
double Particle::GetPy() const { return fPy; }
double Particle::GetPz() const { return fPz; } */