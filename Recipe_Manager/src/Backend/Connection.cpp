//
// Created by Pavel on 4/16/2017.
//

#include "Connection.h"


///used for user login - connect to database and look if name and password match, assigns value to id
bool Connection::Connect(const string &name, const string &password, int &id)
{
    try
    {
        if(CheckForSQLInjection(name, password))
        {
            return false;
        }
        PGconn *conn = PQconnectdb("dbname=sxaimwia user=sxaimwia password=WG4lC4zFWPTxZI6qR6Ea8PpmshxhW0s2 \
        host=horton.elephantsql.com port=5432");
        if(PQstatus(conn) == CONNECTION_BAD)
        {
            cout << "Can't open database" << endl;
            return false;
        }
        string sql = "SELECT * FROM \"public\".\"users\" WHERE user_name='" + name + "' AND user_password='" + password + "';";

        PGresult *res = PQexec(conn,sql.c_str());
        int rows = 0;
        if(PQresultStatus(res) == PGRES_TUPLES_OK)
        {
            rows = PQntuples(res);
        }
        if(rows==0)
        {
            cout << "Username and password does not match" << endl;
            PQfinish(conn);
            return false;
        }
        rows = PQntuples(res);
        for(int i=0; i<rows; i++)
        {
            string tmp = PQgetvalue(res, i, 0);
            id = atoi( tmp.c_str() );
        }
        cout << "Successful login." << endl;
        PQclear(res);
        PQfinish(conn);
    }
    catch(const std::exception &e)
    {
        cerr << e.what() << std::endl;
        return false;
    }
    return true;
}

/// if registered name does not exist in database, inserts it into database, assigns value to id
bool Connection::Register(const string &name, const string &password, int &id)
{
    try
    {
        if(CheckForSQLInjection(name, password))
        {
            return false;
        }
        PGconn *conn = PQconnectdb("dbname=sxaimwia user=sxaimwia password=WG4lC4zFWPTxZI6qR6Ea8PpmshxhW0s2 \
        host=horton.elephantsql.com port=5432");
        if(PQstatus(conn) == CONNECTION_BAD)
        {
            cout << "Can't open database" << endl;
            return false;
        }

        string sql = "SELECT * FROM \"public\".\"users\" WHERE user_name='" + name + "';";
        PGresult *res = PQexec(conn,sql.c_str());
        int rows = 0;
        if(PQresultStatus(res) == PGRES_TUPLES_OK)
        {
            rows = PQntuples(res);
        }
        if(rows!=0)
        {
            cout << "Username taken." << endl;
            PQfinish(conn);
            return false;
        }
        PQfinish(conn);
        sql = "INSERT INTO \"public\".\"users\" (id_user,user_name,user_password) VALUES (nextval('serial'), '" + name + "', '" +
              password + "');";
        res = this->query(sql);
        PQclear(res);

        sql = "SELECT * FROM \"public\".\"users\" WHERE user_name='" + name + "' AND user_password='" + password + "';";
        res = this->query(sql);

        if(PQresultStatus(res) == PGRES_TUPLES_OK)
        {
            rows = PQntuples(res);
            for(int i=0; i<rows; i++)
            {
                string tmp = PQgetvalue(res, i, 0);
                id = atoi( tmp.c_str() );
            }
        }
        cout << "Successful registration." << endl;
        PQclear(res);
        PQfinish(conn);
    }
    catch(const std::exception &e)
    {
        cerr << e.what() << std::endl;
        return false;
    }
    return true;
}

/**
 * connects to database and queries database using given sql statement
 *  \return pqxx:return from sql query
 */
PGresult * Connection::query(const string sql)
{
    PGresult * r;
    try
    {
        PGconn *conn = PQconnectdb("dbname=sxaimwia user=sxaimwia password=WG4lC4zFWPTxZI6qR6Ea8PpmshxhW0s2 \
        host=horton.elephantsql.com port=5432");

        if (PQstatus(conn) == CONNECTION_BAD) {

            fprintf(stderr, "Connection to database failed: %s\n",
                    PQerrorMessage(conn));
            PQfinish(conn);
        }

        r = PQexec(conn, sql.c_str());

        PQfinish(conn);
    }
    catch(const std::exception &e)
    {
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
bool Connection::CheckForSQLInjection(string firstString, string secondString) const
{
    transform(firstString.begin(), firstString.end(), firstString.begin(), ::toupper);
    transform(secondString.begin(), secondString.end(), secondString.begin(), ::toupper);
    if((firstString.find("DROP") != string::npos) || (secondString.find("DROP") != string::npos))
    {
        return true;
    }
    if((firstString.find("DELETE") != string::npos) || (secondString.find("DELETE") != string::npos))
    {
        return true;
    }
    if((firstString.find("ALTER") != string::npos) || (secondString.find("ALTER") != string::npos))
    {
        return true;
    }
    if((firstString.find("UPDATE") != string::npos) || (secondString.find("UPDATE") != string::npos))
    {
        return true;
    }
    if((firstString.find("GETREQUESTSRING") != string::npos) || (secondString.find("GETREQUESTSRING") != string::npos))
    {
        return true;
    }
    if((firstString.find(" OR ") != string::npos) || (secondString.find(" OR ") != string::npos))
    {
        return true;
    }
    return false;
}

Connection::Connection()
{

}

Connection::~Connection()
{

}