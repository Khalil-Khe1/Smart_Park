#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "jeux.h"
#include <string>
#include <ctime>
#include <qpixmap.h>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include "Arduino.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Setup Arduino
    int ret = A.connect_arduino();
    switch(ret){
        case 0:
            qDebug() << "Arduino is available and connected to: " << A.getarduino_port_name();
            break;
        case 1:
            qDebug() << "Arduino is available but not connected to: " << A.getarduino_port_name();
            break;
        case -1:
            qDebug() << "Arduino is not available." ;
    }
    QObject::connect(A.getserial(), SIGNAL(readyRead()), this, SLOT(update_label()));

    //Setup Tables
    ui->tableView->setModel(Jtmp.Afficher());
    ui->tableView_2->setModel(Jtmp.AfficherNom());
    ui->tableView_3->setModel(Jtmp.AfficherNom());
    QPixmap Map ("C:/Users/ASUS/Desktop/QT_Khalil/Atelier_Connexion/Images/Map.PNG");
    ui->image->setPixmap(Map);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_butAjouter_clicked()
{
    /*std::time_t t = std::time(nullptr);
    std::tm *const t_info = std::localtime(&t);
    QString year = (QString) 1900 + t_info->tm_year;
    QStringRef year2(&year, 2, 2);*/
    QString id = Jtmp.ConvTracker() + "JX21";
    //QString id= ui->lineID->text();
    QString etat = ui->BoxEtat->currentText();
    QString type = ui->BoxType->currentText();
    int ticket = ui->linePrix->text().toInt();
    int um = ui->lineUsage->text().toInt();
    int x = ui->lineCoordX->text().toInt();
    int y = ui->lineCoordY->text().toInt();
    QString nom = ui->lineNom->text();
    QString img = ui->lineIMG->text();

    JEUX J(id, etat, type, ticket, um, 0, x, y, nom, img);

    bool test = J.Ajouter();
    if(test)
        {
            QMessageBox::information(nullptr, QObject::tr("database is open"),
                        QObject::tr("Ajout avec succés.\nClick Cancel to exit."), QMessageBox::Ok);

    }
        else
           { QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                        QObject::tr("Ajout échoué.\nClick Cancel to exit."), QMessageBox::Ok);
    }
    ui->tableView->setModel(Jtmp.Afficher());
}

void MainWindow::on_butSupprimer_clicked()
{
    QString id_del=ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toString();

    bool supp = Jtmp.Supprimer(id_del);

    if(supp)
        {
            QMessageBox::information(nullptr, QObject::tr("database is open"),
                        QObject::tr("Suppression avec succés.\n"
                                    "Click Cancel to exit."), QMessageBox::Ok);

    }
        else
           { QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                        QObject::tr("Suppression échoué.\n"
                                    "Click Cancel to exit."), QMessageBox::Ok);
    }
    ui->tableView->setModel(Jtmp.Afficher());
}

void MainWindow::on_butModifier_clicked()
{
    QString id_mod=ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toString();
    QString etat = ui->BoxEtat->currentText();
    QString type = ui->BoxType->currentText();
    int ticket = ui->linePrix->text().toInt();
    int um = ui->lineUsage->text().toInt();
    int x = ui->lineCoordX->text().toInt();
    int y = ui->lineCoordY->text().toInt();
    QString nom = ui->lineNom->text();
    QString img = ui->lineIMG->text();

    JEUX J(id_mod, etat, type, ticket, um, 0, x, y, nom, img);

    bool test = J.Modifier(id_mod);

    if(test)
        {
            QMessageBox::information(nullptr, QObject::tr("database is open"),
                        QObject::tr("Modification avec succés.\n"
                                    "Click Cancel to exit."), QMessageBox::Ok);

    }
        else
           { QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                        QObject::tr("Modification échoué.\n"
                                    "Click Cancel to exit."), QMessageBox::Ok);
    }
    ui->tableView->setModel(Jtmp.Afficher());
}

void MainWindow::on_Search_clicked()
{
    if((ui->comboBox->currentText() == "")||(ui->lineRechercher->text() == "")){
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                                QObject::tr("Veuillez selectez une paramètre.\n"), QMessageBox::Ok);
    }
    else {
        ui->tableView->setModel(Jtmp.Rechercher(ui->lineRechercher->text(), ui->comboBox->currentIndex()));
    }
}

void MainWindow::on_butTrier_clicked()
{
    ui->tableView->setModel(Jtmp.Tri(ui->comboBox_2->currentIndex(), ui->comboBox_3->currentIndex()));
}

void MainWindow::on_tableView_2_clicked(const QModelIndex &index)
{
    QString tab[8] = {"NOM", "ID", "PRIX", "TYPE", "ETAT", "USAGE_TOT", "USAGE_MAINTENANCE", "IMAGE"};
    QString fields[8] = {"labelNom", "labelID", "labelPrix", "labelType", "labelEtat", "labelUT", "labelUM"};
    QString indexNom = ui->tableView_2->model()->data(ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),0)).toString();
    QSqlQuery query;
    bool test = false;
    query.prepare("SELECT * FROM JEUX");
    query.exec();
    while(!test){
        query.next();
        if(query.value(7).toString() == indexNom){
            test = true;
        }
    }

    ui->labelNom->setText(query.value(7).toString());
    ui->labelID->setText(query.value(0).toString());
    ui->labelPrix->setText(query.value(2).toString());
    ui->labelType->setText(query.value(8).toString());
    ui->labelEtat->setText(query.value(1).toString());
    ui->labelUM->setText(query.value(4).toString());
    ui->labelUT->setText(query.value(3).toString());
    QPixmap Map (query.value(9).toString());

    ui->imgJeux->setPixmap(Map);
    ui->imgJeux->setScaledContents( true );
    ui->imgJeux->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    //GetEveryColumn

    /*for(int i = 0; i < 8; i++){
        QLabel * label = findChild<QLabel*>(fields[i]);
        label->setText(Jtmp.AfficherImage(tab[i], indexNom));
    }*/

}

