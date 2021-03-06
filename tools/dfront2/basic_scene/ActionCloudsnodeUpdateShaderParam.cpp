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

#include "ActionCloudsNodeUpdateShaderParam.h"

using namespace DrawSpace;
using namespace DrawSpace::Core;
using namespace DrawSpace::Dynamics;
using namespace DrawSpace::Utils;


void ActionCloudsNodeUpdateShaderParam::Execute( DrawSpace::Core::PropertyPool& p_propertypool )
{
    dsstring scene_name = p_propertypool.GetPropValue<dsstring>( "scene_name" );
    dsstring pass_name = p_propertypool.GetPropValue<dsstring>( "pass_name" );
    dsstring id = p_propertypool.GetPropValue<dsstring>( "id" );
    Vector value = p_propertypool.GetPropValue<Vector>( "value" );


    for( std::map<void*, BasicSceneMainFrame::SceneNodeEntry<DrawSpace::Clouds>>::iterator it = BasicSceneMainFrame::GetInstance()->m_clouds_nodes.begin(); it != BasicSceneMainFrame::GetInstance()->m_clouds_nodes.end(); ++it )
    {
        if( it->second.name == scene_name )
        {
            DrawSpace::Core::SceneNode<Clouds>* clouds = it->second.scene_node;
            DrawSpace::Utils::CloudsDescriptor clouds_descr = BasicSceneMainFrame::GetInstance()->m_clouds_descriptors[it->first];

            if( clouds_descr.chunk_descriptor.passes_slots.count( pass_name ) > 0 )
            {
                Pass* current_pass = dynamic_cast<Pass*>( ConfigsBase::GetInstance()->GetConfigurableInstance( pass_name ) );

                int id_index = -1;

                for( size_t i = 0; i < clouds_descr.chunk_descriptor.passes_slots[pass_name].shader_params.size(); i++ )
                {
                    if( clouds_descr.chunk_descriptor.passes_slots[pass_name].shader_params[i].id == id )
                    {
                        id_index = i;
                        break;
                    }
                }

                if( id_index == -1 )
                {
                    wxMessageBox( "ChunkNode:UpdateShaderParam : unknown shader param id for this node", "Script error", wxICON_ERROR );
                    return;
                }

                clouds->GetContent()->GetNodeFromPass( current_pass )->SetShaderRealVector( id, value );

                // update descriptor
                clouds_descr.chunk_descriptor.passes_slots[pass_name].shader_params[id_index].value = value;

                BasicSceneMainFrame::GetInstance()->m_clouds_descriptors[it->first] = clouds_descr;

                return;
            }
            else
            {
                wxMessageBox( "ChunkNode:UpdateShaderParam : unknown pass name for this node", "Script error", wxICON_ERROR );
                return;
            }
        }
    }

}
