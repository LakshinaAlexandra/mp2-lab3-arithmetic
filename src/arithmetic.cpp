// реализация функций и классов для вычисления арифметических выражений

#include "arithmetic.h"
using namespace std;
#include <string>
#include "cstdlib"
#include <iostream>

const string  symb = "/*+-().0123456789abcdefghijklmnopqrstuvwxyz";



arithmetic::arithmetic (const string anyvyr)
{
	vyr = anyvyr;
	delspace();
	pTerm = new Term[vyr.length()];
	nTerm = 0;
	devide();
	a = NULL;
}

arithmetic& arithmetic::operator=(const arithmetic& a)
{
	vyr = a.vyr;
	nTerm = a.nTerm;
	delete[] pTerm;
	pTerm = new Term[nTerm];
	for (int i = 0; i < nTerm; i++)
		pTerm[i] = a.pTerm[i];
	return *this;
}

arithmetic::~arithmetic()
{
	delete[] pTerm;
	if (a != NULL)
		delete [] a;
}

void arithmetic::delspace()
{
	int i = 0;
	while (i < vyr.length())
	{
		if (vyr[i] == ' ')
			vyr.erase(i, 1);
		else i++;
	}
}

void arithmetic::devide()
{
	int thisSymb;
	TermTypes last, now;
	if (vyr!="")
	{
		nTerm++;
		thisSymb = symb.find(vyr[0]);
		if (thisSymb != -1)
			if (thisSymb < 4)
				last = OPERATOR;
			else if (thisSymb < 5)
				last = LBRACKET;
			else if (thisSymb < 6)
				last = RBRACKET;
			else if (thisSymb < 17)
				last = NUMBER;
			else last = VARIABLE;
		else
			last = UNKNOWN;
		pTerm[nTerm-1].str += vyr[0];


		for (int i = 1; i < vyr.length(); i++)
		{
			thisSymb = symb.find(vyr[i]);
			if (thisSymb != -1)
				if (thisSymb < 4)
					now = OPERATOR;
				else if (thisSymb < 5)
					now = LBRACKET;
				else if (thisSymb < 6)
					now = RBRACKET;
				else if (thisSymb < 17)
					now = NUMBER;
				else 
					now = VARIABLE;
			else
				now = UNKNOWN;

			if (now != last  ||  now == OPERATOR  ||   now == LBRACKET  ||  now == RBRACKET)
			{
				pTerm[nTerm-1].type = last;
				nTerm++;
			}
			pTerm[nTerm-1].str += vyr[i];
			last = now;
		}
		pTerm[nTerm-1].type = last;
	}
}


bool arithmetic:: check_symbol() const
{
	bool res = true;
	
	for (int i = 0; i < nTerm; i++)
	{
		if (pTerm[i].type == UNKNOWN)
		{	
			res = false;
			cout << "  " << "Incorrect symbols" << endl;
		}

		int g = 0;
		if (pTerm[i].type == NUMBER)
		{
			for (int j = 0; j < pTerm[i].str.length(); j++)
				if (pTerm[i].str[j] == '.')
					g++;
			if (g > 1 )
			{
					cout << "  " << "Incorrect symbols" << endl;
					res = false;
			}
			if ( pTerm[i].str.front() == '.'    ||     pTerm[i].str.back() == '.')
			{
				cout << "  " << "Incorrect symbols" << endl;
				res = false;
			}
		}
	}
	return res;
}

bool arithmetic::check_operations() const
{
	bool res = true;
	TermTypes now = pTerm[0].type;
	TermTypes next = now;
	int p=-1;

	for (int i=0; i<(nTerm-1); i++)
	{
		next=pTerm[i+1].type;
		if ((now == NUMBER || now == VARIABLE) && (next == NUMBER || next == VARIABLE || next == LBRACKET))
		{
			cout << "  " << "Operations error" << endl;
			return false;
		}
		
		if (now == OPERATOR && (next == OPERATOR || next == RBRACKET))
		{
			cout << "  " << "Operations error" << endl;
			return false;
		}
		if (now == RBRACKET && (next != OPERATOR && next != RBRACKET))
		{
			cout << "  " << "Operations error" << endl;
			return false;
		}
		if   (now == LBRACKET && ((next == OPERATOR && pTerm[i + 1].str != "-") || next == RBRACKET))
		{
			cout << "  " << "Operations error" << endl;
			return false;
		}
		now=next;
	}
	if (next == LBRACKET || next == OPERATOR)
	{
		cout << "  " << "Operations error" << endl;
		res = false;
	}
	if ( pTerm[0].type != NUMBER     &&     pTerm[0].type != VARIABLE     &&     pTerm[0].type != LBRACKET     &&      pTerm[0].str != "-")
	{
		cout << "  " << "Operations error" << endl;
		res = false;
	}
	return res;
}


