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
  uint32_t            m_Pages;
  uint32_t            m_Share;
  pthread_barrier_t * m_Barrier;
};

static void        childProcess                            ( CCPU            * cpu,
                                                             TChild          * arg )
{
  checkResize ( cpu, arg -> m_Pages );
  rwTest ( cpu, arg -> m_Share, arg -> m_Pages );
  pthread_barrier_wait ( arg -> m_Barrier );
  rTest ( cpu, 0, arg -> m_Share );
  rTest ( cpu, arg -> m_Share, arg -> m_Pages );
}

static void        initProcess                             ( CCPU            * cpu,
                                                             void            * arg )
{
  const int PROCESSES = 10;
  const int BASE_SIZE = 1500;
  static TChild childData[PROCESSES];
  pthread_barrier_t  bar;

  checkResize ( cpu, BASE_SIZE );

  rwiTest ( cpu, 0, BASE_SIZE );

  pthread_barrier_init ( &bar, NULL, PROCESSES + 1 );

  for ( int i = 0; i < PROCESSES; i ++ )
  {
    childData[i] . m_Pages = BASE_SIZE + ( i - PROCESSES / 2 ) * 20;
    childData[i] . m_Share = BASE_SIZE / 2;
    childData[i] . m_Barrier = &bar;
    cpu -> NewProcess ( &childData[i], (void (*)(CCPU *, void*))childProcess, true );
  }
  pthread_barrier_wait ( &bar );
  rTest ( cpu, 0, BASE_SIZE );
  pthread_barrier_destroy ( &bar );
}

int                main                                    ( void )
{
  const int PAGES = 10 * 1024;

  // PAGES + extra 4KiB for alignment
  uint8_t * mem = new uint8_t [ PAGES * CCPU::PAGE_SIZE + CCPU::PAGE_SIZE ];

  // align to a mutiple of 4KiB
  uint8_t * memAligned = (uint8_t *) (( ((uintptr_t) mem) + CCPU::PAGE_SIZE - 1) & ~(uintptr_t) ~CCPU::ADDR_MASK );

  testStart  ();
  MemMgr ( memAligned, PAGES, NULL, initProcess );
  testEnd ( "test #6" );
  delete [] mem;
  return 0;
}
