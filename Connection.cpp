//
// Created by Pavel on 4/16/2017.
//

#include "Connection.h"

Connection::Connection() {

}

bool Connection::Connect(string name,string password)
{
    try{
        connection C("dbname=sxaimwia user=sxaimwia password=WG4lC4zFWPTxZI6qR6Ea8PpmshxhW0s2 \
        host=horton.elephantsql.com port=5432");
        if (C.is_open()) {

        } else {
            cout << "Can't open database" << endl;
            return false;
        }
        string sql = "SELECT * FROM \"public\".\"users\" WHERE user_name='" + name + "' AND user_password='" + password + "';";

        nontransaction N(C);

        // Execute SQL query
        result R( N.exec( sql ));
        if(R.size()==0)
        {
            cout << "username and password does not match" << endl;
            C.disconnect ();
            return false;
        }
        cout << "successful login" << endl;
        C.disconnect ();
    }catch (const std::exception &e){
        cerr << e.what() << std::endl;
        return false;
    }
    return true;
}

result Connection::query(string sql) {
    result r;
    try{
        connection C("dbname=sxaimwia user=sxaimwia password=WG4lC4zFWPTxZI6qR6Ea8PpmshxhW0s2 \
        host=horton.elephantsql.com port=5432");
        work txn{C};
        // SQL statement
        result r = txn.exec(sql);
        txn.commit();
    }
    catch (const std::exception &e){
        cerr << e.what() << std::endl;
    }
    return r;
}