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
  pthread_mutex_t  m_Mtx;
  pthread_cond_t   m_Cond;
  int              m_Pages;
  bool             m_Free;
};

static void        childProcess                            ( CCPU            * cpu,
                                                             TChild          * arg )
{
  checkResize ( cpu, arg -> m_Pages );
  rwiTest ( cpu, 0, arg -> m_Pages );
  if ( arg -> m_Free ) checkResize ( cpu, 0 );
  pthread_mutex_lock ( &arg -> m_Mtx );
  pthread_cond_signal ( &arg -> m_Cond );
  pthread_mutex_unlock ( &arg -> m_Mtx );
}

static void        initProcess                             ( CCPU            * cpu,
                                                             void            * arg )
{
  TChild childData;

  checkResize ( cpu, 500 );
  rwiTest ( cpu, 0, 500 );

  pthread_mutex_init ( &childData . m_Mtx, NULL );
  pthread_cond_init ( &childData . m_Cond, NULL );

  for ( int i = 0; i < 8; i ++ )
  {
    childData . m_Pages = (i+1) * 600;
    childData . m_Free  = true;
    pthread_mutex_lock ( &childData . m_Mtx );
    cpu -> NewProcess ( &childData, (void (*)(CCPU *, void*))childProcess,  false );
    pthread_cond_wait ( &childData . m_Cond, &childData . m_Mtx );
    pthread_mutex_unlock ( &childData . m_Mtx );
  }
  pthread_cond_destroy ( &childData . m_Cond );
  pthread_mutex_destroy ( &childData . m_Mtx );
}

int                main                                    ( void )
{
  const int PAGES = 8 * 1024;

  // PAGES + extra 4KiB for alignment
  uint8_t * mem = new uint8_t [ PAGES * CCPU::PAGE_SIZE + CCPU::PAGE_SIZE ];

  // align to a mutiple of 4KiB
  uint8_t * memAligned = (uint8_t *) (( ((uintptr_t) mem) + CCPU::PAGE_SIZE - 1) & ~(uintptr_t) ~CCPU::ADDR_MASK );

  testStart ();
  MemMgr ( memAligned, PAGES, NULL, initProcess );
  testEnd ( "test #3" );

  delete [] mem;
  return 0;
}
