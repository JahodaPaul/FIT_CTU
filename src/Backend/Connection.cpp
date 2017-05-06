//
// Created by Pavel on 4/16/2017.
//

#include "Connection.h"

Connection::Connection() {

}

///used for user login - connect to database and look if name and password match, assigns value to id
bool Connection::Connect(string name,string password,int &id)
{
    try{
        if(CheckForSQLInjection(name,password))
        {
            return false;
        }
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
        for (result::const_iterator c = R.begin(); c != R.end(); ++c)
        {
            id = c[0].as<int>();
        }
        cout << "Successful login." << endl;
        C.disconnect ();
    }catch (const std::exception &e){
        cerr << e.what() << std::endl;
        return false;
    }
    return true;
}

/// if registered name does not exist in database, inserts it into database, assigns value to id
bool Connection::Register(string name, string password,int &id) {
    try{
        if(CheckForSQLInjection(name,password))
        {
            return false;
        }
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

        sql = "SELECT * FROM \"public\".\"users\" WHERE user_name='" + name + "' AND user_password='" + password + "';";
        R=this->query(sql);

        if(R.size()!=0)
        {
            for (result::const_iterator c = R.begin(); c != R.end(); ++c)
            {
                id = c[0].as<int>();
            }
        }

        cout << "Successful registration." << endl;
        C.disconnect ();
    }catch (const std::exception &e){
        cerr << e.what() << std::endl;
        return false;
    }
    return true;
}

/**
 * connects to database and queries database using given sql statement
 *  \return pqxx:return from sql query
 */
result Connection::query(const string sql) {
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
}

/**
 *
 * @param firstString
 * @param secondString
 * \return true if there is a danger
 */
bool Connection::CheckForSQLInjection(string firstString,string secondString) const
{
    transform(firstString.begin(), firstString.end(), firstString.begin(), ::toupper);
    transform(secondString.begin(), secondString.end(), secondString.begin(), ::toupper);
    if ((firstString.find("DROP") != string::npos) || (secondString.find("DROP") != string::npos)) {
        return true;
    }
    if ((firstString.find("DELETE") != string::npos) || (secondString.find("DELETE") != string::npos)) {
        return true;
    }
    if ((firstString.find("ALTER") != string::npos) || (secondString.find("ALTER") != string::npos)) {
        return true;
    }
    if ((firstString.find("UPDATE") != string::npos) || (secondString.find("UPDATE") != string::npos)) {
        return true;
    }
    if ((firstString.find("GETREQUESTSRING") != string::npos) || (secondString.find("GETREQUESTSRING") != string::npos)) {
        return true;
    }
    if ((firstString.find(" OR ") != string::npos) || (secondString.find(" OR ") != string::npos)) {
        return true;
    }
    return false;
}