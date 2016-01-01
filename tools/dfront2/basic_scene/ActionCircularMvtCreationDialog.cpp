/*
*                                                                          
* DrawSpace Rendering engine                                               
* Emmanuel Chaumont Copyright (c) 2013-2016                              
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

#include <wx/wx.h>
#include "BasicSceneMainFrame.h"

#include "ActionCircularMvtCreationDialog.h"

void ActionCircularMvtCreationDialog::Execute( void )
{
    DIALOG_ACTION_DECLARE( DIALOG_CIRCMVT_CREATION_TITLE )

    DIALOG_APPENDROOT_STRING( "scene name", "" )

    DIALOG_APPENDROOT_NODE( "center position", center_pos_root )
    DIALOG_APPENDNODE_FLOAT( center_pos_root, "x", 0.0 );
    DIALOG_APPENDNODE_FLOAT( center_pos_root, "y", 0.0 );
    DIALOG_APPENDNODE_FLOAT( center_pos_root, "z", 0.0 );

    DIALOG_APPENDROOT_NODE( "delta center position", dcenter_pos_root )
    DIALOG_APPENDNODE_FLOAT( dcenter_pos_root, "x", 5.0 );
    DIALOG_APPENDNODE_FLOAT( dcenter_pos_root, "y", 0.0 );
    DIALOG_APPENDNODE_FLOAT( dcenter_pos_root, "z", 0.0 );

    DIALOG_APPENDROOT_NODE( "axis", axis_root )
    DIALOG_APPENDNODE_FLOAT( axis_root, "x", 0.0 );
    DIALOG_APPENDNODE_FLOAT( axis_root, "y", 1.0 );
    DIALOG_APPENDNODE_FLOAT( axis_root, "z", 0.0 );

    DIALOG_APPENDROOT_FLOAT( "initial angle", 0.0 );
    DIALOG_APPENDROOT_FLOAT( "initial theta", 0.0 );
    DIALOG_APPENDROOT_FLOAT( "initial phi", 0.0 );

    DIALOG_APPLY
    DIALOG_SHOW
}
