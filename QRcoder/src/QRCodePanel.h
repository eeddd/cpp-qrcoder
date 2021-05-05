#pragma once
#include<wx/wx.h>
#include "QrCode.hpp"

class QRCodePanel : public wxPanel
{
	wxString text;
	wxBitmap image;
	qrcodegen::QrCode qrCode;

public:
	QRCodePanel(wxFrame* parent);

	void generateQR(const wxString& text);

	void paintEvent(wxPaintEvent& evt);
	void paintNow();
	void render(wxDC& dc);
	void clear();

	void setText(const wxString txt);

	DECLARE_EVENT_TABLE()
};

