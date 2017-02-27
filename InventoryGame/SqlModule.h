#ifndef SQLMODULE_H
#define SQLMODULE_H

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>

class DbAccess
{
public:
	DbAccess(){};
	~DbAccess(){};
	bool connectToDb();
	bool createTables();
	int getIdforSubject(QString tType, QString tPath);
	bool insertSubject(QString tType, QString tPath);
	bool updateSubject(int id, QString tType, QString tPath);
	bool deleteSubject(int id);
	int getIdforInventory(int tRow, int tColumn);
	bool insertInventory(int tRow, int tColumn, int tSubjectId, int tCount);
	bool updateInventory(int id, int tRow, int tColumn, int tSubjectId, int tCount);
	bool deleteInventory(int id);
private:
	const QString driver = "QSQLITE";
	QSqlDatabase db;
};
#endif