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
// �������� ������ :
/*
	1 ������ - ���������� ������� ��� ��
	2 ������ - ���������� ������� ��� ��
	3 ������ - ���������� ������� ��������������
	4 ������ - �� ���������� �������
	5 ������ - ���������� ������� ��������(������)
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
		int INDEX = 1; char INDX[3];// ������ ������
		IT::IDDATATYPE iddatatype;
		IT::IDTYPE idtype;
		FST::FST *a = FST::automat();
		LT::Entry strokaLT; int index = 0;
		IT::Entry strokaIT;
		char Position1[7];		strcpy_s(Position1, " ");		// ��� ����� ������� ��������� --->   };
		char Position2[7];		strcpy_s(Position2, " ");		// ��� ����� ������� ��������� --->   �������� ������� ������ ������ �������
		
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
					//FLAG = false; // ������ 17*00 18,9 ������� ������������ ������
					for (int i = 0; i <= 16; i++) 
					{
						a[i].string = (char*)buf.c_str();
						if (FST::execute(a[i]))
						{
							lex_recognized = true;
							//---------- �������� �� string/integer ������ ��������� //
							if (i == 0)
								if (!strcmp("string", a[i].string)) iddatatype = IT::STR;
								else iddatatype = IT::INT;
							if (i == 5) { strcpy_s(Position1, "main"); }
							//---------- �������� ������ �� ������� ---------------//
							if (i == 6 && lt->size > 1)							   //
								if (lt->table[lt->size - 1].lexema == '}')								   //
								{																		   //
									strcpy_s(Position1, " ");		// ����� ������� ��������� ������ !!!! //
									strcpy_s(Position2, " ");
								}																		   //   
							//---------- �������������� . -------------------------//
							if (i == 14)
							{
								// --- ������  --- ���������� ������� ��������

								if (buf.length() > 6)
									throw ERROR_THROW_IN(107, k, -1);

								//----------
								if (lt->size > 1 &&		 // ������� ������� ��� ������ � ��������� �������
														 // ��� �������� ���������� � ���� �������
									lt->table[lt->size-1].lexema == 'f') 
									
								{
									strokaIT.iddatatype = iddatatype;
									strokaIT.idxfirstLE = (*lt).size;
									strcpy_s(strokaIT.id, a[i].string);
									strokaIT.idtype = IT::F;

									if (!strcmp(Position1, " "))
										strcpy_s(Position1, strokaIT.id); // �������� ���� ������ ��� �������� ��������!!!
									else strcpy_s(Position2, strokaIT.id);		
									// ������ ����� �������� ��� �������������� ������� ������

									strokaLT.idxTI = it->size;
									IT::Add(*it, strokaIT);
								}
								else 
									if (lt->size > 1 && // ��� ���������� declare integer/string 
									// � � ��� ���������� (���������)
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
									if (lt->size > 1 && // ��� ���������� ���������� �������
									lt->table[lt->size-1].lexema == 't')
									 
									{
										strokaIT.iddatatype = iddatatype;
										strokaIT.idxfirstLE = (*lt).size;
										//strcpy_s(strokaIT.id, Position[1]);//---------------
										
										
										if (strcmp(Position1, " ") && !strcmp(Position2, " ")) // pos1 != " " && pos2 == " "			
											// ��� �������� ��� � ��������� ������� �� ��� ��������
											// �� ���� ���� pos[1] != " " �� ��������� [1] ������� ����� ������
											strcpy_s(strokaIT.id, Position1); // �������� ���� ������ ��� �������� ��������!!!
										if (strcmp(Position1, " ") && strcmp(Position2, " ")) strcpy_s(strokaIT.id, Position2);
										// pos1 != " " && pos2 != " "
										//	 string function fs (string a, string b)
										//	{
										//		declare  string function substr(string a,integer n);
										//		declare integer function strlen(string k);
										//  }
										// ������ ����� �������� ��� �������������� ������� ������
										
										strcat_s(strokaIT.id, a[i].string);

										strokaIT.idtype = IT::P;
										strokaLT.idxTI = it->size;
										IT::Add(*it, strokaIT);
									}
								else 
									if (lt->size > 1 && lt->table[lt->size - 1].lexema != 't'
									// ��� ���������� ����������, ������ ������ �� ���������
									&& lt->table[lt->size - 1].lexema != 'f')
								    {
									if (strcmp(Position1, " "))				// ��� �������� ��� � ��������� ������� �� ��� ��������
											// �� ���� ���� pos[1] != " " �� ��������� [1] ������� ����� ������
										strcpy_s(strokaIT.id, Position1); // �������� ���� ������ ��� �������� ��������!!!
										else strcpy_s(strokaIT.id, Position2);
										strokaLT.idxTI = it->size;
										// ������ ����� �������� ��� �������������� ������� ������
										if (IsId(*it, a[i].string) < 0)					// �������� �� ��� �������
											// �� ���� ���� �� ������ ����� ������� �� ��� ����������
											// � ���� ������� ������� � ���� ������� 
											// ����� ��� ������� � ���� ��������� ������
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
							//------------ ������� 15 - ����� 16 - ������ ----------
							if (15 == i)			// 15 16 LEXEMS
							{													
								strokaIT.idxfirstLE = (*lt).size;				
								strokaIT.idtype = IT::L;						
																				
								strcpy_s(strokaIT.id, "LEX");
								auto sTR = std::to_string(INDEX); // ��� �������� � string ��� ��� itoa 
								// ������ �� ����� �������� . . .
								// � ����� �������� ������ � char* . . .
								strcat_s(strokaIT.id, (char*)sTR.c_str());	// ���������� ����� ������ . . .
								//
								INDEX++;
								
								strokaIT.iddatatype = IT::INT;
								strokaIT.value.vint = atoi(a[i].string);
								// ������ � ���
								strokaLT.idxTI = it->size;
								IT::Add(*it, strokaIT);
							}
							if (16 == i)
							{
								strokaIT.idxfirstLE = (*lt).size;
								strokaIT.idtype = IT::L;
								strokaIT.iddatatype = IT::STR;
								strcpy_s(strokaIT.id, "LEX");

								auto sTR = std::to_string(INDEX); // ������� � string ��� ��� itoa 
								// ������ �� ����� �������� . . .
								// � ����� �������� ������ � char* . . .
								strcat_s(strokaIT.id, (char*)sTR.c_str());	// ���������� ����� ������ . . .
								
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
							//-------- ��� +-*/  ------------------------------------
							else if (i == 13)
							{
								strokaIT.idxfirstLE = (*lt).size;
								strcpy_s(strokaIT.id, a[i].string);
								strokaLT.idxTI = it->size;
								IT::Add(*it, strokaIT);
							}

							// ��� ��������������� �.�. ���� ���������� ��
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
				//else { if (!FLAG) ++k; FLAG = true; }  //	������ 17*00 18,9 ������� ������������ ������
				else ++k;
				strokaIT.value.vint = TI_INT_DEFAULT;
				strokaIT.value.vstr->str = TI_STR_DEFAULT;
				buf = "";
			}
			if (in.text[i] == '\'')						// ��� ������ �������� � string
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
