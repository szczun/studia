#include <TFile.h>
#include <iostream>
#include <TTree.h>
#include <TBranch.h>
#include <TH1F.h>
#include <vector> 
#include <TCanvas.h>
#include <TLegend.h>
#include <TPave.h>

void jet_pt() {

    const char* filename = "user.cnahuelh.42043993.ANALYSIS._000018.root";

    TFile* file = TFile::Open(filename, "READ");
    if (file->IsZombie()){
        std::cerr << "Couldn't open the file " << filename << std::endl;
        return;
    }

    TTree* tree = (TTree*)file->Get("AntiKt4HI;1");

    if (!tree) {
        std::cerr << "Couldn't find tree named " << tree->GetName() << std::endl;
        return;
    }

    TBranch* jet_pt_branch = tree->GetBranch("jet_pt");

    if (!jet_pt_branch) {
        std::cerr << "Couldn't find branch named jet_pt" << std::endl;
        return;
    }

    TH1F* hist = new TH1F("jet_pt_hist", "Histogram of jet p_{T}", 50, 0, 250);
    TCanvas* c1 = new TCanvas("c1", "Canvas", 800, 600);

    std::vector<float>* jet_pt = nullptr;

    TLegend* legend_jet_pt = new TLegend(0.3, 0.5, 0.5, 0.7);

    tree->SetBranchAddress("jet_pt", &jet_pt);

    Long64_t nEntries = tree->GetEntries();

    for (Long64_t i = 0; i < nEntries; i++) {
        tree->GetEntry(i);  

        for (float pt : *jet_pt) {  
            hist->Fill(pt);
        }
    }

    hist->Draw();
    hist->SetLineColor(kBlack);
    hist->SetFillColor(kRed-6);
    hist->SetStats(0);
    hist->GetXaxis()->SetTitle("p_{T} [GeV]");
    hist->GetYaxis()->SetTitle("Events / 5 GeV");

    std::vector<bool>* trigger_decisions = nullptr;
    tree->SetBranchAddress("trigger_decisions", &trigger_decisions);

    const int num_triggers = 24; 
    int sums[num_triggers] = {0}; 
    for (Long64_t i = 0; i < tree->GetEntries(); i++) {
        tree->GetEntry(i);

        for (size_t j = 0; j < trigger_decisions->size(); j++) {
            if (trigger_decisions->at(j)) { 
                sums[j]++;
            }
        }
    }

    std::cout << "Liczba zliczeń triggera HLT_mu4_L1MU3V: " << sums[5] << std::endl;
    std::cout << "Liczba zliczeń triggera HLT_mu4_j40_ion_dRAB05_L1MU3V: " << sums[12] << std::endl;

    TH1F* hist_jet_pt_trigX = new TH1F("hist_jet_pt_trigx", "", 50, 0, 250);
    TH1F* hist_jet_pt_trigY = new TH1F("hist_jet_pt_trigY", "", 50, 0, 250);



    for(Long64_t i = 0; i < tree->GetEntries(); i++){
        tree->GetEntry(i);

        if(trigger_decisions->at(5)){
            for(float pt : *jet_pt){
                hist_jet_pt_trigX->Fill(pt);
            }
        }

        if(trigger_decisions->at(12)){
            for(float pt: *jet_pt){
                hist_jet_pt_trigY->Fill(pt);
            }
        }
    }

    hist_jet_pt_trigX->Draw("SAME");
    hist_jet_pt_trigX->SetLineColor(kBlack);
    hist_jet_pt_trigX->SetFillColor(kBlue-6);
    hist_jet_pt_trigX->SetStats(0);

    hist_jet_pt_trigY->Draw("SAME");
    hist_jet_pt_trigY->SetLineColor(kBlack);
    hist_jet_pt_trigY->SetFillColor(kGreen-6);
    hist_jet_pt_trigY->SetStats(0);

    c1->Draw();
    c1->Update();

    legend_jet_pt->SetBorderSize(0);
    legend_jet_pt->AddEntry(hist, "p_{T} of jet", "f");
    legend_jet_pt->AddEntry(hist_jet_pt_trigX, "p_{T} of jet for trigger HLT_mu4_L1MU3V", "f");
    legend_jet_pt->AddEntry(hist_jet_pt_trigY, "p_{T} of jet for trigger HLT_mu4_j40_ion_dRAB05_L1MU3V", "f");

    Float_t textsize = 0.03;
    legend_jet_pt->SetTextSize(textsize);

    legend_jet_pt->Draw();
}
