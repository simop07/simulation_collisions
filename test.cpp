#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "particle.hpp"
#include "particleType.hpp"
#include "resonanceType.hpp"

TEST_CASE("ParticleType and ResonanceType") {
  ParticleType const pT1{"e-", 0.511, -1};
  ParticleType const pT2{"p+", 10e3, 1};

  ResonanceType const rT1{"k+", 0.423, -1, 0.7};
  ResonanceType const rT2{"k-", 0.836, 1, 0.6};

  SUBCASE("Testing methods") {
    CHECK(pT1.GetName() == ("e-"));
    CHECK(pT1.GetMass() == doctest::Approx(0.511));
    CHECK(pT1.GetCharge() == -1);
    CHECK(pT1.GetWidth() == 0);

    CHECK(pT2.GetName() == ("p+"));
    CHECK(pT2.GetMass() == doctest::Approx(10e3));
    CHECK(pT2.GetCharge() == 1);
    CHECK(pT2.GetWidth() == 0);

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
    // const here is needed
    ParticleType const* a[2]{&pT1, &rT1};

    // Name, mass and charge are printed for ParticleType, while name, mass,
    // charge and width are shown for ResonanceType
    for (int i{}; i != 2; ++i) {
      a[i]->Print();
    }
  }
}

TEST_CASE("Particle") {
  // Separating outputs for better readability
  std::string s{"\n****************** Line break ******************\n"};
  std::cout << s << '\n';

  Particle::AddParticleType("e-", 0.511, -1);
  Particle::AddParticleType("p+", 10e3, 1);
  Particle::AddParticleType("k+", 0.423, -1, 0.7);

  // Checking error in Particle::Particle
  Particle pTest1{"Not_There"};

  // Checking right insertion
  Particle p1{"e-", 2.3e3, -3.43e3, -6.32e3};
  Particle p2{"p+"};
  Particle const p3{"k+", 1e3, -1e3, 2.1e3};

  CHECK(Particle::GetSize() == 3);

  CHECK(p1.GetIndex() == 0);
  CHECK(p2.GetIndex() == 1);
  CHECK(p3.GetIndex() == 2);

  // Checking error in AddParticleType
  Particle::AddParticleType("p+", 0.466, 2, 1.8);
  Particle::AddParticleType("k+", 0.463, 1, 0.8);

  Particle::PrintParticle();

  // Checking 2 errors in SetIndex
  p1.SetIndex(4);
  p1.SetIndex("Not_There");

  CHECK_FALSE(p1.GetIndex() == 4);

  std::cout << s;

  p1.PrintIndex();
  p2.PrintIndex();
  p3.PrintIndex();

  SUBCASE("Testing Set/GetIndex") {
    p1.SetIndex(1);
    p1.PrintIndex();

    CHECK(p1.GetIndex() == 1);
    CHECK(p2.GetIndex() == 1);

    p1.SetIndex("p+");
    CHECK(p1.GetIndex() == 1);
    p1.SetIndex(0);
  }

  CHECK(p1.GetIndex() == 0);

  // Testing GetP
  CHECK(p1.GetPx() == doctest::Approx(2.3e3));
  CHECK(p1.GetPy() == doctest::Approx(-3.43e3));
  CHECK(p1.GetPz() == doctest::Approx(-6.32e3));
  CHECK(p2.GetPx() == doctest::Approx(0.));
  CHECK(p2.GetPy() == doctest::Approx(0.));
  CHECK(p2.GetPz() == doctest::Approx(0.));
  CHECK(p3.GetPx() == doctest::Approx(1e3));
  CHECK(p3.GetPy() == doctest::Approx(-1e3));
  CHECK(p3.GetPz() == doctest::Approx(2.1e3));

  // Testing GetMass
  CHECK(p1.GetMass() == doctest::Approx(0.511));
  CHECK(p2.GetMass() == doctest::Approx(10e3));
  CHECK(p3.GetMass() == doctest::Approx(0.423));

  // Testing GetCharge
  CHECK(p1.GetCharge() == -1);
  CHECK(p2.GetCharge() == 1);
  CHECK(p3.GetCharge() == -1);

  // Testing GetEnergy
  CHECK(p1.GetEnergy() == doctest::Approx(7549.66).epsilon(1.));
  CHECK(p2.GetEnergy() == doctest::Approx(10e3).epsilon(1.));
  CHECK(p3.GetEnergy() == doctest::Approx(2531.8));

  // Testing GetInvMass
  CHECK(p1.GetInvMass(p2) == doctest::Approx(15842).epsilon(1.));
  CHECK(p2.GetInvMass(p3) == doctest::Approx(12273).epsilon(1.));
  CHECK(p3.GetInvMass(p1) == doctest::Approx(7301).epsilon(1.));

  // Testing SetP
  p2.SetP(1e3, -4e3, -5e3);

  CHECK(p2.GetPx() == doctest::Approx(1e3));
  CHECK(p2.GetPy() == doctest::Approx(-4e3));
  CHECK(p2.GetPz() == doctest::Approx(-5e3));
}