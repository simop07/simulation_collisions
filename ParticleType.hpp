#ifndef PARTICLETYPE_HPP
#define PARTICLETYPE_HPP

#include <iostream>

class ParticleType {
 public:
  auto GetName() const;
  auto GetMass() const;
  auto GetCharge() const;

  ParticleType(char* name = '\0', double mass = 0., int charge = 0)
      : fName{name}, fMass{mass}, fCharge{charge} {}

 private:
  char* const fName;
  double const fMass;
  int const fCharge;
};

inline std::ostream& operator<<(std::ostream& os, ParticleType const& p) {
  os << "Name: " << p.GetName() << "Mass: " << p.GetMass()
     << "Charge: " << p.GetCharge();
  return os;
}

#endif