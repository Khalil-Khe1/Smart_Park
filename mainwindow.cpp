#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"staff.h"
#include<QMessageBox>
#include<QSqlTableModel>
#include<QTableView>
 #include <QItemSelectionModel>
#include<QListWidgetItem>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(Etmp->afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_ajouter_clicked()
{
    //recuperation des informtions
    int id=ui->lineEdit_ID->text().toInt();
    //
    QString nom=ui->lineEdit_nom->text();
    QString prenom=ui->lineEdit_prenom->text();
    QString fonction=ui->comboBox->currentText();
    QDate datedenaissance=ui->dateEdit->date();
    staff S(id,nom,prenom,fonction,datedenaissance);

    bool test1=S.ajouter();
    //id=ui->tableView->selectionBehavior();
   // bool test2=S.supprimer(id);
   // bool test2=S.supprimer(ui->tableView->selectionBehavior());
    if (test1) //si requete executée ==>QMessageBox::information
    {
        ui->tableView->setModel(S.afficher());
        QMessageBox::information(nullptr, QObject::tr("ajout"),
                    QObject::tr("ajout avec succes .\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("ajout"),
                    QObject::tr("insert failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}


void MainWindow::on_supprimer_clicked()
{
    //int id =ui->lineEdit_2->text().toInt ;
      int id=ui->lineEdit_ID->text().toInt();
    bool test =Etmp->supprimer(id);
    if (test)
    {    ui->tableView->setModel(Etmp->afficher());
        QMessageBox::information(nullptr, QObject::tr("supprimer"),
                                 QObject::tr("suppression avec succes .\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);

                 }
                 else
                     QMessageBox::critical(nullptr, QObject::tr("supprimer"),
                                 QObject::tr("delete failed.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_modifier_clicked()
{
    staff S ;
  int id=ui->lineEdit_ID->text().toInt();
 QString nom=ui->lineEdit_nom->text();
 QString prenom=ui->lineEdit_prenom->text();
 QString fonction=ui->comboBox->currentText();
 QDate date_naissance=ui->dateEdit->date();
 staff S1(id,nom,prenom,fonction,date_naissance);
 //bool test= S.modifier(id,nom,prenom,fonction,date_naissance);
  bool test;
  test= S1.modifier( id , nom, prenom, fonction, date_naissance);
 if (test)
     //[☺]
    {
     ui->tableView->setModel(S1.afficher());
     QMessageBox::information(nullptr, QObject::tr("MODIFIER"),
                                   QObject::tr("MODIFICATION avec succes .\n"
                                               "Click Cancel to exit."), QMessageBox::Cancel);

     }
                   else
                       QMessageBox::critical(nullptr, QObject::tr("MODIFIER"),
                                   QObject::tr("UPDATE failed.\n"
                                               "Click Cancel to exit."), QMessageBox::Cancel);
 }







//void QAbstractButton::clicked(bool checked = false);


void MainWindow::on_tableView_activated(const QModelIndex &index)
{
    //prendre la valeur de l'indexe et la renvoie en une valeur
    QString val=ui->tableView->model()->data(index).toString();
    //int val1=ui->tableView->model()->data(index).toInt();
    QSqlQuery qry ;


    //qry.prepare("SELECT * from staff where nom='"+val+"'or nom ='"+val+"' or prenom ='"+val+"' or fonction ='"+val+"' or date_naissance ='"+val+"' ");
     qry.prepare("SELECT nom, prenom , id , fonction , date_naissance FROM staff");
    if (qry.exec())
    {


       QMessageBox::information(nullptr, QObject::tr("select"),
                    QObject::tr("selection avec succes .\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("error"),
                    QObject::tr("select failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}





/*
void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{

    QListWidgetItem *it=ui->listWidget->takeItem(mnSelected);
    mnSelected=currentRow;
}

*/







void MainWindow::on_rechercher_clicked()
{
    if(ui->checkBox_id->isChecked()){
    int id=ui->ln_rechercher_id->text().toInt();
    QSqlQueryModel* test=Etmp->rechercher_id(id);
    QMessageBox msgBox;
        if(test){
            msgBox.setText("recherche avec succes");
            ui->tableView->setModel(Etmp->rechercher_id(id));
        }
            else
            msgBox.setText(("client introuvable"));

            msgBox.exec();
    }
    else if(ui->checkBox_nom->isChecked())
    {
       QString nom=ui->ln_recherche_nom->text();
       QSqlQueryModel* test2=Etmp->rechercher_nom(nom);
       QMessageBox msgBox;
           if(test2){
               msgBox.setText("recherche avec succes");
               ui->tableView->setModel(Etmp->rechercher_nom(nom));
           }
               else
               msgBox.setText(("client introuvable"));

               msgBox.exec();
    }
    else if(ui->checkBox_prenom->isChecked())
    {
       QString prenom=ui->ln_chercher_prenom->text();
       QSqlQueryModel* test2=Etmp->rechercher_prenom(prenom);
       QMessageBox msgBox;
           if(test2){
               msgBox.setText("recherche avec succes");
               ui->tableView->setModel(Etmp->rechercher_prenom(prenom));
           }
               else
               msgBox.setText(("client introuvable"));

               msgBox.exec();
    }
    else if((ui->checkBox_prenom->isChecked())&&(ui->checkBox_nom->isChecked()))
    {
        QString nom=ui->ln_recherche_nom->text();
       QString prenom=ui->ln_chercher_prenom->text();
       QSqlQueryModel* test2=Etmp->rechercher_nomprenom(nom, prenom);
       QMessageBox msgBox;
           if(test2){
               msgBox.setText("recherche avec succes");
               ui->tableView->setModel(Etmp->rechercher_nomprenom(nom, prenom));
           }
               else
               msgBox.setText(("client introuvable"));

               msgBox.exec();
    }
    else if((ui->checkBox_id->isChecked())&&(ui->checkBox_nom->isChecked()))
    {
        QString nom=ui->ln_recherche_nom->text();
       int id=ui->ln_rechercher_id->text().toInt();
       QSqlQueryModel* test2=Etmp->rechercher_nomid(nom, id);
       QMessageBox msgBox;
           if(test2){
               msgBox.setText("recherche avec succes");
               ui->tableView->setModel(Etmp->rechercher_nomid(nom, id));
           }
               else
               msgBox.setText(("client introuvable"));

               msgBox.exec();
    }
    else if((ui->checkBox_id->isChecked())&&(ui->checkBox_prenom->isChecked()))
    {
        QString prenom=ui->ln_chercher_prenom->text();
       int id=ui->ln_rechercher_id->text().toInt();
       QSqlQueryModel* test2=Etmp->rechercher_prenomid(prenom, id);
       QMessageBox msgBox;
           if(test2){
               msgBox.setText("recherche avec succes");
               ui->tableView->setModel(Etmp->rechercher_prenomid(prenom, id));
           }
               else
               msgBox.setText(("client introuvable"));

               msgBox.exec();
    }
    else if((ui->checkBox_id->isChecked())&&(ui->checkBox_prenom->isChecked())&&(ui->checkBox_nom->isChecked()))
    {
        QString nom=ui->ln_recherche_nom->text();
        QString prenom=ui->ln_chercher_prenom->text();
       int id=ui->ln_rechercher_id->text().toInt();
       QSqlQueryModel* test2=Etmp->rechercher_prenom_id_nom(prenom, id,nom);
       QMessageBox msgBox;
           if(test2){
               msgBox.setText("recherche avec succes");
               ui->tableView->setModel(Etmp->rechercher_prenom_id_nom(prenom, id,nom));
           }
               else
               msgBox.setText(("staff introuvable"));

               msgBox.exec();
    }
}



void MainWindow::on_employe_currentChanged(int index)
{
            QTextCharFormat f=ui->calendarWidget->weekdayTextFormat(Qt::Saturday);

                    Etmp->calendrier(f,ui->calendarWidget);

            Etmp->statistiques(ui->widget_2);
}

void MainWindow::on_trie_par_age_clicked()
{
    QSqlQueryModel* test=Etmp->triparAge();
    QMessageBox msgBox;
        if(test){
            msgBox.setText("tri avec succes");
            ui->tableView->setModel(Etmp->triparAge());
        }
            else
            msgBox.setText(("echec"));

            msgBox.exec();
}
