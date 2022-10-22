#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "Particle.hpp"
#include "ParticleType.hpp"
#include "ResonanceType.hpp"
#include "doctest.h"

TEST_CASE("ParticleType and ResonanceType") {
  ParticleType pType1{"electron", 0.511, -1};
  ParticleType pType2{"proton", 0.937, 1};

  ResonanceType rType1{"res1", 0.423, -1, 0.7};
  ResonanceType rType2{"res2", 0.836, 1, 0.6};

  SUBCASE("Testing methods") {
    CHECK(pType1.GetName() == ("electron"));
    CHECK(pType1.GetMass() == doctest::Approx(0.511));
    CHECK(pType1.GetCharge() == -1);

    CHECK(pType2.GetName() == ("proton"));
    CHECK(pType2.GetMass() == doctest::Approx(0.937));
    CHECK(pType2.GetCharge() == 1);

    CHECK(rType1.GetName() == ("res1"));
    CHECK(rType1.GetMass() == doctest::Approx(0.423));
    CHECK(rType1.GetCharge() == -1);
    CHECK(rType1.GetWidth() == doctest::Approx(0.7));

    CHECK(rType2.GetName() == ("res2"));
    CHECK(rType2.GetMass() == doctest::Approx(0.836));
    CHECK(rType2.GetCharge() == 1);
    CHECK(rType2.GetWidth() == doctest::Approx(0.6));

    // Testing output streams directly on screen
    pType1.Print();
    pType2.Print();
    rType1.Print();
    rType2.Print();
  }

  SUBCASE("Testing virtual function") {
    ParticleType* a[2]{&pType1, &rType1};

    // Name, mass and charge are printed for ParticleType, while name, mass,
    // charge and width are shown for ResonanceType
    for (int i{}; i != 2; ++i) {
      a[i]->Print();
    }
  }
}

TEST_CASE("Particle") {
  // Particle p1{"electron"};
  // Particle p2{"proton", 2.8e-2, -5.3e-3, 4.5e-2};

  // CHECK_THROWS_MESSAGE()??
}