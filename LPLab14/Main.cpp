#include <iostream>
#include "Error.h"  // ��������� ������
#include "In.h"		// ���� ��������� �����
#include "Log.h"	// ������ � ����������
#include "Parm.h"	// ��������� ����������
#include "FST.h"
#include "LT.h"
#include "IT.h"


using namespace std;
int wmain(int agrc, wchar_t* agrv[])
{
	setlocale(LC_ALL, "RUSSIAN");
	Log::LOG log = Log::INITLOG;
	try
	{
		Parm::PARM parm = Parm::getparm(agrc, agrv);
		log = Log::getlog(parm.log);
		Log::WriteLine(log, "�����: ", "��� ������ ", "");
		WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in);
		Log::WriteIn(log, in);
		Log::WriteText(log, in);
		LT::LexTable lt = LT::Create(); 
		LT::LexTable *lt_s = &lt;
		IT::IdTable it = IT::Create();
		IT::IdTable *it_s = &it;
		LT::table(in, lt_s, it_s);
		Log::WriteLT(lt, log, it);

		Log::WriteLT_ALL(lt, log);
		Log::WriteIT_ALL(it, log);


		//-----������ LEX ��� ������� 
		In::Delete(in);
		LT::Delete(lt);
		IT::Delete(it);
		Log::Close(log);
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	}
	cout << "End of program, press F" << endl;// system("pause");
}
