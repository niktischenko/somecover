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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "trackerbackend.h"
#include <QModelIndexList>
#include <QModelIndex>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
		QMainWindow(parent),
		ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	TrackerBackend tracker;
	_entries = tracker.getEntries();
	_model = new QStandardItemModel(this);
	_model->setColumnCount(2);
	ui->tableView->setModel(_model);
	_map_entries_to_model();
	_downloader = new Downloader();
	_total_to_download = 0;
	connect (ui->downloadButton, SIGNAL(clicked()), this, SLOT(_download()));
	connect (_downloader, SIGNAL(downloaded(Entry)), this, SLOT(_downloaded(Entry)));
	connect (_downloader, SIGNAL(failed(Entry)), this, SLOT(_failed(Entry)));
	connect (ui->cancelButton, SIGNAL(clicked()), this, SLOT(_remove_selected()));
	connect (ui->actionClear, SIGNAL(triggered()), this, SLOT(_clear_selection()));
	connect (ui->actionHelp, SIGNAL(triggered()), this, SLOT(_help()));
	ui->progressBar->hide();

	QDir dir;
	dir.mkdir(QDir::homePath()+"/.covers");
	dir.mkdir(QDir::homePath()+"/.covers/.thumbs");
	setAttribute(Qt::WA_Maemo5AutoOrientation);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::_map_entries_to_model() {
	int row = 0;
	_model->setRowCount(_entries.count());
	foreach (Entry entry, _entries) {
		QIcon icon;
		QString coverpath = entry.getThumbPath();
		QFile file(coverpath);
		if (!file.exists()) {
			icon = QIcon(":/images/defaultcover.png");
		} else {
			icon.addFile(coverpath);
		}
		_model->setItem(row, 0, new QStandardItem(icon, ""));
		_model->setItem(row++, 1, new QStandardItem(QString("%1 (%2)").arg(entry.Album).arg(entry.Artist)));
	}
}

void MainWindow::_download() {
	_total_to_download = 0;
	foreach (Entry entry, _entries) {
		QFile file (entry.getCoverPath());
		if (!file.exists()) {
			_downloader->download(entry);
			_total_to_download++;
		}
	}
	ui->progressBar->setValue(0);
	ui->progressBar->show();
	ui->progressBar->setMaximum(_total_to_download);
}

void MainWindow::_downloaded(Entry entry) {
//	qWarning() << "DOWNLOADED: " << entry.Album << entry.Artist;
	int index = _entries.indexOf(entry);
	_model->setItem(index, 0, new QStandardItem(QIcon(entry.getThumbPath()), ""));
	ui->tableView->repaint();
	ui->progressBar->setValue(ui->progressBar->value()+1);
	if (ui->progressBar->value() == _total_to_download) {
		ui->progressBar->hide();
	}
}

void MainWindow::_failed(Entry entry) {
	qWarning() << "FAILED: " << entry.Album << entry.Artist;
	ui->progressBar->setValue(ui->progressBar->value()+1);
	if (ui->progressBar->value() == _total_to_download) {
		ui->progressBar->hide();
	}
}

void MainWindow::_remove(int row) {
	Entry entry = _entries.at(row);
	_model->setItem(row, 0, new QStandardItem(QIcon(":/images/defaultcover.png"), ""));
	QFile::remove(entry.getCoverPath());
	QFile::remove(entry.getThumbPath());
}

void MainWindow::_remove_selected() {
	QModelIndexList selected = ui->tableView->selectionModel()->selectedIndexes();
	ui->tableView->selectionModel()->clearSelection();
	foreach (QModelIndex id, selected) {
		_remove(id.row());
	}
}

void MainWindow::_clear_selection() {
	ui->tableView->selectionModel()->clearSelection();
}

void MainWindow::_help() {
	QMessageBox::information(this, tr("Help"), tr("Album art downloader for SomePlayer and TPlayer. v.1.0\n"
				      "Author: Nikolay Tischenko (somebody)\n\n"
				      "This manager uses LastFM API to get album art for your music.\n"
				      "It stores downloaded files in ~/.covers directory.\n"
				      "Also in ~/.covers/.thumbs stored 80x80 thumbnails of downloaded art"));
}
