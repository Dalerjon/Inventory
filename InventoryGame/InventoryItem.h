#ifndef INVENTORYITEM_H
#define INVENTORYITEM_H

//� ����������� ������ ������ �������� ������, ��� ��� ����� ������������ ���� ����� �� ������ ��� Subject ������, 
// �� � ��� ������ �������.

template<class T>
class InventoryItem
{
public:
	
	//������������
	InventoryItem()
	{
		count = 0;
		item = T();
	}

	template <class Y, class X>
	InventoryItem(Y iItem, X itemCount)
	{
		item = iItem;
		count = itemCount;
	}

	~InventoryItem(){};

	//�������� �� ������� ������
	template <class T>
	bool isEmpty()
	{
		if (0 == count)
			return true;
		return false;
	}

	//������� � ������
	template <class T>
	bool insertItem(T iItem, int itemCount)
	{
		item = iItem;
		count = itemCount;
	}

	//�������� �� ������
	template <class T>
	bool deleteItem()
	{
		count = 0;
		item = T();
	}

	//Accessors � Mutators
	template <class T>
	void setItem(T iItem)
	{
		item = iItem;
	}

	template <class T>
	void setCount(int iCount)
	{
		count = iCount;
	}

	template <class T>
	int getCount()
	{
		return count;
	}

	template <class T>
	T getItem()
	{
		return item;
	}

private:
	int count = 0;
	T item{};
};
#endif