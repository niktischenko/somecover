#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QStandardItem>
#include "trackerbackend.h"
#include "downloader.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QList<Entry> _entries;
    QStandardItemModel *_model;
    Downloader *_downloader;
    int _total_to_download;
    QWidget *_help_widget;

    void _map_entries_to_model();

private slots:
    void _download();
    void _downloaded(Entry entry);
    void _failed(Entry entry);
    void _remove_selected();
    void _remove(int row);
    void _clear_selection();
    void _help();
};

#endif // MAINWINDOW_H
