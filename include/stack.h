// ���������� � ���������� ���������� �����
// ���� ������������ ��������: 
// - ������� ��������, 
// - ���������� ��������, 
// - �������� �������� �������� (��� ��������)
// - �������� �� �������, 
// - ��������� ���������� ��������� � �����
// - ������� �����
// ��� ������� � ������ ���� ������ �������������� ������


#pragma once


// ���������� ���������� �����
template<class SType>
class Stack
{
private:
	int Size;                                                       // ������������ ���������� ��������� � �����
	int top;                                                        // ����� �������� ��������
	SType* sMem;                                                    // ��������� �� ����
	int GetNextIndex() const {return top+1;}                        // �������� ������ ���������� ��������                                                  
public:
	Stack (int n=100);                                              // ����������� ��� ����������
	Stack (const Stack<SType>& s);                                  // ����������� �����������
	~Stack();                                                       // ����������
	void Push (const SType& newEl);                                 // �������� ������� �� ������� �����
	SType Peek() const;                                             // ������� ������� � ������� ����� ��� ��� ��������
	SType Pop();                                                    // ������� ������� � ������� ����� � ������� ��� (���������� ��������)
	int GetSize() const {return top + 1;}                           // �������� ���������� ��������� � �����
	bool IsEmpty() const {return top == -1;}                        // ������ ����
	bool operator==(const Stack<SType>& s) const;
};
	
// ���������� ���������� �����
template<class SType>			                                    // ����������� 
Stack<SType>::Stack(int n=100 ): 
	Size(n)
{
	top = -1;
	sMem = new SType[Size];
}

template<class SType>			                                    // ����������� �����������
Stack<SType>::Stack(const Stack<SType>& s)
{
	Size = s.Size;
    sMem = new SType[Size];
	for (int i = 0; i <(top+1); i++)
		sMem[i] = s.sMem[i];
}

template<class SType>			                                // ����������
Stack<SType>::~Stack()
{
	delete[] sMem;
}

template<class SType>			                                // �������� ������� �� ������� �����
void Stack<SType>::Push(const SType& newEl)
{
	if (top == Size - 1)
	{
		SType* temp;
		Size = Size*2;
		temp = new SType[Size];
		for (int i = 0; i < top + 1; i++)
			temp[i] = sMem[i];
		delete[] sMem;
		sMem = temp;		
	}
	    top+=1;
		sMem[top]=newEl;
}

template<class SType>			                               // ������� ������� � ������� ����� ��� ��� ��������
SType Stack<SType>::Peek() const
{
	if (!IsEmpty())
		return sMem[top];
	else
		throw 1;
}

template<class SType>			                              // ������� ������� � ������� ����� � ������� ��� (���������� ��������)
SType Stack<SType>::Pop()
{
	if (!IsEmpty())
		return sMem[top--];
	else
		throw 1;
}


template<class SType>
inline bool Stack<SType>::operator==(const Stack<SType>& s) const
{
	if (this != &s)
	{
		if (top == s.top)
		{
			for (int i = 0; i < top; i++)
				if (sMem[i] != s.sMem[i])
					return false;
			return true;
		}
		else
			return false;
	}
	else
		return true;
}

