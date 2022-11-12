#include <array>

#include "TCanvas.h"
#include "TF1.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH3F.h"
#include "TMath.h"
#include "TROOT.h"
#include "TRandom.h"
#include "TStyle.h"
#include "particle.hpp"

void analysis() {
  using namespace std;

  // Cosmetics
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(1122);
  gStyle->SetOptFit(111);
  gStyle->SetPalette(57);
  gStyle->SetOptTitle(0);

  // Loading ROOT File
  TFile* file = new TFile("simulation_collisions.root", "READ");

  // Reading histograms in ROOT File
  TH1F* h1 = (TH1F*)file->Get("h1");
  TH1F* h2 = (TH1F*)file->Get("h2");
  TH1F* h3 = (TH1F*)file->Get("h3");
  TH1F* h4 = (TH1F*)file->Get("h4");
  TH1F* h5 = (TH1F*)file->Get("h5");
  TH1F* h6 = (TH1F*)file->Get("h6");
  TH1F* h7 = (TH1F*)file->Get("h7");
  TH1F* h8 = (TH1F*)file->Get("h8");
  TH1F* h9 = (TH1F*)file->Get("h9");
  TH1F* h10 = (TH1F*)file->Get("h10");
  TH1F* h11 = (TH1F*)file->Get("h11");
  TH3F* h12 = (TH3F*)file->Get("h12");

  // Creating array that contains all TH1F histograms
  std::array<TH1F*, 11> histos{h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11};

  // Creating Canvas and drawing histosgrams
  TCanvas* canvas =
      new TCanvas("c1", "Generation particles", 200, 10, 900, 500);
  canvas->Divide(4, 3);

  // Drawing histograms
  for (int q{}; q != 11; ++q) {
    canvas->cd(q + 1);

    // Cosmetics
    histos[q]->SetMarkerStyle(20);
    histos[q]->SetMarkerSize(0.5);
    histos[q]->SetLineColor(1);
    histos[q]->GetYaxis()->SetTitleOffset(1.2);
    histos[q]->GetXaxis()->SetTitleSize(0.04);
    histos[q]->GetYaxis()->SetTitleSize(0.04);
    histos[q]->GetXaxis()->SetTitle("x");
    histos[q]->GetYaxis()->SetTitle("Entries");
    histos[q]->DrawCopy("H");
    histos[q]->DrawCopy("E,P,SAME");
  }

  // Drawing TH3F histogram
  canvas->cd(12);
  h12->DrawCopy();

  // Analysing histograms
  std::for_each(histos.begin(), histos.end(), [&](TH1F* h) {
    cout << left << setw(10) << "\nName:" << left << setw(10) << h->GetName()
         << left << setw(10) << "\nEntries:" << h->Integral() << left
         << setw(10) << '\n';

    if (h == h1) {
      for (int i{}; i != h->GetNbinsX(); ++i) {
        cout << "\nParticles generated:" << h->GetBinContent(i) / h->Integral()
             << "\nBin:" << h->GetBinContent(i) << " ± " << h->GetBinError(i)
             << '\n';
      }
    }

    if (h == h2) {
    }
  });

  // Creating functions for fitting
  TF1* f1 = new TF1("f1", "pol0", 0., 2 * TMath::Pi());
  TF1* f2 = new TF1("f2", "pol0", 0., TMath::Pi());
  TF1* f3 = new TF1("f3", "expo", 0., 10);
  f1->SetParameter(0, 1 / 2 * TMath::Pi());
  f2->SetParameter(0, 1 / TMath::Pi());
  f3->SetParameters(0, -1);
  h2->Fit("f1", "BQ");
  h3->Fit("f2", "BQ");
  h4->Fit("f3", "BQ");
  cout << "Parameter azimuthal angle fit: " << f1->GetParameter(0) << '\n';
  cout << "Parameter polar angle fit: " << f2->GetParameter(0) << '\n';

  cout << "\u03c7^2/NDF azimuthal angle fit: "
       << f1->GetChisquare() / f1->GetNDF() << '\n';
  cout << "\u03c7^2/NDF polar angle fit: " << f2->GetChisquare() / f2->GetNDF()
       << '\n';
  cout << "\u03c7^2 probability azimuthal angle fit: " << f2->GetProb() << '\n';
  cout << "\u03c7^2 probability polar angle fit: " << f2->GetProb() << '\n';

  cout << "Parameters 3D impulse fit: 1) " << f3->GetParameter(0) << "\t 2) "
       << f3->GetParameter(1) << '\n';
  cout << "\u03c7^2/NDF 3D impulse fit: " << f3->GetChisquare() / f3->GetNDF()
       << '\n';
  cout << "\u03c7^2 probability 3d impulse fit: " << f3->GetProb() << '\n';

  // Creating histograms of differences using copy constructors
  TH1F* hDiff1 = new TH1F(*(histo[6]));
  TH1F* hDiff2 = new TH1F(*(histo[6]));

  file->Close();
}