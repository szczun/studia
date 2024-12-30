#include <TFile.h>
#include <iostream>
#include <TTree.h>
#include <TH1F.h>
#include <TLegend.h>
#include <TMath.h>
#include <TEfficiency.h>
#include <TCanvas.h>

void trigger_efficiency(){
    const char* filename = "user.cnahuelh.42043993.ANALYSIS._000018.root";

    int trigger_counts = 0;
    int probe_counts = 0;

    TFile* file = new TFile(filename, "READ");

    if (file->IsZombie()){
        std::cerr << "File could not be opened" << std::endl;
        return;
    }

    TTree* tree = (TTree*)file->Get("AntiKt4HI;1");

    if(!tree){
        std::cerr << "Tree couldn't be found" << std::endl;
        return;
    }

    std::vector<Double_t>* jet_pt = nullptr;
    std::vector<Double_t>* jet_eta = nullptr;
    std::vector<Double_t>* jet_phi = nullptr;

    std::vector<Double_t>* muon_pt = nullptr;
    std::vector<Double_t>* muon_eta = nullptr;
    std::vector<Double_t>* muon_phi = nullptr;

    std::vector<bool>* trigger_decisions = nullptr;

    tree->SetBranchAddress("jet_pt", &jet_pt);
    tree->SetBranchAddress("jet_eta", &jet_eta);
    tree->SetBranchAddress("jet_phi", &jet_phi);

    tree->SetBranchAddress("muon_pt", &muon_pt);
    tree->SetBranchAddress("muon_eta", &muon_eta);
    tree->SetBranchAddress("muon_phi", &muon_phi);

    tree->SetBranchAddress("trigger_decisions", &trigger_decisions);

    Double_t dR;

    TEfficiency* hist_eff_jet = new TEfficiency("eff_hist_jets", "HLT_mu4_j40_dRAB05_L1MU3V efficiency", 20, 0, 200);
    TEfficiency* hist_eff_muon = new TEfficiency("eff_hist_muons", "HLT_mu4_j40_dRAB05_L1MU3V efficiency", 20, 0, 200);


    for(Long64_t i = 0; i < tree->GetEntries(); i++){
        tree->GetEntry(i);

        bool trigger_on = false;
        bool probe_on = false;   

            for(size_t j = 0; j < jet_pt->size(); j++){

                for(size_t k = 0; k < muon_pt->size(); k++){

                    dR = TMath::Sqrt(
                            TMath::Power((jet_eta->at(j) - muon_eta->at(k)), 2) +
                            TMath::Power((jet_phi->at(j) - muon_phi->at(k)), 2)
                            );

                    if (dR < 0.5 && muon_pt->at(k) > 4 && jet_pt->at(j) > 40 && trigger_decisions->at(5) == true && trigger_on == false){
                        trigger_on = true;

                        hist_eff_jet->Fill(trigger_decisions->at(12), jet_pt->at(j));
                        hist_eff_muon->Fill(trigger_decisions->at(12), muon_pt->at(k));

                        if(trigger_decisions->at(12) && probe_on == false){
                            probe_on = true;
                        }

                    }
                }
            }

        if(trigger_on)
            trigger_counts++;
        if(probe_on)
            probe_counts++;
    }

    TCanvas* c1 = new TCanvas("c1", "Trigger Efficiency - Jet pT", 800, 600);
    hist_eff_jet->Draw("AP");
    c1->SaveAs("trigger_efficiency_jet_pt.png");

    TCanvas* c2 = new TCanvas("c2", "Trigger Efficiency - Muon pT", 800, 600);
    hist_eff_muon->Draw("AP");
    c2->SaveAs("trigger_efficiency_muon_pt.png");

    std::cout << "Liczba zdarzeń referencyjnych: " << probe_counts << std::endl;
    std::cout << "Liczba zdarzeń z triggerem: " << trigger_counts << std::endl;

    // Obliczanie i wyświetlanie wydajności
    double efficiency = (probe_counts > 0) ? (double)probe_counts / trigger_counts : 0;
    std::cout << "Wydajność triggera: " << efficiency * 100 << " %" << std::endl;
    
}
