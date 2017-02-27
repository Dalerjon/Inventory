#include "stdafx.h"
#include "InventoryItem.h"

template <class T>
InventoryItem<T>::InventoryItem()
{
	item = 0;
	T = T();
}

template <class T>
InventoryItem<T>::InventoryItem(T iItem, int itemCount)
{
	item = iItem;
	count = itemCount;
}

template <class T>
InventoryItem<T>::~InventoryItem()
{

}

template <class T>
bool InventoryItem<T>::insertItem(T iItem, int itemCount)
{
	item = iItem;
	count = itemCount;
}

template <class T>
bool InventoryItem<T>::deleteItem()
{
	count = 0;
	item = T();
}

template <class T>
void InventoryItem<T>::setItem(T iItem)
{
	item = iItem;
}


template <class T>
void InventoryItem<T>::setCount(int iCount)
{
	count = iCount;
}

template <class T>
int InventoryItem<T>::getCount()
{
	return count;
}

template <class T>
T InventoryItem<T>::getItem()
{
	return item;
}