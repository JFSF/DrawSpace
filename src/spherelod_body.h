/*
*                                                                          
* DrawSpace Rendering engine                                               
* Emmanuel Chaumont Copyright (c) 2013-2015                              
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

#ifndef _SPHERELOD_BODY_H_
#define _SPHERELOD_BODY_H_

#include "renderer.h"
#include "spherelod_face.h"

namespace DrawSpace
{
namespace SphericalLOD
{
class Body
{
public:
    typedef DrawSpace::Core::BaseCallback2<void, Patch*, int> PatchUpdateHandler;

protected:

    Face*                                                                       m_faces[6];
    static DrawSpace::Core::Meshe*                                              m_planetpatch_meshe;

    dsreal                                                                      m_diameter;    
    dsreal                                                                      m_hotpoint_altitud;

    std::vector<PatchUpdateHandler*>                                            m_patchupdate_handlers;

    int                                                                         m_current_face;
    
    Patch*                                                                      m_current_patch;

    void check_currentpatch_event( Patch* p_newvalue, int p_currentpatch_lod );

public:

    Body( dsreal p_diameter );
    virtual ~Body( void );

    static void BuildMeshe( void );
    
    void Compute( void );
    void Initialize( void );
    void RegisterPatchUpdateHandler( PatchUpdateHandler* p_handler );
    void UpdateHotPoint( const DrawSpace::Utils::Vector& p_hotpoint );
    DrawSpace::Core::Meshe* GetPatcheMeshe( void );

    Patch* GetFaceCurrentLeaf( int p_faceid );
    Face* GetFace( int p_faceid );

    dsreal GetHotPointAltitud( void );
    int GetCurrentFace (void );

    void SetHotState( bool p_hotstate );
    void UpdateRelativeAlt( dsreal p_alt );

    friend class Drawing;
};
}
}
#endif
