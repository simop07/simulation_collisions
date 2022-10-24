#include "particle.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>

Particle::Particle(std::string const& name, double px, double py, double pz)
    : fPx{px}, fPy{py}, fPz{pz} {
  auto index = FindParticle(name);

  // Converting unsigned int in signed int to make comparisons without narrowing
  auto size = GetSize();

  if (index == size) {
    std::cerr << "No matches found for particle \'" << name << "\'.\n";
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
  auto size = GetSize();

  if (index != size) {
    std::cerr << "Particle \'" << name << "\' already inserted.\n";
  } else {
    ResonanceType* resT = new ResonanceType{name, mass, charge, width};
    fParticleType.push_back(resT);

    // ??
    std::cout << "Inserted particle \'" << name << "\' in index " << index
              << ".\n";
  }
}

// inserire un cout che avverta della scelta??
void Particle::SetIndex(int index) {
  auto size = GetSize();

  if (index >= size) {
    std::cerr << "Particle not found.\n";
  } else {
    fIndex = index;
  }
}

void Particle::SetIndex(std::string const& name) {
  SetIndex(FindParticle(name));
}

void Particle::PrintParticle() {
  std::for_each(fParticleType.begin(), fParticleType.end(),
                [](ParticleType* p) { p->Print(); });
}

// Printing data with same spacing
void Particle::PrintIndex() const {
  using namespace std;

  cout << left << setw(10) << "\nIndex:" << fIndex << left << setw(10)
       << "\nName" << fParticleType[fIndex]->GetName() << left << setw(10)
       << "\nPx:" << fPx << left << setw(10) << "\nPy:" << fPy << left
       << setw(10) << "\nPz:" << fPz << '\n';
}

double Particle::GetPx() const { return fPx; }

double Particle::GetPy() const { return fPy; }

double Particle::GetPz() const { return fPz; }

double Particle::GetIndexMass() const {
  return fParticleType[fIndex]->GetMass();
}

/* Particle& Particle::operator+=(Particle const& p) {
  fPx += p.fPx;
  fPy += p.fPy;
  fPy += p.fPz;
  return *this;
} */

double Particle::GetEnergy() const {
  return sqrt(GetIndexMass() * GetIndexMass() +
              (fPx * fPx + fPy * fPy + fPz * fPz));
}

double Particle::InvMass(Particle const& p) const {
  return sqrt((GetEnergy() + p.GetEnergy()) * (GetEnergy() + p.GetEnergy()) -
              (fPx * p.fPx + fPy * p.fPy + fPz * p.fPz) *
                  (fPx * p.fPx + fPy * p.fPy + fPz * p.fPz));
}

void Particle::SetP(double px, double py, double pz) {
  fPx = px;
  fPy = py;
  fPz = pz;
}

int Particle::GetSize() {
  int size = fParticleType.size();
  return size;
}