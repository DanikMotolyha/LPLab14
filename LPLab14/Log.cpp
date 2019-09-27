#include "Log.h"
#include "Error.h"
#include "Parm.h"
#include "FST.h"
#include "LT.h"
#include "IT.h"
#include <ctime>
#include <cstdlib>
#include <cwchar>
#include <iomanip>
using namespace std;
namespace Log
{
	LOG getlog(wchar_t logfile[])
	{
		LOG lg;
		lg.stream = new std::wofstream(logfile);
		if (!lg.stream)
		{
			throw ERROR_THROW(112);
		}
		else
		{
			wcscpy_s(lg.logfile, logfile);
			return lg;
		}
	}
	void WriteLine(LOG log, const char* c, ...)
	{
		const char **ptr = &c;
		int k = 0;
		while (ptr[k] != "")
		{
			*log.stream << ptr[k];
			k++;
		}
	}
	//void WriteLine(LOG log, const wchar_t* c, ...)
	//{
	//	char p[100];
	//	const wchar_t **ptr = &c;
	//	int k = 0;
	//	while (ptr[k] != L"")
	//	{
	//		wcstombs(p, ptr[k], 50);
	//		*log.stream << p;
	//		k++;
	//	}
	//}
	void WriteLog(LOG log)
	{
		*log.stream << "\n---- Протокол ----\n---- Дата: ";
		time_t rawtime;
		struct tm * timeinfo;
		char buffer[80];                              // строка, в которой будет храниться текущее время
		time(&rawtime);                               // текущая дата в секундах
		timeinfo = localtime(&rawtime);               // преобразование секунд в локальное время
		strftime(buffer, 20, "%x %X", timeinfo);      // преобразование даты в строку
		*log.stream << buffer;
		*log.stream << " ----\n";
	}
	void WriteParm(LOG log, Parm::PARM parm)
	{
		char *in = new char[IN_MAX_LEN_TEXT];
		char *out = new char[IN_MAX_LEN_TEXT];
		char *logg = new char[IN_MAX_LEN_TEXT];
		int x = wcstombs(in, parm.in, wcslen(parm.in));		in[x] = '\0';
		x = wcstombs(out, parm.out, wcslen(parm.out));		out[x] = '\0';
		x = wcstombs(logg, parm.log, wcslen(parm.log));		logg[x] = '\0';
		*log.stream << "------ Параметры ----------\n"
			<< "-in: " << in
			<< "\n-out: " << out
			<< "\n-log: " << logg << "\n";
		delete in;
		delete out;
		delete logg;
	}
	void WriteIn(LOG log, In::IN in)
	{
		*log.stream << "---- Исходные данные ----\n"
			<< "Количество символов: " << in.size
			<< "\nПроигнорировано: " << in.ignor
			<< "\nКоличество строк: " << in.lines << "\n\n";
	}
	// new command for write redact text
	void WriteText(LOG log, In::IN in)
	{
		*log.stream << "Первая фаза анализатора :" << '\n';
		int i = 0;
		while ((char)in.text[i] != '\0')
		{
			*log.stream << (wchar_t)in.text[i];
			i++;
		}
		*log.stream << '\n';
	}
	//**********************************
	void WriteLT(LT::LexTable lt, LOG log, IT::IdTable it)
	{
		// 18*9 надо поменять тк изменен был счетчик строк 
		// теперь должны быть пустые строки и он должен не игнорить их
		// размер взять из in где считало количество строк
		int stroka = 1, i = 0;
		bool str = true;
		*log.stream << "\n\nПротокол по работе анализатора ->\n\n";
		while(i != lt.size)
		{
				if (str)
				{
					if (stroka < 10)
						*log.stream << '0' << stroka << "   ";
					else *log.stream << stroka << "   ";
				}
			if (stroka == lt.table[i].sn)
			{
				str = false;
				if (lt.table[i].lexema == 'v')
				{
					*log.stream << it.table[lt.table[i].idxTI].id;
				}
				else	*log.stream << lt.table[i].lexema;
				i++;
			}
			else
			{
				stroka += 1;
				*log.stream << '\n'; 
				str = true;
			}
		}
	}
	void WriteLT_ALL(LT::LexTable lt, LOG log)
	{
		*log.stream << "\n\nПротокол по работе ТЛ - Полная ТЛ ->\n\n"
			<< "---+----------------------+-----------------+--------------------------+\n"
			<< " № | номер в табл идентиф |    лексема      |  номер в исходном коде   |\n"
			<< "---+----------------------+-----------------+--------------------------+\n";
		for (int i = 0; i < lt.size; i++)
		{
			*log.stream << setw(3) << i << '|' << setw(22) << lt.table[i].idxTI << '|' << setw(17) << lt.table[i].lexema
				<< '|' << setw(26) << lt.table[i].sn << '|' << endl;
			*log.stream << "---+----------------------+-----------------+--------------------------+\n";
		}
	}
	void WriteIT_ALL(IT::IdTable it, LOG log)
	{
		*log.stream << "\n\nПротокол по работе ТИ - Полная ТИ ->\n\n"
			<< "---+----------------------+-----------------+---------------+--------------------+---------------------+\n"
			<< " № | инд первой стр в ТЛ  |  идентификатор  |  тип данных   | тип идентификатора |      значение       |\n"
			<< "---+----------------------+-----------------+---------------+--------------------+---------------------+\n";
		for (int i = 0; i < it.size; i++)
		{
			*log.stream << setw(3) << i << "|" << setw(22) << it.table[i].idxfirstLE << '|' << setw(17) << it.table[i].id
				<< '|' << setw(15) << it.table[i].iddatatype << '|' << setw(20) << it.table[i].idtype << '|';
			/*if (it.table[i].idtype == 1, it.table[i].idtype == 3, it.table[i].idtype == 4) {*/
				if (it.table[i].iddatatype == 1)
				{
					*log.stream << setw(10) << it.table[i].value.vint;
				}
				else
				{
					for (int j = 0; j <= it.table[i].value.vstr[0].len; j++)
					{
						*log.stream << it.table[i].value.vstr[j].str;
					}
				}
			//}
			*log.stream << "\n---+----------------------+-----------------+---------------+--------------------+---------------------+\n";
		}
	}
	void WriteError(LOG log, Error::ERROR error)
	{
		*log.stream << "\nОшибка " << error.id << ": " << error.message;
		if(!error.inext.col == -1)
		*log.stream << ", строка: " << error.inext.line << ", позиция: " << error.inext.col;
			*log.stream << ", строка: " << error.inext.line;
	}
	void Close(LOG log)
	{
		log.stream->close();
	}
}
