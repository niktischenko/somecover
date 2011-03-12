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

#include "downloader.h"
#include <QtNetwork/QtNetwork>
#include <QUrl>
#include <QFile>
#include <QDebug>

Downloader::Downloader() : QObject (0) {
	_request = "http://someplayer.some-body.ru/cover.php?artist=%1&album=%2";
	manager = new QNetworkAccessManager(this);
	connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(_requestFinished(QNetworkReply*)));
}

void Downloader::download(Entry entry) {
//	qWarning() << "requested for downloading: "<< entry.Artist << entry.Album;
	QString request = _request.arg(entry.Artist).arg(entry.Album);
	manager->get(QNetworkRequest(QUrl(request)));
}

void Downloader::_requestFinished(QNetworkReply *reply) {
	QByteArray data = reply->readAll();
	reply->close();
	reply->deleteLater();
	Entry entry;
	entry.Artist = reply->url().queryItemValue("artist");
	entry.Album = reply->url().queryItemValue("album");
	if (data == QString("").toAscii()) {
		emit failed(entry);
//		qWarning() << "download failed: no such album art";
		return;
	}
	QString file = entry.getCoverPath();
	QFile coverFile(file);
	if (!coverFile.open(QFile::WriteOnly)) {
		emit failed(entry);
//		qWarning() << "failed to save";
		return;
	}
	coverFile.write(data);
	coverFile.close();
	QImage image(file);
	QImage thumb = image.scaled(QSize(80, 80), Qt::KeepAspectRatio);
	QFile thumbFile (entry.getThumbPath());
	if (!thumbFile.open(QFile::WriteOnly)) {
		emit failed(entry);
//		qWarning() << "failed to save thumb";
		return;
	}
	thumb.save(&thumbFile);
	thumbFile.close();
	emit downloaded(entry);
//	qWarning() << "downloaded: "+entry.Album+" ("+entry.Artist+")";
}
