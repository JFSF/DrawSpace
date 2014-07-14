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

#ifndef _SPECTATORMOVEMENT_H_
#define _SPECTATORMOVEMENT_H_

#include "movement.h"
#include "inertbody.h"
#include "timemanager.h"

namespace DrawSpace
{
namespace Core
{
class SpectatorMovement : public Movement
{
protected:

    typedef DrawSpace::Core::CallBack<SpectatorMovement, void, const dsstring&> SpectatorTimer;

    dsreal                          m_scalepos;
    long                            m_posperiod;

    DrawSpace::Dynamics::InertBody* m_attachedbody;

    bool                            m_compute;

    SpectatorTimer*                 m_timercb;

    void compute_pos( void );

    void on_timer( const dsstring& p_timername );

public:

    SpectatorMovement( void );
    virtual ~SpectatorMovement( void );


    virtual void Init( DrawSpace::Dynamics::InertBody* p_attachedbody, dsreal p_scalepos, long p_posperiod, DrawSpace::Utils::TimeManager& p_timemanager, const dsstring& p_timername );
    virtual void Compute( DrawSpace::Utils::TimeManager& p_timemanager );


};

}
}

#endif