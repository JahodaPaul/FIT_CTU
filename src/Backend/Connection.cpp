//
// Created by Pavel on 4/16/2017.
//

#include "Connection.h"

Connection::Connection() {

}

///used for user login - connect to database and look if name and password match
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
            cout << "Username and password does not match" << endl;
            C.disconnect ();
            return false;
        }
        cout << "Successful login." << endl;
        C.disconnect ();
    }catch (const std::exception &e){
        cerr << e.what() << std::endl;
        return false;
    }
    return true;
}

/// if registered name does not exist in database, inserts it into database
bool Connection::Register(string name, string password) {
    try{
        connection C("dbname=sxaimwia user=sxaimwia password=WG4lC4zFWPTxZI6qR6Ea8PpmshxhW0s2 \
        host=horton.elephantsql.com port=5432");
        if (C.is_open()) {

        } else {
            cout << "Can't open database" << endl;
            return false;
        }
        string sql = "SELECT * FROM \"public\".\"users\" WHERE user_name='" + name + "';";
        work txn(C);
        // SQL statement
        result R = txn.exec(sql);
        // Execute SQL query
        if(R.size()!=0)
        {
            cout << "Username taken." << endl;
            C.disconnect ();
            return false;
        }
        C.disconnect();
        sql = "INSERT INTO \"public\".\"users\" (id_user,user_name,user_password) VALUES (nextval('serial'), " + txn.quote(name) + ", " + txn.quote(password) + ");";
        R = this->query(sql);
        cout << "Successful registration." << endl;
        C.disconnect ();
    }catch (const std::exception &e){
        cerr << e.what() << std::endl;
        return false;
    }
    return true;
}

///connects to database and queries database using given sql statement
result Connection::query(string sql) {
    result r;
    try{
        connection C("dbname=sxaimwia user=sxaimwia password=WG4lC4zFWPTxZI6qR6Ea8PpmshxhW0s2 \
        host=horton.elephantsql.com port=5432");
        work txn(C);
        // SQL statement
        r = txn.exec(sql);
        txn.commit();
    }
    catch (const std::exception &e){
        cerr << e.what() << std::endl;
    }
    return r;
    /**
     *  \return pqxx:return from sql query
     */
}