#include "stdafx.h"
#include <QtWidgets>
#include "dropabletable.h"
#include "GameWindow.h"

DropableTable::DropableTable(QWidget *parent)
: QTableWidget(parent)
{
	
}

//инициализация таблиц
void DropableTable::initTable()
{
	if (0 == QString::compare(this->objectName(), "invTableWidget", Qt::CaseInsensitive))
	{
		inv.setSize<Subject>(this->rowCount(), this->columnCount());
		inv.initListWithEmptyValues<Subject>();
	}
	if (0 == QString::compare(this->objectName(), "objTableWidget", Qt::CaseInsensitive))
	{
		sub.setPath(":/images/apple.jpg");
		sub.setType("Food");
		
		QLabel *iconLb = new QLabel(this);
		iconLb->setGeometry(QRect(0, 0, 149, 149));
		iconLb->setMinimumSize(QSize(149, 149));
		iconLb->setMaximumSize(QSize(149, 149));
		QImage img(QString::fromUtf8(":/images/apple.jpg"));
		iconLb->setPixmap(QString::fromUtf8(":/images/apple.jpg"));
		iconLb->setObjectName("iconLb");
		iconLb->setAttribute(Qt::WA_DeleteOnClose);
		this ->setCellWidget(0, 0, iconLb);
	}
	clearImg = QImage(QString::fromUtf8(":/images/apple.jpg"));
}

//очистка таблицы
void DropableTable::clearTable()
{
	this->clear();
	inv.clearInventory<Subject>();
}

//переопределение базового метода
void DropableTable::dragEnterEvent(QDragEnterEvent *event)
{
	if (event->mimeData()->hasFormat("x-qabstractitemmodeldatalist")) {
		if (event->source() == this) {
			event->setDropAction(Qt::MoveAction);
			event->accept();
		}
		else {
			event->acceptProposedAction();
		}
	}
	else {
		event->ignore();
	}
}

//переопределение базового метода
void DropableTable::dragMoveEvent(QDragMoveEvent *event)
{
	if (event->mimeData()->hasFormat("x-qabstractitemmodeldatalist")) {
		if (event->source() == this) {
			event->setDropAction(Qt::MoveAction);
			event->accept();
		}
		else {
			event->acceptProposedAction();
		}
	}
	else {
		event->ignore();
	}
}

