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


#ifndef DOWNLOADER_H
#define DOWNLOADER_H
#include "entry.h"
#include <QImage>
#include <QString>
#include <QtNetwork/QNetworkAccessManager>
#include <QUrl>

#define AUTH_KEY "78b9d09661da64f0bc6c146c524bae4a"

class Downloader : public QObject{
	Q_OBJECT
public:
	Downloader();
	void download(Entry entry);
private:
	QString _request;
	QNetworkAccessManager *manager;
	void _prepare_image(QString file, QString content_type);

private slots:
	void _requestFinished(QNetworkReply *reply);

signals:
	void downloaded(Entry);
	void failed(Entry);

};

#endif // DOWNLOADER_H
