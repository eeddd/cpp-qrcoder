#include "QRCodePanel.h"
#include "QrCode.hpp"

BEGIN_EVENT_TABLE(QRCodePanel, wxPanel)
	EVT_PAINT(QRCodePanel::paintEvent)
END_EVENT_TABLE()


QRCodePanel::QRCodePanel(wxFrame* parent)
	: wxPanel(parent), text(""), qrCode(qrcodegen::QrCode::encodeText("", qrcodegen::QrCode::Ecc::LOW))
{
}

void QRCodePanel::generateQR(const wxString& text)
{
	clear();
	
	setText(text);
	qrCode = qrcodegen::QrCode::encodeText(text.c_str(), qrcodegen::QrCode::Ecc::LOW);
	
	paintNow();

}

void QRCodePanel::paintEvent(wxPaintEvent& evt)
{
	wxPaintDC dc(this);
	render(dc);
}

void QRCodePanel::paintNow()
{
	wxClientDC dc(this);
	render(dc);
}

void QRCodePanel::render(wxDC& dc)
{
	if (text.IsEmpty()) return;
			
	wxColour black, white;
	black.Set(wxT("#000000"));
	white.Set(wxT("#ffffff"));

	wxBrush bbrush(black);
	wxBrush wbrush(white);
	wbrush.SetStyle(wxBRUSHSTYLE_TRANSPARENT);

	dc.SetPen(*wxTRANSPARENT_PEN);
		
	int w = 20;

	int size = qrCode.getSize();
	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			bool b = qrCode.getModule(x, y);

			if (b)
				dc.SetBrush(bbrush);
			else
				dc.SetBrush(wbrush);

			dc.DrawRectangle(x * w, y * w, w, w);
		}
	}
}

void QRCodePanel::clear()
{
	wxClientDC dc(this);
	dc.Clear();
}

void QRCodePanel::setText(const wxString txt)
{
	text = txt;
}