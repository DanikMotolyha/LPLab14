#include "Parm.h"
#include "In.h"
#include "LT.h"
#include "IT.h"
#include "Error.h"
#include "FST.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;
// написаны ошибки :
/*
	1 ошибка - превышение размера для ЛТ
	2 ошибка - превышение размера для ТИ
	3 ошибка - превышение размера идентификатора
	4 ошибка - не распознана лексема
	5 ошибка - превышение размера литерала(строка)
*/
namespace LT
{
	char mass[17] = {'t','f','d','r','p','m',';',',','{','}','(',')','=','v','i','l','l'};
	LexTable Create()
	{
		LexTable lt;
		lt.size = 0;
		lt.table = new Entry[LT_MAXSIZE];
		return lt;
	}
	void Add(LexTable& lt, Entry entry)
	{
		if(lt.size+1 > LT_MAXSIZE) throw ERROR_THROW(106);
		lt.table[lt.size++] = entry;
	}
	void table(In::IN in, LT::LexTable *lt, IT::IdTable *it)
	{
		int INDEX = 1; char INDX[3];// ИНДЕКС ЛЕКСЕМ
		IT::IDDATATYPE iddatatype;
		IT::IDTYPE idtype;
		FST::FST *a = FST::automat();
		LT::Entry strokaLT; int index = 0;
		IT::Entry strokaIT;
		char Position1[7];		strcpy_s(Position1, " ");		// для конца области видимости --->   };
		char Position2[7];		strcpy_s(Position2, " ");		// для конца области видимости --->   параметр функции внутри другой функции
		
		int k = 1;
		bool flag_separate = false, FLAG = false, lex_recognized = false;
		int i = 0; string buf;
		if (in.text[0] == ' ') i++;
		while (in.text[i] != '\0')
		{
			if (in.text[i] != ' ' || flag_separate)	buf += in.text[i];
			else          
			{
				if (buf != (char*)"|")
				{
					//FLAG = false; // правка 17*00 18,9 попытка ввостановить строки
					for (int i = 0; i <= 16; i++) 
					{
						a[i].string = (char*)buf.c_str();
						if (FST::execute(a[i]))
						{
							lex_recognized = true;
							//---------- проверка на string/integer первое изменение //
							if (i == 0)
								if (!strcmp("string", a[i].string)) iddatatype = IT::STR;
								else iddatatype = IT::INT;
							if (i == 5) { strcpy_s(Position1, "main"); }
							//---------- проверка выхода из функции ---------------//
							if (i == 6 && lt->size > 1)							   //
								if (lt->table[lt->size - 1].lexema == '}')								   //
								{																		   //
									strcpy_s(Position1, " ");		// конец области видимости функии !!!! //
									strcpy_s(Position2, " ");
								}																		   //   
							//---------- идентификаторы . -------------------------//
							if (i == 14)
							{
								// --- ошибка  --- превышение размера индентиф

								if (buf.length() > 6)
									throw ERROR_THROW_IN(107, k, -1);

								//----------
								if (lt->size > 1 &&		 // находим идентиф под функию и добавляем префикс
														 // для названия переменных в этой функции
									lt->table[lt->size-1].lexema == 'f') 
									
								{
									strokaIT.iddatatype = iddatatype;
									strokaIT.idxfirstLE = (*lt).size;
									strcpy_s(strokaIT.id, a[i].string);
									strokaIT.idtype = IT::F;

									if (!strcmp(Position1, " "))
										strcpy_s(Position1, strokaIT.id); // копируем назв фунцию для префикса основную!!!
									else strcpy_s(Position2, strokaIT.id);		
									// теперь копия префикса для второстепенной функции внутри

									strokaLT.idxTI = it->size;
									IT::Add(*it, strokaIT);
								}
								else 
									if (lt->size > 1 && // для переменных declare integer/string 
									// т е это переменные (обявление)
										lt->table[lt->size - 2].lexema == 'd' &&
										lt->table[lt->size - 1].lexema == 't')
									 
									{
										strokaIT.iddatatype = iddatatype;
										strokaIT.idxfirstLE = (*lt).size;
										strokaIT.idtype = IT::V;

										strcpy_s(strokaIT.id, Position1);
										strcat_s(strokaIT.id, a[i].string);

										if (iddatatype == 1)
											strokaIT.value.vint = TI_INT_DEFAULT;
										else
										{
											strokaIT.value.vstr[1].str = TI_STR_DEFAULT;
											strokaIT.value.vstr[0].len = 0;
										}

										strokaLT.idxTI = it->size;
										IT::Add(*it, strokaIT);
									}
								else 
									if (lt->size > 1 && // для переменных параметров функции
									lt->table[lt->size-1].lexema == 't')
									 
									{
										strokaIT.iddatatype = iddatatype;
										strokaIT.idxfirstLE = (*lt).size;
										//strcpy_s(strokaIT.id, Position[1]);//---------------
										
										
										if (strcmp(Position1, " ") && !strcmp(Position2, " ")) // pos1 != " " && pos2 == " "			
											// тут наоборот чем с префиксом функции тк тут параметр
											// то есть если pos[1] != " " то добавляем [1] префикс иначе второй
											strcpy_s(strokaIT.id, Position1); // копируем назв фунцию для префикса основную!!!
										if (strcmp(Position1, " ") && strcmp(Position2, " ")) strcpy_s(strokaIT.id, Position2);
										// pos1 != " " && pos2 != " "
										//	 string function fs (string a, string b)
										//	{
										//		declare  string function substr(string a,integer n);
										//		declare integer function strlen(string k);
										//  }
										// теперь копия префикса для второстепенной функции внутри
										
										strcat_s(strokaIT.id, a[i].string);

										strokaIT.idtype = IT::P;
										strokaLT.idxTI = it->size;
										IT::Add(*it, strokaIT);
									}
								else 
									if (lt->size > 1 && lt->table[lt->size - 1].lexema != 't'
									// для безымянных переменных, создаю ссылки на исходники
									&& lt->table[lt->size - 1].lexema != 'f')
								    {
									if (strcmp(Position1, " "))				// тут наоборот чем с префиксом функции тк тут параметр
											// то есть если pos[1] != " " то добавляем [1] префикс иначе второй
										strcpy_s(strokaIT.id, Position1); // копируем назв фунцию для префикса основную!!!
										else strcpy_s(strokaIT.id, Position2);
										strokaLT.idxTI = it->size;
										// теперь копия префикса для второстепенной функции внутри
										if (IsId(*it, a[i].string) < 0)					// проверка на имя функции
											// то есть если не найдет имени функции то это переменная
											// и надо ставить префикс в виде функции 
											// иначе это функция и надо создавать ссылку
										{
										strcat_s(strokaIT.id, a[i].string);
										if(IsId(*it, strokaIT.id) == -1) throw ERROR_THROW_IN(2, k, -1);
										IT::Entry *ind = &(it->table[IsId(*it, strokaIT.id)]);
										IT::Add(*it, *ind);
										}
										else
										{	IT::Entry *ind = &(it->table[IsId(*it, a[i].string)]);
											IT::Add(*it, *ind);}										
									}	
							}
							//------------ ЛЕКСЕМЫ 15 - цифры 16 - строки ----------
							if (15 == i)			// 15 16 LEXEMS
							{													
								strokaIT.idxfirstLE = (*lt).size;				
								strokaIT.idtype = IT::L;						
																				
								strcpy_s(strokaIT.id, "LEX");
								auto sTR = std::to_string(INDEX); // ТУТ ПЕРЕВОЖУ В string ТАК КАК itoa 
								// просто не хочет работать . . .
								// а потом перевожу стринг в char* . . .
								strcat_s(strokaIT.id, (char*)sTR.c_str());	// добавление счета лексем . . .
								//
								INDEX++;
								
								strokaIT.iddatatype = IT::INT;
								strokaIT.value.vint = atoi(a[i].string);
								// преобр в инт
								strokaLT.idxTI = it->size;
								IT::Add(*it, strokaIT);
							}
							if (16 == i)
							{
								strokaIT.idxfirstLE = (*lt).size;
								strokaIT.idtype = IT::L;
								strokaIT.iddatatype = IT::STR;
								strcpy_s(strokaIT.id, "LEX");

								auto sTR = std::to_string(INDEX); // перевод В string ТАК КАК itoa 
								// просто не хочет работать . . .
								// а потом перевожу стринг в char* . . .
								strcat_s(strokaIT.id, (char*)sTR.c_str());	// добавление счета лексем . . .
								
								INDEX++;
								for (int d = 1, j = 0; a[i].string[d] != '\0' ; d++, j++)
								{
									if(d > TI_STR_MAXSIZE) throw ERROR_THROW_IN(109, k, -1);
									if (a[i].string[d] == '\'')
									strokaIT.value.vstr[0].len = d-1;
									strokaIT.value.vstr[d].str = a[i].string[d];
								}
								strokaLT.idxTI = it->size;
								IT::Add(*it, strokaIT);
							}
							//-------- для +-*/  ------------------------------------
							else if (i == 13)
							{
								strokaIT.idxfirstLE = (*lt).size;
								strcpy_s(strokaIT.id, a[i].string);
								strokaLT.idxTI = it->size;
								IT::Add(*it, strokaIT);
							}

							// без идентификаторов т.е. само заполнение ТЛ
							if(i < 13) 
								strokaLT.idxTI = LT_TI_NULLIDX;
							strokaLT.lexema = mass[i];
							strokaLT.sn = k;
							LT::Add(*lt, strokaLT);
							delete[] a[i].rstates;
							break;
						}
						else delete[] a[i].rstates;
					}
					if (!lex_recognized) throw ERROR_THROW_IN(108, k, -1);
					lex_recognized = false;

				}
				//else { if (!FLAG) ++k; FLAG = true; }  //	правка 17*00 18,9 попытка ввостановить строки
				else ++k;
				strokaIT.value.vint = TI_INT_DEFAULT;
				strokaIT.value.vstr->str = TI_STR_DEFAULT;
				buf = "";
			}
			if (in.text[i] == '\'')						// для чтения пробелов в string
			{
				if (index % 2 == 0)		flag_separate = true;
				else					flag_separate = false;
				index++;
			}
			i++;
		}
	}
	
	
	Entry GetEntry(LexTable& lextable,int n)
	{
		return lextable.table[n];
	}
	void Delete(LexTable& lextable) 
	{
			delete[] lextable.table;
	}
}
