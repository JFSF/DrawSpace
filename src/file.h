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

#ifndef _FILE_H_
#define _FILE_H_

#include "drawspace_commons.h"
#include "archive.h"
#include <Physfs.h>

namespace DrawSpace
{
namespace Utils
{

class File
{

public:
    typedef enum
    {
        LOCALFILESYSTEM,
        VIRTUALFILESYSTEM,

    } FSMode;

protected:

    static FSMode       m_fsMode;
    static dsstring     m_virtualFsArchiveName;
    FILE*               m_fp;
    PHYSFS_file*        m_vfp;

    static long	        fileSize( FILE *p_fp );

public:

    typedef enum
    {
        CREATENEW,
        OPENEXISTINGB,
        CREATENEWTEXT,
        OPENEXISTINGTEXT,

    } Mode;

    File( const dsstring& p_filename, Mode p_mode );
    ~File( void );

    static void MountVirtualFS( const dsstring& p_virtualFsArchiveName );
    static void UnmountVirtualFS( void );

    void SaveArchive( Archive& p_arc );
    bool LoadArchive( Archive& p_arc );
    long FileSize( void );

    void Puts( const dsstring& p_string );
    bool Gets( char* p_buff, int p_nbToRead );
    void Flush( void );

    static void* LoadAndAllocBinaryFile( const dsstring& p_file, long* p_size );
};
}
}
#endif
