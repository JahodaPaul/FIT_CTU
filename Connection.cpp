//
// Created by Pavel on 4/16/2017.
//

#include "Connection.h"

Connection::Connection() {

}

void Connection::Connect()
{
    string sql;
    try{
        connection C("dbname=sxaimwia user=sxaimwia password=WG4lC4zFWPTxZI6qR6Ea8PpmshxhW0s2 \
      host=horton.elephantsql.com port=5432");
        if (C.is_open()) {
            cout << "Opened database successfully: " << C.dbname() << endl;

        } else {
            cout << "Can't open database" << endl;
            return;
        }
            /* Create SQL statement */
            sql = "SELECT * FROM \"public\".\"cheese\" WHERE name_cheese='Acorn';";

            /* Create a non-transactional object. */
            nontransaction N(C);

            /* Execute SQL query */
            result R( N.exec( sql ));

            /* List down all the records */
            for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
                cout << "ID = " << c[0].as<int>() << endl;
                cout << "Name = " << c[1].as<string>() << endl;
            }



        C.disconnect ();
    }catch (const std::exception &e){
        cerr << e.what() << std::endl;
        return;
    }
}