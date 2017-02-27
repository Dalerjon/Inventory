#include "stdafx.h"
#include "Inventory.h"


template<class T>
Inventory<T>::Inventory()
{

}

template<class T>
Inventory<T>::~Inventory()
{

}

template<class T>
int Inventory<T>::calculateIndex(int r, int c)
{
	int index;
	if (r > rowCount || c > columnCount || r < 0 || c < 0)
	{
		index = -1;
	}
	if (r == 0 && c = 0)
	{
		index = 0;
	}
	if (0 != r)
	{
		index = r * columnCount + c;
	}
	else
	{
		index = r + 1;
	}
	return index;
}

template<class T>
void Inventory<T>::setSize(int rCount, int cCount)
{
	rowCount = rCount;
	columnCount = cCount;
}

template<class T>
void Inventory<T>::clear()
{
	columnCount = 0;
	rowCount = 0;
	itemList.clear();
}