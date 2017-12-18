// тесты для вычисления арифметических выражений

#include "arithmetic.h"
#include "gtest.h"
#include "stack.h"
#include <iostream>
using namespace std;

string e[23] = { "/", "-", "2--5", "4*8+", "+4*8", "(1+2)(3+4)", "(", ")", "(1*2", "1+2)", "13(1+1)", "(1+1)13", "12&", "p2", "D", "2-5+к", "1..1", "x.1-13", "",  "(14-1*)", "$14", "1/-8", "+12-8"};
string j[7] = { "-8+(12-5*9)/12+(-7)", "2+9-(s)", "11-9/9-4", "(-8+3)", "-1", "(-1)" , "4+(12-1)" };
string h[5] = { "(85-5)/20-6*4", "(3+8/4)*(-4)", "(52-2)/5-30", "-20+0*95", "((46.04-0.04-6)/10-24)" };

class One : public ::testing::TestWithParam<string>
{
protected:
	string s1;
public:
	One() { s1 = GetParam(); }
	~One() {}
};


class Two : public One
{
protected:
	string s2;
public:
	Two() { s2 = GetParam(); }
	~Two() {}
};


class Three : public Two
{
protected:
	string s3;
public:
	Three() { s3 = GetParam(); }
	~Three() {}
};





TEST_P(One, error_checking_1)              
{
	arithmetic w(s1);
	EXPECT_EQ(false, w.nomistakes());
}
INSTANTIATE_TEST_CASE_P(inst1, One, ::testing::ValuesIn(e));


TEST_P(Two, error_checking_2)             
{
	arithmetic w(s2);
	EXPECT_EQ(true, w.nomistakes());
}
INSTANTIATE_TEST_CASE_P(inst2, Two, ::testing::ValuesIn(j));


TEST_P(Three, right_calculation)                  
{
	arithmetic w(s3);
	w.OPN();
	w.print_OPN();
	EXPECT_EQ( -20,  w.calculation());
}
INSTANTIATE_TEST_CASE_P(inst3, Three, ::testing::ValuesIn(h));




TEST(arithmethic, can_devide_expression)          
{
	arithmetic a("-85+12+(-2.2/^)");
	Term rig[11];
	Term* p = a.getTerms();
	rig[0] = Term("-",OPERATOR);
	rig[1] = Term("85",NUMBER);
	rig[2] = Term("+", OPERATOR);
	rig[3] = Term("12", NUMBER);
	rig[4] = Term("+", OPERATOR);
	rig[5] = Term("(", LBRACKET);
	rig[6] = Term("-", OPERATOR);
	rig[7] = Term("2.2", NUMBER);
	rig[8] = Term("/", OPERATOR);
	rig[9] = Term("^", UNKNOWN);
	rig[10] = Term(")", RBRACKET);
	bool res = true;
	for (int i = 0; i < a.getnTerm(); i++)
		if (rig[i] != p[i])
			res = false;
	EXPECT_EQ(true,res);
	ASSERT_NO_THROW(a = arithmetic(""));
	EXPECT_EQ(0, a.getnTerm());
}




TEST(arithmetic, can_transform_to_OPN_1)                          
{
	arithmetic a("-1+1");                                         //  0 1 - 1 +
	a.OPN();
	Term* p = a.getPolishTerms();
	int nP = a.getnPolishTerms();
	a.print_OPN();
	EXPECT_EQ(5, nP);
	EXPECT_EQ(Term("0", NUMBER), p[0]);
	EXPECT_EQ(Term("1", NUMBER), p[1]);
	EXPECT_EQ(Term("-", OPERATOR), p[2]);
	EXPECT_EQ(Term("1", NUMBER), p[3]);
	EXPECT_EQ(Term("+", OPERATOR), p[4]);
}


TEST(arithmetic, can_transform_to_OPN_2)              
{
	arithmetic a("3+(-2+3)");                     //  3   0  2  -  3  +  +
	a.OPN();
	Term* p = a.getPolishTerms(); 
	int nP = a.getnPolishTerms();
	a.print_OPN();
	EXPECT_EQ(7, nP);
    EXPECT_EQ(Term("3", NUMBER), p[0]);
	EXPECT_EQ(Term("0", NUMBER), p[1]);
	EXPECT_EQ(Term("2", NUMBER), p[2]);
	EXPECT_EQ(Term("-", OPERATOR), p[3]);
	EXPECT_EQ(Term("3", NUMBER), p[4]);
	EXPECT_EQ(Term("+", OPERATOR), p[5]);
	EXPECT_EQ(Term("+", OPERATOR), p[6]);
}


TEST(arithmetic, can_transform_to_OPN_3)                  
{
	arithmetic a("25+3*(7.1-2)*2");               // 25  3  7.1  2  -  *  2  *  + 
	a.OPN();
	Term lex[9];
	lex[0] = Term("25", NUMBER);
	lex[1] = Term("3", NUMBER);
	lex[2] = Term("7.1", NUMBER);
	lex[3] = Term("2", NUMBER);
	lex[4] = Term("-", OPERATOR);
	lex[5] = Term("*", OPERATOR);
	lex[6] = Term("2", NUMBER);
	lex[7] = Term("*", OPERATOR);
	lex[8] = Term("+", OPERATOR);
	
	Term* p = a.getPolishTerms();
	int nP = a.getnPolishTerms();
	a.print_OPN();
	ASSERT_EQ(9, nP);
	bool res = true;
	for (int i = 0; i < 9; i++)
		if (lex[i] != p[i])
			res = false;
	EXPECT_EQ(true,res);
}





