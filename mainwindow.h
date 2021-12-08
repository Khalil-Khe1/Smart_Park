#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "place.h"
#include <QMainWindow>
#include <QSqlTableModel>
#include <QMediaPlayer>
#include <QUrl>
#include <popup.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_valider_2_clicked();

    void on_pushButton_sup_clicked();

    void on_pushButton_recherche_clicked();

    void on_pushButton_modifier_2_clicked();

    void on_pushButton_tri_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_pushButton_clicked();

    void on_pushButton_pdf_clicked();

    void on_pushButton_trib_clicked();

    void on_pushButton_trip_clicked();



    void on_pushButton_update_clicked();

    void on_pushButton_rechercheb_clicked();

    void on_pushButton_recherchep_clicked();

private:
    Ui::MainWindow *ui;
    place ptmp;
    QMediaPlayer *click;
    Popup *popup;
};
#endif // MAINWINDOW_H
