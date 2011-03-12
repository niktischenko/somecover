#ifndef ENTRY_H
#define ENTRY_H
#include <QString>

class Entry {
public:
	QString Artist;
	QString Album;
	QString getCoverPath();
	QString getThumbPath();
	const bool operator ==(const Entry e) {
		return (Artist.toLower() == e.Artist.toLower() && Album.toLower() == e.Album.toLower());
	}
};

#endif // ENTRY_H
