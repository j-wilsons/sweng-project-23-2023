#include "MatchingEngine.h"
#include <sql.h>
#include <sqlext.h>
#include <cstdio>
#include "json.hpp"
#include <iostream>

using json = nlohmann::json;

SQLCHAR *connectionString = (SQLCHAR *)"Driver={ODBC Driver 18 for SQL Server};Server=tcp:trinity-fixers-server.database.windows.net,1433;Database=FIX Server Database;Uid=TCDADMIN;Pwd={Password2001};Encrypt=yes;TrustServerCertificate=no;Connection Timeout=30;";

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

void deleteOrder(int orderId)
{
    SQLHSTMT stmt = NULL;
    SQLCHAR *query = (SQLCHAR *)"DELETE FROM orders WHERE id = ?";

    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    ret = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &orderId, 0, NULL);
    ret = SQLExecDirect(stmt, query, SQL_NTS);

    if (SQL_SUCCEEDED(ret))
    {
        printf("Order with ID %d deleted successfully.\n", orderId);
    }
    else
    {
        printf("Error deleting order with ID %d.\n", orderId);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void showSQLError(unsigned int handleType, const SQLHANDLE &handle)
{
    SQLCHAR SQLState[1024];
    SQLCHAR message[1024];
    SQLINTEGER nativeError;
    SQLSMALLINT textLength;

    SQLGetDiagRec(handleType, handle, 1, SQLState, &nativeError, message, sizeof(message), &textLength);
    printf("SQL Error: %s\nMessage: %s\n", SQLState, message);
}

void addOrderToDatabase(int orderId, const std::string &side, double price, int quantity, const std::string &timestamp, const std::string &username, const std::string &ticker)
{
    try
    {
        SQLHSTMT stmt = NULL;
        SQLCHAR *query = (SQLCHAR *)"INSERT INTO orders (side, price, quantity, username, ticker) VALUES (?, ?, ?, ?, ?);";

        // Allocate a statement handle
        ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

        // Bind parameters
        SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, side.size(), 0, (SQLPOINTER)side.c_str(), 0, NULL);
        SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE, 0, 0, &price, 0, NULL);
        SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &quantity, 0, NULL);
        SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, username.size(), 0, (SQLPOINTER)username.c_str(), 0, NULL);
        SQLBindParameter(stmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, ticker.size(), 0, (SQLPOINTER)ticker.c_str(), 0, NULL);

        // Execute query
        ret = SQLExecDirect(stmt, query, SQL_NTS);
        if (SQL_SUCCEEDED(ret))
        {
            printf("\nOrder added to the database successfully.\n");
            printf("\nMatching Engine searching...\n");
            startEngine();
        }
        else
        {
            printf("\nError adding order to the database.\n");
            showSQLError(SQL_HANDLE_STMT, stmt); // Display the error message
        }

        // Free statement handle
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    }
    catch (std::exception &e)
    {
        std::cout << e.what();
    }
}

json pullOrderTable()
{
    printf("pulling");
    json orders;
    SQLHSTMT stmt = NULL;
    SQLCHAR *query = (SQLCHAR *)"SELECT * FROM orders";
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    ret = SQLExecDirect(stmt, query, SQL_NTS);

    if (SQL_SUCCEEDED(ret))
    {
        printf("\nquery succesful\n");

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
        // std::cout << orders.dump(4) << std::endl;
    }
    else
    {
        printf("\nError retrieving data from table.\n");
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    return orders;
}