// To compile in SHELL: "g++ resonanceType.cpp particleType.cpp particle.cpp
// simulation.cpp `root-config --cflags --libs`"

#include <algorithm>
#include <cstdlib>

#include "TCanvas.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH3F.h"
#include "TLatex.h"
#include "TMath.h"
#include "TROOT.h"
#include "TRandom.h"
#include "TStyle.h"
#include "particle.hpp"
#include "particleType.hpp"
#include "resonanceType.hpp"

// Cosmetics
void setStyle() {
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(1122);
  gStyle->SetPalette(57);
  gStyle->SetOptTitle(0);
}

void simulation() {
  // Cosmetics
  setStyle();

  // To avoid reloading manually if .so is present
  R__LOAD_LIBRARY(particleType_cpp.so);
  R__LOAD_LIBRARY(resonanceType_cpp.so);
  R__LOAD_LIBRARY(particle_cpp.so);

  // Generating random generator seed
  gRandom->SetSeed();

  // Creating TFile
  TFile* file = new TFile("simulation_collisions.root", "RECREATE");

  // \u03C0 is the unicode escape character for pion particles
  Particle::AddParticleType("\u03C0+", 0.13957, 1);
  Particle::AddParticleType("\u03C0-", 0.13957, -1);
  Particle::AddParticleType("K+", 0.49367, 1);
  Particle::AddParticleType("K-", 0.49367, -1);
  Particle::AddParticleType("p+", 0.93827, +1);
  Particle::AddParticleType("p-", 0.93827, -1);
  Particle::AddParticleType("K*", 0.89166, 0, 0.05);

  // Printing particles'info
  Particle::PrintParticle();

  // Creating histograms

  TH1F* h1 = new TH1F("h1", "Particle types", 7, 0, 7);

  TH1F* h2 =
      new TH1F("h2", "Azimuthal angle distribution", 1e3, 0, 2 * TMath::Pi());
  TH1F* h3 = new TH1F("h3", "Polar angle distribution", 1e3, 0, TMath::Pi());
  TH1F* h4 = new TH1F("h4", "Impulse distribution", 500, 0, 10);
  TH1F* h5 = new TH1F("h5", "Transverse impulse distribution", 500, 0, 10);
  TH1F* h6 = new TH1F("h6", "Particle energy distribution", 500, 0, 10);
  TH1F* h7 = new TH1F(
      "h7", "Invariant mass between discordant charge particles", 80, 0, 3);
  TH1F* h8 = new TH1F(
      "h8", "Invariant mass between concordant charge particles", 80, 0, 3);
  TH1F* h9 = new TH1F(
      "h9", "Invariant mass between pion+/kaon- and pion-/kaon+", 150, 0, 3);
  TH1F* h10 = new TH1F(
      "h10", "Invariant mass between pion+/kaon+ and pion-/kaon-", 150, 0, 3);
  TH1F* h11 = new TH1F(
      "h11", "Invariant mass between particles generated from decayment", 200,
      0, 3);
  TH3F* h12 = new TH3F("h12", "3D azimuthal and polar angles distribution", 100,
                       -1, 1, 100, -1, 1, 100, -1, 1);

  // Applying Sumw2() method on invariant mass histograms
  h7->Sumw2();
  h8->Sumw2();
  h9->Sumw2();
  h10->Sumw2();
  h11->Sumw2();

  // Respectively number of events and particles generated per event
  constexpr double nGen{1e5};
  constexpr double nPar{1e2};

  // Creating array of 100+ generated particles
  std::array<Particle, 120> eventParticles;

  // Filling histograms

  double phi{};
  double theta{};
  double p{};
  double xRNDM{};
  double yRNDM{};

  for (int i{}; i != nGen; ++i) {
    // Used to track eventParticles effective size every event
    int effectiveSize{100};

    for (int j{}; j != nPar; ++j) {
      Particle particle;

      phi = gRandom->Uniform(0, 2 * TMath::Pi());
      theta = gRandom->Uniform(0, TMath::Pi());
      p = gRandom->Exp(1);
      xRNDM = gRandom->Rndm();

      if (xRNDM < 0.4) {
        particle.SetIndex("\u03C0+");
      } else if (xRNDM < 0.8) {
        particle.SetIndex("\u03C0-");
      } else if (xRNDM < 0.85) {
        particle.SetIndex("K+");
      } else if (xRNDM < 0.90) {
        particle.SetIndex("K-");
      } else if (xRNDM < 0.945) {
        particle.SetIndex("p+");
      } else if (xRNDM < 0.99) {
        particle.SetIndex("p-");
      } else {
        particle.SetIndex("K*");
      }

      particle.SetP(p * TMath::Sin(theta) * TMath::Cos(phi),
                    p * TMath::Sin(theta) * TMath::Sin(phi),
                    p * TMath::Cos(theta));

      eventParticles[j] = particle;

      h1->Fill(particle.GetIndex());
      h2->Fill(phi);
      h3->Fill(theta);
      h12->Fill(TMath::Sin(theta) * TMath::Cos(phi),
                TMath::Sin(theta) * TMath::Sin(phi), TMath::Cos(theta));
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
                        dau1.SetIndex("\u03C0+");
                        dau2.SetIndex("K-");
                        par.Decay2Body(dau1, dau2);
                      } else {
                        dau1.SetIndex("\u03C0-");
                        dau2.SetIndex("K+");
                        par.Decay2Body(dau1, dau2);
                      }
                      eventParticles[effectiveSize] = dau1;
                      eventParticles[effectiveSize + 1] = dau2;
                      effectiveSize += 2;

                      h11->Fill(dau1.GetInvMass(dau2));
                    }
                  });

    // Variable needed to find all combinations of the particles that are in the
    // array, taken at groups of two
    int n{};

    std::for_each(
        eventParticles.begin(), eventParticles.begin() + effectiveSize - 1,
        [&](Particle const& par_i) {
          auto nx = std::next((eventParticles.begin() + n));

          std::for_each(
              nx, eventParticles.begin() + effectiveSize - 1,
              [&](Particle const& par_j) {
                if (par_i.GetCharge() * par_j.GetCharge() < 0) {
                  h7->Fill(par_i.GetInvMass(par_j));
                  if (((par_i.GetIndex() == 0 && par_j.GetIndex() == 3) ||
                       (par_i.GetIndex() == 3 && par_j.GetIndex() == 0)) ||
                      ((par_i.GetIndex() == 1 && par_j.GetIndex() == 2) ||
                       (par_i.GetIndex() == 2 && par_j.GetIndex() == 1))) {
                    h9->Fill(par_i.GetInvMass(par_j));
                  }
                } else if (par_i.GetCharge() * par_j.GetCharge() > 0) {
                  h8->Fill(par_i.GetInvMass(par_j));
                  if (((par_i.GetIndex() == 0 && par_j.GetIndex() == 2) ||
                       (par_i.GetIndex() == 2 && par_j.GetIndex() == 0)) ||
                      ((par_i.GetIndex() == 1 && par_j.GetIndex() == 3) ||
                       (par_i.GetIndex() == 3 && par_j.GetIndex() == 1))) {
                    h10->Fill(par_i.GetInvMass(par_j));
                  }
                }
              });
          ++n;
        });

    // Clearing the array at the end of every event
    std::fill(eventParticles.begin(), eventParticles.end(), Particle());
  }

  // Writing all on TFile
  file->cd();
  file->Write();
  file->Close();
}

// Add main in order to compile from SHELL
int main() {
  setStyle();

  simulation();

  return EXIT_SUCCESS;
}
