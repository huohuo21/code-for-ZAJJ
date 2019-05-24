void cmsLumi(bool channel)
{
        TLatex latex;
        latex.SetNDC();
        latex.SetTextSize(0.04);
        latex.SetLineWidth(2);
        float lumiel=35.9;
        float lumimu=35.9;
        int beamcomenergytev=13;
        latex.SetTextAlign(31);
        latex.SetTextAlign(11);
        latex.DrawLatex(0.18,0.82,"Preliminary");
        latex.DrawLatex(0.18,0.86,"CMS");
        latex.SetTextSize(0.03);
        latex.DrawLatex(0.76,0.92,Form("35.9 fb^{-1} (%d TeV)", (beamcomenergytev)));
}
