#pragma once
#pragma warning(disable : 4996)
#include <fstream>
#include "In.h"
#include "Parm.h"
#include "LT.h"
#include "Error.h"
#include "IT.h"
namespace Log
{
	struct LOG
	{
		wchar_t logfile[PARM_MAX_SIZE];
		std::wofstream* stream;
	};
	void WriteLT_ALL(LT::LexTable lt, LOG log);
	void WriteIT_ALL(IT::IdTable it, LOG log);
    void WriteLT(LT::LexTable lt, LOG log, IT::IdTable it);
	static LOG INITLOG = { L"", NULL };
	LOG getlog(wchar_t logfile[]);
	void WriteLine(LOG log, const char* c, ...);
	//void WriteLine(LOG log, const wchar_t* c, ...);
	void WriteLog(LOG log);
	void WriteParm(LOG log, Parm::PARM parm);
	void WriteIn(LOG log, In::IN in);
	void WriteError(LOG log, Error::ERROR error);
	//void WritetoLogFST(Log::LOG log, In::IN in);
	void WriteText(Log::LOG log, In::IN in);
	void Close(LOG log);
}
