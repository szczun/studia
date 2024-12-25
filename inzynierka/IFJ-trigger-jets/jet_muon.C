#include <RtypesCore.h>
#include <TFile.h>
#include <iostream>
#include <TTree.h>
#include <vector>
#include <TMath.h>
#include <TH1F.h>
#include <TLegend.h>
#include <TCanvas.h>


void jet_muon(){
    const char* filename = "user.cnahuelh.42043993.ANALYSIS._000018.root"; 
    TFile* file = TFile::Open(filename, "READ");

    if(file->IsZombie()){
        std::cerr << "Couldn't find file named: " << filename << std::endl;
        return;
    }

    TTree* tree = (TTree*)file->Get("AntiKt4HI;1");

    if(!tree){
        std::cerr << "Couldn't open tree named " << tree->GetName() << std::endl;
    }

    // jet_pt, muon_pt, eta_jet, eta_mu, phi_jet, phi_mu
     
    std::vector<float>* jet_pt = nullptr;
    std::vector<float>* mu_pt = nullptr;
    std::vector<float>* eta_jet  = nullptr;
    std::vector<float>* eta_mu  = nullptr;
    std::vector<float>* phi_jet = nullptr;
    std::vector<float>* phi_mu = nullptr;
    std::vector<bool>* trigger_decisions = nullptr;

    tree->SetBranchAddress("jet_pt", &jet_pt);
    tree->SetBranchAddress("muon_pt", &mu_pt);
    tree->SetBranchAddress("jet_eta", &eta_jet);
    tree->SetBranchAddress("muon_eta", &eta_mu);
    tree->SetBranchAddress("jet_phi", &phi_jet);
    tree->SetBranchAddress("muon_phi", &phi_mu);
    tree->SetBranchAddress("trigger_decisions", &trigger_decisions);

    TH1F* hist_jet_dRab_lower = new TH1F("hist_jet_dRab_lower", "Transverse momentum of jet", 100, 0, 150);
    TH1F* hist_jet_dRab_higher = new TH1F("hist_jet_dRab_higher", "Transverse momentum of jet", 100, 0, 150);

    TCanvas* c1 = new TCanvas("c1", "Canvas for histogram", 800, 600);

    for(Long64_t i = 0; i < tree->GetEntries(); i++){
        tree->GetEntry(i);

        if(trigger_decisions->at(12) == true){
            for(size_t j = 0; j < jet_pt->size(); j++){
                for(size_t k = 0; k < mu_pt->size(); k++){

                    Double_t dRAB = TMath::Sqrt(
                        TMath::Power(eta_jet->at(j) - eta_mu->at(k), 2) +
                        TMath::Power(phi_jet->at(j) - phi_mu->at(k), 2)
                    );

                    if(dRAB < 0.5){
                        hist_jet_dRab_lower->Fill(jet_pt->at(j));
                    }

                    else if(dRAB > 0.5){
                        hist_jet_dRab_higher->Fill(jet_pt->at(j));
                    }
                }
            }
        }
    }

    double global_max = TMath::Max(hist_jet_dRab_lower->GetMaximum(), hist_jet_dRab_higher->GetMaximum());
    hist_jet_dRab_lower->SetMaximum(1.2 * global_max);

    hist_jet_dRab_lower->Draw();
    hist_jet_dRab_lower->SetStats(0);
    hist_jet_dRab_lower->GetXaxis()->SetTitle("p_{T} [GeV]");
    hist_jet_dRab_lower->SetFillColor(kRed-4);

    hist_jet_dRab_higher->Draw("SAME");
    hist_jet_dRab_higher->SetFillColorAlpha(kGreen-4, 0.5);

    TLegend* legend = new TLegend(0.6, 0.6, 0.8, 0.8);
    legend->AddEntry(hist_jet_dRab_lower, "Jet p_{T} dRab < 0.5", "f");
    legend->AddEntry(hist_jet_dRab_higher, "Jet p_{T} dRab > 0.5", "f");
    legend->SetBorderSize(0);
    legend->Draw();
    
    c1->Draw();
}

  

