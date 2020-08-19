﻿#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <stdio.h>
#include <stdlib.h>
#ifdef WIN32
#include <conio.h>
#endif
#include <ctype.h>

#ifdef WIN32
#include <windows.h>
#include <tchar.h>
#endif

#include <SQLAPI.h>
#include <samisc.h>


//#include "refcursors.cpp"

size_t FromStringWriter(SAPieceType_t& ePieceType,
	void* pBuf, size_t nLen, void* pAddlData);

void IntoStringReader(
	SAPieceType_t ePieceType,
	void* pBuf,
	size_t nLen,
	size_t nBlobSize,
	void* pAddlData);

/*
static FILE *pFile = NULL;
size_t nTotalBound;
size_t FromFileWriter(SAPieceType_t &ePieceType,
	void *pBuf, size_t nLen, void *pAddlData)
{
	if (ePieceType == SA_FirstPiece)
	{
		const char *sFilename = (const char *)pAddlData;
		pFile = fopen(sFilename, "rb");
		if (!pFile)
			SAException::throwUserException(-1, _TSA("Can not open file '%s'"),
			(const SAChar*)SAString(sFilename));
		nTotalBound = 0;
	}

	size_t nRead = fread(pBuf, 1, nLen, pFile);
	nTotalBound += nRead;

	// show progress
	printf("%d bytes of file bound\n", nTotalBound);

	if (feof(pFile))
	{
		if (ePieceType == SA_FirstPiece)
			ePieceType = SA_OnePiece;
		else
			ePieceType = SA_LastPiece;

		fclose(pFile);
		pFile = NULL;
	}
	return nRead;
}

SAString ReadWholeFile(const char *sFilename, bool binaryData)
{
	SAString s;
	char sBuf[1024];
	FILE *pFile = fopen(sFilename, binaryData ? "rb" : "rt");

	if (!pFile)
		SAException::throwUserException(-1, _TSA("Error opening file '%s'\n"),
		(const SAChar*)SAString(sFilename));

	do
	{
		size_t nRead = fread(sBuf, 1, sizeof(sBuf), pFile);
		s += SAString((const void*)sBuf, nRead);
	} while (!feof(pFile));

	fclose(pFile);
	return s;
}

SAString ReadWholeTextFile(const SAChar *szFilename)
{
	SAString s;
	char szBuf[32 * 1024];
	FILE *pFile = _tfopen(szFilename, _TSA("rb"));

	if (!pFile)
		SAException::throwUserException(-1, _TSA("Error opening file '%s'\n"),
		(const SAChar*)SAString(szFilename));

	do
	{
		size_t nRead = fread(szBuf, 1, sizeof(szBuf), pFile);
		s += SAString(szBuf, nRead);
	} while (!feof(pFile));

	fclose(pFile);
	return s;
}

void WriteWholeFile(const char *sFilename, const SAString& data)
{
	FILE *pFile = fopen(sFilename, "wb");
	size_t n, written = 0, len = data.GetBinaryLength();
	const void* pData = (const void*)data;

	sa_tprintf(_TSA("PRGLEN: %d\n"), len);

	if (!pFile)
		SAException::throwUserException(-1, _TSA("Error opening file '%s'\n"),
		(const SAChar*)SAString(sFilename));

	while (len > written) {
		n = fwrite((const char*)pData + written, 1, sa_min(1024, len - written), pFile);
		if (n <= 0)
			break;
		written += n;
	}

	fclose(pFile);
}

size_t nTotalRead;

void IntoFileReader(
	SAPieceType_t ePieceType,
	void *pBuf,
	size_t nLen,
	size_t nBlobSize,
	void *pAddlData)
{
	const char *sFilename = (const char *)pAddlData;

	if (ePieceType == SA_FirstPiece || ePieceType == SA_OnePiece)
	{
		nTotalRead = 0;

		pFile = fopen(sFilename, "wb");
		if (!pFile)
			SAException::throwUserException(-1, _TSA("Can not open file '%s' for writing"),
			(const SAChar*)SAString(sFilename));
	}

	fwrite(pBuf, 1, nLen, pFile);

	nTotalRead += nLen;

	if (ePieceType == SA_LastPiece || ePieceType == SA_OnePiece)
	{
		fclose(pFile);
		pFile = NULL;
		printf("%s : %d bytes of %d read\n",
			sFilename, nTotalRead, nBlobSize);
	}
}
*/

#include <locale.h>

