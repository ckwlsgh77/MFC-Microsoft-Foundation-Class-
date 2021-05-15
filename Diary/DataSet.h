#pragma once
#include "atldbcli.h"

typedef CCommand<CDynamicStringAccessorW, CRowset> DbCommand;
class CDataSet
{
public:
	CDataSet();
	~CDataSet();
	CSession m_dbSession;
	bool m_bOpenSession;
	bool Open();
	bool Query(CString strQuery, DbCommand* pDbCommand);
};

