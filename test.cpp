#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "particle.hpp"
#include "particleType.hpp"
#include "resonanceType.hpp"
#include "doctest.h"

TEST_CASE("ParticleType and ResonanceType") {
  ParticleType pT1{"e-", 0.511, -1};
  ParticleType pT2{"p+", 0.937, 1};

  ResonanceType rT1{"k+", 0.423, -1, 0.7};
  ResonanceType rT2{"k-", 0.836, 1, 0.6};

  SUBCASE("Testing methods") {
    CHECK(pT1.GetName() == ("e-"));
    CHECK(pT1.GetMass() == doctest::Approx(0.511));
    CHECK(pT1.GetCharge() == -1);

    CHECK(pT2.GetName() == ("p+"));
    CHECK(pT2.GetMass() == doctest::Approx(0.937));
    CHECK(pT2.GetCharge() == 1);

    CHECK(rT1.GetName() == ("k+"));
    CHECK(rT1.GetMass() == doctest::Approx(0.423));
    CHECK(rT1.GetCharge() == -1);
    CHECK(rT1.GetWidth() == doctest::Approx(0.7));

    CHECK(rT2.GetName() == ("k-"));
    CHECK(rT2.GetMass() == doctest::Approx(0.836));
    CHECK(rT2.GetCharge() == 1);
    CHECK(rT2.GetWidth() == doctest::Approx(0.6));

    // Testing output streams directly on screen
    pT1.Print();
    pT2.Print();
    rT1.Print();
    rT2.Print();
  }

  SUBCASE("Testing virtual function") {
    ParticleType* a[2]{&pT1, &rT1};

    // Name, mass and charge are printed for ParticleType, while name, mass,
    // charge and width are shown for ResonanceType
    for (int i{}; i != 2; ++i) {
      a[i]->Print();
    }
  }
}

TEST_CASE("Particle") {
  // Separating outputs for better readability
  std::cout << "\n****************** Line break ******************\n\n";

  Particle::AddParticleType("e-", 0.511, -1);
  Particle::AddParticleType("p+", 0.937, 1);
  Particle::AddParticleType("k+", 0.423, -1, 0.7);

  // Checking error in Particle::Particle
  Particle pTest1{"Not_There"};

  // Checking right insertion
  Particle p1{"e-", 2.3e3, -3.43e3, -6.32e3};
  Particle p2{"p+"};
  Particle p3{"k+", 1e3, -1e3, 2.1e3};

  // Checking error in Particle::AddParticleType
  Particle::AddParticleType("p+", 0.466, 2, 1.8);
  Particle::AddParticleType("k+", 0.463, 1, 0.8);
}