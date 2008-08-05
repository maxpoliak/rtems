/*
 *  COPYRIGHT (c) 1989-2008.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  $Id$
 */

#include <rtems.h>
#include <rtems/libio.h>
#include <rtems/libcsupport.h>

void bsp_libc_init(
  void       *heap_start,
  uint32_t    heap_size,
  int         use_sbrk
)
{
    RTEMS_Malloc_Initialize( heap_start, heap_size, use_sbrk );

    /*
     *  Init the RTEMS libio facility to provide UNIX-like system
     *  calls for use by newlib (ie: provide open, close, etc)
     *  Uses malloc() to get area for the iops, so must be after malloc init
     */

    rtems_libio_init();

    /*
     * Set up for the libc handling.
     */

    libc_init();
}
