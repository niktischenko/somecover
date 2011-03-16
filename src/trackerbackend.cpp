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

#include "trackerbackend.h"
#include <QDebug>

TrackerBackend::TrackerBackend(QObject *parent) :
		QObject(parent)
{
}

Q_DECLARE_METATYPE(QList<QStringList>)

QList<Entry> TrackerBackend::getEntries() {
	QList<Entry> entries;
	qDBusRegisterMetaType<QList<QStringList> > ();
	QDBusInterface iface ("org.freedesktop.Tracker",
			      "/org/freedesktop/Tracker/Metadata",
			      "org.freedesktop.Tracker.Metadata");
	QList<QVariant> arguments;
	QStringList fields;
	fields << "Audio:Album" << "Audio:Artist";
	arguments << "Music" << fields << "" << false << 0 << 32000;
	QDBusReply <QList<QStringList> > reply = iface.callWithArgumentList(QDBus::AutoDetect, "GetUniqueValues", arguments);;
	QList<QStringList> pairs = reply.value();
	foreach (QStringList pair, pairs) {
		Entry entry;
		entry.Artist = pair.at(1);
		entry.Album = pair.at(0);
		entry.Artist.replace("&", "");
		entry.Album.replace("&", "");
		entry.Album = entry.Album.trimmed();
		entry.Artist = entry.Artist.trimmed();
		if (!entry.Album.isEmpty() && !entry.Artist.isEmpty()) {
			if (!entries.contains(entry)) {
				entries.append(entry);
			}
		}
	}
	return entries;
}
