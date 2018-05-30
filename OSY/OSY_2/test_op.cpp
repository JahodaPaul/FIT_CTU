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
static int g_Fail;
static pthread_mutex_t g_Mtx;

//-------------------------------------------------------------------------------------------------
void               reportError                             ( const char      * prefix,
                                                             ... )
{
  va_list va;

  pthread_mutex_lock ( &g_Mtx );
  g_Fail ++;
  va_start ( va, prefix );
  vprintf (prefix, va );
  va_end ( va );
  pthread_mutex_unlock ( &g_Mtx );
}
//-------------------------------------------------------------------------------------------------
void               checkResize                             ( CCPU            * cpu,
                                                             uint32_t          limit )
{
  cpu -> SetMemLimit ( limit );
  if ( cpu -> GetMemLimit () != limit )
    reportError ( "Mem limit error: %d expected, %d returned\n", limit, cpu -> GetMemLimit () );
}
//-------------------------------------------------------------------------------------------------
static void        checkWrite                              ( CCPU            * cpu,
                                                             uint32_t          addr,
                                                             uint32_t          val )
{
  if ( ! cpu -> WriteInt ( addr, val ) )
    reportError ( "failed: WriteInt ( %x, %u )\n", addr, val );
}
//-------------------------------------------------------------------------------------------------
static void        checkRead                               ( CCPU            * cpu,
                                                             uint32_t          addr,
                                                             uint32_t          expected )
{
  uint32_t val;

  if ( ! cpu -> ReadInt ( addr, val ) )
    reportError ( "failed: ReadInt ( %x, ... )\n", addr );
  else if ( val != expected )
    reportError ( "read mismatch, addr %x, read: %u, expected: %u\n", addr, val, expected );
}
//-------------------------------------------------------------------------------------------------
void               wTest                                   ( CCPU            * cpu,
                                                             uint32_t          fromPage,
                                                             uint32_t          toPage )
{
  for ( uint32_t addr = fromPage * CCPU::PAGE_SIZE; addr < toPage * CCPU::PAGE_SIZE; addr += 32 )
    checkWrite ( cpu, addr, addr ^ fromPage );
}
//-------------------------------------------------------------------------------------------------
void               rTest                                   ( CCPU            * cpu,
                                                             uint32_t          fromPage,
                                                             uint32_t          toPage )
{
  for ( uint32_t addr = fromPage * CCPU::PAGE_SIZE; addr < toPage * CCPU::PAGE_SIZE; addr += 32 )
    checkRead ( cpu, addr, addr ^ fromPage );
}
//-------------------------------------------------------------------------------------------------
void               iTest                                   ( CCPU            * cpu,
                                                             uint32_t          pages )
{
  uint32_t val;

  for ( uint32_t i = pages * CCPU::PAGE_SIZE; i < 4 * pages * CCPU::PAGE_SIZE; i += 744 )
    if ( cpu -> ReadInt ( i, val ) )
      reportError ( "readInt (%d) succeeds, shall fail\n", i );

  for ( uint32_t i = pages * CCPU::PAGE_SIZE; i < 4 * pages * CCPU::PAGE_SIZE; i += 952 )
    if ( cpu -> WriteInt ( i, i - 300 ) )
      reportError ( "writeInt (%d) succeeds, shall fail\n", i );

  for ( uint32_t i = pages * CCPU::PAGE_SIZE; i < 0xfff00000; i += 500000 )
    if ( cpu -> ReadInt ( i, val ) )
      reportError ( "readInt (%d) succeeds, shall fail\n", i );

  for ( uint32_t i = pages * CCPU::PAGE_SIZE; i < 0xfff00000; i += 500000 )
    if ( cpu -> WriteInt ( i, i - 300 ) )
      reportError ( "writeInt (%d) succeeds, shall fail\n", i );
}
//-------------------------------------------------------------------------------------------------
void               rwTest                                  ( CCPU            * cpu,
                                                             uint32_t          fromPage,
                                                             uint32_t          toPage )
{
  wTest ( cpu, fromPage, toPage );
  rTest ( cpu, fromPage, toPage );
}
//-------------------------------------------------------------------------------------------------
void               rwiTest                                 ( CCPU            * cpu,
                                                             uint32_t          fromPage,
                                                             uint32_t          toPage )
{
  wTest ( cpu, fromPage, toPage );
  rTest ( cpu, fromPage, toPage );
  iTest ( cpu, toPage );
}
//-------------------------------------------------------------------------------------------------
void               testStart                               ( void )
{
  pthread_mutex_init ( &g_Mtx, NULL );
  g_Fail = 0;
}
//-------------------------------------------------------------------------------------------------
void               testEnd                                 ( const char      * prefix )
{
  pthread_mutex_destroy ( &g_Mtx );
  printf ( "%s: %d failures\n", prefix, g_Fail );
}
//-------------------------------------------------------------------------------------------------
