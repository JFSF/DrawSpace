/*
*                                                                          
* DrawSpace Rendering engine                                               
* Emmanuel Chaumont Copyright (c) 2013-2017                        
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

#include "ActionLongLatLongLat.h"

using namespace DrawSpace;
using namespace DrawSpace::Core;
using namespace DrawSpace::Dynamics;
using namespace DrawSpace::Utils;


void ActionLongLatLongLat::Execute( DrawSpace::Core::PropertyPool& p_propertypool )
{
    dsstring scene_name = p_propertypool.GetPropValue<dsstring>( "scene_name" );
    SceneNode<LongLatMovement>** node_ptr = p_propertypool.GetPropValue<SceneNode<LongLatMovement>**>( "existing_node" );

    for( std::map<void*, BasicSceneMainFrame::SceneNodeEntry<DrawSpace::Core::LongLatMovement>>::iterator it = BasicSceneMainFrame::GetInstance()->m_ll_nodes.begin(); it != BasicSceneMainFrame::GetInstance()->m_ll_nodes.end(); ++it )
    {
        if( it->second.name == scene_name )
        {
            // node exists
            *node_ptr = it->second.scene_node;
            break;
        }
    }
}
