#include <TFile.h>
#include <iostream>
#include <TTree.h>
#include <vector>
#include <TH1F.h>
#include <TLegend.h>
#include <TMath.h>
#include <TCanvas.h> 

void trigger_diff(){
    const char* filename = "user.cnahuelh.42043993.ANALYSIS._000018.root";
    TFile* file = TFile::Open(filename, "READ");

    if (file->IsZombie()){
        std::cerr << "File named " << filename << " couldn't be oepened" << std::endl;
    }

    TTree* tree = (TTree*)file->Get("AntiKt4HI;1");

    if (!tree){
        std::cerr << "Tree named " << tree->GetName() << " could not be opened" << std::endl;
    }

    std::vector<Double_t>* jet_pt = nullptr;
    std::vector<Double_t>* muon_pt = nullptr;

    std::vector<Double_t>* truth_jet_pt = nullptr;
    
    tree->SetBranchAddress("jet_pt", &jet_pt);
    tree->SetBranchAddress("muon_pt", &muon_pt);
    tree->SetBranchAddress("truth_jet_pt", &truth_jet_pt);

    TCanvas* canvas = new TCanvas("canvas", "Canvas for histogram", 800, 600);
    TH1F* hist_pt_diff = new TH1F("hist_pt_diff", "Distribution of jet p_{T} - muon p_{T}", 50, 0, 200);

    Double_t mean;
    Double_t sigma;

    for(Long64_t i = 0; i < tree->GetEntries(); i++){
        tree->GetEntry(i);

        for(size_t j = 0; j < jet_pt->size(); j++){
            for(size_t k = 0; k < muon_pt->size(); k++){
                Double_t pt_diff = jet_pt->at(j) - muon_pt->at(k);
                hist_pt_diff->Fill(TMath::Abs(pt_diff));
            }
        }
    }    

    hist_pt_diff->Draw();
    hist_pt_diff->SetFillColor(kBlue-3);
    hist_pt_diff->GetXaxis()->SetTitle("#Delta p_{T}");
    hist_pt_diff->SetStats(0);
    
    TLegend* legend = new TLegend(0.6, 0.6, 0.8, 0.7);
    legend->SetBorderSize(0);
    legend->AddEntry(hist_pt_diff, "p_{T} difference", "f");
    legend->Draw();

    canvas->Draw();
    canvas->Update();

}