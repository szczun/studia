#include <TCanvas.h>
#include <TH1F.h>
#include <TRandom.h>

void xd()
{
    // Tworzymy obiekt histogramu
    TH1F *hist = new TH1F("hist", "Histogram Przykład;; y", 100, -4, 4);

    // Generujemy dane losowe i dodajemy je do histogramu
    TRandom *rand = new TRandom();
    for (int i = 0; i < 10000; i++)
    {
        hist->Fill(rand->Gaus(0, 1)); // Wypełniamy histogram danymi z rozkładu normalnego
    }

    // Tworzymy obiekt płótna do wyświetlenia histogramu
    TCanvas *canvas = new TCanvas("canvas", "Histogram", 800, 600);

    // Rysujemy histogram
    hist->Draw();

    // Zapisujemy wykres do pliku
    canvas->SaveAs("histogram.png");
}
