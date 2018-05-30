#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <pthread.h>
#include <semaphore.h>
#include "common.h"
using namespace std;
#endif /* __PROGTEST__ */

#include <iostream> //todo smazat

//-------------------------------------------------------------------------------------------------
                   CCPU::CCPU                              ( uint8_t   * memStart,
                                                             uint32_t    pageTableRoot )
{
  m_MemStart = memStart;
  m_PageTableRoot = pageTableRoot;
}
//-------------------------------------------------------------------------------------------------
bool               CCPU::ReadInt                           ( uint32_t          address,
                                                             uint32_t        & value )
{
  if ( address & 0x3 ) return false; // not aligned
  uint32_t * addr = virtual2Physical ( address, false );
  if ( ! addr ) return false;
  value = *addr;
  return true;
}
//-------------------------------------------------------------------------------------------------
bool               CCPU::WriteInt                          ( uint32_t          address,
                                                             uint32_t          value )
{
  if ( address & 0x3 ) return false; // not aligned
  uint32_t * addr = virtual2Physical ( address, true );
  if ( ! addr ) return false;
  *addr = value;
  return true;
}
//-------------------------------------------------------------------------------------------------
uint32_t         * CCPU::virtual2Physical                  ( uint32_t          address,
                                                             bool              write )
{
  const uint32_t reqMask = BIT_PRESENT | BIT_USER | (write ? BIT_WRITE : 0 );
  const uint32_t orMask = BIT_REFERENCED | (write ? BIT_DIRTY : 0);



  while ( 1 )
  {
    uint32_t * level1 = (uint32_t *)(m_MemStart + (m_PageTableRoot & ADDR_MASK)) + (address >> 22);

    if ( (*level1 & reqMask ) != reqMask )
    {
      if ( pageFaultHandler ( address, write ) ) continue;
      return NULL;
    }
    uint32_t * level2 = (uint32_t *)(m_MemStart + (*level1 & ADDR_MASK )) + ((address >> OFFSET_BITS) & (PAGE_DIR_ENTRIES - 1));

    if ( (*level2 & reqMask ) != reqMask )
    {
      if ( pageFaultHandler ( address, write ) ) continue;
      return NULL;
    }
   *level1 |= orMask;
   *level2 |= orMask;
    return (uint32_t *)(m_MemStart + (*level2 & ADDR_MASK) + (address & ~ADDR_MASK));
  }
}
//-------------------------------------------------------------------------------------------------

