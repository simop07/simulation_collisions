#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <vector>

#include "particleType.hpp"
#include "resonanceType.hpp"

class Particle {
 public:
  Particle(std::string const& name, double px = 0., double py = 0.,
           double pz = 0.);

  // Default constructor
  Particle();

  // Method used to add particles in fParticleType
  static void AddParticleType(std::string const& name, double mass, int charge,
                              double width = 0.);

  void SetIndex(int index);

  void SetIndex(std::string const& name);

  void SetP(double px, double py, double pz);

  // Getters and printers

  int GetIndex() const;

  static void PrintParticle();

  void PrintIndex() const;

  double GetPx() const;

  double GetPy() const;

  double GetPz() const;

  double GetMass() const;

  double GetEnergy() const;

  double GetInvMass(Particle const& p) const;

  // Used to get fParticleType's size in tests and in member funtions above
  static int GetSize();

  int GetCharge() const;

  // Decay in two particles
  int Decay2Body(Particle& dau1, Particle& dau2) const;

 private:
  static std::vector<ParticleType*> fParticleType;

  int fIndex;
  double fPx;
  double fPy;
  double fPz;

  static int FindParticle(std::string const& particleName);

  void Boost(double bx, double by, double bz);
};

#endif