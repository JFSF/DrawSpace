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


#ifndef _LUA_DRAWSPACE_H_
#define _LUA_DRAWSPACE_H_

#include "drawspace_commons.h"
#include "callback.h"
#include "mediator.h"
#include "luna.h"

class LuaDrawSpace
{
public:

    DrawSpace::Core::BaseCallback<void, DrawSpace::Core::PropertyPool&>*    m_scriptcalls_handler;

protected:


public:
    LuaDrawSpace( lua_State* p_L );
    ~LuaDrawSpace( void );
     
    int Lua_DisplayFramerate( lua_State* p_L );
    int Lua_DisplayCurrentCamera( lua_State* p_L );
    int Lua_CreateSceneNodeGraph( lua_State* p_L );

    int Lua_LoadKeyUpScript( lua_State* p_L );
    int Lua_LoadKeyDownScript( lua_State* p_L );
    int Lua_LoadMouseScript( lua_State* p_L );


    static const char className[];
    static const Luna2<LuaDrawSpace>::RegType methods[];
};

#endif