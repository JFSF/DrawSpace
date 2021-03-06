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

#ifndef _CONFIGSBASE_H_
#define _CONFIGSBASE_H_

#include "configurable.h"
#include "callback.h"

namespace DrawSpace
{
namespace Core
{
class ConfigsBase
{
public:

    typedef BaseCallback<void, DrawSpace::Core::Configurable*> ConfigurableInstanceRegistrationHandler;

protected:

    static ConfigsBase*                                     m_instance;


    std::map<dsstring, DrawSpace::Core::Configurable*>      m_configurables_instances;
    std::vector<DrawSpace::Core::Configurable*>             m_ordered_configurables_instances;  // vector where config instances are stored in the same order as they were registered


    ConfigurableInstanceRegistrationHandler*                m_configinstancereg_handler;

    ConfigsBase( void );

public:

    static ConfigsBase* GetInstance( void )
    {
        if( NULL == m_instance )
        {
            m_instance = new ConfigsBase();
        }

        return m_instance;
    }
    
    virtual ~ConfigsBase( void );

    void RegisterConfigurableInstanceRegistrationHandler( ConfigurableInstanceRegistrationHandler* p_handler );

    void RegisterConfigurableInstance( const dsstring& p_id, DrawSpace::Core::Configurable* p_conf );
    DrawSpace::Core::Configurable* GetConfigurableInstance( const dsstring& p_id );
    
    bool ConfigurableInstanceExists( const dsstring& p_id );

    void GetConfigsInstancesList( std::map<dsstring, DrawSpace::Core::Configurable*>& p_list );
    void GetOrderedConfigsInstancesList( std::vector<DrawSpace::Core::Configurable*>& p_list );

    
};
}
}
#endif
