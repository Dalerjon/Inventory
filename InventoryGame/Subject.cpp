#include "stdafx.h"
#include "Subject.h"

Subject::Subject()
{
	type = "";
	path = "";
}

Subject::Subject(QString sType, QString sPath)
{
	type = sType;
	path = sPath;
}

Subject::Subject(const Subject& sub)
{
	type = sub.type;
	path = sub.path;
}

Subject::~Subject()
{
}

//Accessors и Mutators
QString Subject::getPath()
{
	return path;
}

QString Subject::getType()
{
	return type;
}

void Subject::setPath(QString sPath)
{
	path = sPath;
}

void Subject::setType(QString sType)
{
	type = sType;
}

//функции для работы с БД
bool Subject::inserToDb(DbAccess* db)
{
	return db->insertSubject(type, path);
}
bool Subject::deleteFromDb(DbAccess* db, int id)
{
	return db->deleteSubject(id);
}
bool Subject::updateInDb(DbAccess* db, int id)
{
	return db->updateSubject(id, type, path);
}
int Subject::getId(DbAccess* db)
{
	return db->getIdforSubject(type, path);
}