int main(int argc, char** argv)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	setlocale(LC_ALL, "");

	SACommand cmd;

	SAConnection con;

	cmd.setConnection(&con);

	try
	{
		//con.setOption(_TSA("UseAPI")) = _TSA("OLEDB"); // force SQLAPI to use OLEDB instead of ODBC
		//con.setOption(_TSA("OLEDBProvider")) = _TSA("CompactEdition.4.0");
		//con.setClient(SA_SQLServer_Client);

		/*
		con.setOption(_TSA("DBPROP_INIT_TIMEOUT")) = _TSA("5"); // 5 second DB connect time out - not network connect time out!
		con.setOption(_TSA("CreateDatabase")) = _TSA("TRUE");
		con.setOption(_TSA("DBPROP_SSCE_ENCRYPTDATABASE")) = _TSA("VARIANT_TRUE");
		con.setOption(_TSA("DBPROP_SSCE_MAXBUFFERSIZE")) = _TSA("102400"); // what is the maximum size possible? "The largest amount of memory, in kilobytes, that SQL Server Compact Edition can use before it starts flushing changes to disk. The default value is 640 kilobytes."
		con.setOption(_TSA("DBPROP_SSCE_MAX_DATABASE_SIZE")) = _TSA("4091");
		con.setOption(_TSA("DBPROP_SSCE_TEMPFILE_MAX_SIZE")) = _TSA("4091");
		con.setOption(_TSA("DBPROP_SSCE_DEFAULT_LOCK_ESCALATION")) = _TSA("250000");  // http://msdn.microsoft.com/en-us/library/ms172010(SQL.100).aspx
		con.setOption(_TSA("DBPROP_SSCE_AUTO_SHRINK_THRESHOLD")) = _TSA("100"); // disable auto shrink
		con.setOption(_TSA("DBPROP_SSCE_DEFAULT_LOCK_TIMEOUT")) = _TSA("500"); // 0.5 seconds
		*/
		//con.Connect(_TSA("D:\\1a0f1652-1e85-4048-8b8f-1574793ab8bd.sdf"), _TSA("sa"), _TSA("{F084AF71-AA6F-45c2-A0C3-5160070C0F52}"));

		//con.setOption(_TSA("SQLNCLI.LIBS")) = _TSA("sqlsrv32.dll");

		//con.Connect(_TSA("server=demo12"), _TSA("DBA"), _TSA("sql"), SA_SQLAnywhere_Client);
		//con.Connect(_TSA("server=demo17"), _TSA("DBA"), _TSA("sql"), SA_SQLAnywhere_Client);
		//con.Connect(_TSA("ol_informix1210"), _TSA("yas"), _TSA("Cthdthjr"), SA_Informix_Client);
		//con.Connect(_TSA("bedlam-wx\\sql2017,49805@test"), _TSA(""), _TSA(""), SA_SQLServer_Client);		
		//con.setOption(_TSA("UseAPI")) = _TSA("OLEDB");
		//con.setOption(_TSA("SQLNCLI.LIBS")) = _TSA("sqlncli11.dll");
		//con.Connect(_TSA("bedlam-m\\sql2014en@test"), _TSA(""), _TSA(""), SA_SQLServer_Client);
		//con.Connect(_TSA("Driver=SQLite3 ODBC Driver;Database=d:\\sqlite.db;"), _TSA(""), _TSA(""), SA_ODBC_Client);
		//con.Connect(_TSA("ora111"), _TSA("sys"), _TSA("java"), SA_Oracle_Client);
		//con.Connect(_TSA("ora1221"), _TSA(""), _TSA(""), SA_Oracle_Client);
		//con.Connect(_TSA("localhost@test"), _TSA("postgres"), _TSA("java"), SA_PostgreSQL_Client);

		//con.setOption(_TSA("CS_SEC_ENCRYPTION")) = _TSA("CS_TRUE");
		//api.setClient(SA_Sybase_Client);
		//con.Connect(_TSA("xxx@master"), _TSA("sa"), _TSA("java1970"), SA_Sybase_Client);

		//con.Connect(_TSA("SAMPLE"), _TSA("db2admin"), _TSA("java"), SA_DB2_Client);
		//con.Connect(_TSA("DSN=SAMPLE;TraceFileName=d:\\db2.log;Trace=1;TraceFlush=1"), _TSA(""), _TSA(""), SA_DB2_Client);

		//con.setOption(_TSA("IBASE.LIBS")) = _TSA("fbclient.dll");
		//con.Connect(_TSA("localhost/ibxe3:d:/Test_xe3.gdb"), _TSA("SYSDBA"), _TSA("masterkey"), SA_InterBase_Client);

		//con.setOption(_TSA("IBASE.LIBS")) = _TSA("fbclient.dll");
		//con.Connect(_TSA("localhost:d:/Firebird/3.0.2-x64/test.gdb"), _TSA("SYSDBA"), _TSA("masterkey"), SA_InterBase_Client);
		//con.Connect(_TSA("xnet://d:/Firebird/3.0.2-x64/test.gdb"), _TSA("SYSDBA"), _TSA("masterkey"), SA_InterBase_Client);

		//SAString sVer = con.ServerVersionString();

		//con.setOption(SACON_OPTION_APPNAME) = _TSA("SQLAPI");
		//con.Connect(_TSA("localhost@test2"), _TSA("admin"), _TSA("admin"), SA_CubeSQL_Client);

		//con.Connect(_TSA("Server=(localdb)\\MSSQLLocalDB;AttachDbFileName=D:\\TEST.MDF"), _TSA(""), _TSA(""), SA_SQLServer_Client);

		//con.setAutoCommit(SAAutoCommit_t::SA_AutoCommitOff);
		//con.setOption(_TSA("MYSQL.LIBS")) = _TSA("D:\\mysql\\5.7.18-winx64\\lib\\libMySQL.dll");
		//long x = con.ClientVersion();

		//con.Connect(_TSA("localhost@test"), _TSA("root"), _TSA(""), SA_MySQL_Client);

		//con.setOption(_TSA("SQLNCLI.LIBS")) = _TSA("sqlncli11.dll");
		//con.setOption(_TSA("SQLNCLI.LIBS")) = _TSA("sqlsrv32.dll");
		//con.Connect(_TSA("bedlam-m\\sql2014en@test"), _TSA(""), _TSA(""), SA_SQLServer_Client);
		//con.Connect(_TSA("SQL2014EN"), _TSA(""), _TSA(""), SA_ODBC_Client);
		//con.setOption(_TSA("UseAPI")) = ("OLEDB");
		//con.Connect(_TSA("bedlam-m\\sql2017@test"), _TSA(""), _TSA(""), SA_SQLServer_Client);
		//con.Connect(_TSA("kdx"), _TSA("yas"), _TSA("java"), SA_Oracle_Client);

		//con.setOption(_TSA("LIBPQ.LIBS")) = _TSA("sqlite3.dll");
		//con.Connect(_TSA("localhost@test"), _TSA("postgres"), _TSA("java"), SA_PostgreSQL_Client);

		//con.setOption(_TSA("UseAPI")) = ("OLEDB");
		//con.setOption(_TSA("OLEDBProvider")) = _TSA("SQLOLEDB");
		//con.Connect(_TSA("localhost@test"), _TSA("root"), _TSA(""), SA_MySQL_Client);
		//con.Connect(_TSA("d:/test.db"), _TSA(""), _TSA(""), SA_SQLite_Client);

con.setOption(_TSA("UseAPI")) = ("OLEDB");
con.setOption(_TSA("OLEDBProvider")) = _TSA("CompactEdition.4.0");
con.Connect(_TSA("d:\\datamodel.sdf"), _TSA(""), _TSA(""), SA_SQLServer_Client);

//con.Connect(_TSA("MSACCESS"), _TSA(""), _TSA(""), SA_ODBC_Client);
/*
cmd.setCommandText(_TSA("insert into t1(f1) values(:1)"));
cmd.Param(1).setAsString() = SAString("xxxx");
cmd.Param(1).setAsString() = SAString(L"xxxx");
cmd << SAString("xxxx") << SAString(L"xxx");

cmd.Execute();
*/
cmd.setCommandText(_TSA("select AUTOINC_SEED, AUTOINC_INCREMENT from INFORMATION_SCHEMA.COLUMNS"), SA_CmdSQLStmt);
cmd.Execute();
while (cmd.FetchNext())
{
	printf("%s\t%s\n", cmd.Field(1).asString().GetMultiByteChars(), cmd.Field(2).asString().GetMultiByteChars());
}
	}
	catch (SAException& x)
	{
		printf("ERROR:\n%s\n", x.ErrText().GetMultiByteChars());
	}

	return 0;
}

size_t FromStringWriter(SAPieceType_t& ePieceType,
	void* pBuf, size_t nLen, void* pAddlData)
{
	SAString* data = (SAString*)pAddlData;
	memcpy(pBuf, (const void*)(*data), nLen);
	ePieceType = SA_LastPiece;
	return nLen;
}

void IntoStringReader(
	SAPieceType_t ePieceType,
	void* pBuf,
	size_t nLen,
	size_t nBlobSize,
	void* pAddlData)
{
	SAString* data = (SAString*)pAddlData;
	size_t oldLen = data->GetBinaryLength();
	memcpy((char*)data->GetBinaryBuffer(oldLen + nLen) + oldLen, pBuf, nLen);
	data->ReleaseBinaryBuffer(oldLen + nLen);
}

