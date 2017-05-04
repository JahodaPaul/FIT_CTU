#include "test_helpers.hxx"

using namespace std;
using namespace pqxx;


// Test program for libpqxx.  Modify the database inside a NonTransaction, and
// verify that the change gets made regardless of whether the NonTransaction is
// eventually committed or aborted.  A lazy connection is used.
namespace
{
int BoringYear = 1977;


void test_039(transaction_base &T1)
{
  test::create_pqxxevents(T1);
  connection_base &C(T1.conn());
  const string Table = "pqxxevents";


  // Verify our start condition before beginning: there must not be a 1977
  // record already.
  result R( T1.exec("SELECT * FROM " + Table + " "
	              "WHERE year=" + to_string(BoringYear)) );

  PQXX_CHECK_EQUAL(
	R.size(),
	0u,
	"Already have a row for " + to_string(BoringYear) + ", cannot test.");

  // (Not needed, but verify that clear() works on empty containers)
  R.clear();
  PQXX_CHECK(R.empty(), "Result is non-empty after clear().");

  // OK.  Having laid that worry to rest, add a record for 1977.
  T1.exec("INSERT INTO " + Table + " VALUES"
            "(" +
	    to_string(BoringYear) + ","
	    "'Yawn'"
	    ")");

  // Abort T1.  Since T1 is a NonTransaction, which provides only the
  // transaction class interface without providing any form of transactional
  // integrity, this is not going to undo our work.
  T1.abort();

  // Verify that our record was added, despite the Abort()
  nontransaction T2(C, "T2");
  R = T2.exec("SELECT * FROM " + Table + " "
		"WHERE year=" + to_string(BoringYear));
  PQXX_CHECK_EQUAL(R.size(), 1u, "Unexpected result size.");

  PQXX_CHECK(R.capacity() >= R.size(), "Result's capacity is too small.");

  R.clear();
  PQXX_CHECK(R.empty(), "result::clear() is broken.");

  // Now remove our record again
  T2.exec("DELETE FROM " + Table + " "
	    "WHERE year=" + to_string(BoringYear));

  T2.commit();

  // And again, verify results
  nontransaction T3(C, "T3");

  R = T3.exec("SELECT * FROM " + Table + " "
	        "WHERE year=" + to_string(BoringYear));

  PQXX_CHECK_EQUAL(R.size(), 0u, "Record is not gone as expected.");
}
} // namespace

PQXX_REGISTER_TEST_CT(test_039, lazyconnection, nontransaction)
