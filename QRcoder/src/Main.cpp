#include<wx/wx.h>
#include "QRCodePanel.h"


class MainFrame : public wxFrame
{
	wxTextCtrl *txtInput;
	QRCodePanel* imgPanel;

public:
	MainFrame(const wxString &title)
		: wxFrame(NULL, -1, title, wxDefaultPosition, wxSize(800, 600))
	{
		wxInitAllImageHandlers();

		txtInput = new wxTextCtrl(this, -1);
		imgPanel = new QRCodePanel(this);

		wxButton* btn = new wxButton(this, 10001, "Generate");
		btn->Bind(wxEVT_BUTTON, &MainFrame::OnClickGenerate, this);

		wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);
		hbox->Add(txtInput, 1, wxALL | wxEXPAND, 0);
		hbox->Add(btn, 0, wxALL | wxEXPAND, 1);

		wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
		vbox->Add(hbox, 0, wxALL | wxEXPAND, 1);
		vbox->Add(imgPanel, 1, wxALL | wxEXPAND, 1);
		SetSizer(vbox);
	}

	void OnClickGenerate(wxCommandEvent &event)
	{
		imgPanel->generateQR(txtInput->GetValue());
	}
};


class App : public wxApp
{
public:
	virtual bool OnInit()
	{
		MainFrame* frm = new MainFrame("QR Generator");
		frm->Show();
		return true;
	}
};

IMPLEMENT_APP(App);