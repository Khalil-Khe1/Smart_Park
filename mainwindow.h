#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"staff.h"
#include"chatstaff.h"
#include"chatwindow.h"
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
    void on_pushButton_ajouter_clicked();
    //void on_tableView_activated(const QModelIndex &index);
    // void on_supprimer_clicked();

    void on_supprimer_clicked();

       void on_modifier_clicked();

   //    void on_listWidget_currentRowChanged(int currentRow);

       void on_tableView_activated(const QModelIndex &index);
      // void on_pushButton_clicked();
       void on_rechercher_clicked();



       void on_employe_currentChanged(int index);

       void on_trie_par_age_clicked();

private:
    Ui::MainWindow *ui;
    staff *Etmp;
};



#endif // MAINWINDOW_H
