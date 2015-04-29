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

#ifndef _LUA_LINEARMOVEMENT_H_
#define _LUA_LINEARMOVEMENT_H_

#include "drawspace_commons.h"
#include "callback.h"
#include "mediator.h"
#include "linearmovement.h"
#include "luna.h"

class LuaLinearMovementNode
{
public:

    DrawSpace::Core::BaseCallback<void, DrawSpace::Core::PropertyPool&>*    m_scriptcalls_handler;

protected:

    DrawSpace::Core::SceneNode<DrawSpace::Core::LinearMovement>             m_linear_node;
    DrawSpace::Core::SceneNode<DrawSpace::Core::LinearMovement>*            m_existing_linear_node;

    DrawSpace::Utils::Vector                                                m_initpos;
    DrawSpace::Utils::Vector                                                m_dir;
    dsreal                                                                  m_initial_theta;
    dsreal                                                                  m_initial_phi;
    

public:

    LuaLinearMovementNode( lua_State* p_L );
    ~LuaLinearMovementNode( void );
     
    int Lua_LinkTo( lua_State* p_L );
    int Lua_LoadScript( lua_State* p_L );

    int Lua_SetInitpos( lua_State* p_L );
    int Lua_SetDirection( lua_State* p_L );
    int Lua_SetInitialTheta( lua_State* p_L );
    int Lua_SetInitialPhi( lua_State* p_L );

    int Lua_SetPhi( lua_State* p_L );
    int Lua_SetTheta( lua_State* p_L );
    int Lua_SetSpeed( lua_State* p_L );

    static const char className[];
    static const Luna2<LuaLinearMovementNode>::RegType methods[];
};

#endif