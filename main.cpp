#include <algorithm>
#include <array>

#include "TH1F.h"
#include "TMath.h"
#include "TRandom.h"
#include "particle.hpp"
#include "particleType.hpp"
#include "resonanceType.hpp"

int main() {
  gRandom->SetSeed();

  // \u03C0 is the unicode escape character for lowercase greek letter pi
  Particle::AddParticleType("\u03C0+", 0.13957, 1);
  Particle::AddParticleType("\u03C0-", 0.13957, -1);
  Particle::AddParticleType("K+", 0.49367, 1);
  Particle::AddParticleType("K-", 0.49367, -1);
  Particle::AddParticleType("p+", 0.93827, +1);
  Particle::AddParticleType("p-", 0.93827, -1);
  Particle::AddParticleType("K*", 0.89166, 0, 0.05);

  Particle::PrintParticle();

  double nGen{1e5};
  double nPar{1e2};

  std::array<Particle, 120> eventParticles;

  /* TH1F* h[2];
  TString histName = "h";
  TString title[2] = {"generated particle types", "azimuthal and polar angle
  distribution", "impulse, transverse impulse and particles' energy
  distribution", "invariant mass"}; for (Int_t i = 0; i < 2; i++) { h[i] = new
  TH1F(histName + i, title[i], 100, 0, 10);
    // Cosmetics
    h[i]->SetLineColor(1);
    h[i]->GetYaxis()->SetTitleOffset(1.2);
    h[i]->GetXaxis()->SetTitleSize(0.04);
    h[i]->GetYaxis()->SetTitleSize(0.04);
    h[i]->GetXaxis()->SetTitle("x");
    h[i]->GetYaxis()->SetTitle("Entries");
    h[i]->Sumw2();  // Important
  } */

  TH1F* h1 = new TH1F("h1", "Generated particle types", 7, 0, 7);

  TH1F* h2 =
      new TH1F("h2", "Azimuthal angle distribution", 1e3, 0, 2 * TMath::Pi());

  TH1F* h3 = new TH1F("h3", "Polar angle distribution", 1e3, 0, TMath::Pi());
  TH1F* h4 = new TH1F("h4", "Impulse distribution", 500, 0, 10);
  TH1F* h5 = new TH1F("h5", "Transverse impulse distribution", 500, 0, 10);
  TH1F* h6 = new TH1F("h6", "Particle energy", 500, 0, 10);
  TH1F* h7 = new TH1F("h7", "Invariant mass for all particles", 80, 0, 2);

  double phi{};
  double theta{};
  double p{};
  double xRNDM{};
  double yRNDM{};

  for (int i{}; i != nGen; ++i) {
    Particle particle;

    int effectiveSize{};

    for (int j{}; j != nPar; ++j) {
      phi = gRandom->Uniform(0, 2 * TMath::Pi());
      theta = gRandom->Uniform(0, TMath::Pi());
      p = gRandom->Exp(1);
      xRNDM = gRandom->Rndm();

      if (xRNDM < 0.01) {
        particle.SetIndex("K*");
      } else if (xRNDM < 0.055) {
        particle.SetIndex("p+");
      } else if (xRNDM < 0.1) {
        particle.SetIndex("p-");
      } else if (xRNDM < 0.15) {
        particle.SetIndex("K+");
      } else if (xRNDM < 0.2) {
        particle.SetIndex("K-");
      } else if (xRNDM < 0.6) {
        particle.SetIndex("\u03C0+");
      } else {
        particle.SetIndex("\u03C0+");
      }

      particle.SetP(p * TMath::Sin(theta) * TMath::Cos(phi),
                    p * TMath::Sin(theta) * TMath::Sin(phi),
                    p * TMath::Cos(theta));

      eventParticles[j] = particle;

      effectiveSize = j;

      h1->Fill(particle.GetIndex());
      h2->Fill(phi);
      h3->Fill(theta);
      h4->Fill(p);
      h5->Fill(TMath::Sqrt(particle.GetPx() * particle.GetPx() +
                           particle.GetPy() * particle.GetPy()));
      h6->Fill(particle.GetEnergy());
    }

    std::for_each(eventParticles.begin(), eventParticles.end(),
                  [&](Particle const& par) {
                    if (par.GetIndex() == 6) {
                      Particle dau1;
                      Particle dau2;
                      yRNDM = gRandom->Rndm();

                      if (yRNDM < 0.5) {
                        dau1.SetIndex("p+");
                        dau2.SetIndex("K-");
                        par.Decay2Body(dau1, dau2);
                      } else {
                        dau1.SetIndex("p-");
                        dau2.SetIndex("K+");
                        par.Decay2Body(dau1, dau2);
                      }
                      eventParticles[effectiveSize] = dau1;
                      eventParticles[effectiveSize + 1] = dau2;
                      effectiveSize = effectiveSize + 2;
                    }
                  });

    // Getting iterator to last not empty particle
    auto it = &eventParticles.back();

    // Variable needed to find all combinations of the particles that are in the
    // array, taken at groups of two
    int n{};

    std::for_each(eventParticles.begin(), it, [&](Particle const& par_i) {
      auto nx = std::next((eventParticles.begin() + i));
      std::for_each(nx, it, [&](Particle const& par_j) {
        h7->Fill(par_i.GetInvMass(par_j));
      });

      ++n;
    });

    std::fill(eventParticles.begin(), it, Particle());
  }
}