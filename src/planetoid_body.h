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

#ifndef _PLANETOID_BODY_H_
#define _PLANETOID_BODY_H_

#include "planetoid_fragment.h"


namespace DrawSpace
{
namespace Planetoid
{

class Body
{
public:

    typedef DrawSpace::Core::CallBack2<DrawSpace::Planetoid::Body, void, DrawSpace::Scenegraph::CameraEvent, DrawSpace::Core::TransformNode*>       CameraEvtCb;

    typedef DrawSpace::Core::BaseCallback<void, DrawSpace::Planetoid::Body*>                                                                        PlanetRelativeEventHandler;

protected:

    typedef struct
    {
        bool                            attached;
        DrawSpace::Dynamics::InertBody* body;

        Fragment*                       fragment;

    } RegisteredBody;


    typedef enum
    {
        FREE,
        FREE_ON_PLANET,
        INERTBODY_LINKED,
        COLLIDER_LINKED

    } CameraType;

    typedef struct
    {
        bool                                update_meshe;

        CameraType                          type;
        DrawSpace::Dynamics::InertBody*     attached_body;
        DrawSpace::Dynamics::Collider*      attached_collider;

        DrawSpace::Dynamics::CameraPoint*   camera;

        Fragment*                           fragment;


    } RegisteredCamera;


    dsreal                                                      m_ray;

    DrawSpace::Dynamics::World                                  m_world;
    dsstring                                                    m_name;
    DrawSpace::Dynamics::Orbiter*                               m_orbiter;
        
    DrawSpace::SphericalLOD::Drawing*                           m_drawable;
    
    CameraEvtCb*                                                m_camera_evt_cb;
      
    std::map<DrawSpace::Dynamics::InertBody*, RegisteredBody>   m_registered_bodies;
    std::map<dsstring, RegisteredCamera>                        m_registered_camerapoints;
    dsstring                                                    m_current_camerapoint;

    std::vector<Fragment*>                                      m_planetfragments_list;

    std::map<dsstring, DrawSpace::SphericalLOD::Body*>          m_sphericallod_body_list;

    void attach_body( DrawSpace::Dynamics::InertBody* p_body );
    void detach_body( DrawSpace::Dynamics::InertBody* p_body );
    void body_find_attached_camera( DrawSpace::Dynamics::InertBody* p_body, std::vector<dsstring>& p_name );
    void on_camera_event( DrawSpace::Scenegraph::CameraEvent p_event, DrawSpace::Core::TransformNode* p_node );

    void create_camera_collisions( const dsstring& p_cameraname, DrawSpace::Dynamics::CameraPoint* p_camera, RegisteredCamera& p_cameradescr );


public:
    
    Body( const dsstring& p_name, dsreal p_ray );
    virtual ~Body( void );

    DrawSpace::SphericalLOD::Drawing*   GetDrawable( void );
    DrawSpace::Dynamics::Orbiter*       GetOrbiter( void );
    DrawSpace::Dynamics::World*         GetWorld( void );

    CameraEvtCb*                        GetCameraEvtCb( void );

    void                                ApplyGravity( void );

    void                                ManageBodies( void );
    void                                Update( void );

    void                                RegisterInertBody( const dsstring& p_bodyname, DrawSpace::Dynamics::InertBody* p_body );
    void                                RegisterCollider( DrawSpace::Dynamics::Collider* p_collider );
    void                                RegisterIncludedInertBody( const dsstring& p_bodyname, DrawSpace::Dynamics::InertBody* p_body, const DrawSpace::Utils::Matrix& p_initmat );
    bool                                RegisterCameraPoint( DrawSpace::Dynamics::CameraPoint* p_camera );

    void                                GetName( dsstring& p_name );
    
    void                                GetCameraHotpoint( const dsstring& p_name, DrawSpace::Utils::Matrix& p_outmat );

    Fragment*                           GetRegisteredBodyPlanetFragment( DrawSpace::Dynamics::InertBody* p_body );

};



}
}


#endif