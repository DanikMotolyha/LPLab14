#include "FST.h"
FST::RELATION::RELATION(char с, short nn)	// ребро:символ -> вершима графа переходов  ј
{
	symbol = с;			// символ перехода
	nnode = nn;			// номер смежной вершины
};
FST::NODE::NODE()			// по умолчанию  // вершина графа переходов
{
	n_relation = 0;
	RELATION *relations = NULL;
}
FST::FST * FST::automat()
{
	FST *AT = new FST[16];						
	
	FST *a = new FST(nullptr, 8,
		NODE(2, RELATION('i', 1), RELATION('s', 1)),
		NODE(2, RELATION('n', 2), RELATION('t', 2)),
		NODE(2, RELATION('t', 3), RELATION('r', 3)),
		NODE(2, RELATION('e', 4), RELATION('i', 4)),
		NODE(2, RELATION('g', 5), RELATION('n', 5)),
		NODE(2, RELATION('e', 6), RELATION('g', 7)),
		NODE(1, RELATION('r', 7)),
		NODE());
	AT[0] = *a; delete a;
	FST *b = new FST(nullptr, 9,
		NODE(1, RELATION('f', 1)),
		NODE(1, RELATION('u', 2)),
		NODE(1, RELATION('n', 3)),
		NODE(1, RELATION('c', 4)),
		NODE(1, RELATION('t', 5)),
		NODE(1, RELATION('i', 6)),
		NODE(1, RELATION('o', 7)),
		NODE(1, RELATION('n', 8)),
		NODE());
	AT[1] = *b; delete b;
	FST *c = new FST(nullptr, 8,
		NODE(1, RELATION('d', 1)),
		NODE(1, RELATION('e', 2)),
		NODE(1, RELATION('c', 3)),
		NODE(1, RELATION('l', 4)),
		NODE(1, RELATION('a', 5)),
		NODE(1, RELATION('r', 6)),
		NODE(1, RELATION('e', 7)),
		NODE());
	AT[2] = *c; delete c;
	FST *e = new FST(nullptr, 7,
		NODE(1, RELATION('r', 1)),
		NODE(1, RELATION('e', 2)),
		NODE(1, RELATION('t', 3)),
		NODE(1, RELATION('u', 4)),
		NODE(1, RELATION('r', 5)),
		NODE(1, RELATION('n', 6)),
		NODE());
	AT[3] = *e; delete e;
	FST *q = new FST(nullptr, 6,
		NODE(1, RELATION('p', 1)),
		NODE(1, RELATION('r', 2)),
		NODE(1, RELATION('i', 3)),
		NODE(1, RELATION('n', 4)),
		NODE(1, RELATION('t', 5)),
		NODE());
	AT[4] = *q; delete q;
	FST *r = new FST(nullptr, 5,
		NODE(1, RELATION('m', 1)),
		NODE(1, RELATION('a', 2)),
		NODE(1, RELATION('i', 3)),
		NODE(1, RELATION('n', 4)),
		NODE());
	AT[5] = *r; delete r;
	FST *z = new FST(nullptr, 2,
		NODE(1, RELATION(';', 1)),
		NODE());
	AT[6] = *z; delete z;
	FST *w = new FST(nullptr, 2,
		NODE(1, RELATION(',', 1)),
		NODE());
	AT[7] = *w; delete w;
	FST *t = new FST(nullptr, 2,
		NODE(1, RELATION('{', 1)),
		NODE());
	AT[8] = *t; delete t;
	FST *qw = new FST(nullptr, 2,
		NODE(1, RELATION('}', 1)),
		NODE());
	AT[9] = *qw; delete qw;
	FST *z1 = new FST(nullptr, 2,
		NODE(1, RELATION('(', 1)),
		NODE());
	AT[10] = *z1; delete z1;
	FST *w1 = new FST(nullptr, 2,
		NODE(1, RELATION(')', 1)),
		NODE());
	AT[11] = *w1; delete w1;
	FST *t2 = new FST(nullptr, 2,
		NODE(1, RELATION('=', 1)),
		NODE());
	AT[12] = *t2; delete t2;
	FST *q2w = new FST(nullptr, 2,
		NODE(4, RELATION('+', 1),
			RELATION('*', 1),
			RELATION('/', 1),
			RELATION('-', 1)),
		NODE());
	AT[13] = *q2w; delete q2w;
	FST *a1 = new FST(nullptr, 1,		// идентификаторы
		NODE(26, RELATION('a', 0), RELATION('b', 0),
			RELATION('c', 0), RELATION('d', 0),
			RELATION('e', 0), RELATION('f', 0),
			RELATION('g', 0), RELATION('h', 0),
			RELATION('i', 0), RELATION('j', 0),
			RELATION('k', 0), RELATION('l', 0),
			RELATION('m', 0), RELATION('n', 0),
			RELATION('o', 0), RELATION('p', 0),
			RELATION('q', 0), RELATION('r', 0),
			RELATION('s', 0), RELATION('t', 0),
			RELATION('u', 0), RELATION('v', 0),
			RELATION('w', 0), RELATION('x', 0),
			RELATION('y', 0), RELATION('z', 0)));
	AT[14] = *a1; delete a1;
	FST *a12 = new FST(nullptr, 1,		// литералы
		NODE(10,
			RELATION('1', 0), RELATION('4', 0),
			RELATION('2', 0), RELATION('5', 0),
			RELATION('3', 0), RELATION('6', 0),
			RELATION('7', 0), RELATION('7', 0),
			RELATION('9', 0), RELATION('0', 0)));
	AT[15] = *a12; delete a12;
	FST *a13 = new FST(nullptr, 3,
		NODE(1, 
			RELATION('\'', 1)),
		NODE(71,
			RELATION(' ', 1),
			RELATION('a', 1), RELATION('b', 1),	RELATION('c', 1), RELATION('d', 1), RELATION('e', 1), RELATION('f', 1),
			RELATION('g', 1), RELATION('h', 1),	RELATION('i', 1), RELATION('j', 1), RELATION('k', 1), RELATION('l', 1),
			RELATION('m', 1), RELATION('n', 1), RELATION('o', 1), RELATION('p', 1), RELATION('q', 1), RELATION('r', 1),
			RELATION('s', 1), RELATION('t', 1), RELATION('u', 1), RELATION('v', 1), RELATION('w', 1), RELATION('x', 1),
			RELATION('y', 1), RELATION('z', 1), 
			
			RELATION('1', 1), RELATION('2', 1), RELATION('3', 1), RELATION('4', 1),	RELATION('5', 1),
			RELATION('6', 1), RELATION('7', 1), RELATION('8', 1), RELATION('9', 1), RELATION('0', 1),
			
			RELATION('а', 1), RELATION('б', 1), RELATION('в', 1), RELATION('г', 1), RELATION('д', 1), RELATION('е', 1),
			RELATION('Є', 1), RELATION('ж', 1),	RELATION('з', 1), RELATION('и', 1), RELATION('й', 1), RELATION('к', 1),
			RELATION('л', 1), RELATION('м', 1),	RELATION('н', 1), RELATION('о', 1), RELATION('п', 1), RELATION('р', 1),
			RELATION('с', 1), RELATION('т', 1),	RELATION('у', 1), RELATION('ф', 1), RELATION('х', 1), RELATION('ц', 1),
			RELATION('ч', 1), RELATION('ш', 1), RELATION('щ', 1), RELATION('ь', 1), RELATION('ы', 1), RELATION('ъ', 1),
			RELATION('э', 1), RELATION('ю', 1),	RELATION('€', 1),
			
			RELATION('\'', 2)),
		NODE());
	AT[16] = *a13; delete a13;
	return AT;
}
FST::NODE::NODE(short n, RELATION rel, ...) // с параметрами
{
	n_relation = n;
	RELATION *p = &rel;
	relations = new RELATION[n];
	for (short i = 0; i < n; i++) relations[i] = p[i];
}
FST::FST::FST()
{
	string = nullptr;
}
FST::FST::FST(char* s, short ns, NODE n, ...)
{
	string = s;																				// цепочка (строка, завершаетс€ 0x00)
	nstates = ns;																			// количество состо€ний  ј	
	nodes = new NODE[ns];																	// краф переходов
	NODE *p = &n;																			// граф переходов: [0] - начальное состо€ние, [nstate-1] - конечне
	for (int k = 0; k < ns; k++) nodes[k] = p[k];
	rstates = new short[nstates];															// возможные состо€ни€ на определенной позиции
	memset(rstates, 0xff, sizeof(short)*nstates);
	rstates[0] = 0;
	position = -1;																			// начало позиции ( тк в execute будет инкремент с 0 начинать)
}
bool step(FST::FST &fst, short* &rstates)													//один шаг автомата
{
	bool rc = false;
	std::swap(rstates, fst.rstates);														// смена массивов	в первой итерации -1 на 0
	for (short i = 0; i < fst.nstates; i++)													// проход всех состо€ний 
	{
		if (rstates[i] == fst.position)														// проверка возможного состо€ни€ с позицией в цепочке
			for (short j = 0; j < fst.nodes[i].n_relation; j++)								// тут уже идем по состо€нию -> по ребрам
			{																				// по ребрам графа переходов
				if (fst.nodes[i].relations[j].symbol == fst.string[fst.position])			// проверка символа ребра с символом цепочки
				{
					fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;		// грубоговор€ флаг дл€ следующего шага по позиции 
																							//массив флагов дл€ состо€ний
					rc = true;
				};
			};
	};
	return rc;
};
bool FST::execute(FST &fst)						
{												
	short *rstates = new short[fst.nstates];	
	memset(rstates, 0xff, sizeof(short)*fst.nstates);
	//----------------------------------------------------
	fst.rstates = new short[fst.nstates];															// возможные состо€ни€ на определенной позиции
	memset(fst.rstates, 0xff, sizeof(short)*fst.nstates);
	fst.rstates[0] = 0;
	fst.position = -1;
	//----------------------------------------------------
	short lstring = strlen(fst.string);						// по длине цепочки (кол символов)
	bool rc = true;
	for (short i = 0; i < lstring && rc; i++)
	{
		fst.position++;				// продвинули позицию
		rc = step(fst, rstates);	// один шаг автомата
	};
	delete[] rstates;
	//delete[] fst.rstates;
	//------------------------------------------------------
	//------------------------------------------------------
	return(rc ? (fst.rstates[fst.nstates - 1] == lstring) : rc);
}
