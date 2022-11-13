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

Particle::Particle() { fIndex = -1; }

std::vector<ParticleType*> Particle::fParticleType{};

int Particle::FindParticle(std::string const& particleName) {
  auto it = std::find_if(
      fParticleType.begin(), fParticleType.end(),
      [&](ParticleType* p) { return particleName == p->GetName(); });

  // Findng iterator position
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

    std::cout << "Inserted particle \'" << name << "\' in index " << index
              << ".\n";
  }
}

void Particle::SetIndex(int index) {
  auto size = GetSize();

  // < -1 is used because default constructor sets fIndex to -1
  if (index >= size || index < -1) {
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

void Particle::PrintIndex() const {
  using namespace std;

  // Printing data with same spacing
  cout << left << setw(10) << "\nIndex:" << fIndex << left << setw(10)
       << "\nName" << fParticleType[fIndex]->GetName() << left << setw(10)
       << "\nPx:" << fPx << left << setw(10) << "\nPy:" << fPy << left
       << setw(10) << "\nPz:" << fPz << '\n';
}

double Particle::GetPx() const { return fPx; }

double Particle::GetPy() const { return fPy; }

double Particle::GetPz() const { return fPz; }

double Particle::GetMass() const { return fParticleType[fIndex]->GetMass(); }

double Particle::GetEnergy() const {
  return sqrt(GetMass() * GetMass() + (fPx * fPx + fPy * fPy + fPz * fPz));
}

double Particle::GetInvMass(Particle const& p) const {
  return sqrt((GetEnergy() + p.GetEnergy()) * (GetEnergy() + p.GetEnergy()) -
              ((fPx + p.fPx) * (fPx + p.fPx) + (fPy + p.fPy) * (fPy + p.fPy) +
               (fPz + p.fPz) * (fPz + p.fPz)));
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

int Particle::GetCharge() const { return fParticleType[fIndex]->GetCharge(); }

int Particle::Decay2Body(Particle& dau1, Particle& dau2) const {
  if (GetMass() == 0.) {
    printf("Decayment cannot be preformed if mass is zero.\n");
    return 1;
  }

  double massMot = GetMass();
  double massDau1 = dau1.GetMass();
  double massDau2 = dau2.GetMass();

  if (fIndex > -1) {  // add width effect

    // gaussian random numbers

    float x1, x2, w, y1, y2;

    double invnum = 1. / RAND_MAX;
    do {
      x1 = 2.0 * rand() * invnum - 1.0;
      x2 = 2.0 * rand() * invnum - 1.0;
      w = x1 * x1 + x2 * x2;
    } while (w >= 1.0);

    w = sqrt((-2.0 * log(w)) / w);
    y1 = x1 * w;
    y2 = x2 * w;

    massMot += fParticleType[fIndex]->GetWidth() * y1;
  }

  if (massMot < massDau1 + massDau2) {
    printf(
        "Decayment cannot be preformed because mass is too low in this "
        "channel.\n");
    return 2;
  }

  double pout =
      sqrt(
          (massMot * massMot - (massDau1 + massDau2) * (massDau1 + massDau2)) *
          (massMot * massMot - (massDau1 - massDau2) * (massDau1 - massDau2))) /
      massMot * 0.5;

  double norm = 2 * M_PI / RAND_MAX;

  double phi = rand() * norm;
  double theta = rand() * norm * 0.5 - M_PI / 2.;
  dau1.SetP(pout * sin(theta) * cos(phi), pout * sin(theta) * sin(phi),
            pout * cos(theta));
  dau2.SetP(-pout * sin(theta) * cos(phi), -pout * sin(theta) * sin(phi),
            -pout * cos(theta));

  double energy = sqrt(fPx * fPx + fPy * fPy + fPz * fPz + massMot * massMot);

  double bx = fPx / energy;
  double by = fPy / energy;
  double bz = fPz / energy;

  dau1.Boost(bx, by, bz);
  dau2.Boost(bx, by, bz);

  return 0;
}

void Particle::Boost(double bx, double by, double bz) {
  double energy = GetEnergy();

  // Boost this Lorentz vector
  double b2 = bx * bx + by * by + bz * bz;
  double gamma = 1.0 / sqrt(1.0 - b2);
  double bp = bx * fPx + by * fPy + bz * fPz;
  double gamma2 = b2 > 0 ? (gamma - 1.0) / b2 : 0.0;

  fPx += gamma2 * bp * bx + gamma * bx * energy;
  fPy += gamma2 * bp * by + gamma * by * energy;
  fPz += gamma2 * bp * bz + gamma * bz * energy;
}