//переопределение базового метода. Обработка нажатия мыши. 
void DropableTable::mousePressEvent(QMouseEvent *event)
{
	//Проверяем есть ли рисунок на том месте куда мы нажали
	QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
	if (!child)
		return;
	if (0 != QString::compare(child->metaObject()->className(), "QLabel", Qt::CaseInsensitive))
		return;

	if (event->button() == Qt::LeftButton) 
	{
		//заполняем данные для перетаскивания
		QPixmap pixmap = *child->pixmap();

		QByteArray itemData;
		QDataStream dataStream(&itemData, QIODevice::WriteOnly);
		if (0 == QString::compare(this->objectName(), "invTableWidget", Qt::CaseInsensitive))
		{
			//сохраняем параметры ячейки, откуда перетаскиваем объект
			clickedRow = this->rowAt(event->pos().y());
			clickedColumn = this->columnAt(event->pos().x());
			int count = inv.itemCountAt<Subject>(this->rowAt(event->pos().y()), this->columnAt(event->pos().x()));
			dataStream << pixmap << count << sub.getPath() << sub.getPath();
		}
		else
		{
			dataStream << pixmap << 1 << sub.getPath() << sub.getType();
		}

		QMimeData *mimeData = new QMimeData;
		mimeData->setData("x-qabstractitemmodeldatalist", itemData);

		QDrag *drag = new QDrag(this);
		drag->setMimeData(mimeData);
		drag->setPixmap(pixmap);
		drag->setHotSpot(event->pos() - child->pos());

		if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
			if (0 == QString::compare(this->objectName(), "invTableWidget", Qt::CaseInsensitive))
			{
				//этот блок обрабатывается если перетаскивание происходит в инвентаре
				child->close();
				this->removeCellWidget(this->rowAt(event->pos().y()), this->columnAt(event->pos().x()));
				inv.delteItemAt<Subject>(this->rowAt(event->pos().y()), this->columnAt(event->pos().x()));
				inv.deleteFromDb<Subject>(this->rowAt(event->pos().y()), this->columnAt(event->pos().x()));
				//логика для отклика на действия на стороне сервера или клиента
				GameWindow* mainParent = ((GameWindow*) this->parentWidget()->parentWidget()->parentWidget());
				if (mainParent->isServer)
				{
					
					if (mainParent->server->isSocketActive())
						mainParent->server->startWrite(inv.itemAtToXmlString<Subject>(this->rowAt(event->pos().y()), this->columnAt(event->pos().x()), "", "", 0));
				}
				else
				{
					if (mainParent->client->isSocketActive())
						mainParent->client->startWrite(inv.itemAtToXmlString<Subject>(this->rowAt(event->pos().y()), this->columnAt(event->pos().x()), "", "", 0));
				}
			}
		}
		else {
			child->show();
		}
	}
	if (event->button() == Qt::RightButton)
	{
		//блок удаления объекта и воспроизведение соответствующего звука
		if (0 == QString::compare(this->objectName(), "invTableWidget", Qt::CaseInsensitive))
		{
			if (!inv.inventoryAtIsEmpty<Subject>(this->rowAt(event->pos().y()), this->columnAt(event->pos().x())))
			{
				int curCount = inv.itemCountAt<Subject>(this->rowAt(event->pos().y()), this->columnAt(event->pos().x()));
				if (curCount == 1)
				{
					inv.delteItemAt<Subject>(this->rowAt(event->pos().y()), this->columnAt(event->pos().x()));
					QSound::play(":/sounds/bite.wav");
					this->removeCellWidget(this->rowAt(event->pos().y()), this->columnAt(event->pos().x()));
					inv.deleteFromDb<Subject>(this->rowAt(event->pos().y()), this->columnAt(event->pos().x()));
					GameWindow* mainParent = ((GameWindow*) this->parentWidget()->parentWidget()->parentWidget());
					if (mainParent->isServer)
					{
						
						if (mainParent->server->isSocketActive())
							mainParent->server->startWrite(inv.itemAtToXmlString<Subject>(this->rowAt(event->pos().y()), this->columnAt(event->pos().x()), "", "", 0)); 
					}
					else
					{
						if (mainParent->client->isSocketActive())
							mainParent->client->startWrite(inv.itemAtToXmlString<Subject>(this->rowAt(event->pos().y()), this->columnAt(event->pos().x()), "", "", 0)); 
					}
				}
				if (curCount > 1)
				{
					curCount = curCount - 1;
					
					QLabel *newIcon = new QLabel(this);
					newIcon->setGeometry(QRect(0, 0, 149, 149));
					newIcon->setMinimumSize(QSize(149, 149));
					newIcon->setMaximumSize(QSize(149, 149));
					newIcon->setObjectName("iconLb");
					newIcon->setAttribute(Qt::WA_DeleteOnClose);

					QImage img = clearImg;
					QPainter* painter = new QPainter(&img);
					painter->setPen(Qt::black);
					painter->setFont(QFont("Arial", 10));
				    painter->drawText(img.rect(), Qt::AlignRight | Qt::AlignBottom, QString::number(curCount));
					newIcon->setPixmap(QPixmap::fromImage(img));
					inv.setItemAt<Subject>(this->rowAt(event->pos().y()), this->columnAt(event->pos().x()), sub, curCount);
					inv.updateInDb<Subject>(this->rowAt(event->pos().y()), this->columnAt(event->pos().x()));
					GameWindow* mainParent = ((GameWindow*) this->parentWidget()->parentWidget()->parentWidget());
					if (mainParent->isServer)
					{
						
						if (mainParent->server->isSocketActive())
							mainParent->server->startWrite(inv.itemAtToXmlString<Subject>(this->rowAt(event->pos().y()), this->columnAt(event->pos().x()), sub.getPath(), sub.getType(), curCount));
					}
					else
					{
						if (mainParent->client->isSocketActive())
							mainParent->client->startWrite(inv.itemAtToXmlString<Subject>(this->rowAt(event->pos().y()), this->columnAt(event->pos().x()), sub.getPath(), sub.getType(), curCount)); 
					}
						
					QSound::play(":/sounds/bite.wav");
					this->setCellWidget(this->rowAt(event->pos().y()), this->columnAt(event->pos().x()), newIcon);
					delete painter;
				}
			}
		}
	}
	inv.showDebug<Subject>();
}

