#include <stdio.h>
#include <stdlib.h>
#include <sqlext.h>
#include <sql.h>

#define NAME_LEN 50
#define PHONE_LEN 20

// OK -- cc SQLBindColtest.c -I sql/include/odbc_linux -I/usr/include -I /opt/microsoft/msodbcsql17/include/ -lodbc -o exec && ./exec 

void show_error() { printf("errorn"); }

int main()
{
    printf("Start");

    SQLHENV henv;
    SQLHDBC hdbc;
    SQLHSTMT hstmt = 0;
    SQLRETURN retcode;
    SQLCHAR szName[NAME_LEN], szPhone[PHONE_LEN], sCustID[NAME_LEN];
    SQLLEN cbName = 0, cbCustID = 0, cbPhone = 0;

    // Allocate environment handle
    retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);

    // Set the ODBC version environment attribute
    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
    {
        
        retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER *)SQL_OV_ODBC3, 0);

        // Allocate connection handle
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
        {
            retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);

            // Set login timeout to 5 seconds
            if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
            {
                SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);

                // Connect to data source
                retcode = SQLConnect(hdbc, (SQLCHAR *)"MSSQLTest", 10, (SQLCHAR *)"sa", 3, (SQLCHAR *)"M@sterX@!", 10);

                // Allocate statement handle
                if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
                {
                    printf("\r\nConnected");

                    retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

                    retcode = SQLExecDirect(hstmt, (SQLCHAR *)"SELECT * FROM SYSOBJECTS", SQL_NTS);
                    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
                    {
                        // Bind columns 1, 2, and 3
                        retcode = SQLBindCol(hstmt, 1, SQL_C_CHAR, sCustID, 100, &cbCustID);
                        retcode = SQLBindCol(hstmt, 2, SQL_C_CHAR, szName, NAME_LEN, &cbName);
                        retcode = SQLBindCol(hstmt, 3, SQL_C_CHAR, szPhone, PHONE_LEN, &cbPhone);

                        // Fetch and print each row of data. On an error, display a message and exit.
                        for (int i = 0;; i++)
                        {
                            retcode = SQLFetch(hstmt);
                            if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
                                show_error();
                            if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
                                printf("%d: %s %s %sn", i + 1, sCustID, szName, szPhone);
                            else
                                break;
                        }
                    }

                    // Process data
                    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
                    {
                        SQLCancel(hstmt);
                        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
                    }

                    SQLDisconnect(hdbc);
                }

                SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
            }
        }
        SQLFreeHandle(SQL_HANDLE_ENV, henv);
    }
}