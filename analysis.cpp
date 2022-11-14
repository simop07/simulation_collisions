// To compile in shell: "analysis.cpp `root-config --cflags --libs`"

#include <array>
#include <iomanip>
#include <iostream>

#include "TCanvas.h"
#include "TF1.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH3F.h"
#include "TLatex.h"
#include "TROOT.h"
#include "TStyle.h"

// Draw with Plain style in ROOT
void setStyle() {
  gROOT->SetStyle("Default");
  gStyle->SetOptStat(1122);
  gStyle->SetOptFit(1111);
  gStyle->SetPalette(57);
  gStyle->SetOptTitle(0);
}

void analysis() {
  using namespace std;

  // Loading ROOT File
  TFile* file1 = new TFile("simulation_collisions.root", "READ");

  // Creating ROOT File
  TFile* file2 = new TFile("analysis_collisions.root", "RECREATE");

  // Reading histograms in ROOT File
  TH1F* h1 = (TH1F*)file1->Get("h1");
  TH1F* h2 = (TH1F*)file1->Get("h2");
  TH1F* h3 = (TH1F*)file1->Get("h3");
  TH1F* h4 = (TH1F*)file1->Get("h4");
  TH1F* h5 = (TH1F*)file1->Get("h5");
  TH1F* h6 = (TH1F*)file1->Get("h6");
  TH1F* h7 = (TH1F*)file1->Get("h7");
  TH1F* h8 = (TH1F*)file1->Get("h8");
  TH1F* h9 = (TH1F*)file1->Get("h9");
  TH1F* h10 = (TH1F*)file1->Get("h10");
  TH1F* h11 = (TH1F*)file1->Get("h11");
  TH3F* h12 = (TH3F*)file1->Get("h12");

  // Creating Canvas
  TCanvas* c1 = new TCanvas("c1", "Particle Distribution", 200, 10, 900, 500);
  c1->Divide(2, 2);

  TCanvas* c2 = new TCanvas("c2", "Impulse", 200, 10, 900, 500);
  c2->Divide(1, 2);

  TCanvas* c3 = new TCanvas("c3", "Energy", 200, 10, 900, 500);
  TCanvas* c4 = new TCanvas("c4", "Invariant Mass", 200, 10, 900, 500);
  c4->Divide(2, 2);

  TCanvas* c5 =
      new TCanvas("c5", "Invariant Mass Decayed Particles", 200, 10, 900, 500);
  TCanvas* c6 = new TCanvas("c6", "1st Difference", 200, 10, 900, 500);
  TCanvas* c7 = new TCanvas("c7", "2nd Difference", 200, 10, 900, 500);

  // Creating functions for fitting
  TF1* f1 = new TF1("funiform1", "pol0", 0., 2 * TMath::Pi());
  TF1* f2 = new TF1("funiform2", "pol0", 0., TMath::Pi());
  TF1* f3 = new TF1("fexpo", "expo", 0., 10.);
  TF1* f4 = new TF1("fgaus1", "gaus", 0., 2.);
  TF1* f5 = new TF1("fgaus2", "gaus", 0., 2.);
  TF1* f6 = new TF1("fgaus3", "gaus", 0., 2.);

  // Creating histograms of differences using copy constructor
  TH1F* hDiff1 = new TH1F(*h7);
  TH1F* hDiff2 = new TH1F(*h9);

  hDiff1->SetTitle(
      "Difference between particles with concordand/discordant charge");
  hDiff2->SetTitle(
      "Difference between concordant/discordant decayed particles");

  hDiff1->Add(h7, h8, 1, -1);
  hDiff2->Add(h9, h10, 1, -1);

  // Creating array that contains all TH1F histograms
  std::array<TH1F*, 13> histos{h1, h2, h3,  h4,  h5,     h6,    h7,
                               h8, h9, h10, h11, hDiff1, hDiff2};

  // Setting parameters and fitting
  double const kMass{0.89166};
  double const kWidth{0.050};
  f1->SetParameter(0, 1e4);
  f2->SetParameter(0, 1e4);
  f3->SetParameters(0, -1);
  f4->SetParameter(1, kMass);
  f4->SetParameter(2, kWidth);
  f5->SetParameter(1, kMass);
  f5->SetParameter(2, kWidth);
  f6->SetParameter(1, kMass);
  f6->SetParameter(2, kWidth);

  // Cosmetics
  f1->SetLineColor(kYellow);
  f2->SetLineColor(kYellow);
  f3->SetLineColor(kYellow);
  f4->SetLineColor(kRed);
  f5->SetLineColor(kRed);
  f6->SetLineColor(kRed);
  f1->SetLineWidth(2);
  f2->SetLineWidth(2);
  f3->SetLineWidth(2);
  f4->SetLineWidth(2);
  f5->SetLineWidth(2);
  f6->SetLineWidth(2);
  f1->SetLineStyle(2);
  f2->SetLineStyle(2);
  f3->SetLineStyle(2);
  f4->SetLineStyle(2);
  f5->SetLineStyle(2);
  f6->SetLineStyle(2);

  h2->Fit("funiform1", "BQ");
  h3->Fit("funiform2", "BQ");
  h4->Fit("fexpo", "BQ");
  h11->Fit("fgaus3", "BQ");
  hDiff1->Fit("fgaus1", "BQ");
  hDiff2->Fit("fgaus2", "BQ");

  // Native array of particles'name
  const char* label[7]{"\u03C0+", "\u03C0-", "K+", "K-", "p+", "p-", "K*"};

  // Drawing histograms on Canvas
  std::for_each(histos.begin(), histos.end(), [&](TH1F* h) {
    if (h == h1) {
      c1->cd(1);
      h->GetXaxis()->SetBinLabel(1, "#pi+");
      h->GetXaxis()->SetBinLabel(2, "#pi-");
      h->GetXaxis()->SetBinLabel(3, label[2]);
      h->GetXaxis()->SetBinLabel(4, label[3]);
      h->GetXaxis()->SetBinLabel(5, label[4]);
      h->GetXaxis()->SetBinLabel(6, label[5]);
      h->GetXaxis()->SetBinLabel(7, label[6]);
      h->GetXaxis()->SetTitle("Particles");
    } else if (h == h2) {
      c1->cd(2);
      h->GetXaxis()->SetTitle("#theta (rad)");
      h->SetMaximum(12000);
      h->SetMinimum(8000);
    } else if (h == h3) {
      c1->cd(3);
      h->GetXaxis()->SetTitle("#phi (rad)");
      h->SetMaximum(12000);
      h->SetMinimum(8000);
    } else if (h == h4) {
      c2->cd(1);
      h->GetXaxis()->SetTitle("Impulse (GeV/c)");
    } else if (h == h5) {
      c2->cd(2);
      h->GetXaxis()->SetTitle("Transverse impulse (GeV/c)");
    } else if (h == h6) {
      c3->cd();
      h->GetXaxis()->SetTitle("Energy (GeV)");
    } else if (h == h7) {
      c4->cd(1);
      h->GetXaxis()->SetTitle("Mass (GeV/c^{2})");
    } else if (h == h8) {
      c4->cd(2);
      h->GetXaxis()->SetTitle("Mass (GeV/c^{2})");
    } else if (h == h9) {
      c4->cd(3);
      h->GetXaxis()->SetTitle("Mass (GeV/c^{2})");
    } else if (h == h10) {
      c4->cd(4);
      h->GetXaxis()->SetTitle("Mass (GeV/c^{2})");
    } else if (h == h11) {
      c5->cd();
      h->GetXaxis()->SetTitle("Mass (GeV/c^{2})");
    } else if (h == hDiff1) {
      c6->cd();
      h->GetXaxis()->SetTitle("Mass (GeV/c^{2})");
    } else if (h == hDiff2) {
      c7->cd();
      h->GetXaxis()->SetTitle("Mass (GeV/c^{2})");
    }

    // Cosmetics
    h->SetMarkerStyle(20);
    h->SetMarkerSize(0.5);
    h->SetLineColor(kBlue + 4);
    h->SetFillColor(kBlue - 2);
    h->GetYaxis()->SetTitleOffset(1.2);
    h->GetXaxis()->SetTitleSize(0.04);
    h->GetYaxis()->SetTitleSize(0.04);
    h->GetYaxis()->SetTitle("Entries");
    gStyle->SetOptFit(1111);
    h->DrawCopy("H");
    h->DrawCopy("E,P,SAME");
  });

  // Drawing 3D angle distribution
  c1->cd(4);
  h12->SetMarkerColor(kBlue + 4);
  h12->GetXaxis()->SetTitleOffset(1.5);
  h12->GetYaxis()->SetTitleOffset(1.5);
  h12->GetZaxis()->SetTitleOffset(1.2);
  h12->GetXaxis()->SetTitleSize(0.04);
  h12->GetYaxis()->SetTitleSize(0.04);
  h12->GetZaxis()->SetTitleSize(0.04);
  h12->GetXaxis()->SetTitle("x-density");
  h12->GetYaxis()->SetTitle("y-density");
  h12->GetZaxis()->SetTitle("z-density");
  h12->DrawCopy();

  // Analysing histograms

  // Printing name and entries for all histograms
  std::for_each(histos.begin(), histos.end(), [&](TH1F* h) {
    cout << left << setw(10) << "\nName:" << h->GetTitle() << left << setw(10)
         << "\nEntries:" << h->Integral() << '\n';

    if (h == h1) {
      for (int i{1}; i != h->GetNbinsX(); ++i) {
        cout << "\n\u0025 of " << label[i - 1] << left << setw(10)
             << " generated: " << (h->GetBinContent(i) / h->GetEntries()) * 100.
             << "\u0025\n"
             << label[i - 1] << " in " << i << " bin: " << h->GetBinContent(i)
             << " ± " << h->GetBinError(i) << '\n';
      }
    }
  });

  // Printing datas in shell
  cout << left << setw(39) << "\nParameter azimuthal angle fit:" << left
       << setw(38) << "\np0:" << f1->GetParameter(0) << " ± "
       << f1->GetParError(0) << left << setw(39)
       << "\n\u03c7^2/NDF azimuthal angle fit:"
       << f1->GetChisquare() / f1->GetNDF() << left << setw(39)
       << "\n\u03c7^2 probability azimuthal angle fit:" << f1->GetProb()
       << '\n';

  cout << left << setw(39) << "\nParameter azimuthal angle fit:" << left
       << setw(38) << "\np0:" << f2->GetParameter(0) << " ± "
       << f2->GetParError(0) << left << setw(39)
       << "\n\u03c7^2/NDF azimuthal angle fit:"
       << f2->GetChisquare() / f2->GetNDF() << left << setw(39)
       << "\n\u03c7^2 probability azimuthal angle fit:" << f2->GetProb()
       << '\n';

  cout << left << setw(39) << "\nParameter 3D impulse fit:" << left << setw(38)
       << "\np0:" << f2->GetParameter(0) << " ± " << f2->GetParError(0) << left
       << setw(39) << "\n\u03c7^2/NDF azimuthal angle fit:"
       << f2->GetChisquare() / f2->GetNDF() << left << setw(39)
       << "\n\u03c7^2 probability azimuthal angle fit:" << f2->GetProb()
       << '\n';

  cout << "\nParameters 3D impulse fit:" << left << setw(38)
       << "\np0:" << f3->GetParameter(0) << " ± " << f3->GetParError(0) << left
       << setw(38) << "\np1:" << f3->GetParameter(1) << " ± "
       << f3->GetParError(1) << left << setw(39)
       << "\n\u03c7^2/NDF 3D impulse fit:" << f3->GetChisquare() / f3->GetNDF()
       << left << setw(39)
       << "\n\u03c7^2 probability 3d impulse fit:" << f3->GetProb() << '\n';

  cout << left << setw(37) << "\nMass K* =" << f4->GetParameter(1) << " ± "
       << f4->GetParError(1) << left << setw(37)
       << "\nWidth K* =" << f4->GetParameter(2) << " ± " << f4->GetParError(2)
       << left << setw(37) << "\nAmplitude =" << f4->GetParameter(0) << " ± "
       << f4->GetParError(0) << left << setw(38)
       << "\n\u03c7^2/NDF 1st difference fit:"
       << f4->GetChisquare() / f4->GetNDF() << left << setw(38)
       << "\n\u03c7^2 probability 1st difference fit:" << f4->GetProb() << '\n';

  cout << left << setw(37) << "\nMass K* =" << f4->GetParameter(1) << " ± "
       << f5->GetParError(1) << left << setw(37)
       << "\nWidth K* =" << f5->GetParameter(2) << " ± " << f5->GetParError(2)
       << left << setw(37) << "\nAmplitude =" << f5->GetParameter(0) << " ± "
       << f5->GetParError(0) << left << setw(38)
       << "\n\u03c7^2/NDF 2nd difference fit:"
       << f5->GetChisquare() / f5->GetNDF() << left << setw(38)
       << "\n\u03c7^2 probability 2nd difference fit:" << f5->GetProb() << '\n';

  // Writing on new TFile
  file2->cd();
  c1->Write();
  c2->Write();
  c3->Write();
  c4->Write();
  c5->Write();
  c6->Write();
  c7->Write();

  // Saving Canvas in .pdf, .png and .gif format
  c1->Print("particleDistribution.pdf");
  c2->Print("impulse.pdf");
  c3->Print("energy.pdf");
  c4->Print("invariantMass.pdf");
  c5->Print("invariantMassDecay.pdf");
  c6->Print("decayParticleData1.pdf");
  c7->Print("decayParticleData1.pdf");
  c1->Print("particleDistribution.png");
  c2->Print("impulse.png");
  c3->Print("energy.png");
  c4->Print("invariantMass.png");
  c5->Print("invariantMassDecay.png");
  c6->Print("decayParticleData1.png");
  c7->Print("decayParticleData1.png");
  c1->Print("particleDistribution.gif");
  c2->Print("impulse.gif");
  c3->Print("energy.gif");
  c4->Print("invariantMass.gif");
  c5->Print("invariantMassDecay.gif");
  c6->Print("decayParticleData1.gif");
  c7->Print("decayParticleData1.gif");

  file1->Close();
  file2->Close();
}

int main() { analysis(); }