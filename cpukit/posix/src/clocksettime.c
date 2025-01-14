/**
 * @file
 *
 * @ingroup POSIXAPI
 *
 * @brief Set Time of Clock
 */

/*
 *  COPYRIGHT (c) 1989-2007.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.org/license/LICENSE.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <time.h>

#include <rtems/score/todimpl.h>
#include <rtems/seterr.h>

/*
 *  14.2.1 Clocks, P1003.1b-1993, p. 263
 */

int clock_settime(
  clockid_t              clock_id,
  const struct timespec *tp
)
{
  Status_Control status;

  if ( !tp )
    rtems_set_errno_and_return_minus_one( EINVAL );

  if ( clock_id == CLOCK_REALTIME ) {
    ISR_lock_Context lock_context;

    status = _TOD_Is_valid_new_time_of_day( tp );
    if ( status != STATUS_SUCCESSFUL ) {
      rtems_set_errno_and_return_minus_one( STATUS_GET_POSIX( status ) );
    }

    _TOD_Lock();
    _TOD_Acquire( &lock_context );
      status = _TOD_Set( tp, &lock_context );
    _TOD_Unlock();

    if ( status != STATUS_SUCCESSFUL ) {
      rtems_set_errno_and_return_minus_one( STATUS_GET_POSIX( status ) );
    }
  }
#ifdef _POSIX_CPUTIME
  else if ( clock_id == CLOCK_PROCESS_CPUTIME_ID ) {
    rtems_set_errno_and_return_minus_one( ENOSYS );
  }
#endif
#ifdef _POSIX_THREAD_CPUTIME
  else if ( clock_id == CLOCK_THREAD_CPUTIME_ID ) {
    rtems_set_errno_and_return_minus_one( ENOSYS );
  }
#endif
  else {
    rtems_set_errno_and_return_minus_one( EINVAL );
  }

  return 0;
}
