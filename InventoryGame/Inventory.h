#ifndef INVENTORY_H
#define INVENTORY_H
#include <QList>
#include "InventoryItem.h"
#include "SqlModule.h"

//� ����������� ������ ������ �������� ������, ��� ��� ����� ������������ ���� ����� �� ������ ��� Subject ������, 
// �� � ��� ������ �������. ��������  ����� ����� �������� ����� Artefacts ��� ��� �����������  ������������
// ��(��-���� ��� ���������� ��� �������������), � �������� ��� ��� ��������. ������, ��� ����� ����� ���������� �����
// InvrntoryItem. ��� �������� �������, � ������ InvrntoryItem ��������� ������ ������ ��� ������ � ������� Subject.


template<class T> 
class Inventory
{
public:
	Inventory()
	{
		db.connectToDb();
		db.createTables();
	}
	~Inventory(){};
	
	//����� ��� �������, ����� ������ �������
	template<class T>
	void showDebug()
	{
		QString s = "list= {";
		for (int i = 0; i < rowCount*columnCount; i++)
		{
			s = s + " " + QString::number(itemList[i].getCount<T>()) + ", ";
		}
		s = s + "}";
		qDebug() << s.toLatin1();
	}

	//������� ��� ������������� ������ ������� ���������
	template<class T>
	void initListWithEmptyValues()
	{
		for (int i = 0; i < rowCount*columnCount; i++)
		{
			itemList.push_back(InventoryItem<T>());
		}
	}

	//������� ���������
	template<class T>
	void clearInventory()
	{
		for (int i = 0; i < rowCount*columnCount; i++)
		{
			itemList[i]= InventoryItem<T>();
		}
	}

	//�������� �� ������� ������ � ���������
	template<class T>
	bool inventoryAtIsEmpty(int r, int c)
	{
		int index = calculateIndex<T>(r, c);
		if (-1 != index)
		{
			if (itemList[index].isEmpty<T>())
			{
				return true;
			}
		}
		return false;
	}

	//�������� �� ���������
	template<class T>
	bool delteItemAt(int r, int c)
	{
		int index = calculateIndex<T>(r, c);
		if (-1 != index)
		{
			if (!itemList[index].isEmpty<T>())
			{
				itemList[index] = InventoryItem<T>();
				return true;
			}
		}
		return false;
	}
	
	//������� � ���������
	template<class T>
	void setItemAt(int r, int c, T item, int count)
	{
		int index = calculateIndex<T>(r, c);
		if (-1 != index)
		{
			if (itemList[index].isEmpty<T>())
			{
				InventoryItem<T> iItem(item, count);
				itemList[index] = iItem;
			}
			else
			{
				itemList[index].setCount<T>(count);
			}
		}
	}

	//���������� �������� � ������
	template<class T>
	int itemCountAt(int r, int c)
	{
		int index = calculateIndex<T>(r, c);
		if (-1 != index)
		{
			return itemList[index].getCount<T>();
		}
		return -1;
	}
	
	//������� ������� �������� � ������
	template<class T>
	int calculateIndex(int r, int c)
	{
		int index;
		if (r > rowCount || c > columnCount || r < 0 || c < 0)
		{
			index = -1;
			return index;
		}
		if (0 == r && 0 == c)
		{
			index = 0;
			return index;
		}
		if (0 != r)
		{
			index = r * columnCount + c;
			return index;
		}
		else
		{
			index = c;
			return index;
		}
	}
	
	//������������� ������� ���������
	template<class T>
	void setSize(int rCount, int cCount)
	{
		rowCount = rCount;
		columnCount = cCount;
	}
	
	//������� ���������
	template<class T>
	void clear()
	{
		columnCount = 0;
		rowCount = 0;
		itemList.clear();
	}

	//������� ��� ������ � ��
	template<class T>
	void insertToDb(int r, int c)
	{
		int index = calculateIndex<T>(r, c);
		if (-1 != index)
		{
			if (!itemList[index].isEmpty<T>())
			{
				int subCount = itemList[index].getCount<T>();
				int subId = itemList[index].getItem<T>().getId(&db);
				if (0 == subId)
				{
					if (itemList[index].getItem<T>().inserToDb(&db))
					{
						subId = itemList[index].getItem<T>().getId(&db);
					}
				}
				db.insertInventory(r, c, subId, subCount);
			}
		}
	}
	
	template<class T>
	void updateInDb(int r, int c)
	{
		int index = calculateIndex<T>(r, c);
		if (-1 != index)
		{
			if (!itemList[index].isEmpty<T>())
			{
				int subCount = itemList[index].getCount<T>();
				int subId = itemList[index].getItem<T>().getId(&db);
				int invId = db.getIdforInventory(r, c);
				if (0 == invId)
					return;
				if (0 == subId)
				{
					if (itemList[index].getItem<T>().inserToDb(&db))
					{
						subId = itemList[index].getItem<T>().getId(&db);
					}
				}
				db.updateInventory(invId, r, c, subId, subCount);
			}
		}
	}
	
	template<class T>
	void deleteFromDb(int r, int c)
	{
		int index = calculateIndex<T>(r, c);
		if (-1 != index)
		{
			int invId = db.getIdforInventory(r, c);
			if (0 != invId)
			{
				db.deleteInventory(invId);
			}
		}
	}

private:
	int rowCount;
	int columnCount;
	QList<InventoryItem<T> > itemList;
	DbAccess db;
};
#endif