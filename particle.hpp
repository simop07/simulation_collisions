#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <vector>

#include "particleType.hpp"
#include "resonanceType.hpp"

class Particle {
 public:
  Particle(std::string const& name, double px = 0., double py = 0.,
           double pz = 0.);

  int GetIndex() const;

  static void AddParticleType(std::string const& name, double mass, int charge,
                              double width = 0.);

  void SetIndex(int index);

  void SetIndex(std::string const& name);

  static void PrintParticle();

  void PrintIndex() const;

  double GetPx() const;

  double GetPy() const;

  double GetPz() const;

  double GetIndexMass() const;

  // Particle& operator+=(Particle const& p);??

  double GetEnergy() const;

  double InvMass(Particle const& p) const;

  void SetP(double px, double py, double pz);

  // Used to get vector's size
  static int GetSize();

 private:
  static std::vector<ParticleType*> fParticleType;
  int fIndex;
  double fPx;
  double fPy;
  double fPz;

  static int FindParticle(std::string const& particleName);
};

#endif