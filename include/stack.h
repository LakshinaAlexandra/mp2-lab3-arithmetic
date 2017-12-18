// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память


#pragma once


// Объявление шаблонного стека
template<class SType>
class Stack
{
private:
	int Size;                                                       // максимальное количество элементов в стеке
	int top;                                                        // номер текущего элемента
	SType* sMem;                                                    // указатель на стек
	int GetNextIndex() const {return top+1;}                        // получить индекс следующего элемента                                                  
public:
	Stack (int n=100);                                              // конструктор без параметров
	Stack (const Stack<SType>& s);                                  // конструктор копирования
	~Stack();                                                       // деструктор
	void Push (const SType& newEl);                                 // записать элемент на вершину стека
	SType Peek() const;                                             // вернуть элемент с вершины стека без его удаления
	SType Pop();                                                    // удалить элемент с вершины стека и вернуть его (извлечение элемента)
	int GetSize() const {return top + 1;}                           // получить количество элементов в стеке
	bool IsEmpty() const {return top == -1;}                        // пустой стек
	bool operator==(const Stack<SType>& s) const;
};
	
// Реализация шаблонного стека
template<class SType>			                                    // Конструктор 
Stack<SType>::Stack(int n=100 ): 
	Size(n)
{
	top = -1;
	sMem = new SType[Size];
}

template<class SType>			                                    // Конструктор копирования
Stack<SType>::Stack(const Stack<SType>& s)
{
	Size = s.Size;
    sMem = new SType[Size];
	for (int i = 0; i <(top+1); i++)
		sMem[i] = s.sMem[i];
}

template<class SType>			                                // Деструктор
Stack<SType>::~Stack()
{
	delete[] sMem;
}

template<class SType>			                                // Записать элемент на вершину стека
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

template<class SType>			                               // Вернуть элемент с вершины стека без его удаления
SType Stack<SType>::Peek() const
{
	if (!IsEmpty())
		return sMem[top];
	else
		throw 1;
}

template<class SType>			                              // Удалить элемент с вершины стека и вернуть его (извлечение элемента)
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

