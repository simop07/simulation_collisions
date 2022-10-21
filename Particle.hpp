#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <vector>

#include "ParticleType.hpp"
#include "ResonanceType.hpp"

class Particle {
 public:
  Particle(std::string const& name, double px = 0., double py = 0.,
           double pz = 0.);

 private:
  static std::vector<ParticleType*> fParticleType;
  int fIndex;
  double fPx;
  double fPy;
  double fPz;

  int FindParticle(std::string const& particleName) const;
};

#endif