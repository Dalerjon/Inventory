#ifndef SUBJECT_H
#define SUBJECT_H
#include <QString>

#include "SqlModule.h"

class Subject{
public:
	Subject();
	Subject(QString, QString);
	Subject(const Subject& sub);
	~Subject();
	QString getPath();
	QString getType();
	void setPath(QString);
	void setType(QString);

	bool inserToDb(DbAccess* db);
	bool deleteFromDb(DbAccess* db, int id);
	bool updateInDb(DbAccess* db, int id);
	int getId(DbAccess* db);
private:
	QString type = "";
	QString path = "";
};
#endif