/**
 * @file
 *
 * @ingroup RTEMSImplClassicClock
 *
 * @brief This source file contains the implementation of
 *   rtems_clock_get_tod_timeval().
 */

/*
 *  COPYRIGHT (c) 1989-2008.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.org/license/LICENSE.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/rtems/clock.h>
#include <rtems/score/todimpl.h>

rtems_status_code rtems_clock_get_tod_timeval(
  struct timeval  *time_of_day
)
{
  if ( !time_of_day )
    return RTEMS_INVALID_ADDRESS;

  if ( !_TOD_Is_set() )
    return RTEMS_NOT_DEFINED;

  _TOD_Get_timeval( time_of_day );

  return RTEMS_SUCCESSFUL;
}
