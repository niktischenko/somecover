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

#include "entry.h"
#include <QDir>
#include <QByteArray>
#include <QCryptographicHash>

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

QString Entry::getMediaArtLocalPath() {
	QString album = Album;
	QRegExp rsb("\\[.*\\]");
	QRegExp rfb("{.*}");
	QRegExp rrb("\\(.*\\)");
	QRegExp stripB("^[()_{}[]!@#$^&*+=|\\\\/\"'?<>~`\\s\\t]*");
	QRegExp stripE("[()_{}[]!@#$^&*+=|\\\\/\"'?<>~`\\s\\t]*$");
	album = album.replace(rsb, "");
	album = album.replace(rfb, "");
	album = album.replace(rrb, "");
	album = album.replace(stripB, "");
	album = album.replace(stripE, "");
	album = album.replace("  ", " ");
	album = album.replace("\t", " ");
	album = album.toLower();
	QByteArray first_hash = QCryptographicHash::hash(QString(" ").toUtf8(), QCryptographicHash::Md5).toHex();
	QByteArray second_hash = QCryptographicHash::hash(QString(album).toUtf8(), QCryptographicHash::Md5).toHex();
	return QDir::homePath()+QString("/.cache/media-art/album-%1-%2.jpeg").arg(first_hash.constData()).arg(second_hash.constData());
}
