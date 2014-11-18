/*
*                                                                          
* DrawSpace Rendering engine                                               
* Emmanuel Chaumont Copyright (c) 2013-2014                                
*                                                                          
* This file is part of DrawSpace.                                          
*                                                                          
*    DrawSpace is free software: you can redistribute it and/or modify     
*    it under the terms of the GNU General Public License as published by  
*    the Free Software Foundation, either version 3 of the License, or     
*    (at your option) any later version.                                   
*                                                                          
*    DrawSpace is distributed in the hope that it will be useful,          
*    but WITHOUT ANY WARRANTY; without even the implied warranty of        
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         
*    GNU General Public License for more details.                          
*                                                                          
*    You should have received a copy of the GNU General Public License     
*    along with DrawSpace.  If not, see <http://www.gnu.org/licenses/>.    
*                                                                          
*/

#ifndef __BasicSceneMainFrame__
#define __BasicSceneMainFrame__


#include "panel.h"
#include "drawspace.h"

class BasicSceneMainFrame : public MainFrame
{
protected:

    bool                                                    m_glready;
    DrawSpace::Utils::TimeManager                           m_timer;
    std::map<dsstring, DrawSpace::Core::Movement*>          m_movements;

    virtual void OnClose( wxCloseEvent& event );
    virtual void OnIdle( wxIdleEvent& event );
    virtual void OnAssetsListItemActivated( wxListEvent& p_event );
    virtual void OnConfigsListItemActivated( wxListEvent& p_event );
    virtual void OnPassesListItemActivated( wxListEvent& p_event );
    virtual void OnPassesListItemSelected( wxListEvent& p_event );
    virtual void OnShadersListItemActivated( wxListEvent& p_event );
    virtual void OnCreateMvtButtonClicked( wxCommandEvent& p_event );
    virtual void OnMvtsListItemActivated( wxListEvent& p_event );


public:
	BasicSceneMainFrame( wxWindow* parent );

    void SetGLReady( void );

    void Update( void );
	
};

#endif // __BasicSceneMainFrame__