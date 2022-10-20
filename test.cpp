#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "ParticleType.hpp"
#include "doctest.h"

TEST_CASE("ParticleType methods") {
  ParticleType pType1{"electron", 0.511, -1};
  ParticleType pType2{"proton", 0.937, 1};

  CHECK(pType1.GetName() == ("electron"));
  CHECK(pType1.GetMass() == doctest::Approx(0.511));
  CHECK(pType1.GetCharge() == doctest::Approx(-1));

  CHECK(pType2.GetName() == ("proton"));
  CHECK(pType2.GetMass() == doctest::Approx(0.937));
  CHECK(pType2.GetCharge() == doctest::Approx(1));

  SUBCASE("Operator <<") {
    std::stringstream out1;
    std::stringstream out2;
    out1 << pType1;
    out2 << pType2;

    CHECK(out1.str() == "Name: electron\tMass: 0.511\tCharge: -1");
    CHECK(out2.str() == "Name: proton\tMass: 0.937\tCharge: 1");
  }
}