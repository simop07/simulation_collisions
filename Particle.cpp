#include "Particle.hpp"
//#include <cassert>
//#include <stdexcept>
//#include <iterator>

#include <algorithm>
#include <cmath>

Particle::Particle(std::string const& name, double px, double py, double pz)
    : fPx{px}, fPy{py}, fPz{pz} {
  auto index = FindParticle(name);

  // Converting unsigned int in signed int
  auto size = GetSize();

  // scrivere la possibilità di riprovare??
  // lasciare throw
  if (index == size) {
    // throw std::runtime_error{"Invalid input: no correspondence found.\n"};
    std::cout << "No correspondence found\n";
  } else {
    fIndex = index;
  }

  // assert(fIndex != size);
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

  if (index == size) {
    // std::cerr << "Invalid input: particle already inserted.\n";
    std::cout << "Particle already inserted.\n";
  } else {
    ResonanceType* resT = new ResonanceType{name, mass, charge, width};
    fParticleType.push_back(resT);
  }
}

// inserire un cout che avverta della scelta??
void Particle::SetIndex(int index) { fIndex = index; }

void Particle::SetIndex(std::string const& name) {
  auto index = FindParticle(name);
  auto size = GetSize();

  if (index == size) {
    // std::cerr << "Invalid input: particle not found.\n";
    std::cout << "Particle not found.\n";
  } else {
    fIndex = index;
  }
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