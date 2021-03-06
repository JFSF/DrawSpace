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

#include "ActionCloudsEditionApply.h"

using namespace DrawSpace;
using namespace DrawSpace::Core;
using namespace DrawSpace::Dynamics;
using namespace DrawSpace::Utils;

void ActionCloudsEditionApply::Execute( BasicSceneObjectPropertiesDialog* p_dialog )
{
    DIALOG_GETGRID
    DIALOG_PROPERTIES_VARS

    DrawSpace::Utils::CloudsDescriptor clouds_descr = BasicSceneMainFrame::GetInstance()->m_clouds_descriptors[p_dialog->GetTreeItem().GetID()];
    BasicSceneMainFrame::SceneNodeEntry<DrawSpace::Clouds> cne = BasicSceneMainFrame::GetInstance()->m_clouds_nodes[p_dialog->GetTreeItem().GetID()];

    DIALOG_GET_FLOAT_PROPERTY( "sorting distance", sd )        
    cne.scene_node->GetContent()->SetSortingDistance( sd );

    for( std::map<dsstring, ChunkPassDescriptor>::iterator it = clouds_descr.chunk_descriptor.passes_slots.begin(); it != clouds_descr.chunk_descriptor.passes_slots.end(); ++it )
    {
        dsstring pass_name = it->first;
        ChunkPassDescriptor pass_descr = it->second;
        
        DIALOG_EXPLORE_NODES_BEGIN( pass_name, "shader parameter %d", i, sp_slot )

            DIALOG_GET_STRING_PROPERTY( DIALOG_INCREMENT_STRING( sp_slot, "param id" ), param_id )
            
            DIALOG_GET_FLOAT_PROPERTY( DIALOG_INCREMENT_STRING( sp_slot, "values.x" ), val_x )
            DIALOG_GET_FLOAT_PROPERTY( DIALOG_INCREMENT_STRING( sp_slot, "values.y" ), val_y )
            DIALOG_GET_FLOAT_PROPERTY( DIALOG_INCREMENT_STRING( sp_slot, "values.z" ), val_z )
            DIALOG_GET_FLOAT_PROPERTY( DIALOG_INCREMENT_STRING( sp_slot, "values.w" ), val_w )
          
            DIALOG_WXSTRING_TO_DSSTRING( param_id, param_id2 )

            Pass* current_pass = dynamic_cast<Pass*>( ConfigsBase::GetInstance()->GetConfigurableInstance( pass_name ) );

            cne.scene_node->GetContent()->GetNodeFromPass( current_pass )->SetShaderRealVector( param_id2, Vector( val_x, val_y, val_z, val_w ) );

            // update descriptor
            clouds_descr.chunk_descriptor.passes_slots[pass_name].shader_params[i].value = Vector( val_x, val_y, val_z, val_w );

            BasicSceneMainFrame::GetInstance()->m_clouds_descriptors[p_dialog->GetTreeItem().GetID()] = clouds_descr;

        DIALOG_EXPLORE_NODES_END( i )
    }
}
