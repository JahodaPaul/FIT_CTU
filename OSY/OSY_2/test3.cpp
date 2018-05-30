#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cstdarg>
#include <pthread.h>
#include <semaphore.h>
#include "common.h"
#include "test_op.h"
using namespace std;

struct TChild
{
  int              m_Pages;
  bool             m_Free;
};

static void        childProcess                            ( CCPU            * cpu,
                                                             TChild          * arg )
{
  checkResize ( cpu, arg -> m_Pages );
  rwiTest ( cpu, 0, arg -> m_Pages );
  if ( arg -> m_Free ) checkResize ( cpu, 0 );
}

static void        initProcess                             ( CCPU            * cpu,
                                                             void            * arg )
{
  static TChild childData[10];

  checkResize ( cpu, 500 );
  rwiTest ( cpu, 0, 500 );

  for ( int i = 0; i < 10; i ++ )
  {
    childData[i] . m_Pages = (i+1) * 100;
    childData[i] . m_Free = i & 1;
    cpu -> NewProcess ( &childData[i], (void (*)(CCPU *, void*))childProcess,  false );
  }
}

int                main                                    ( void )
{
  const int PAGES = 10 * 1024;
  // PAGES + extra 4KiB for alignment
  uint8_t * mem = new uint8_t [ PAGES * CCPU::PAGE_SIZE + CCPU::PAGE_SIZE ];

  // align to a mutiple of 4KiB
  uint8_t * memAligned = (uint8_t *) (( ((uintptr_t) mem) + CCPU::PAGE_SIZE - 1) & ~(uintptr_t) ~CCPU::ADDR_MASK );

  testStart ();
  MemMgr ( memAligned, PAGES, NULL, initProcess );
  testEnd ( "test #4" );

  delete [] mem;
  return 0;
}
