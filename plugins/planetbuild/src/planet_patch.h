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

#ifndef _PLANET_PATCH_H_
#define _PLANET_PATCH_H_

#include "meshe.h"

class Patch : public DrawSpace::Core::Meshe
{
public:

	static const int    NorthNeighbour      = 0;
	static const int    SouthNeighbour      = 1;
	static const int    WestNeighbour       = 2;
	static const int    EastNeighbour       = 3;
	static const int    NorthWestNeighbour  = 4;
	static const int    NorthEastNeighbour  = 5;
	static const int    SouthWestNeighbour  = 6;
	static const int    SouthEastNeighbour  = 7;

	static const int    FrontPlanetFace    = 0;
	static const int    RearPlanetFace     = 1;
	static const int    LeftPlanetFace     = 2;
	static const int    RightPlanetFace    = 3;
	static const int    TopPlanetFace      = 4;
	static const int    BottomPlanetFace   = 5;

protected:

	dsreal          m_sidelength;
	dsreal          m_xpos;
	dsreal          m_ypos;
	dsreal          m_ray;

	int             m_resolution;
	int             m_orientation;

	Patch*          m_neighbours[8];
	dsstring		m_name;

	void build( void );

    void cubetosphere( const DrawSpace::Utils::Vector& p_in, DrawSpace::Utils::Vector& p_out );

public:
	Patch( int p_resolution, dsreal p_ray, int p_orientation, const dsstring& p_name, Patch* p_parent, int p_parentnodeid );
	virtual ~Patch( void );

	void SetNeighbour( Patch* p_patch, int p_id );
	Patch* GetNeighbour( int p_id );

	void GetName( dsstring& p_name );
	dsreal GetSideLength( void );

	void GetPos( dsreal& p_xpos, dsreal& p_ypos );
	
};

#endif