void DropableTable::dropEvent(QDropEvent *event)
{
	if (event->mimeData()->hasFormat("x-qabstractitemmodeldatalist")) 
	{
		//проверяем перетаскивание произошло или нет
		if (clickedRow == this->rowAt(event->pos().y()) && clickedColumn == this->columnAt(event->pos().x()))
			return;
		QByteArray itemData = event->mimeData()->data("x-qabstractitemmodeldatalist");
		QDataStream dataStream(&itemData, QIODevice::ReadOnly);

		//считываем данные
		QImage img;
		int count;
		QString path;
		QString type;
		dataStream >> img  >> count >> path >> type;
		sub.setPath(path);
		sub.setType(type);

		QLabel *newIcon = new QLabel(this);
		newIcon->setGeometry(QRect(0, 0, 149, 149));
		newIcon->setMinimumSize(QSize(149, 149));
		newIcon->setMaximumSize(QSize(149, 149));
		newIcon->setObjectName("iconLb");
		newIcon->setAttribute(Qt::WA_DeleteOnClose);

		if (inv.inventoryAtIsEmpty<Subject>(this->rowAt(event->pos().y()), this->columnAt(event->pos().x())) && count == 1)
		{
			//этот блок обрабатыватся если перетаскивание произошло в пустую ячейку, а также источником перетаскивания является
			// не инвентарь
			img = clearImg;
			QPainter* painter = new QPainter(&img);
			painter->setPen(Qt::black);
			painter->setFont(QFont("Arial", 10));
			painter->drawText(img.rect(), Qt::AlignRight|Qt::AlignBottom, QString::number(count));
			newIcon->setPixmap(QPixmap::fromImage(img));
			inv.setItemAt<Subject>(this->rowAt(event->pos().y()), this->columnAt(event->pos().x()), sub, count);
			inv.insertToDb<Subject>(this->rowAt(event->pos().y()), this->columnAt(event->pos().x()));
			GameWindow* mainParent = ((GameWindow*) this->parentWidget()->parentWidget()->parentWidget());
			if (mainParent->isServer)
			{
				if (mainParent->server->isSocketActive())
					mainParent->server->startWrite(inv.itemAtToXmlString<Subject>(this->rowAt(event->pos().y()), this->columnAt(event->pos().x()), sub.getPath(), sub.getType(), count));
			}
			else
			{
				if (mainParent->client->isSocketActive())
					mainParent->client->startWrite(inv.itemAtToXmlString<Subject>(this->rowAt(event->pos().y()), this->columnAt(event->pos().x()), sub.getPath(), sub.getType(), count));
			}
			delete painter;
				
			this->setCellWidget(this->rowAt(event->pos().y()), this->columnAt(event->pos().x()), newIcon);
		}
		else if (inv.inventoryAtIsEmpty<Subject>(this->rowAt(event->pos().y()), this->columnAt(event->pos().x())) && count > 1)
		{
			//этот блок обрабатыватся если перетаскивание произошло в пустую ячейку, а также источником перетаскивания является
			// инвентарь
			img = clearImg;
			QPainter* painter = new QPainter(&img);
			painter->setPen(Qt::black);
			painter->setFont(QFont("Arial", 10));
			painter->drawText(img.rect(), Qt::AlignRight | Qt::AlignBottom, QString::number(count));
			newIcon->setPixmap(QPixmap::fromImage(img));
			inv.setItemAt<Subject>(this->rowAt(event->pos().y()), this->columnAt(event->pos().x()), sub, count);
			inv.insertToDb<Subject>(this->rowAt(event->pos().y()), this->columnAt(event->pos().x()));
			GameWindow* mainParent = ((GameWindow*) this->parentWidget()->parentWidget()->parentWidget());
			if (mainParent->isServer)
			{
				
				if (mainParent->server->isSocketActive())
					mainParent->server->startWrite(inv.itemAtToXmlString<Subject>(this->rowAt(event->pos().y()), this->columnAt(event->pos().x()), sub.getPath(), sub.getType(), count));
			}
			else
			{
				if (mainParent->client->isSocketActive())
					mainParent->client->startWrite(inv.itemAtToXmlString<Subject>(this->rowAt(event->pos().y()), this->columnAt(event->pos().x()), sub.getPath(), sub.getType(), count));
			}
			this->setCellWidget(this->rowAt(event->pos().y()), this->columnAt(event->pos().x()), newIcon);
		}
		else
		{
			//этот блок обрабатыватся если перетаскивание произошло не пустую ячейку, а также источником перетаскивания является
			// инвентарь
			img = clearImg;
			QPainter* painter = new QPainter(&img);
			painter->setPen(Qt::black);
			painter->setFont(QFont("Arial", 10));
			if (count != -1)
			{
				int curCount = inv.itemCountAt<Subject>(this->rowAt(event->pos().y()), this->columnAt(event->pos().x()));
				painter->drawText(img.rect(), Qt::AlignRight | Qt::AlignBottom, QString::number(count + curCount));
				newIcon->setPixmap(QPixmap::fromImage(img));
				inv.setItemAt<Subject>(this->rowAt(event->pos().y()), this->columnAt(event->pos().x()), sub, count + curCount);
				inv.updateInDb<Subject>(this->rowAt(event->pos().y()), this->columnAt(event->pos().x()));
				GameWindow* mainParent = ((GameWindow*) this->parentWidget()->parentWidget()->parentWidget());
				if (mainParent->isServer)
				{
					
					if (mainParent->server->isSocketActive())
						mainParent->server->startWrite(inv.itemAtToXmlString<Subject>(this->rowAt(event->pos().y()), this->columnAt(event->pos().x()), sub.getPath(), sub.getType(), count + curCount));
				}
				else
				{
					if (mainParent->client->isSocketActive())
						mainParent->client->startWrite(inv.itemAtToXmlString<Subject>(this->rowAt(event->pos().y()), this->columnAt(event->pos().x()), sub.getPath(), sub.getType(), count + curCount));
				}
					
				this->setCellWidget(this->rowAt(event->pos().y()), this->columnAt(event->pos().x()), newIcon);
			}
			delete painter;
		}
		if (event->source() == this) {
			event->setDropAction(Qt::MoveAction);
			event->accept();
		}
		else {
			event->acceptProposedAction();
		}
	}
	else {
		event->ignore();
	}
	clickedColumn = clickedRow = -1;
	inv.showDebug<Subject>();
}

