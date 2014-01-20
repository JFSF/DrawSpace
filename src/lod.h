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

#ifndef _LOD_H_
#define _LOD_H_

#include "drawspace_commons.h"
#include "vsphere.h"
#include "callback.h"

namespace DrawSpace
{
namespace Core
{
class LodStep
{
public:

    typedef enum
    {
        IN_LODSTEP,
        OUT_LODSTEP,

    } Event;

protected:

    VSphere*                                m_vsphere;
    dsreal                                  m_kinf;
    dsreal                                  m_ksup;
    bool                                    m_in;
    BaseCallback2<void, LodStep*, Event>*   m_handler;

public:
    LodStep( dsreal p_kinf, dsreal p_ksup, VSphere* p_vsphere );
    virtual ~LodStep( void );

    virtual void RegisterHandler( BaseCallback2<void, LodStep*, Event>* p_handler );

    virtual void Run( void );

};
}
}

#endif