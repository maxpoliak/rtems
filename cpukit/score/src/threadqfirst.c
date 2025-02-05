/**
 * @file
 *
 * @ingroup RTEMSScoreThreadQueue
 *
 * @brief This source file contains the implementation of
 *   _Thread_queue_First().
 */

/*
 *  COPYRIGHT (c) 1989-2014.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.org/license/LICENSE.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/score/threadqimpl.h>

Thread_Control *_Thread_queue_First(
  Thread_queue_Control          *the_thread_queue,
  const Thread_queue_Operations *operations
)
{
  Thread_queue_Heads   *heads;
  Thread_Control       *the_thread;
  Thread_queue_Context  queue_context;

  _Thread_queue_Acquire( the_thread_queue, &queue_context );
  heads = the_thread_queue->Queue.heads;

  if ( heads != NULL ) {
    the_thread = ( *operations->first )( heads );
  } else {
    the_thread = NULL;
  }

  _Thread_queue_Release( the_thread_queue, &queue_context );

  return the_thread;
}
