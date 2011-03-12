#ifndef DOWNLOADER_H
#define DOWNLOADER_H
#include "entry.h"
#include <QImage>
#include <QString>
#include <QtNetwork/QNetworkAccessManager>
#include <QUrl>

class Downloader : public QObject{
	Q_OBJECT
public:
	Downloader();
	void download(Entry entry);
private:
	QString _request;
	QNetworkAccessManager *manager;

private slots:
	void _requestFinished(QNetworkReply *reply);

signals:
	void downloaded(Entry);
	void failed(Entry);

};

#endif // DOWNLOADER_H
