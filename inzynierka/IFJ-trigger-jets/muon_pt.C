#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <iostream>
#include <TLegend.h>

void muon_pt(){
    const char* filename = "user.cnahuelh.42043993.ANALYSIS._000018.root";
    TFile* file = TFile::Open(filename, "READ");

    if (file->IsZombie()){
        std::cerr << "Couldn't open the file: " << filename << std::endl;
    }

    TTree* tree = (TTree*)file->Get("AntiKt4HI;1");

    if (!tree){
        std::cerr << "Couldn't find tree named " << tree->GetName() << std::endl;
    }

    TBranch* mu_pt_branch = tree->GetBranch("muon_pt");

    if (!mu_pt_branch) {
        std::cerr << "Couldn't find branch named" << mu_pt_branch->GetName() << std::endl;
    }

    TH1F* hist_muon_pt_all = new TH1F("muon_pt_histogram", "#mu p_{T} distribution", 50, 0, 50);
    TH1F* hist_muon_pt_trigx = new TH1F("muon_pt_histogram_trigx", "#mu p_{T} distribution", 50, 0, 50);
    TH1F* hist_muon_pt_trigy = new TH1F("muon_pt_histogram_trigy", "#mu p_{T} distribution", 50, 0, 50);
    

    TCanvas* c1 = new TCanvas("c1", "Canvas for muon p_{T} histogram", 800, 600);
    TLegend* legend = new TLegend(0.3, 0.5, 0.5, 0.7);

    std::vector<float>* muon_pt = nullptr;

    tree->SetBranchAddress("muon_pt", &muon_pt);

    for (Long64_t i = 0; i < tree->GetEntries(); i++){
        tree->GetEntry(i);

        for(float pt : *muon_pt){
            hist_muon_pt_all->Fill(pt);
        }
    }

    std::vector<bool>* trigger_decisions = nullptr;
    tree->SetBranchAddress("trigger_decisions", &trigger_decisions);

    const size_t n_trigd = 24;
    int sums[n_trigd] = {0};

    for(Long64_t i = 0; i < tree->GetEntries(); i++){
        tree->GetEntry(i);

        if(trigger_decisions->at(5)){
            for(float pt : *muon_pt){
                hist_muon_pt_trigx->Fill(pt);
            }
        }

        if(trigger_decisions->at(12)){
            for(float pt : *muon_pt){
                hist_muon_pt_trigy->Fill(pt);
            }
        }
    }

    hist_muon_pt_all->Draw();
    hist_muon_pt_all->SetFillColor(kBlue);
    hist_muon_pt_all->SetLineColor(kBlack);
    hist_muon_pt_all->SetLineWidth(2);
    hist_muon_pt_all->SetStats(0);
    hist_muon_pt_all->GetXaxis()->SetTitle("p_{T} [GeV]");
    hist_muon_pt_all->GetYaxis()->SetTitle("Events / 2 GeV");

    hist_muon_pt_trigx->SetFillColor(kGreen);
    hist_muon_pt_trigx->Draw("SAME");


    hist_muon_pt_trigy->SetFillColor(kRed);
    hist_muon_pt_trigy->Draw("SAME");

    c1->Draw();
    c1->Update();

    legend->SetBorderSize(0);
    legend->AddEntry(hist_muon_pt_all, "p_{T} of all muons", "f");
    legend->AddEntry(hist_muon_pt_trigx, "p_{T} of muons for trigger HLT_mu4_L1MU3V", "f");
    legend->AddEntry(hist_muon_pt_trigy, "p_{T} of muons for trigger HLT_mu4_j40_L1MU3V", "f");
    Float_t textsize = 0.03;
    legend->SetTextSize(textsize);

    legend->Draw();
}
