#include "stdafx.h"
#include "SqlModule.h"

//подключаемся к БД
bool DbAccess::connectToDb()
{
	if (QSqlDatabase::isDriverAvailable(driver))
	{
		db = QSqlDatabase::addDatabase(driver);
		QFile file("inventory.db");
		if (file.exists())
			file.remove();
		db.setDatabaseName("inventory.db");
		if (db.open())
			return true; 
		qDebug() << db.lastError();
	}
	return false;
}

//создем 2 таблицы Subject и Inventory
bool DbAccess::createTables()
{
	QSqlQuery a_query("inventory");
	QString command = "CREATE TABLE subject ("
		"id integer PRIMARY KEY AUTOINCREMENT, "
		"type VARCHAR(255), "
		"path VARCHAR(255)"
		");";
	bool result = a_query.exec(command);
	if (!result) {
		qDebug() << db.lastError();
		qDebug() << a_query.lastError();
		return false;
	}
	command = "CREATE TABLE inventory ("
		"id integer PRIMARY KEY AUTOINCREMENT, "
		"row integer,"
		"column integer,"
		"subject_id integer,"
		"count integer"
		");";
	result = a_query.exec(command);
	if (!result) {
		return false;
	}
	return true;
}

//функция для получения id из таблицы Subject
int DbAccess::getIdforSubject(QString tType, QString tPath)
{
	QSqlQuery a_query("inventory");
	
	QString command = "SELECT * FROM subject where type = '" + tType + "' and path ='" + tPath + "'";
	if (!a_query.exec(command)) {
		return 0;
	}
	QSqlRecord rec = a_query.record();
	int id = 0;
	QString type = "";
	QString path = "";

	while (a_query.next()) {
		id = a_query.value(rec.indexOf("id")).toInt();
		type = a_query.value(rec.indexOf("type")).toString();
		path = a_query.value(rec.indexOf("path")).toString();
		if (0 != id)
			break;
	}

	return id;
}

//вставка в таблицу Subject
bool DbAccess::insertSubject(QString tType, QString tPath)
{
	QSqlQuery a_query("inventory");
	QString action = "INSERT INTO subject(type, path) "
		"VALUES ('%1', '%2');";
	QString command = action.arg(tType)
		.arg(tPath);
	bool result = a_query.exec(command);
	if (!result) {
		qDebug() << a_query.lastError();
		return false;
	}
	return true;
}

//обновление строки в таблице Subject
bool DbAccess::updateSubject(int id, QString tType, QString tPath)
{
	QSqlQuery a_query("inventory");
	QString command = "UPDATE subject set type = '" + tType + "', path = '" + tPath + "' where id = " + QString::number(id);
	std::string temp = command.toStdString();
	bool result = a_query.exec(command);
	if (!result) {
		qDebug() << a_query.lastError();
		return false;		
	}
	return true;
}

//удаление строки в таблице Subject
bool DbAccess::deleteSubject(int id)
{
	QSqlQuery a_query("inventory");
	QString command = " DELETE from subject where id = " + QString::number(id);
	bool result = a_query.exec(command);
	std::string temp = command.toStdString();
	if (!result) {
		qDebug() << a_query.lastError();
		return false;		
	}
	return true;
}
//функция для получения id из таблицы inventory
int DbAccess::getIdforInventory(int tRow, int tColumn)
{
	QSqlQuery a_query("inventory");

	QString command = "SELECT * FROM inventory where row = " + QString::number(tRow) + " and column =" + QString::number(tColumn);
	if (!a_query.exec(command)) {
		return 0;
		qDebug() << a_query.lastError();
	}
	QSqlRecord rec = a_query.record();
	int id = 0;
	int row = 0;
	int column = 0;
	int subjectID = 0;
	int count = 0;

	while (a_query.next()) {
		id = a_query.value(rec.indexOf("id")).toInt();
		row = a_query.value(rec.indexOf("row")).toInt();
		column = a_query.value(rec.indexOf("column")).toInt();
		subjectID = a_query.value(rec.indexOf("subject_id")).toInt();
		count = a_query.value(rec.indexOf("count")).toInt();
		if (0 != id)
			break;
	}
	return id;
}
//вставка в таблицу Inventory
bool DbAccess::insertInventory(int tRow, int tColumn, int tSubjectId, int tCount)
{
	QSqlQuery a_query("inventory");
	QString action = "INSERT INTO inventory(row, column, subject_id, count) "
		"VALUES (%1, %2, %3, %4);";
	QString command = action.arg(tRow)
		.arg(tColumn)
		.arg(tSubjectId)
		.arg(tCount);
	std::string temp = command.toStdString();
	bool result = a_query.exec(command);
	if (!result) {
		qDebug() << a_query.lastError();
		return false;
	}
	return true;
}
//обновление строки в таблице Inventory
bool DbAccess::updateInventory(int id, int tRow, int tColumn, int tSubjectId, int tCount)
{
	QSqlQuery a_query("inventory");
	QString command = "UPDATE inventory set row = " + QString::number(tRow)
		+ ", column = " + QString::number(tColumn)
		+ ", subject_id = " + QString::number(tSubjectId)
		+ ", count = " + QString::number(tCount)
		+ " where id =" + QString::number(id);
	std::string temp = command.toStdString();
	bool result = a_query.exec(command);
	if (!result) {
		qDebug() << a_query.lastError();
		return false;
	}
	return true;
}
//удаление строки в таблице Inventory
bool DbAccess::deleteInventory(int id)
{
	QSqlQuery a_query("inventory");
	QString command = " DELETE from inventory where id =" + QString::number(id);
	std::string temp = command.toStdString();
	bool result = a_query.exec(command);
	if (!result) {
		qDebug() << a_query.lastError();
		return false;
	}
	return true;
}