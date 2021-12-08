#include "mainwindow.h"
#include "connexion.h"
#include <QApplication>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QSqlTableModel>
#include <QUrl>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    connexion c;

    bool test=c.createconnexion();
    MainWindow w;
    if(test)
    {w.show();
        QMessageBox::information(nullptr,QObject::tr("database is open"),
                              QObject::tr("connection successful.\n"
                                          "click cancel to exit."),QMessageBox::Cancel);

    }
    else
         QMessageBox::critical(nullptr,QObject::tr("database is not open"),
                              QObject::tr("connection failed.\n"
                                          "click cancel to exit."),QMessageBox::Cancel);

    return a.exec();
}
