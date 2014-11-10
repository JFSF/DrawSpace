///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __PANEL_H__
#define __PANEL_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/listctrl.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/notebook.h>
#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class Panel
///////////////////////////////////////////////////////////////////////////////
class Panel : public wxDialog 
{
	private:
	
	protected:
		wxNotebook* m_notebook1;
		wxPanel* m_camerasPanel;
		wxPanel* m_passesPanel;
		wxPanel* m_resourcesPanel;
		wxListCtrl* m_assets_listCtrl;
		wxListCtrl* m_configs_listCtrl;
		wxPanel* m_scenePanel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnAssetsListItemActivated( wxListEvent& event ) { event.Skip(); }
		
	
	public:
		
		Panel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Basic_scene commands"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 565,644 ), long style = 0 ); 
		~Panel();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class ObjectsListDialog
///////////////////////////////////////////////////////////////////////////////
class ObjectsListDialog : public wxDialog 
{
	private:
	
	protected:
		wxListCtrl* m_listCtrl;
		wxButton* m_button4;
	
	public:
		
		ObjectsListDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 537,388 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~ObjectsListDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class ObjectPropertiesDialog
///////////////////////////////////////////////////////////////////////////////
class ObjectPropertiesDialog : public wxDialog 
{
	private:
	
	protected:
		wxPropertyGrid* m_propertyGrid;
		wxButton* m_close_button;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCloseButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		ObjectPropertiesDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 381,318 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~ObjectPropertiesDialog();
	
};

#endif //__PANEL_H__
