#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "jeux.h"
#include "Arduino.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_butAjouter_clicked();

    void on_butSupprimer_clicked();

    void on_butModifier_clicked();

    void on_Search_clicked();

    void on_butTrier_clicked();

    void on_tableView_2_clicked(const QModelIndex &index);

    void on_butUsage_clicked();

    void on_pushMaintenir_clicked();

    void on_tableView_3_clicked(const QModelIndex &index);

    void on_VerifID_clicked();

    void on_num_0_clicked();

    void on_num_clicked();

    void on_num_2_clicked();

    void on_num_3_clicked();

    void on_num_5_clicked();

    void on_num_4_clicked();

    void on_num_6_clicked();

    void on_num_7_clicked();

    void on_num_8_clicked();

    void on_num_9_clicked();

    void on_num_10_clicked();

private:
    Ui::MainWindow *ui;
    JEUX Jtmp;
    Arduino A;
};

#endif // MAINWINDOW_H
