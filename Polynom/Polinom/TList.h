#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include "TMonom.h"
using namespace std;

template <class T>
class TList 
{
protected:
	TNode<T>* pFirst, * pCurr, * pPrev, * pLast, * pStop;
	int len;
public:
	TList();
	~TList();

	bool IsEmpty();
	bool IsNotEmpty();
	void InsFirst(T value);
	void InsLast(T value);
	void InsCurr(T value);

	void DelFirst();
	void DelCurr();
	void GoNext();
	bool IsEnd();

	void Reset();
	T GetCurr();

};

//Конструктор по умолчанию
template<class T>
TList<T>::TList()
{
	pStop = nullptr;
	pFirst = pCurr = pPrev = pLast = pStop;
	len = 0;
}
//Деструктор
template<class T>
TList<T>::~TList()
{
	while (pFirst != pStop)
	{
		TNode<T>* tmp = pFirst;
		pFirst = pFirst->pNext;
		delete tmp;
	}
	pLast = pPrev = pCurr = pStop;
	len = 0;
}

//Проверки на (не) пустоту списка
template<class T>
bool TList<T>::IsEmpty()
{
	return pFirst == nullptr;
}

template<class T>
bool TList<T>::IsNotEmpty()
{
	return pFirst != nullptr;
}

//Добавление элемента в начало, в конец и в определённое место списка
template<class T>
void TList<T>::InsFirst(T value)
{
	TNode<T>* newNode = new TNode<T>;
	newNode->val = value;
	newNode->pNext = pFirst;
	pFirst = newNode;
	len++;
	if (len == 1)
	{
		pLast = pFirst;
		pCurr = pFirst;
	}
}

template<class T>
void TList<T>::InsLast(T value)
{
	if (len > 0) 
	{
		TNode<T>* newNode = new TNode<T>;
		newNode->val = value;
		newNode->pNext = pStop;
		pLast->pNext = newNode;
		pLast = newNode;

		len++;
	}
	else
	{
		InsFirst(value);
	}
}

template<class T>
void TList<T>::InsCurr(T value)
{
	if (pCurr == pFirst) 
	{
		InsFirst(value);
	}
	else if (pCurr == pLast)
	{
		InsLast(value);
	}
	else {
		TNode<T>* newNode = new TNode<T>;
		newNode->val = value;
		newNode->pNext = pCurr;
		pCurr = newNode;
		pPrev->pNext = pCurr;
		len++;
	}
}
//Удаление с начала и из определённого места списка
template<class T>
void TList<T>::DelFirst()
{
	if (IsEmpty())
	{
		throw "Empty!";
	}

	if (pCurr == pFirst)
	{
		pPrev = pStop;
		pCurr = pCurr->pNext;
	}

	TNode<T>* newNode = pFirst;
	pFirst = newNode->pNext;
	delete newNode;
	len--;
	if (pFirst == pStop) 
	{
		pLast = pStop;
	}
}

template<class T>
void TList<T>::DelCurr()
{
	if (IsEmpty())
	{
		throw "Empty!";
	}

	if (pCurr == pFirst) 
	{
		DelFirst();
	}
	else {
		TNode<T>* newNode = pCurr;
		pCurr = newNode->pNext;
		pPrev->pNext = pCurr;
		delete newNode;
		len--;
	}
}
//Движение дальше по списку на следующее звено
template<class T>
void TList<T>::GoNext()
{
	pPrev = pCurr;
	pCurr = pCurr->pNext;
}
//Проверка пришли ли в конец списка
template<class T>
bool TList<T>::IsEnd()
{
	return pCurr == pStop;
}
//Получить значение данного звена
template<class T>
T TList<T>::GetCurr()
{
	return pCurr->val;
}
//Сброс к самому началу
template<class T>
void TList<T>::Reset()
{
	pPrev = pStop;
	pCurr = pFirst;
}

///////////////////		THEADLIST		////////////////////////////
//Самый первый элемент
template <class T>
class THeadList : public TList<T>
{
protected:
	TNode<T>* pHead;
public:
	THeadList();
	~THeadList();
	void InsFirst(T elem);
	void DelFirst();
};

template<class T>
THeadList<T>::THeadList()
{
	len = 0;
	pHead = new TNode<T>;
	pHead->pNext = pHead;
	pFirst = pLast = pPrev = pCurr = pStop = pHead;
}

template<class T>
THeadList<T>::~THeadList()
{
	while (pFirst != pStop) 
	{
		TNode<T>* newNode = pFirst;
		pFirst = pFirst->pNext;
		delete newNode;
	}
	delete pHead;
}

template<class T>
void THeadList<T>::InsFirst(T elem)
{
	TList::InsFirst(elem);
	pHead->pNext = pFirst;
}

template<class T>
void THeadList<T>::DelFirst()
{
	TList::DelFirst();
	pHead->pNext = pFirst;
}
