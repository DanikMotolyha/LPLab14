#pragma once
#include "IT.h"
#define LEXEMA_FIXSIZE 1			// ������������� ������ �������
#define LT_MAXSIZE 4096				// ������������ ���������� ����� � ������� ������
#define	LT_TI_NULLIDX 0xffffffff	// ��� �������� ������� ���������������
//#define LEX_INTEGER 't'				// ������� ��� integer
//#define LEX_STRING 't'				// ������� ��� string
//#define	LEX_ID 'i'					// ������� ��� ��������������
//#define LEX_LITERAL 'l'				// ������� ��� ��������
//#define	LEX_FUNCTION 'f'			// ������� ��� function
//#define LEX_DECLARE 'd'				// ������� ��� declare
//#define LEX_RETURN 'r'				// ������� ��� return
//#define LEX_PRINT 'p'				// ������� ��� print
//#define LEX_SEMICOLON ';'			// ������� ��� ;
//#define LEX_COMMA ','				// ������� ��� ,
//#define LEX_LEFTBRACE '{'			// ������� ��� {
//#define LEX_BRACELET '}'			// ������� ��� }
//#define LEX_LEFTTHESIS '('			// ������� ��� (
//#define LEX_RIGHTHESIS ')'			// ������� ��� )
//#define LEX_PLUS 'v'				// ������� ��� +
//#define LEX_MINUS 'v'				// ������� ��� -
//#define LEX_STAR 'v'				// ������� ��� *
//#define LEX_DIRSLASH 'v'			// ������� ��� /

namespace LT			// ������� ������
{
	struct Entry		// ������ ������� ������
	{
		char lexema;	// �������
		int sn;		// ����� ������ � �������� ������
		int idxTI;	// ������ � ������� ��������������� ��� LT_LI_NULLIDX
	};

	struct LexTable			// ��������� ������� ������
	{
		int size;			// ������� ������ ������� ������ 
		Entry* table;		// ������ ����� ������� ������
	};

	LexTable Create();// ������� ������� ������
	void Add(		// �������� ������ � ������� ������
		LexTable& lextable,			// ��������� ������� ������
		Entry entry);				// ������ ������� ������
	Entry GetEntry(						// �������� ������ ������� ������
		LexTable& lextable,				// ��������� ������� ������
		int n							// ����� ���������� ������
	);

	void table(In::IN in, LT::LexTable *lt, IT::IdTable *it);
	void Delete(LexTable& lextable);			// ������� ������� ������

}