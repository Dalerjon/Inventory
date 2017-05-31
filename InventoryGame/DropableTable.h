#ifndef DROPABLETABLE_H
#define DROPABLETABLE_H

#include <QTableWidget>
#include <QSound>
#include "Inventory.h"
#include "Subject.h"
#include "TupleObject.h"


class QDragEnterEvent;
class QDropEvent;
class QLabel;

class DropableTable : public QTableWidget
{
public:
	DropableTable(QWidget *parent = 0);
	void initTable();
	void clearTable();
	void updateTable(inventoryObject obj);
	Inventory<Subject> inv;
protected:
	void dragEnterEvent(QDragEnterEvent *event) override;
	void dragMoveEvent(QDragMoveEvent *event) override;
	void dropEvent(QDropEvent *event) override;
	void DropableTable::mousePressEvent(QMouseEvent *event);

private:
	
	Subject sub;

	//для чистого экземпляра картинки
	QImage clearImg;

	//сохраняем номер строки и столбца при нажатии на ячейку
	int clickedRow = -1;
	int clickedColumn = -1;
};

#endif