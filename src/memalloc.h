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

#ifndef _MEMALLOC_H_
#define _MEMALLOC_H_

#include "drawspace_commons.h"
#include "tracedefs.h"

#define _DRAWSPACE_NEW_( __type__, __item__ ) DrawSpace::Utils::MemAlloc::GetInstance()->Register<__type__>( new __item__, sizeof( __item__ ), #__item__, __FUNCTION__, __LINE__, __FILE__ )
#define _DRAWSPACE_NEW_EXPLICIT_SIZE_( __type__, __item__, __size__ ) DrawSpace::Utils::MemAlloc::GetInstance()->Register<__type__>( new __item__, __size__, #__item__, __FUNCTION__, __LINE__, __FILE__ )
#define _DRAWSPACE_DELETE_( __ptr__ ) delete __ptr__; DrawSpace::Utils::MemAlloc::GetInstance()->Unregister( __ptr__ ); __ptr__ = NULL
#define _DRAWSPACE_DELETE_N_( __ptr__ ) delete[] __ptr__; DrawSpace::Utils::MemAlloc::GetInstance()->Unregister( __ptr__ ); __ptr__ = NULL

namespace DrawSpace
{
namespace Utils
{
class MemAlloc
{
protected:

    typedef struct
    {
        size_t      size;
        dsstring    item;
        dsstring    func;
        long        linenum;
        dsstring    file;

    } entry;

    static MemAlloc*        m_instance;
    std::map<void*, entry>  m_blocs;
    size_t                  m_totalsize;

    MemAlloc( void );

    void register_bloc( void* p_ptr, size_t p_size, const std::string& p_item, const std::string& p_funcname, long p_line, const std::string& p_filename );

public:
    
    ~MemAlloc( void );

    static MemAlloc* GetInstance( void );

    void DumpContent( void );

    template <typename base>
    base* Register( base* p_ptr, size_t p_size, const std::string& p_item, const std::string& p_funcname, long p_line, const std::string& p_filename )
    {
        base* t = p_ptr;
        register_bloc( t, p_size, p_item, p_funcname, p_line, p_filename );

        return t;
    };

    void Unregister( void* p_ptr );

    static DrawSpace::Logger::Sink* GetLogSink( void );
};
}
}

#endif
