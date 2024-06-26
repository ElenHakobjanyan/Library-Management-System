#ifndef BOOKWINDOW_H
#define BOOKWINDOW_H

#include <QtWidgets>
#include <QtSql>

#include "ui_bookwindow.h"


class BookWindow: public QMainWindow
{
    Q_OBJECT
public:
    BookWindow();

private slots:
    void about();

    void on_editModeCheckBox_clicked(bool checked);

private:
    void showError(const QSqlError &err);
    Ui::BookWindow ui;
    QSqlRelationalTableModel *model;
    int authorIdx, genreIdx;

    void createMenuBar();
};

#endif
