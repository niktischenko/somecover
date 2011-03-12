#include "entry.h"
#include <QDir>

QString Entry::getCoverPath() {
	QString aname = Artist.toLower().trimmed();
	QString aalbum = Album.toLower().trimmed();
	aname.replace("/", "");
	aalbum.replace("/", "");
	return QDir::homePath()+"/.covers/"+aname+" - "+aalbum+".jpg";
}

QString Entry::getThumbPath() {
	QString aname = Artist.toLower().trimmed();
	QString aalbum = Album.toLower().trimmed();
	aname.replace("/", "");
	aalbum.replace("/", "");
	return QDir::homePath()+"/.covers/.thumbs/"+aname+" - "+aalbum+".jpg";
}
