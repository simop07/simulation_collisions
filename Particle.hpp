#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <algorithm>
#include <cassert>
#include <iterator>
#include <stdexcept>
#include <vector>

#include "ParticleType.hpp"
#include "ResonanceType.hpp"

class Particle {
 public:
  Particle(std::string const& name, double px = 0., double py = 0.,
           double pz = 0.);

  int GetIndex() const;

  static void AddParticleType(std::string const& name, double mass, int charge,
                              double width = 0.);

  void SetIndex(int index);
  void SetIndex(std::string const& name);

  /* double GetPx() const;
  double GetPy() const;
  double GetPz() const; */

 private:
  static std::vector<ParticleType*> fParticleType;
  int fIndex;
  double fPx;
  double fPy;
  double fPz;

  static int FindParticle(std::string const& particleName);
};

#endif