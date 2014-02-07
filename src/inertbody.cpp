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

#include "inertbody.h"

using namespace DrawSpace;
using namespace DrawSpace::Core;
using namespace DrawSpace::Utils;
using namespace DrawSpace::Dynamics;


InertBody::InertBody( Body* p_body, DrawSpace::Interface::Drawable* p_drawable, const Parameters& p_parameters ) : Body( p_body, p_drawable )
{
    btTransform bt_transform;

    bt_transform.setIdentity();
    bt_transform.setOrigin( btVector3( p_parameters.initial_pos[0], p_parameters.initial_pos[1], p_parameters.initial_pos[2] ) );

    switch( p_parameters.shape )
    {
        case Body::BOX_SHAPE:
            m_collisionShape = _DRAWSPACE_NEW_( btBoxShape, btBoxShape( btVector3( p_parameters.box_dims[0], p_parameters.box_dims[1], p_parameters.box_dims[2] ) ) );
            break;
    }

    m_motionState = _DRAWSPACE_NEW_( btDefaultMotionState, btDefaultMotionState( bt_transform ) );

    btVector3 localInertia( 0, 0, 0 );
    if( p_parameters.mass > 0.0 )
    {        
        m_collisionShape->calculateLocalInertia( p_parameters.mass, localInertia );
    }

    btRigidBody::btRigidBodyConstructionInfo boxRigidBodyConstructionInfo( p_parameters.mass, m_motionState, m_collisionShape, localInertia );
    btRigidBody* body = _DRAWSPACE_NEW_(  btRigidBody, btRigidBody( boxRigidBodyConstructionInfo ) );
}

InertBody::~InertBody( void )
{
    _DRAWSPACE_DELETE_( m_rigidBody );
    _DRAWSPACE_DELETE_( m_collisionShape );
    _DRAWSPACE_DELETE_( m_motionState );
}

void InertBody::GetParameters( Parameters& p_parameters )
{
    p_parameters = m_parameters;
}