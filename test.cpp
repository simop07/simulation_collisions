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
  // Checking for runtime error
  // CHECK_THROWS_AS(Particle par1{"p1"}, std::runtime_error);
  Particle par1{"p1"};
  Particle par2{"p2", 2.3e3, -3.43e3, -6.32e3};

  CHECK(par2.GetPx() == 2.3e3);
  CHECK(par2.GetPy() == -3.43e3);
  CHECK(par2.GetPz() == -6.32e3);

  par1.SetP(1e3, -1e3, 2.1e3);

  CHECK(par1.GetPx() == 1e3);
  CHECK(par1.GetPy() == -1e3);
  CHECK(par1.GetPz() == 2.1e3);

  Particle::AddParticleType("electron", 0.511, -1);
  par1.AddParticleType("kaon", -0.011, 3, 2.4);
  par2.AddParticleType("proton", 0.937, 1);
  // Insert tests for code above
  par1.SetIndex(1);
  par2.SetIndex(2);
  // Inssert test for SetIndex(std::string const& name)
  CHECK(par1.GetIndex() == 1);
  CHECK(par2.GetIndex() == 2);

  Particle::PrintParticle();
  // Insert code to test the above
  /*  par1.PrintIndex();
   par2.PrintIndex(); */
  // Insert code to test the above
  /* Particle::GetSize(); */
  // Insert code to test the above
}