#ifndef PARTICLETYPE_HPP
#define PARTICLETYPE_HPP

#include <iostream>
#include <iomanip>

class ParticleType {
 public:
  ParticleType(std::string const& name, double mass, int charge);

  std::string const GetName() const;
  double GetMass() const;
  int GetCharge() const;
  virtual void Print() const;

 private:
  std::string const fName;
  double const fMass;
  int const fCharge;
};

#endif