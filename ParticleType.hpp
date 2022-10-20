#ifndef PARTICLETYPE_HPP
#define PARTICLETYPE_HPP

#include <iostream>

class ParticleType {
  public:
  char const* GetName() const;
  double GetMass() const;
  int GetCharge() const;

  ParticleType(char* name, double mass, int charge)
      : fName{name}, fMass{mass}, fCharge{charge} {}

 private:
  char const* fName;
  double const fMass;
  int const fCharge;
};

inline std::ostream& operator<<(std::ostream& os, ParticleType const& p) {
  os << "Name: " << p.GetName() << "\tMass: " << p.GetMass()
     << "\tCharge: " << p.GetCharge();
  return os;
}

#endif