void MainWindow::on_butUsage_clicked()
{
    QString tab[8] = {"NOM", "ID", "PRIX", "TYPE", "ETAT", "USAGE_TOT", "USAGE_MAINTENANCE", "IMAGE"};
    QString fields[8] = {"labelNom", "labelID", "labelPrix", "labelType", "labelEtat", "labelUT", "labelUM"};
    QString indexNom = ui->tableView_2->model()->data(ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),0)).toString();

    QSqlQuery query;
    bool test = false;
    query.prepare("SELECT * FROM JEUX");
    query.exec();
    while(!test){
        query.next();
        if(query.value(7).toString() == indexNom){
            test = true;
        }
    }

    int UM = query.value(4).toInt();
    int UT = query.value(3).toInt();

    int use = ui->spinUse->value();
    if(Jtmp.Jouer(indexNom, UM, UT, use)){
            QMessageBox::information(nullptr, QObject::tr("database is open"),
                        QObject::tr("Modification avec succés.\n"
                                    "Click Cancel to exit."), QMessageBox::Ok);

    }
        else
           { QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                        QObject::tr("Modification échoué.\n"
                                    "Click Cancel to exit."), QMessageBox::Ok);
    }

}

void MainWindow::on_pushMaintenir_clicked()
{
    QString indexNom = ui->tableView_2->model()->data(ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),0)).toString();
    if(Jtmp.Maintenir(indexNom)){
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("Modification avec succés.\n"
                                "Click Cancel to exit."), QMessageBox::Ok);
    }
    else
       { QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("Modification échoué.\n"
                                "Click Cancel to exit."), QMessageBox::Ok);
}
}

void MainWindow::on_tableView_3_clicked(const QModelIndex &index)
{
    QString indexNom = ui->tableView_3->model()->data(ui->tableView_3->model()->index(ui->tableView_3->currentIndex().row(),0)).toString();
    QSqlQuery query;
    bool test = false;
    query.prepare("SELECT * FROM JEUX");
    query.exec();
    while(!test){
        query.next();
        if(query.value(7).toString() == indexNom){
            test = true;
        }
    }

    int x = query.value(5).toInt();
    int y = query.value(6).toInt();
     QPixmap pin("C:/Users/ASUS/Desktop/QT_Khalil/Atelier_Connexion/Images/Pin.PNG");
     ui->labelPin->setPixmap(pin);
     ui->labelPin->setScaledContents( true );
     ui->labelPin->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
     ui->labelPin->setGeometry(x, y, 50, 50
                               );


}

void MainWindow::on_VerifID_clicked()
{
    QString str;
    QByteArray data;
    data = (QByteArray) "*";
    A.write_to_arduino(data);
    if(A.Access()){
       data = (QByteArray) "Access Granted";

    }
    else{
       data = (QByteArray) "Access Denied";
    }
    A.code = "";
    A.write_to_arduino(data);
}

void MainWindow::on_num_0_clicked()
{
    QByteArray data;
    data = (QByteArray) "0";
    A.write_to_arduino(data);
    A.code = A.code + "0";
}

void MainWindow::on_num_clicked()
{
    QByteArray data;
    data = (QByteArray) "1";
    A.write_to_arduino(data);
    A.code = A.code + "1";
}

void MainWindow::on_num_2_clicked()
{
    QByteArray data;
    data = (QByteArray) "2";
    A.write_to_arduino(data);
    A.code = A.code + "2";
}

void MainWindow::on_num_3_clicked()
{
    QByteArray data;
    data = (QByteArray) "3";
    A.write_to_arduino(data);
    A.code = A.code + "3";
}

void MainWindow::on_num_5_clicked()
{
    QByteArray data;
    data = (QByteArray) "4";
    A.write_to_arduino(data);
    A.code = A.code + "4";
}

void MainWindow::on_num_4_clicked()
{
    QByteArray data;
    data = (QByteArray) "5";
    A.write_to_arduino(data);
    A.code = A.code + "5";
}

void MainWindow::on_num_6_clicked()
{
    QByteArray data;
    data = (QByteArray) "6";
    A.write_to_arduino(data);
    A.code = A.code + "6";
}

void MainWindow::on_num_7_clicked()
{
    QByteArray data;
    data = (QByteArray) "7";
    A.write_to_arduino(data);
    A.code = A.code + "7";
}

void MainWindow::on_num_8_clicked()
{
    QByteArray data;
    data = (QByteArray) "8";
    A.write_to_arduino(data);
    A.code = A.code + "8";
}

void MainWindow::on_num_9_clicked()
{
    QByteArray data;
    data = (QByteArray) "9";
    A.write_to_arduino(data);
    A.code = A.code + "9";
}

void MainWindow::on_num_10_clicked()
{
    QByteArray data;
    data = (QByteArray) "*";
    A.write_to_arduino(data);
    A.code = "";
}
