#include <iostream>
#include <map>

#include "test_helpers.hxx"

using namespace std;
using namespace pqxx;


// Test program for libpqxx.  Issue queries through a pipeline, and retrieve
// results both in-order and out-of-order.
namespace
{
typedef map<pipeline::query_id, int> Exp;

template<typename MAPIT>
void checkresult(pipeline &P, MAPIT c)
{
  const result r = P.retrieve(c->first);
  const int val = r.at(0).at(0).as(int(0));
  PQXX_CHECK_EQUAL(val, c->second, "Wrong result from pipeline.");
}


void test_071(transaction_base &W)
{
  pipeline P(W);

  // Keep expected result for every query we issue
  Exp values;

  // Insert queries returning various numbers
  for (int i=1; i<10; ++i) values[P.insert("SELECT " + to_string(i))] = i;

  // Retrieve results in query_id order, and compare to expected values
  for (Exp::const_iterator c=values.begin(); c!=values.end(); ++c)
    checkresult(P, c);

  PQXX_CHECK(P.empty(), "Pipeline was not empty retrieving all results.");

  values.clear();

  // Insert more queries returning various numbers
  P.retain(20);
  for (int i=100; i>90; --i) values[P.insert("SELECT " + to_string(i))] = i;

  P.resume();

  // Retrieve results in reverse order
  for (Exp::reverse_iterator c=values.rbegin(); c!=values.rend(); ++c)
    checkresult(P, c);

  values.clear();
  P.retain(10);
  for (int i=1010; i>1000; --i) values[P.insert("SELECT "+to_string(i))] = i;
  for (Exp::const_iterator c=values.begin(); c!=values.end(); ++c)
  {
    if (P.is_finished(c->first))
      cout << "Query #" << c->first << " completed despite retain()" << endl;
  }

  // See that all results are retrieved by complete()
  P.complete();
  for (Exp::const_iterator c=values.begin(); c!=values.end(); ++c)
    PQXX_CHECK(P.is_finished(c->first), "Query not finished after complete().");
}
} // namespace

PQXX_REGISTER_TEST_C(test_071, asyncconnection)