void DropableTable::updateTable(inventoryObject obj)
{
	int row = -1;
	int column = -1;
	QString path;
	QString type;
	int count = 0;
	
	QLabel *newIcon = new QLabel(this);
	newIcon->setGeometry(QRect(0, 0, 149, 149));
	newIcon->setMinimumSize(QSize(149, 149));
	newIcon->setMaximumSize(QSize(149, 149));
	newIcon->setObjectName("iconLb");
	newIcon->setAttribute(Qt::WA_DeleteOnClose);

	row = std::get<0>(obj);
	column = std::get<1>(obj);
	path = std::get<2>(obj);
	type = std::get<3>(obj);
	count = std::get<4>(obj);
	if (inv.itemCountAt<Subject>(row, column) != count)
	{
		QImage img;
		if (inv.itemCountAt<Subject>(row, column) == 0)
		{
			sub.setPath(path);
			sub.setType(type);
			img = clearImg;
			QPainter* painter = new QPainter(&img);
			painter->setPen(Qt::black);
			painter->setFont(QFont("Arial", 10));
			painter->drawText(img.rect(), Qt::AlignRight | Qt::AlignBottom, QString::number(count));
			newIcon->setPixmap(QPixmap::fromImage(img));
			inv.setItemAt<Subject>(row, column, sub, count);
			inv.insertToDb<Subject>(row, column);
			this->setCellWidget(row, column, newIcon);
			delete painter;
		}
		else
		{
			if (inv.itemCountAt<Subject>(row, column) != 0 && count == 0)
			{
				inv.delteItemAt<Subject>(row, column);
				this->removeCellWidget(row, column);
				inv.deleteFromDb<Subject>(row, column);
			}
			else
			{
				sub.setPath(path);
				sub.setType(type);
				img = clearImg;
				QPainter* painter = new QPainter(&img);
				painter->setPen(Qt::black);
				painter->setFont(QFont("Arial", 10));
				painter->drawText(img.rect(), Qt::AlignRight | Qt::AlignBottom, QString::number(count));
				newIcon->setPixmap(QPixmap::fromImage(img));
				inv.setItemAt<Subject>(row, column, sub, count);
				inv.updateInDb<Subject>(row, column);
				this->setCellWidget(row, column, newIcon);
				delete painter;
			}
		}
	}
}

