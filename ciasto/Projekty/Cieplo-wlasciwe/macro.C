#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <TGraph.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TLatex.h>
#include <TF1.h>
#include <TStyle.h>
#include <TLegend.h>

void macro(){
    std::string filename = "Au.dat";
    std::fstream file;
    file.open(filename);

    const double au_mass = 196.97; // atomic mass of gold
    const double Na = 6.02e23;
    const double kb = 1.38e-23;

    if(!file.is_open()){
        std::cerr << "Couldn't open the file " << filename << std::endl;
    }

    double temperature;
    double s_heat_cap;

    std::vector<double> temperatures;
    std::vector<double> s_heat_caps;


    TGraph* graph = new TGraph();
    TLegend* legend = new TLegend(0.2, 0.6, 0.4, 0.8);

    graph->SetMarkerStyle(kFullCircle);
    // graph->SetTitle("Wykres ciepła właściwego w funkcji temperatury");
    graph->GetXaxis()->SetTitle("Temperatura [K]");
    graph->GetYaxis()->SetTitle("Cieplo wlasciwe [J mol^{-1} K^{-1}]");

    while(!file.eof()){
        file >> temperature >> s_heat_cap;
        temperatures.push_back(temperature);
        s_heat_caps.push_back(s_heat_cap);

        graph->SetPoint(graph->GetN(), temperature, s_heat_cap*au_mass);
    }

    file.close();

    TF1* fn = new TF1("fn", "[0]*x + 3*(6.02e23)*(1.38e-23)*0.8*TMath::Pi()^4 * (x/[1])^3", temperatures[0], temperatures[temperatures.size()-1]);
    fn->SetParameter(0, 0.006);
    fn->SetParameter(1, 170);

    TCanvas* canvas = new TCanvas("c1", "Canvas for plot", 800, 600);
    graph->Draw("AP");  
    canvas->SetGridx();
    canvas->SetGridy();
    graph->SetStats(0);
    graph->Fit("fn", "R");
    legend->AddEntry(graph, "Dane");
    legend->AddEntry(fn, "Dopasowana krzywa");
    legend->SetBorderSize(0);
    legend->SetTextSize(0.03);
    legend->Draw();
    canvas->SaveAs("wykres.pdf");
}