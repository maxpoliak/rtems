/**
 * @file
 *
 * @ingroup RTEMSScoreIntErr
 *
 * @brief This source file contains the definition of ::_System_state_Current
 *   and the implementation of _Terminate() and _Internal_error().
 */

/*
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.org/license/LICENSE.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/score/interr.h>
#include <rtems/score/cpuimpl.h>
#include <rtems/score/smpimpl.h>
#include <rtems/score/sysstate.h>
#include <rtems/score/userextimpl.h>

System_state_Codes _System_state_Current;

void _Terminate(
  Internal_errors_Source the_source,
  Internal_errors_t      the_error
)
{
  _User_extensions_Fatal( the_source, the_error );
  _System_state_Set( SYSTEM_STATE_TERMINATED );
  _SMP_Request_shutdown();
  _CPU_Fatal_halt( the_source, the_error );
}

void _Internal_error( Internal_errors_Core_list core_error )
{
  _Terminate( INTERNAL_ERROR_CORE, core_error );
}
