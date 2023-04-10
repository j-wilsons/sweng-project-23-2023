#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <cstdio>
#include "DataBaseManager.h"
#include "json.hpp"
#include <iostream>

using json = nlohmann::json;

SQLCHAR *connectionString = (SQLCHAR*)"Driver={ODBC Driver 18 for SQL Server};Server=tcp:trinity-fixers-server.database.windows.net,1433;Database=FIX Server Database;Uid=TCDADMIN;Pwd={Password2001};Encrypt=yes;TrustServerCertificate=no;Connection Timeout=30;";

SQLHENV env = NULL;
SQLHDBC dbc = NULL;
SQLRETURN ret = SQL_SUCCESS;

void connectToDB()
{
    ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
    ret = SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
    ret = SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);
    ret = SQLDriverConnect(dbc, NULL, connectionString, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_NOPROMPT);
    printf("connected");
}

void pullOrderTable()
{
    printf("pulling");
    SQLHSTMT stmt = NULL;
    SQLCHAR *query = (SQLCHAR *)"SELECT * FROM orders";
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    ret = SQLExecDirect(stmt, query, SQL_NTS);

    if (SQL_SUCCEEDED(ret))
    {
        printf("\nquery succesful\n");
        json orders;

        
        while (SQLFetch(stmt) == SQL_SUCCESS)
        {
            int orderId;
            char side[256];
            char timestamp[256];
            char username[256];
            char ticker[256];
            double price;
            int quantity;

            SQLGetData(stmt, 1, SQL_INTEGER, &orderId, sizeof(orderId), NULL);
            SQLGetData(stmt, 2, SQL_CHAR, side, sizeof(side), NULL);
            SQLGetData(stmt, 3, SQL_C_DOUBLE, &price, sizeof(price), NULL);
            SQLGetData(stmt, 4, SQL_INTEGER, &quantity, sizeof(quantity), NULL);
            SQLGetData(stmt, 5, SQL_CHAR, &timestamp, sizeof(timestamp), NULL);
            SQLGetData(stmt, 6, SQL_CHAR, &username, sizeof(username), NULL);
            SQLGetData(stmt, 7, SQL_CHAR, &ticker, sizeof(ticker), NULL);
            

            json order = {
                {"id", orderId},
                {"side", side},
                {"price", price},
                {"quantity", quantity},
                {"timestamp", timestamp},
                {"username", username},
                {"ticker", ticker},
                };

            orders.push_back(order);
        }
        

        // Print orders in JSON format
        std::cout << orders.dump(4) << std::endl;
    }
    else
    {
        printf("\nError retrieving data from table.\n");
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}