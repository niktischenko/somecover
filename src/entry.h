/*
 * SomeCover - Album art manager for SomePlayer and TPlayer
 * Copyright (C) 2010 Nikolay (somebody) Tischenko <niktischenko@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef ENTRY_H
#define ENTRY_H
#include <QString>

class Entry {
public:
	QString Artist;
	QString Album;
	QString getCoverPath();
	QString getThumbPath();
	QString getMediaArtLocalPath();
	const bool operator ==(const Entry e) {
		return (Artist.toLower() == e.Artist.toLower() && Album.toLower() == e.Album.toLower());
	}
	Entry(const Entry &e) {
		Artist = e.Artist;
		Album = e.Album;
	}
	Entry() {
		Artist = Album = "";
	}
};

#endif // ENTRY_H
