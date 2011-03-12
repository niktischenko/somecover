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
		if (!entry.Album.isEmpty() && !entry.Artist.isEmpty()) {
			if (!entries.contains(entry)) {
				entries.append(entry);
			}
		}
	}
	return entries;
}
