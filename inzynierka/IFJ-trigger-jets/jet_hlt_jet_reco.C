#include <TFile.h>
#include <iostream>
#include <TH1F.h>
#include <TLegend.h>
#include <TTree.h>
#include <vector>
#include <TMath.h>
#include <TCanvas.h>

void jet_hlt_jet_reco(){
    const char* filename = "user.cnahuelh.42043993.ANALYSIS._000018.root";

    TFile* file = new TFile(filename, "READ");
    if(file->IsZombie()){
        std::cerr << "Couldn't open the file named " << filename << std::endl;
        return;
    }

    TTree* tree = (TTree*)file->Get("AntiKt4HI;1");

    std::vector<Double_t>* muon_pt = nullptr;
    std::vector<Double_t>* muon_eta = nullptr;
    std::vector<Double_t>* muon_phi = nullptr;

    std::vector<Double_t>* muon_pt_hlt = nullptr;
    std::vector<Double_t>* muon_eta_hlt = nullptr;
    std::vector<Double_t>* muon_phi_hlt = nullptr;

    tree->SetBranchAddress("muon_pt", &muon_pt);
    tree->SetBranchAddress("muon_eta", &muon_eta);
    tree->SetBranchAddress("muon_phi", &muon_phi);
    tree->SetBranchAddress("muon_HLT_pt", &muon_pt_hlt);
    tree->SetBranchAddress("muon_HLT_eta", &muon_eta_hlt);
    tree->SetBranchAddress("muon_HLT_phi", &muon_phi_hlt);
    
    

    std::vector<Double_t> muons_pt_diff;
    std::vector<Double_t> muons_drab;

    TH1F* hist_diff_pt = new TH1F("hist_diff_pt", "Muons diff", 60, 0, 2);
    TH1F* hist_drab = new TH1F("hist_drab", "", 20, 0, 10);


    for(Long64_t i = 0; i < tree->GetEntries(); i++){
        tree->GetEntry(i);

        for(size_t j = 0; j < muon_pt_hlt->size(); j++){
            for(size_t k = 0; k < muon_pt->size(); k++){
                Double_t dRAB = TMath::Sqrt(
                    TMath::Power((muon_eta->at(k) - muon_eta_hlt->at(j)), 2) +
                    TMath::Power((muon_phi->at(k) - muon_phi_hlt->at(j)), 2)
                );
                muons_drab.push_back(dRAB);
            }
            if (!muons_drab.empty()) {
                Int_t min_index = TMath::LocMin(muons_drab.size(), muons_drab.data());
                hist_diff_pt->Fill((muon_pt_hlt->at(j) - muon_pt->at(min_index)));
                hist_drab->Fill(muons_drab[min_index]);
            }
            muons_drab.clear();
        }
    }

    TCanvas* canvas = new TCanvas("canvas", "Muon pT Difference", 800, 600);
    canvas->Divide(2, 1);
    canvas->cd(1);
    hist_diff_pt->Draw();
    hist_diff_pt->SetFillColor(kBlue);
    hist_diff_pt->GetYaxis()->SetTitle("Events / 0.3 GeV");
    hist_diff_pt->GetXaxis()->SetTitle("p_{T} [GeV]");
    hist_diff_pt->SetStats(0);

    canvas->cd(2);
    hist_drab->SetFillColor(kRed);
    hist_drab->GetXaxis()->SetTitle("dRAB");
    hist_drab->SetTitle("Muons pairs with lowest dRAB");
    hist_drab->SetStats(0);
    hist_drab->Draw("SAME");

}