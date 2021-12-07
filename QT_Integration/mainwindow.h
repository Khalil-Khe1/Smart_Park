#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "integ.h"
#include <QMainWindow>

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
    void on_login_clicked();

    void on_pb_ajouter_clicked();

    void on_pb_modifier_clicked();

    void on_pb_supp_clicked();

    void on_pb_supp2_clicked();

    void on_pb_QR_code_clicked();

    void on_pb_envoyer_mail_clicked();

    void on_pb_rechercher_clicked();

    void on_tri_par_age_clicked();

    void on_tabWidget_2_currentChanged(int index);

private:
    Ui::MainWindow *ui;
    //integ integ1;
    Client C;
};
#endif // MAINWINDOW_H
