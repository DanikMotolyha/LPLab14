#include "Parm.h"
#include "Error.h"
#include <iostream>
#include <locale>
#include <cwchar>

using namespace std;
namespace Parm
{

	PARM getparm(int argc, wchar_t* agrv[])
	{
		bool in = 0, out = 0, log = 0;
		wchar_t ini[PARM_MAX_SIZE] = L"";
		PARM e;
		if (argc == 1) throw ERROR_THROW(100);
		for (int i = 1; i < argc; ++i)
		{
			*agrv = agrv[i];
			if (wcslen(*agrv) > ERROR_MAXSIZE_MESSAGE) throw ERROR_THROW(104)
				int size = wcslen(*agrv);

			if (wcsstr(*agrv, PARM_IN))
			{
				in = true;
				//wchar_t *a = wcsstr(*agrv, (wchar_t*)"d");
				wchar_t *a = *agrv + (wchar_t)4;
				//wcout << a << endl;
				wcsncpy_s(e.in, a, wcslen(a));
				wcsncpy_s(ini, a, wcslen(a));
			}
			if (wcsstr(*agrv, PARM_OUT))
			{
				out = true;
				//wchar_t *a = wcsstr(*agrv, (wchar_t*)"d");
				wchar_t *a = *agrv + (wchar_t)5;
				wcsncpy_s(e.out, a, wcslen(a));
			}
			if (wcsstr(*agrv, PARM_LOG))
			{
				log = true;
				//wchar_t *a = wcsstr(*agrv, (wchar_t*)"d");
				wchar_t *a = *agrv + (wchar_t)5;
				wcsncpy_s(e.log, a, wcslen(a));
			}

		}
		if (!in) throw ERROR_THROW(100);
		if (!out) {
			wcsncpy_s(e.out, ini, wcslen(ini));
		}
		wcsncat_s(e.out, L".out", 4);

		if (!log) {
			wcsncpy_s(e.log, ini, wcslen(ini));
			wcsncat_s(e.log, L".log", 4);
		}
		return e;

	}
}
