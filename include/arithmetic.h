// объявление функций и классов для вычисления арифметических выражений

#pragma once

#include "stack.h"
#include <iostream>
#include <string>
using namespace std;


enum TermTypes {OPERATOR, LBRACKET, RBRACKET, NUMBER, VARIABLE, UNKNOWN };

struct Term
{
	TermTypes type;
	string str;

	Term (const Term& s) {type=s.type; str=s.str;};
	Term (const char s){str=s;};
	Term(string s = "", TermTypes t = OPERATOR) {str = s; type = t;}   // для теста can_devide_expression

	bool operator!=(const Term& lop) const
	{
		bool res;
		if (lop.str != str || lop.type != type)
			return res = true;
		else 
			return res=false;
	}

	bool operator==(const Term& lop) const
	{
		return !(operator!=(lop));
	}

};

class arithmetic
{
private:
	string vyr;
	Term* pTerm;                                           // Массив лексем
	int nTerm;                                             // Кол-во лексем
	Term* a;                                               // Массив лексем в польской записи
	int nP;                                                // Кол-во лексем в польской записи

	void delspace();                                       // Удаление пробелов
	void devide();                                         // Рабор на лексемы
	bool prioritet(Term one, Term two) const;   
	

public:
	arithmetic(const string anyvyr);		              //Конструктор 
	arithmetic& operator=(const arithmetic& a);	          //Перегрузка =
	~arithmetic();                   			          //Деструктор
	bool check_symbol() const;
	bool check_operations() const;
	bool check_brackets() const;
	bool nomistakes();		                              //Проверка выражения на ошибки 
	double calculation();    					          //Вычисление результата	
	int OPN();                                            //Перевод в Польскую запись
	void print_OPN(); 
	Stack <string> vars;

	// для тестов 
	Term* getTerms() const {return  pTerm;};
	int getnTerm() const {return nTerm;};	

	Term* getPolishTerms() const {return  a;};
	int getnPolishTerms() const {return nP;};	
};
	