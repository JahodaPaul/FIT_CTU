#ifndef __test_op_h_2340857234234582345203495623495__
#define __test_op_h_2340857234234582345203495623495__


class CCPU;

void               testStart                               ( void );

void               testEnd                                 ( const char      * prefix );


void               reportError                             ( const char      * prefix,
                                                             ... );
void               rwiTest                                 ( CCPU            * cpu,
                                                             uint32_t          fromPage,
                                                             uint32_t          toPage );
void               rwTest                                  ( CCPU            * cpu,
                                                             uint32_t          fromPage,
                                                             uint32_t          toPage );
void               iTest                                   ( CCPU            * cpu,
                                                             uint32_t          pages );
void               rTest                                   ( CCPU            * cpu,
                                                             uint32_t          fromPage,
                                                             uint32_t          toPage );
void               wTest                                   ( CCPU            * cpu,
                                                             uint32_t          fromPage,
                                                             uint32_t          toPage );
void               checkResize                             ( CCPU            * cpu,
                                                             uint32_t          limit );

#endif /* __test_op_h_2340857234234582345203495623495__ */
