// реализация пользовательского приложения
#include "stack.h"
#include <iostream>
#include "arithmetic.h"
using namespace std;
#include <string>

int main()
{
	string ex;
	cout << "Input your expression:  ";
	getline(cin,ex);
	arithmetic ar(ex);
	if ( ar.nomistakes() == false)
		cout << "Your expression is not correct" << endl;
	else
	{
		ar.OPN(); 
		ar.print_OPN(); 
		cout << "Result: " << ar.calculation() << endl;
	}
  return 0;
}
