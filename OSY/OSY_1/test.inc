#include <chrono>
#include <thread>

//=================================================================================================
class CCustomerTest : public CCustomer
{
  public:
    //---------------------------------------------------------------------------------------------
                             CCustomerTest                 ( void )
                             : m_FITIdx ( 0 ),
                               m_CVUTIdx ( 0 )
    {
      counter = 0;
      prepareTests ();
    }
    //---------------------------------------------------------------------------------------------
    virtual AFITCoin         FITCoinGen                    ( void ) override
    {
//          while((int)m_TestsCVUT . size () != counter){
//    std::this_thread::sleep_for(std::chrono::milliseconds(1000));}
      if ( m_FITIdx < m_TestsFIT . size () )
        return AFITCoin ( m_TestsFIT[m_FITIdx++] . first );
      else
        return AFITCoin ();
    }
    //---------------------------------------------------------------------------------------------
    virtual ACVUTCoin        CVUTCoinGen                   ( void ) override
    {

      if ( m_CVUTIdx < m_TestsCVUT . size () )
        return m_TestsCVUT[m_CVUTIdx++] . first;
      else
        return ACVUTCoin ();
    }
    //---------------------------------------------------------------------------------------------
    virtual void             FITCoinAccept                 ( AFITCoin          x ) override
    {
      auto it = find_if ( m_TestsFIT . begin (), m_TestsFIT . end (), 
                          [ x ] ( const pair<AFITCoin, size_t> & v )
      {
        return v . first == x;
      });
      if ( it == m_TestsFIT . end () )
        printf ( "FITCoin: an unknown problem returned\n" );
      else if ( it -> second != x -> m_Count )
        printf ( "FITCoin: count mismatch, %zu != %zu\n", x -> m_Count, it -> second );
      else{

        printf ( "FITCoin: Perfect, %zu == %zu\n", x -> m_Count, it -> second );}

    }
    //---------------------------------------------------------------------------------------------
    virtual void             CVUTCoinAccept                ( ACVUTCoin         x ) override
    {
      auto it = find_if ( m_TestsCVUT . begin (), m_TestsCVUT . end (), 
                          [ x ] ( const pair<ACVUTCoin, size_t> & v )
      {
        return v . first == x;
      });
      if ( it == m_TestsCVUT . end () )
        printf ( "CVUTCoin: an unknown problem returned\n" );
      else if ( it -> second != x -> m_Count )
        printf ( "CVUTCoin: count mismatch, %zu != %zu\n", x -> m_Count, it -> second );
      else{counter++;
        printf ( "CVUTCoin: Perfect, %zu == %zu\n", x -> m_Count, it -> second );}
    }
    //---------------------------------------------------------------------------------------------
  private:
    vector<pair<AFITCoin, uint64_t> >  m_TestsFIT;
    vector<pair<ACVUTCoin, uint64_t> > m_TestsCVUT;
    size_t                   m_FITIdx;
    size_t                   m_CVUTIdx;
    int counter;
    //---------------------------------------------------------------------------------------------
    void                     prepareTests                  ( void )
    {
       m_TestsFIT . emplace_back ( make_shared<CFITCoin> ( vector<uint32_t>{ 0x2ae8944a, 0x2ae8944a }, 32 ), 4294967296 );
      m_TestsFIT . emplace_back ( make_shared<CFITCoin> ( vector<uint32_t>{ 0x00000000 }, 0 ), 1 );
      m_TestsFIT . emplace_back ( make_shared<CFITCoin> ( vector<uint32_t>{ 0xffffffff }, 0 ), 1 );
      m_TestsFIT . emplace_back ( make_shared<CFITCoin> ( vector<uint32_t>{ 0x6b8b4567 }, 0 ), 1 );
      m_TestsFIT . emplace_back ( make_shared<CFITCoin> ( vector<uint32_t>{ 0x327b23c6 }, 1 ), 33 );
      m_TestsFIT . emplace_back ( make_shared<CFITCoin> ( vector<uint32_t>{ 0x643c9869 }, 15 ), 1846943453 );
      m_TestsFIT . emplace_back ( make_shared<CFITCoin> ( vector<uint32_t>{ 0x66334873 }, 16 ), 2448023843 );
      m_TestsFIT . emplace_back ( make_shared<CFITCoin> ( vector<uint32_t>{ 0x74b0dc51 }, 17 ), 3013746563 );
      m_TestsFIT . emplace_back ( make_shared<CFITCoin> ( vector<uint32_t>{ 0x19495cff }, 31 ), 4294967295 );
      m_TestsFIT . emplace_back ( make_shared<CFITCoin> ( vector<uint32_t>{ 0x2ae8944a }, 32 ), 4294967296 );
      m_TestsFIT . emplace_back ( make_shared<CFITCoin> ( vector<uint32_t>{ 0x406518a4, 0x412f1ca1, 0x406d1ca5 }, 2 ), 0 );
      m_TestsFIT . emplace_back ( make_shared<CFITCoin> ( vector<uint32_t>{ 0x5cad9aeb, 0x7da99afb, 0x5d2992cb, 0x5d2992cb }, 4 ), 147 );
      m_TestsFIT . emplace_back ( make_shared<CFITCoin> ( vector<uint32_t>{ 0x396070f3, 0x3b6070f2, 0x796070a2, 0x796470b2, 0x3a6470f3 }, 9 ), 3294848 );
      m_TestsFIT . emplace_back ( make_shared<CFITCoin> ( vector<uint32_t>{ 0x408543d7, 0x428543d6, 0x4a81c3d7, 0x48a1c3d6, 0x4aa143d7, 0x4a8dc3d7 }, 21 ), 3985193193 );
      m_TestsFIT . emplace_back ( make_shared<CFITCoin> ( vector<uint32_t>{ 0xe31d5fdc, 0xe1891fdc, 0xa19b7fde, 0xe3091ddc, 0xa39f6ddc, 0xe19b4fdc, 0xa11d5ddc }, 6 ), 337 );
      m_TestsFIT . emplace_back ( make_shared<CFITCoin> ( vector<uint32_t>{ 0x5ba85e68, 0x3aa85e78, 0x5aaa5ef8, 0x1baa5efa, 0x7ba856ea, 0x5baa5e68, 0x5bb85678, 0x3aaa5668, 0x5aaa56fa, 0x1bba5e6a }, 1 ), 0 );
      m_TestsFIT . emplace_back ( make_shared<CFITCoin> ( vector<uint32_t>{ 0x72d8aa96, 0x64c8a296, 0x76d8aaf6, 0x64c0aafe, 0x76d8aa9a, 0x76d0aaba, 0x74c0aab2, 0x70c8aaba, 0x64d0aa96, 0x76c0aad2, 0x62c0a2be, 0x74d0aa96, 0x76c8a2f2, 0x74c8aafe, 0x76c8aada, 0x66c0aaf6, 0x70d0aab2, 0x66c0aab6, 0x60d0a29a, 0x76c8aad2, 0x74c8aab2, 0x66c0a2f2, 0x62d8aa96, 0x60d8a2d2, 0x76d8aada, 0x62c0aab6, 0x72d8aaf6, 0x74d0a2de, 0x64c8aab2, 0x60c0a2f2, 0x72d8a292, 0x60c8a2ba, 0x64c8aaf6, 0x72d0a296, 0x66c8a296, 0x64c0a292, 0x62c8aabe, 0x62c8a2b6, 0x76d0aabe, 0x76d8a2d6, 0x62d0aafa, 0x60d8a2fa, 0x74d0aada, 0x60c0aafa, 0x76c0a2f6, 0x74c0aab2, 0x70c0a2d2, 0x70d0aa9a, 0x62c0aada, 0x72d8aafa }, 12 ), 8084682 );
  
      m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0x45, 0x23, 0x98, 0x48, 0xdc }, 0, 1 ), 10 );
      m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0x5c, 0x94, 0x58, 0x1f, 0x7c }, 3, 8 ), 277 );
      m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0x58, 0xd7, 0x41, 0x1e, 0xa9 }, 1, 12 ), 704 );
      m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0xe1, 0x00, 0x62, 0x08, 0x27 }, 0, 25 ), 1390 );
      m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0x23, 0xe9, 0xcd, 0x43, 0x0f }, 0, 70 ), 1600 );
      m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0x25, 0xf9, 0x72, 0xc2, 0xd7 }, 7, 7 ), 76 );
      m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0xc4, 0x07, 0xfb, 0x5d, 0x50, 0xd7 }, 9, 14 ), 597 );
      m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0xba, 0xe4, 0x30, 0xd9, 0x61, 0x89 }, 9, 29 ), 1549 );
      m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0xb1, 0xa3, 0xa8, 0x5a, 0x84, 0xa8, 0xbd }, 15, 20 ), 729 );
      m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0x8c, 0xd0, 0xe0, 0x76, 0x9e, 0x24, 0x86, 0xc4 }, 19, 37 ), 1771 );
      m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0x1d, 0xf8, 0x86, 0xf5, 0xbd, 0x8d, 0xf0, 0x1a, 0xdd }, 6, 16 ), 1209 );
      m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0xc8, 0xd4, 0xc2, 0xf8, 0xad, 0x23, 0x82, 0x5f, 0xc6, 0x2a }, 5, 43 ), 4970 );
      m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0xb9, 0x4a, 0xd3, 0x77, 0xd7, 0xa4, 0x58, 0x4e, 0x42, 0x7c, 0xd4 }, 27, 70 ), 3806 );
      m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0x06, 0x9a, 0xcc, 0x8d, 0x8f, 0x89, 0x1b, 0x7f, 0xa4, 0xf9, 0x48, 0x78 }, 50, 100 ), 2167 );
      m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0xbb, 0x40, 0x26, 0xde, 0xc3, 0x85, 0xa5, 0xed, 0x3f, 0xf0, 0xc1, 0xb7, 0xc7 }, 42, 99 ), 4074 );
      m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0x65, 0x0f, 0x15, 0xa8, 0x8c, 0xe9, 0xaf, 0x26, 0xb6, 0x3c, 0xb6, 0x40, 0x57, 0x35 }, 6, 42 ), 7397 );
      m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0xe4, 0x50, 0x7e, 0x5d, 0x0b, 0xbf, 0x84, 0xea, 0x82, 0x0a, 0x8f, 0x70, 0x4a, 0x7f, 0x31 }, 29, 120 ), 10254 );
      m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0x02, 0x47, 0x96, 0x12, 0x5d, 0x3f, 0x9e, 0x47, 0xee, 0xc5, 0xfd, 0x2b, 0x7b, 0x3e, 0x82, 0xb1 }, 47, 95 ), 5992 );
      m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0x23, 0xd3, 0x2f, 0x81, 0xdf, 0xee, 0x06, 0xca, 0x70, 0x11, 0x59, 0xe0, 0x5b, 0xd9, 0x11, 0x5e, 0x21 }, 87, 101 ), 1260 );
      m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0xa8, 0x70, 0x7e, 0xe7, 0x0e, 0xc5, 0xd6, 0xd4, 0xc3, 0x01, 0x4f, 0x01, 0x84, 0x01, 0x24, 0x57, 0x30, 0xa5 }, 55, 130 ), 8277 );
      m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0x37, 0x1e, 0xac, 0x01, 0x8f, 0xbd, 0x5a, 0x70, 0x18, 0x34, 0x82, 0x77, 0x55, 0x2a, 0xe7, 0xd3, 0x12, 0xf6, 0x99 }, 41, 140 ), 14161 );
      m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0xe8, 0xca, 0x5c, 0xea, 0x1a, 0x5d, 0x6e, 0x1b, 0x82, 0xc5, 0x4b, 0x28, 0xfd, 0x6a, 0xd4, 0xfe, 0xfa, 0x91, 0x59, 0x6a }, 67, 111 ), 6494 );
      m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0xaa, 0x8d, 0xec, 0x21, 0xe3, 0x17, 0x09, 0xb7, 0x29, 0xff, 0x50, 0x12, 0xc9, 0xac, 0xfc, 0xe3, 0x0a, 0x6b, 0xff, 0x8d, 0x31, 0x4a, 0xb5, 0x2e, 0xb5 }, 29, 127 ), 30444 );
      m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0x8a, 0x2c, 0xaf, 0x1b, 0x85, 0x1a, 0xc6, 0x13, 0x06, 0xe8, 0xf6, 0x1d, 0xf1, 0xae, 0x47, 0xf0, 0xfe, 0x5a, 0xb9, 0xab, 0x57, 0x9d, 0xb6, 0xc2, 0x9d, 0x43, 0xf3, 0xe8, 0xf8, 0x22 }, 33, 200 ), 50188 );
      m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0x9d, 0x82, 0x4e, 0x4d, 0x9e, 0xd4, 0x67, 0x64, 0xe7, 0x6e, 0x4c, 0xde, 0x8c, 0x3d, 0x8c, 0xd3, 0x2e, 0x8a, 0x2e, 0xe8, 0x36, 0x85, 0x85, 0xec, 0x48, 0x23, 0x2f, 0x3b, 0x0b, 0x28, 0x5e, 0xa8, 0xab, 0xac, 0xf6 }, 100, 210 ), 28425 );
      m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0x4a, 0x80, 0x5d, 0xae, 0x68, 0xcc, 0xfb, 0x46, 0x58, 0x39, 0xd2, 0x2c, 0x67, 0x5d, 0x5a, 0x4f, 0x94, 0xdf, 0xd5, 0x81, 0x27, 0xf8, 0xb1, 0x63, 0x04, 0xd9, 0xc1, 0xac, 0x85, 0x6e, 0xa2, 0xcf, 0xef, 0x00, 0x7e, 0x57, 0xcd, 0x79, 0x9e, 0x25 }, 45, 300 ), 91049 );
      m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0xb3, 0x71, 0x51, 0x1b, 0xcf, 0xab, 0x6b, 0x63, 0x8b, 0x41, 0xe4, 0xb2, 0x3a, 0x95, 0x16, 0x3e, 0x6f, 0xd8, 0xea, 0xf4, 0x46, 0x8d, 0xc3, 0x36, 0x8e, 0x42, 0x8d, 0x5b, 0xbb, 0x2c, 0x81, 0x6f, 0x9d, 0xd2, 0x8a, 0x6c, 0x7e, 0xf5, 0xd0, 0x09, 0x37, 0xb4, 0xbc, 0x71, 0x4a }, 176, 218 ), 14019 );
      m_TestsCVUT . emplace_back ( make_shared<CCVUTCoin> ( vector<uint8_t>{ 0xd3, 0xaf, 0xb9, 0xab, 0x9a, 0xae, 0xf2, 0x28, 0x72, 0x28, 0xb7, 0xb4, 0xb6, 0x13, 0x70, 0xe2, 0x94, 0xdf, 0x80, 0x67, 0x6a, 0xed, 0xe5, 0x60, 0xbd, 0xef, 0x97, 0x72, 0xac, 0x08, 0xbd, 0x7f, 0xb8, 0x76, 0x2b, 0x53, 0x25, 0x1d, 0x7b, 0x97, 0x46, 0x32, 0x4c, 0xfc, 0x45, 0xbc, 0xdf, 0xda, 0x9c, 0x60 }, 245, 365 ), 22990 );
    }
};
//=================================================================================================
void               TestParallel                            ( void )
{
  //{
    CRig s;
    s.Start(4);
    s.Stop();
  //}
  {
  CRig s7;
  s7.Start(1);
  std::this_thread::sleep_for(std::chrono::milliseconds(5));
  s7.AddCustomer ( make_shared<CCustomerTest> () );
  s7.Stop();
  std::this_thread::sleep_for(std::chrono::milliseconds(5));
  s7.AddCustomer ( make_shared<CCustomerTest> () );
  s7.Start(1);
  s7.Stop();
  s7.Start(1);
  s7.AddCustomer ( make_shared<CCustomerTest> () );
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  s7.Stop();
  s7.Stop();
  s7.Start(0);
  s7.Stop();
  }
  cout << "here" << endl;

  s.Start(1);
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  s.AddCustomer ( make_shared<CCustomerTest> () );
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  s.Stop();

  s.AddCustomer ( make_shared<CCustomerTest> () );
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  s.Start(1);
  s.Stop();
//
  CRig s1;

    s1 . AddCustomer ( make_shared<CCustomerTest> () );
    s1. Start(1);
    //s . Start ( 2 );
    s1 . AddCustomer ( make_shared<CCustomerTest> () );
    s1 . Stop ();

  CRig s2;

  s2.Start(3);
  s2.AddCustomer ( make_shared<CCustomerTest> () );
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  s2.AddCustomer ( make_shared<CCustomerTest> () );
  s2.Stop();

  CRig s3;

s3.AddCustomer ( make_shared<CCustomerTest> () );
s3.AddCustomer ( make_shared<CCustomerTest> () );
s3.AddCustomer ( make_shared<CCustomerTest> () );
s3.AddCustomer ( make_shared<CCustomerTest> () );
s3.AddCustomer ( make_shared<CCustomerTest> () );
s3.AddCustomer ( make_shared<CCustomerTest> () );
s3.AddCustomer ( make_shared<CCustomerTest> () );
s3.AddCustomer ( make_shared<CCustomerTest> () );
s3.AddCustomer ( make_shared<CCustomerTest> () );

  s3.Start(4);
  s3.AddCustomer ( make_shared<CCustomerTest> () );
  s3.AddCustomer ( make_shared<CCustomerTest> () );
  s3.AddCustomer ( make_shared<CCustomerTest> () );
  s3.AddCustomer ( make_shared<CCustomerTest> () );
std::this_thread::sleep_for(std::chrono::milliseconds(500));
  s3.AddCustomer ( make_shared<CCustomerTest> () );
  s3.AddCustomer ( make_shared<CCustomerTest> () );
  s3.AddCustomer ( make_shared<CCustomerTest> () );
  s3.AddCustomer ( make_shared<CCustomerTest> () );
  s3.AddCustomer ( make_shared<CCustomerTest> () );

  s3.Stop();

  CRig s4;
  s4.Start(2);
s4.AddCustomer ( make_shared<CCustomerTest> () );
s4.AddCustomer ( make_shared<CCustomerTest> () );
s4.AddCustomer ( make_shared<CCustomerTest> () );
s4.AddCustomer ( make_shared<CCustomerTest> () );
std::this_thread::sleep_for(std::chrono::milliseconds(500));
s4.AddCustomer ( make_shared<CCustomerTest> () );
s4.AddCustomer ( make_shared<CCustomerTest> () );
s4.AddCustomer ( make_shared<CCustomerTest> () );
s4.AddCustomer ( make_shared<CCustomerTest> () );
s4.AddCustomer ( make_shared<CCustomerTest> () );
s4.AddCustomer ( make_shared<CCustomerTest> () );
s4.AddCustomer ( make_shared<CCustomerTest> () );
s4.AddCustomer ( make_shared<CCustomerTest> () );
s4.AddCustomer ( make_shared<CCustomerTest> () );
s4.AddCustomer ( make_shared<CCustomerTest> () );
s4.AddCustomer ( make_shared<CCustomerTest> () );
s4.AddCustomer ( make_shared<CCustomerTest> () );
s4.AddCustomer ( make_shared<CCustomerTest> () );
s4.AddCustomer ( make_shared<CCustomerTest> () );
s4.Stop();

}
//=================================================================================================
void               TestSequential                          ( void )
{
  CCustomerTest c;
  
  for ( AFITCoin x = c . FITCoinGen (); x ; x = c . FITCoinGen () )
  {
    CRig::Solve ( x );
    c . FITCoinAccept ( x );
  }

  for ( ACVUTCoin x = c . CVUTCoinGen (); x ; x = c . CVUTCoinGen () )
  {
    CRig::Solve ( x );
    c . CVUTCoinAccept ( x );
  }
}
//=================================================================================================
int                main                                    ( void )
{
  //TestSequential ();
  TestParallel ();
  return 0;
}
