#ifndef __common_h__5872395623940562390452903457234__
#define __common_h__5872395623940562390452903457234__

const uint32_t     PROCESS_MAX = 64;

class CCPU
{
  public:
    static const uint32_t    OFFSET_BITS                   =                12;
    static const uint32_t    PAGE_SIZE                     =  1 << OFFSET_BITS;
    static const uint32_t    PAGE_DIR_ENTRIES              =     PAGE_SIZE / 4;
    static const uint32_t    ADDR_MASK                     = ~ (PAGE_SIZE - 1);
    static const uint32_t    BIT_PRESENT                   = 0x0001;
    static const uint32_t    BIT_WRITE                     = 0x0002;
    static const uint32_t    BIT_USER                      = 0x0004;
    static const uint32_t    BIT_REFERENCED                = 0x0020;
    static const uint32_t    BIT_DIRTY                     = 0x0040;

                             CCPU                          ( uint8_t         * memStart,
                                                             uint32_t          pageTableRoot );
    virtual                 ~CCPU                          ( void )
    {
    }
    virtual uint32_t         GetMemLimit                   ( void ) const = 0;
    virtual bool             SetMemLimit                   ( uint32_t          pages ) = 0;
    virtual bool             NewProcess                    ( void            * processArg,
                                                             void           (* entryPoint) ( CCPU *, void * ),
                                                             bool              copyMem ) = 0;

    bool                     ReadInt                       ( uint32_t          address,
                                                             uint32_t        & value );
    bool                     WriteInt                      ( uint32_t          address,
                                                             uint32_t          value );
  protected:
    uint32_t               * virtual2Physical              ( uint32_t          address,
                                                             bool              write );
    virtual bool             pageFaultHandler              ( uint32_t          address,
                                                             bool              write )
    {
      return false;
    }

    uint8_t                * m_MemStart;
    uint32_t                 m_PageTableRoot;
};


void                         MemMgr                        ( void            * mem,
                                                             uint32_t          totalPages,
                                                             void            * processArg,
                                                             void           (* mainProcess) ( CCPU *, void * ));

#endif /* __common_h__5872395623940562390452903457234__ */