bool arithmetic::check_brackets() const
{
	bool res = true;
	int tmp = 0;
	for (int i = 0; i < nTerm; i++)
	{
		if (pTerm[i].type == LBRACKET)
			tmp++;

		if (pTerm[i].type == RBRACKET)
			tmp--;
	}

	if (tmp != 0)
	{
		cout << "Brackets error" << endl;
		res=false;
	}
	return res;
}


int pr(char c)
{
	switch (c)
	{
	case '+': case '-': return 0; break;
	case '*': case '/': return 1; break;
	default: return -1; 
	}
}

bool arithmetic::prioritet(Term one, Term two) const
{
	int prOne, prTwo;
	prOne = pr(one.str[0]);
	prTwo = pr(two.str[0]);

	if (prOne<=prTwo)
		return true;
	else 
		return false;
}




int arithmetic::OPN() 
{
	a = new Term[nTerm*2];               //  а-массив термов - ПЗ
	Stack<Term> b(nTerm*2);	             //  b-стек операций
	int j=0;
	Term null("0", NUMBER);

	for (int i = 0; i < nTerm; i++)
	{
		if ((pTerm[i].type == NUMBER) || (pTerm[i].type == VARIABLE))           
			a[j++]= pTerm[i];                                                         
		                                                                            
		if (pTerm[i].type == LBRACKET)                                                      
			b.Push(pTerm[i]);              

		if (pTerm[i].type == RBRACKET)
		{
			if (!b.IsEmpty())
			while (b.Peek().type != LBRACKET)
				a[j++] = b.Pop();
			b.Pop();
		}

		if (pTerm[i].type == OPERATOR)
		{
			if (pTerm[i].str== "-")
			{
				if (i == 0)
					a[j++]=null;
				else 
					if ((i-1 > 0) && (pTerm[i-1].type == LBRACKET))
						a[j++]=null;
			}
			while ((!b.IsEmpty()) && prioritet(pTerm[i], b.Peek()))
				a[j++]=b.Pop();
			b.Push(pTerm[i]);
		}
	}
	
	while (!b.IsEmpty())
		a[j++]=b.Pop();
	nP = j;
	return j;
}


bool arithmetic:: nomistakes() 
{
	if (vyr.length() > 0)
	{
		bool sm, op, br;
		sm = check_symbol();
		op = check_operations();
		br = check_brackets();
		return sm && op && br;
	}
	else
	{
		cout << "This string is empty";
		return false;
	}
}


double arithmetic::calculation() 
{
	Stack<double> x;
	Stack<string> s;
	double res = 0.0;
	string st_now;
	string cur = "";

	for (int i = 0; i < nP; i++)
	{
		if (a[i].type == VARIABLE)
		{
			cout<<"Input "<<a[i].str<<":";
			double val;
			cin>>val;
			x.Push(val);
			cur+=( a[i].str + "=" + to_string(val));
			vars.Push(cur);
		}

		if (a[i].type == NUMBER || a[i].type == VARIABLE)            
			x.Push(stod(a[i].str));                          //stod Преобразует последовательность символов в double.

		if (a[i].type == OPERATOR)
		{
			double b = x.Pop();      
			double c = x.Pop();
			switch (a[i].str[0])
			{
			case '+': res = b+c; break;
			case '-': res = c-b; break;
			case '*': res = b*c; break;
			case '/': res = c/b; break;
			}
			x.Push(res);
		}
	}
	return x.Pop();
}

void arithmetic:: print_OPN()
{
	cout << "Polish expression: "; 
	for (int i=0; i<nP; i++) 
		cout << a[i].str << "  ";
	cout << endl;
}
