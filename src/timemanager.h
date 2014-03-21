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

#ifndef _TIMEMANAGER_H_
#define _TIMEMANAGER_H_

#include "drawspace_commons.h"
#include "callback.h"

namespace DrawSpace
{
namespace Utils
{
class TimeManager
{
protected:

    long    m_last_tick;
    long    m_frame_count;
    long    m_fps;
    bool    m_ready;
    long    m_last_deltatime;

    typedef Core::BaseCallback<void, dsstring> TimerHandler;

    typedef struct
    {
        bool            state;
        long            period; // ms
        TimerHandler*   handler;
        //long            start_tick;
        long            tick_count;
        long            prev_tick;
        bool            freeze;

    } timer_entry;


    std::map<dsstring, timer_entry> m_timers;

public:
    TimeManager( void ); 
    ~TimeManager( void );

    void    Reset( void );

    void    Update( void );

    long    GetFPS( void );

    //vitesse en degres par seconde
    void    AngleSpeedInc( dsreal *p_angle, dsreal p_angleSpeed );
    void    AngleSpeedDec( dsreal *p_angle, dsreal p_angleSpeed );

    void    TranslationSpeedInc( dsreal *p_translation, dsreal p_speed );
    void    TranslationSpeedDec( dsreal *p_translation, dsreal p_speed );

    dsreal  ConvertUnitPerSecFramePerSec( dsreal p_speed );

    bool    IsReady( void );
    long    GetLastDeltaTime( void );

    void    AddTimer( const dsstring& p_id, long p_period, TimerHandler* p_handler );
    void    SetTimerState( const dsstring& p_id, bool p_state );
    void    SuspendTimer( const dsstring& p_id, bool p_suspend );
    void    SetTimerPeriod( const dsstring& p_id, long p_period );
    void    ClearAllTimers( void );
};
}
}

#endif