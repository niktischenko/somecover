#ifndef TRACKERBACKEND_H
#define TRACKERBACKEND_H

#include <QObject>
#include <QtDBus/QtDBus>
#include "entry.h"


class TrackerBackend : public QObject
{
	Q_OBJECT
public:
	explicit TrackerBackend(QObject *parent = 0);

signals:

public slots:
	QList<Entry> getEntries();

};

#endif // TRACKERBACKEND_H
