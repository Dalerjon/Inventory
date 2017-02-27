#ifndef INVENTORY_H
#define INVENTORY_H
#include <QList>
#include "InventoryItem.h"
#include "SqlModule.h"

//Я использовал шаблон вместо простого класса, так как хотел использовать этот класс не только для Subject класса, 
// но и для других классов. Например  можно будет добавить класс Artefacts где нет возможности  использовать
// ее(то-есть нет количества для использования), а работает она как пассивка. Однако, для этого нужно доработать класс
// InvrntoryItem. Для экономии времени, в классе InvrntoryItem объявлены только методы для работы с классом Subject.


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
	
	//метод для отладки, можно просто удалить
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

	//функция для инициализации списка пустими объектами
	template<class T>
	void initListWithEmptyValues()
	{
		for (int i = 0; i < rowCount*columnCount; i++)
		{
			itemList.push_back(InventoryItem<T>());
		}
	}

	//очистка инвентаря
	template<class T>
	void clearInventory()
	{
		for (int i = 0; i < rowCount*columnCount; i++)
		{
			itemList[i]= InventoryItem<T>();
		}
	}

	//проверка на нустоту ячейки в инвентаре
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

	//удаление из инвентаря
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
	
	//вставка в инвентарь
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

	//количество предмета в ячейке
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
	
	//подсчет индекса элемента в списке
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
	
	//инициализация размера инвентаря
	template<class T>
	void setSize(int rCount, int cCount)
	{
		rowCount = rCount;
		columnCount = cCount;
	}
	
	//очистка инвентаря
	template<class T>
	void clear()
	{
		columnCount = 0;
		rowCount = 0;
		itemList.clear();
	}

	//функции для работы с БД
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