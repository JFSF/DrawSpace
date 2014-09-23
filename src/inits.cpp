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

#include "inits.h"
#include "factory.h"
#include "texture.h"
#include "renderstate.h"

using namespace DrawSpace;
using namespace DrawSpace::Core;

// generic and statics initialisations done here
void DrawSpace::Initialize( void )
{
    Factory::GetInstance()->RegisterAssetInstanciationFuncByText( TEXTURE_TEXT_KEYWORD, Texture::Instanciate );
    Factory::GetInstance()->RegisterAssetInstanciationFuncByArc( TEXTURE_ARC_MAGICNUMBER, Texture::Instanciate );

    RenderState::InitStringMaps();
}