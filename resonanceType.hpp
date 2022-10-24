#ifndef RESONANCETYPE_HPP
#define RESONANCETYPE_HPP
#include "particleType.hpp"

class ResonanceType : public ParticleType {
 public:
  ResonanceType(std::string const& name, double mass, int charge, double width);

  double GetWidth() const;
  void Print() const override;

 private:
  double const fWidth;
};

#endif