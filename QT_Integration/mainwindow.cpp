#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include "QRcode.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QRegExpValidator>
#include "smtp.h"

//Jaw
#include <QPlainTextEdit>
#include <QPrinter>
#include <QPrinterInfo>
#include <QPrintDialog>
#include <QTextStream>
#include <QPainter>
#include <QTextStream>
#include "qcustomplot.h"
#include <QFileDialog>
#include <QTextDocument>
#include <QtPrintSupport/QPrinter>
#include <QFileDialog>
#include <QDialog>
#include<QLineEdit>

#include <QMessageBox>
#include <QIntValidator>
#include <QRegExpValidator>
#include "smtp.h"

#include <QSqlTableModel>
#include <QUrl>
#include <QTableView>
#include <QAbstractItemView>

#include <QSystemTrayIcon>
#include <QDialog>
#include <QTcpSocket>
#include <QFile>
#include<QTextStream>

//Khalil
#include "jeux.h"
#include <string>
#include <ctime>
#include <qpixmap.h>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

//Yahya
#include "menu.h"
#include "connection.h"
#include <QString>
#include<QMessageBox>
#include <iostream>
#include <QTabWidget>
#include<QIntValidator>
#include <QDateEdit>
#include <QPlainTextEdit>
#include <QPrinter>
#include <QPrinterInfo>
#include <QPrintDialog>
#include <QTextStream>
#include <QPainter>
#include <QTextStream>
#include <QFileDialog>
#include <QTextDocument>
#include <QtPrintSupport/QPrinter>
#include <QFileDialog>
#include <QTextDocument>
#include <QMediaPlayer>
#include <strstream>
#include <QSystemTrayIcon>
#include <QRegExpValidator>
#include <QDesktopServices>
#include <QUrl>
#include"smtpYahya.h"
#include"qcustomplot.h"

//Mariem
#include"staff.h"
#include<QMessageBox>
#include<QSqlTableModel>
#include<QTableView>
 #include <QItemSelectionModel>
#include<QListWidgetItem>

//Nour
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "place.h"
#include <QtDebug>
#include <QMessageBox>
#include <QTableView>
#include <QAbstractItemView>
#include <QMediaPlayer>
#include <QSqlTableModel>
#include <QUrl>
#include <QIntValidator>
#include <QPainter>
#include "qcustomplot.h"
#include "exportexcelobject.h"
#include "popup.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_login_clicked()
{
    QString username= ui->lineEdit_username->text();
            QString password= ui->lineEdit_password->text();

    //Init Jawher
    ui->le_CIN->setValidator(new QIntValidator(0 , 9999999, this));
    ui->tab_client->setModel(C.afficher());
    ui->le_Age->setValidator(new QIntValidator(0 , 99, this));
    #define NOM_RX "^([a-z]+[,.]?[ ]?|[a-z]+['-]?)+$"
    QRegExp rxNom(NOM_RX);
    QRegExpValidator*valiNom= new QRegExpValidator(rxNom,this);

    #define addr "^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$"
    QRegExp r(addr);
    QRegExpValidator*valiadd= new QRegExpValidator(r,this);


    ui->le_NOM->setValidator(valiNom);
    ui->le_Prenom->setValidator(valiNom);
    ui->le_Adresse_mail->setValidator(valiadd);
    ui->ln_envoyermail_to->setValidator(valiadd);
    ui->ln_rechercher_id->setValidator(new QIntValidator(0 , 9999999, this));
    ui->ln_recherche_nom->setValidator(valiNom);
    ui->ln_chercher_prenom->setValidator(valiNom);

    //Init Khalil
    ui->tableViewk->setModel(Jtmp.Afficher());
    ui->tableView2k->setModel(Jtmp.AfficherNom());
    ui->tableView3k->setModel(Jtmp.AfficherNom());
    QPixmap Map ("C:/Users/ASUS/Desktop/QT_Khalil/Atelier_Connexion/Images/Map.PNG");
    ui->image->setPixmap(Map);

    //Init Yahya
    ui->menus->setModel((tmpmenu.afficher()));
    ui->prix->setValidator(new QIntValidator(0,9999999,this));

    //Init Mariem
    ui->tableMariem->setModel(Etmp.afficher());

    //Init Nour
    ui->tableView_2->setModel(ptmp.afficher());
    ui->lineEdit_num_3->setValidator(new QIntValidator(0,99,this));
    popup = new Popup;



           setGeometry(QStyle::alignedRect(
                           Qt::RightToLeft,
                           Qt::AlignCenter,
                           size(),
                           qApp->desktop()->availableGeometry()));

        if ( username != "" && password != "" )
        {
            if((username == "khalil")&&(password == "khalil")){
                QMessageBox::information(this,"Login","Username and Password are correct ");
                ui->stackedWidget->setCurrentIndex(2);
            }
            else if((username == "jawher")&&(password == "jawher")){
                QMessageBox::information(this,"Login","Username and Password are correct ");
                ui->stackedWidget->setCurrentIndex(1);
            }
            else if((username == "nour")&&(password == "nour")){
                QMessageBox::information(this,"Login","Username and Password are correct ");
                ui->stackedWidget->setCurrentIndex(3);
            }
            else if((username == "mariem")&&(password == "mariem")){
                QMessageBox::information(this,"Login","Username and Password are correct ");
                ui->stackedWidget->setCurrentIndex(5);
            }
            else if((username == "yahya")&&(password == "yahya")){
                QMessageBox::information(this,"Login","Username and Password are correct ");
                ui->stackedWidget->setCurrentIndex(4);
            }
            else
            {
               QMessageBox::warning(this,"Login","Username and Password is not correct ");

            }
        }
}


//Gestion Clients - Jawher
void MainWindow::on_pb_ajouter_clicked()
{
    int id=ui->le_CIN->text().toInt();
        QString n=ui->le_NOM->text();
        QString p=ui->le_Prenom->text();
        QString A=ui->le_Adresse_mail->text();
        int a=ui->le_Age->text().toInt();

        Client C(id,n,p,A,a);
        bool test=C.ajouter();


                if (test)
                {


                    QMessageBox::information(nullptr, QObject::tr("Ajout produit"),
                                QObject::tr("client ajouté.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);
                            ui->tab_client->setModel(C.afficher());


                }

                else
                {
                    QMessageBox::critical(nullptr, QObject::tr("Ajout produit"),
                                QObject::tr("ajout echoué.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);
                }
}

void MainWindow::on_pb_modifier_clicked()
{
    int id=ui->le_CIN->text().toInt();
        QString n=ui->le_NOM->text();
        QString p=ui->le_Prenom->text();
        QString A=ui->le_Adresse_mail->text();
        int a=ui->le_Age->text().toInt();

        Client C(id,n,p,A,a);
        bool test=C.modifier();

            QMessageBox msgBox;
                if(test){
                    msgBox.setText("modification avec succes");
                    ui->tab_client->setModel(C.afficher());
                }
                    else
                    msgBox.setText(("echec de modification"));

                    msgBox.exec();
}

void MainWindow::on_pb_supp_clicked()
{
    Client C1;
        C1.set_id(ui->le_CIN_supp->text().toInt());
        bool test=C1.supprimer(C1.get_id());
        QMessageBox msgBox;
            if(test){
                msgBox.setText("suppresion avec succes");
                ui->tab_client->setModel(C.afficher());
            }
                else
                msgBox.setText(("echec de suppresion"));

                msgBox.exec();
}

void MainWindow::on_pb_supp2_clicked()
{
    Client C1;
        C1.set_nom(ui->ln_supp2->text());
        bool test=C1.supprimer2(C1.get_nom());
        QMessageBox msgBox;
            if(test){
                msgBox.setText("suppresion avec succes");
                ui->tab_client->setModel(C.afficher());
            }
                else
                msgBox.setText(("echec de suppresion"));

                msgBox.exec();
}



void MainWindow::on_pb_QR_code_clicked()
{
    /*int tabeq=ui->tab_client->currentIndex().row();
                    QVariant idd=ui->tab_client->model()->data(ui->tab_client->model()->index(tabeq,0));
                    QString idC= idd.toString();
                    QSqlQuery qry;
                    qry.prepare("select * from Gestion_client where idC=:idC");
                    qry.bindValue(":idC",idC);
                    qry.exec();
                    QString nom, prenom ,Adresse_mail,ide;
                    int Age;
                    while(qry.next()){
                        nom=qry.value(1).toString();
                        prenom=qry.value(2).toString();
                        Adresse_mail=qry.value(3).toString();

                    }
                    ide=QString(idC);
                    ide="idC: "+ide+" nom: "+nom+" prenom: "+prenom+" Adresse_mail: "+Adresse_mail+" Age: "+Age;
                    QrCode qr = QrCode::encodeText(ide.toUtf8().constData(), QrCode::Ecc::HIGH);

                    // Read the black & white pixels
                    QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
                    for (int y = 0; y < qr.getSize(); y++) {
                        for (int x = 0; x < qr.getSize(); x++) {
                            int color = qr.getModule(x, y);  // 0 for white, 1 for black

                            // You need to modify this part
                            if(color==0)
                                im.setPixel(x, y,qRgb(254, 254, 254));
                            else
                                im.setPixel(x, y,qRgb(0, 0, 0));
                        }
                    }
                    im=im.scaled(200,200);
                    ui->qrlabel->setPixmap(QPixmap::fromImage(im));
                    int i=0 ;
                    for(i=0;i<100;i=i+0.1){
                        i++;
                        ui->progressBar->setValue(i);
                    }*/
}

void MainWindow::on_pb_envoyer_mail_clicked()
{
    Smtp* smtp = new Smtp("jaouher.jaziri@esprit.tn", "201JMT4266", "smtp.gmail.com", 465);
     connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
     smtp->sendMail("jaouher.jaziri@esprit.com", ui->ln_envoyermail_to->text() , ui->ln_envoyermail_subject->text(),ui->plainTextEdit_email->toPlainText());
}

void MainWindow::on_pb_rechercher_clicked()
{
    if(ui->checkBox_id->isChecked()){
        int id=ui->ln_rechercher_id->text().toInt();
        QSqlQueryModel* test=C.rechercher_id(id);
        QMessageBox msgBox;
            if(test){
                msgBox.setText("recherche avec succes");
                ui->tab_client->setModel(C.rechercher_id(id));
            }
                else
                msgBox.setText(("client introuvable"));

                msgBox.exec();
        }
        else if(ui->checkBox_nom->isChecked())
        {
           QString nom=ui->ln_recherche_nom->text();
           QSqlQueryModel* test2=C.rechercher_nom(nom);
           QMessageBox msgBox;
               if(test2){
                   msgBox.setText("recherche avec succes");
                   ui->tab_client->setModel(C.rechercher_nom(nom));
               }
                   else
                   msgBox.setText(("client introuvable"));

                   msgBox.exec();
        }
        else if(ui->checkBox_prenom->isChecked())
        {
           QString prenom=ui->ln_chercher_prenom->text();
           QSqlQueryModel* test2=C.rechercher_prenom(prenom);
           QMessageBox msgBox;
               if(test2){
                   msgBox.setText("recherche avec succes");
                   ui->tab_client->setModel(C.rechercher_prenom(prenom));
               }
                   else
                   msgBox.setText(("client introuvable"));

                   msgBox.exec();
        }
        else if((ui->checkBox_prenom->isChecked())&&(ui->checkBox_nom->isChecked()))
        {
            QString nom=ui->ln_recherche_nom->text();
           QString prenom=ui->ln_chercher_prenom->text();
           QSqlQueryModel* test2=C.rechercher_nomprenom(nom, prenom);
           QMessageBox msgBox;
               if(test2){
                   msgBox.setText("recherche avec succes");
                   ui->tab_client->setModel(C.rechercher_nomprenom(nom, prenom));
               }
                   else
                   msgBox.setText(("client introuvable"));

                   msgBox.exec();
        }
        else if((ui->checkBox_id->isChecked())&&(ui->checkBox_nom->isChecked()))
        {
            QString nom=ui->ln_recherche_nom->text();
           int id=ui->ln_rechercher_id->text().toInt();
           QSqlQueryModel* test2=C.rechercher_nomid(nom, id);
           QMessageBox msgBox;
               if(test2){
                   msgBox.setText("recherche avec succes");
                   ui->tab_client->setModel(C.rechercher_nomid(nom, id));
               }
                   else
                   msgBox.setText(("client introuvable"));

                   msgBox.exec();
        }
        else if((ui->checkBox_id->isChecked())&&(ui->checkBox_prenom->isChecked()))
        {
            QString prenom=ui->ln_chercher_prenom->text();
           int id=ui->ln_rechercher_id->text().toInt();
           QSqlQueryModel* test2=C.rechercher_prenomid(prenom, id);
           QMessageBox msgBox;
               if(test2){
                   msgBox.setText("recherche avec succes");
                   ui->tab_client->setModel(C.rechercher_prenomid(prenom, id));
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
           QSqlQueryModel* test2=C.rechercher_prenom_id_nom(prenom, id,nom);
           QMessageBox msgBox;
               if(test2){
                   msgBox.setText("recherche avec succes");
                   ui->tab_client->setModel(C.rechercher_prenom_id_nom(prenom, id,nom));
               }
                   else
                   msgBox.setText(("client introuvable"));

                   msgBox.exec();
        }
}



void MainWindow::on_tri_par_age_clicked()
{
    QString choix=ui->comboBox->currentText();
        if(choix=="Tri par age croissante"){
        QSqlQueryModel* test=C.triparAge();
        QMessageBox msgBox;
            if(test){
                msgBox.setText("tri avec succes");
                ui->tab_client->setModel(C.triparAge());
            }
                else
                msgBox.setText(("echec"));

                msgBox.exec();
        }
        else if(choix=="Tri par nom croissante")
        {
            QSqlQueryModel* test=C.triparNom();
            QMessageBox msgBox;
                if(test){
                    msgBox.setText("tri avec succes");
                    ui->tab_client->setModel(C.triparNom());
                }
                    else
                    msgBox.setText(("echec"));

                    msgBox.exec();
        }
        else if(choix=="Tri par prenom croissante")
        {
            QSqlQueryModel* test=C.triparPrenom();
            QMessageBox msgBox;
                if(test){
                    msgBox.setText("tri avec succes");
                    ui->tab_client->setModel(C.triparPrenom());
                }
                    else
                    msgBox.setText(("echec"));

                    msgBox.exec();
        }
        else if(choix=="Tri par age decroissante")
        {
            QSqlQueryModel* test=C.triparAgeD();
            QMessageBox msgBox;
                if(test){
                    msgBox.setText("tri avec succes");
                    ui->tab_client->setModel(C.triparAgeD());
                }
                    else
                    msgBox.setText(("echec"));

                    msgBox.exec();
        }
        else if(choix=="Tri par nom decroissante")
        {
            QSqlQueryModel* test=C.triparnomD();
            QMessageBox msgBox;
                if(test){
                    msgBox.setText("tri avec succes");
                    ui->tab_client->setModel(C.triparnomD());
                }
                    else
                    msgBox.setText(("echec"));

                    msgBox.exec();
        }
        else if(choix=="Tri par prenom decroissante")
        {
            QSqlQueryModel* test=C.triparPrenomD();
            QMessageBox msgBox;
                if(test){
                    msgBox.setText("tri avec succes");
                    ui->tab_client->setModel(C.triparPrenomD());
                }
                    else
                    msgBox.setText(("echec"));

                    msgBox.exec();
        }
}

void MainWindow::on_tabWidget_2_currentChanged(int index)
{
    // set dark background gradient:
                      QLinearGradient gradient(0, 0, 0, 400);
                      gradient.setColorAt(0, QColor(90, 90, 90));
                      gradient.setColorAt(0.38, QColor(105, 105, 105));
                      gradient.setColorAt(1, QColor(70, 70, 70));
                      ui->plot->setBackground(QBrush(gradient));


                      // create empty bar chart objects:
                      QCPBars *amande = new QCPBars(ui->plot->xAxis, ui->plot->yAxis);
                      amande->setAntialiased(false);
                      amande->setStackingGap(1);
                       //set names and colors:
                      amande->setName("Repartition des client selon age ");
                      amande->setPen(QPen(QColor(0, 168, 140).lighter(130)));
                      amande->setBrush(QColor(0, 168, 140));
                      // stack bars on top of each other:

                      // prepare x axis with country labels:
                      QVector<double> ticks;
                      QVector<QString> labels;
                      ticks << 1 << 2 << 3 << 4 << 5;
                      labels << "[5..15]" << "[15..25]" << "[25..35]" << "[35..45]" << "[45...]" ;

                      QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
                      textTicker->addTicks(ticks, labels);
                      ui->plot->xAxis->setTicker(textTicker);
                      ui->plot->xAxis->setTickLabelRotation(60);
                      ui->plot->xAxis->setSubTicks(false);
                      ui->plot->xAxis->setTickLength(0, 4);
                      ui->plot->xAxis->setRange(0, 8);
                      ui->plot->xAxis->setBasePen(QPen(Qt::white));
                      ui->plot->xAxis->setTickPen(QPen(Qt::white));
                      ui->plot->xAxis->grid()->setVisible(true);
                      ui->plot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
                      ui->plot->xAxis->setTickLabelColor(Qt::white);
                      ui->plot->xAxis->setLabelColor(Qt::white);

                      // prepare y axis:
                      ui->plot->yAxis->setRange(0,10);
                      ui->plot->yAxis->setPadding(5); // a bit more space to the left border
                      ui->plot->yAxis->setLabel("Statistiques");
                      ui->plot->yAxis->setBasePen(QPen(Qt::white));
                      ui->plot->yAxis->setTickPen(QPen(Qt::white));
                      ui->plot->yAxis->setSubTickPen(QPen(Qt::white));
                      ui->plot->yAxis->grid()->setSubGridVisible(true);
                      ui->plot->yAxis->setTickLabelColor(Qt::white);
                      ui->plot->yAxis->setLabelColor(Qt::white);
                      ui->plot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
                      ui->plot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

                      // Add data:

                      QVector<double> PlaceData;
                      QSqlQuery q1("select Age from Gestion_client");
                      C.statistique(&PlaceData);
                      C.statistique_1(&PlaceData);
                      C.statistique_2(&PlaceData);
                      C.statistique_3(&PlaceData);
                      C.statistique_4(&PlaceData);
                      amande->setData(ticks, PlaceData);
                      // setup legend:
                      ui->plot->legend->setVisible(true);
                      ui->plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
                      ui->plot->legend->setBrush(QColor(255, 255, 255, 100));
                      ui->plot->legend->setBorderPen(Qt::NoPen);
                      QFont legendFont = font();
                      legendFont.setPointSize(5);//888//
                      ui->plot->legend->setFont(legendFont);
                      ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

//Gestion Jeux - Khalil

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
        ui->tableViewk->setModel(Jtmp.Afficher());
}

void MainWindow::on_butModifier_clicked()
{
    QString id_mod=ui->tableViewk->model()->data(ui->tableViewk->model()->index(ui->tableViewk->currentIndex().row(),0)).toString();
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
        ui->tableViewk->setModel(Jtmp.Afficher());
}

void MainWindow::on_butSupprimer_clicked()
{
    QString id_del=ui->tableViewk->model()->data(ui->tableViewk->model()->index(ui->tableViewk->currentIndex().row(),0)).toString();

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
        ui->tableViewk->setModel(Jtmp.Afficher());
}

void MainWindow::on_Search_clicked()
{
    if((ui->comboSearchk->currentText() == "")||(ui->lineRechercher->text() == "")){
            QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                                    QObject::tr("Veuillez selectez une paramètre.\n"), QMessageBox::Ok);
        }
        else {
            ui->tableViewk->setModel(Jtmp.Rechercher(ui->lineRechercher->text(), ui->comboSearchk->currentIndex()));
        }
}

void MainWindow::on_butTrier_clicked()
{
    ui->tableViewk->setModel(Jtmp.Tri(ui->comboTrik->currentIndex(), ui->comboOrdrek->currentIndex()));
}

void MainWindow::on_tableView3k_clicked(const QModelIndex &index)
{
    QString tab[8] = {"NOM", "ID", "PRIX", "TYPE", "ETAT", "USAGE_TOT", "USAGE_MAINTENANCE", "IMAGE"};
        QString fields[8] = {"labelNom", "labelID", "labelPrix", "labelType", "labelEtat", "labelUT", "labelUM"};
        QString indexNom = ui->tableView3k->model()->data(ui->tableView3k->model()->index(ui->tableView3k->currentIndex().row(),0)).toString();
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
}

void MainWindow::on_butUsage_clicked()
{
    QString tab[8] = {"NOM", "ID", "PRIX", "TYPE", "ETAT", "USAGE_TOT", "USAGE_MAINTENANCE", "IMAGE"};
        QString fields[8] = {"labelNom", "labelID", "labelPrix", "labelType", "labelEtat", "labelUT", "labelUM"};
        QString indexNom = ui->tableView3k->model()->data(ui->tableView3k->model()->index(ui->tableView3k->currentIndex().row(),0)).toString();

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
    QString indexNom = ui->tableView3k->model()->data(ui->tableView3k->model()->index(ui->tableView3k->currentIndex().row(),0)).toString();
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

void MainWindow::on_tableView2k_clicked(const QModelIndex &index)
{
    QString indexNom = ui->tableView2k->model()->data(ui->tableView2k->model()->index(ui->tableView2k->currentIndex().row(),0)).toString();
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
         ui->labelPin->setGeometry(x, y, 50, 50);
}

//Gestion Menu - Yahya



void MainWindow::on_pb_enregistrer_clicked()
{
    QString id = ui->ref->text();
        QString nom = ui->nom->text();
        float prix = ui->prix->text().toFloat();
        QString etat = ui->etat->text();
        menu m(id,nom,prix,etat);
        QString email= ui->emailYahya->text();
        if  (bool test=m.ajouter()==false ||(email.isEmpty()))

                         {
                             QMessageBox::critical(0,qApp->tr("erreur"),qApp->tr("veillez remplir les champs vides."),QMessageBox::Cancel);
                         }
        else{

            QMessageBox::critical(0,qApp->tr("success"),qApp->tr(" menu ajouté et un mail a éte envoyé au chef "),QMessageBox::Ok);
            ui->menus->setModel(tmpmenu.afficher());
            Smtp* smtp = new Smtp("yahyafhima1@gmail.com", "Hackerway01", "smtp.gmail.com", 465);
             connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
             QString m1=ui->emailYahya->text();
             smtp->sendMail("yahyafhima1@gmail.com",m1, "Smart Park, menu!","Bienvenue! Vous-avez un nouveau menu!");
    ui->emailYahya->clear();
             ui->ref->clear();
             ui->nom->clear();
              ui->prix->clear();
               ui->etat->clear();


        }
}



void MainWindow::on_modifYahya_clicked()
{
    QString id = ui->ref->text();
       QString nom = ui->nom->text();
       float prix = ui->prix->text().toFloat();
       QString etat = ui->etat->text();

       if (id.isEmpty() || nom.isEmpty() || prix==0.0f ||etat.isEmpty()  )

                        {
                            QMessageBox::critical(0,qApp->tr("erreur"),qApp->tr("veillez remplir les champs vides."),QMessageBox::Cancel);
                        }
       else{


    menu me(id,nom,prix,etat);
    me.modifier();

                 QMessageBox::critical(0,qApp->tr("success"),qApp->tr(" menu a été modifiée."),QMessageBox::Yes);
                 ui->menus->setModel(tmpmenu.afficher());
                 ui->menus->clearSelection();
                   ui->ref->clear();
                     ui->nom->clear();
                       ui->prix->clear();
                         ui->etat->clear();
             }
}

void MainWindow::on_supprimerYahya_clicked()
{
    QString ref = ui->ref2->text();
        if(ref.isEmpty())
            {
                QMessageBox::critical(0,qApp->tr("erreur"),
                                      qApp->tr("veillez donner l identifiant du menu a supprimer"),QMessageBox::Cancel);
            }
        else
        {
            QMessageBox::critical(0,qApp->tr("attention"),
                                  qApp->tr("voulez vous supprimer cette menu?"),QMessageBox::Yes,QMessageBox::No);
            if(QMessageBox::Yes)
            {
                bool test= tmpmenu.supprimer(ref);
                if (test)
                {
                    ui->menus->setModel(tmpmenu.afficher());
                    ui->menus->clearSelection();
                }
            }

        }
}



void MainWindow::on_triYahya_clicked()
{
    ui->menus->setModel(tmpmenu.trie_menuprix());
}



void MainWindow::on_rechercheYahya_clicked()
{
    QString id = ui->ref1->text();
    ui->menus->setModel(tmpmenu.rechercher(id));
}



void MainWindow::on_tabWidget_currentChanged(int index)
{
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(0, 220, 220));
    gradient.setColorAt(1, QColor(190, 120, 60));
    ui->plot_2->setBackground(QBrush(gradient));

    QCPBars *amande = new QCPBars(ui->plot_2->xAxis, ui->plot_2->yAxis);
    amande->setAntialiased(false);
    amande->setStackingGap(1);

    amande->setName("Menu");
    amande->setPen(QPen(QColor(100,
                               9, 205).lighter(130)));
    amande->setBrush(QColor(180, 170, 255));


    QVector<double> ticks;
    QVector<QString> labels;
    tmpmenu.statistique(&ticks,&labels);

    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    ui->plot_2->xAxis->setTicker(textTicker);
    ui->plot_2->xAxis->setTickLabelRotation(60);
    ui->plot_2->xAxis->setSubTicks(false);
    ui->plot_2->xAxis->setTickLength(0, 4);
    ui->plot_2->xAxis->setRange(0, 8);
    ui->plot_2->xAxis->setBasePen(QPen(Qt::white));
    ui->plot_2->xAxis->setTickPen(QPen(Qt::white));
    ui->plot_2->xAxis->grid()->setVisible(true);
    ui->plot_2->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui->plot_2->xAxis->setTickLabelColor(Qt::white);
    ui->plot_2->xAxis->setLabelColor(Qt::white);


    ui->plot_2->yAxis->setRange(0,100);
    ui->plot_2->yAxis->setPadding(5);
    ui->plot_2->yAxis->setLabel("Statistiques");
    ui->plot_2->yAxis->setBasePen(QPen(Qt::white));
    ui->plot_2->yAxis->setTickPen(QPen(Qt::white));
    ui->plot_2->yAxis->setSubTickPen(QPen(Qt::white));
    ui->plot_2->yAxis->grid()->setSubGridVisible(true);
    ui->plot_2->yAxis->setTickLabelColor(Qt::white);
    ui->plot_2->yAxis->setLabelColor(Qt::white);
    ui->plot_2->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->plot_2->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    QVector<double> PlaceData;
    QSqlQuery q1("select prix from MENU where prix>10");
    while (q1.next()) {
        int  nbr_fautee = q1.value(0).toInt();
        PlaceData<< nbr_fautee;
    }
    amande->setData(ticks, PlaceData);

    ui->plot_2->legend->setVisible(true);
    ui->plot_2->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->plot_2->legend->setBrush(QColor(255, 255, 255, 100));
    ui->plot_2->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = font();
    legendFont.setPointSize(5);
    ui->plot_2->legend->setFont(legendFont);
    ui->plot_2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

void MainWindow::on_pdfYahya_clicked()
{
    QSqlDatabase db;
    QTableView table_menu;
    QSqlQueryModel * Modal=new  QSqlQueryModel();

    QSqlQuery qry;
    qry.prepare("SELECT * FROM menu ");
    qry.exec();
    Modal->setQuery(qry);
    table_menu.setModel(Modal);


    db.close();

    QString strStream;
    QTextStream out(&strStream);


    const int rowCount = table_menu.model()->rowCount();
    const int columnCount =  table_menu.model()->columnCount();

    const QString strTitle ="Document";


    out <<  "<html>\n"
            "<img src='C:/Users/21622/Pictures/Camera Roll/harley-quinn-bad-girl-cs.jpg' height='120' width='120'/>"
            "<head>\n"
            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
         <<  QString("<title>%1</title>\n").arg(strTitle)
          <<  "</head>\n"
              "<body bgcolor=#ffffff link=#5000A0>\n"
           << QString("<h3 style=\" font-size: 50px; font-family: Arial, Helvetica, sans-serif; color: #e80e32; font-weight: lighter; text-align: center;\">%1</h3>\n").arg("Liste des menus")
           <<"<br>"

          <<"<table border=1 cellspacing=0 cellpadding=2 width=\"100%\">\n";
    out << "<thead><tr bgcolor=#f0f0f0>";
    for (int column = 0; column < columnCount; column++)
        if (!table_menu.isColumnHidden(column))
            out << QString("<th>%1</th>").arg(table_menu.model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!table_menu.isColumnHidden(column)) {
                QString data = table_menu.model()->data(table_menu.model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table>\n"
            "<br><br>"
         <<"<br>"
        <<"<table border=1 cellspacing=0 cellpadding=2>\n";

    out << "<thead><tr bgcolor=#f0f0f0>";

    out <<  "</table>\n"

            "</body>\n"
            "</html>\n";

    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);

    QPrinter printer;
    QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
    if (dialog->exec() == QDialog::Accepted) {

        document->print(&printer);
    }

    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName("/tmp/menu.pdf");
    printer.setPageMargins(QMarginsF(15, 15, 15, 15));

    delete document;
}

//Gestion Staff - Mariem
void MainWindow::on_ajoutM_clicked()
{
    //recuperation des informtions
    int id=ui->idM->text().toInt();
    //
    QString nom=ui->nomM->text();
    QString prenom=ui->prenomM->text();
    QString fonction=ui->comboFonction->currentText();
    QDate datedenaissance=ui->dateM->date();
    staff S(id,nom,prenom,fonction,datedenaissance);

    bool test1=S.ajouter();
    //id=ui->tableView->selectionBehavior();
    // bool test2=S.supprimer(id);
    // bool test2=S.supprimer(ui->tableView->selectionBehavior());
    if (test1) //si requete executée ==>QMessageBox::information
    {
        ui->tableMariem->setModel(S.afficher());
        QMessageBox::information(nullptr, QObject::tr("ajout"),
                                 QObject::tr("ajout avec succes .\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("ajout"),
                              QObject::tr("insert failed.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_supprimerM_clicked()
{
    //int id =ui->lineEdit_2->text().toInt ;
    int id=ui->idM->text().toInt();
    bool test =Etmp.supprimer(id);
    if (test)
    {    ui->tableMariem->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("supprimer"),
                                 QObject::tr("suppression avec succes .\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("supprimer"),
                              QObject::tr("delete failed.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_modifierM_clicked()
{
    staff S ;
    int id=ui->idM->text().toInt();
    QString nom=ui->nomM->text();
    QString prenom=ui->prenomM->text();
    QString fonction=ui->comboFonction->currentText();
    QDate date_naissance=ui->dateM->date();
    staff S1(id,nom,prenom,fonction,date_naissance);
    //bool test= S.modifier(id,nom,prenom,fonction,date_naissance);
    bool test;
    test= S1.modifier( id , nom, prenom, fonction, date_naissance);
    if (test)
        //[☺]
    {
        ui->tableMariem->setModel(S1.afficher());
        QMessageBox::information(nullptr, QObject::tr("MODIFIER"),
                                 QObject::tr("MODIFICATION avec succes .\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("MODIFIER"),
                              QObject::tr("UPDATE failed.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_tableMariem_activated(const QModelIndex &index)
{
    //prendre la valeur de l'indexe et la renvoie en une valeur
    QString val=ui->tableMariem->model()->data(index).toString();
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


void MainWindow::on_rechercherM_clicked()
{
    if(ui->checkBox_id_2->isChecked()){
        int id=ui->rechIDM->text().toInt();
        QSqlQueryModel* test=Etmp.rechercher_id(id);
        QMessageBox msgBox;
        if(test){
            msgBox.setText("recherche avec succes");
            ui->tableMariem->setModel(Etmp.rechercher_id(id));
        }
        else
            msgBox.setText(("client introuvable"));

        msgBox.exec();
    }
    else if(ui->checkBox_nom_2->isChecked())
    {
        QString nom=ui->rechercheNomM->text();
        QSqlQueryModel* test2=Etmp.rechercher_nom(nom);
        QMessageBox msgBox;
        if(test2){
            msgBox.setText("recherche avec succes");
            ui->tableMariem->setModel(Etmp.rechercher_nom(nom));
        }
        else
            msgBox.setText(("client introuvable"));

        msgBox.exec();
    }
    else if(ui->checkBox_prenom_2->isChecked())
    {
        QString prenom=ui->rechPrenomM->text();
        QSqlQueryModel* test2=Etmp.rechercher_prenom(prenom);
        QMessageBox msgBox;
        if(test2){
            msgBox.setText("recherche avec succes");
            ui->tableMariem->setModel(Etmp.rechercher_prenom(prenom));
        }
        else
            msgBox.setText(("client introuvable"));

        msgBox.exec();
    }
    else if((ui->checkBox_prenom_2->isChecked())&&(ui->checkBox_nom_2->isChecked()))
    {
        QString nom=ui->rechercheNomM->text();
        QString prenom=ui->rechPrenomM->text();
        QSqlQueryModel* test2=Etmp.rechercher_nomprenom(nom, prenom);
        QMessageBox msgBox;
        if(test2){
            msgBox.setText("recherche avec succes");
            ui->tableMariem->setModel(Etmp.rechercher_nomprenom(nom, prenom));
        }
        else
            msgBox.setText(("client introuvable"));

        msgBox.exec();
    }
    else if((ui->checkBox_id_2->isChecked())&&(ui->checkBox_nom_2->isChecked()))
    {
        QString nom=ui->rechercheNomM->text();
        int id=ui->rechIDM->text().toInt();
        QSqlQueryModel* test2=Etmp.rechercher_nomid(nom, id);
        QMessageBox msgBox;
        if(test2){
            msgBox.setText("recherche avec succes");
            ui->tableMariem->setModel(Etmp.rechercher_nomid(nom, id));
        }
        else
            msgBox.setText(("client introuvable"));

        msgBox.exec();
    }
    else if((ui->checkBox_id_2->isChecked())&&(ui->checkBox_prenom_2->isChecked()))
    {
        QString prenom=ui->rechPrenomM->text();
        int id=ui->rechIDM->text().toInt();
        QSqlQueryModel* test2=Etmp.rechercher_prenomid(prenom, id);
        QMessageBox msgBox;
        if(test2){
            msgBox.setText("recherche avec succes");
            ui->tableMariem->setModel(Etmp.rechercher_prenomid(prenom, id));
        }
        else
            msgBox.setText(("client introuvable"));

        msgBox.exec();
    }
    else if((ui->checkBox_id_2->isChecked())&&(ui->checkBox_prenom_2->isChecked())&&(ui->checkBox_nom_2->isChecked()))
    {
        QString nom=ui->rechercheNomM->text();
        QString prenom=ui->rechPrenomM->text();
        int id=ui->rechIDM->text().toInt();
        QSqlQueryModel* test2=Etmp.rechercher_prenom_id_nom(prenom, id,nom);
        QMessageBox msgBox;
        if(test2){
            msgBox.setText("recherche avec succes");
            ui->tableMariem->setModel(Etmp.rechercher_prenom_id_nom(prenom, id,nom));
        }
        else
            msgBox.setText(("staff introuvable"));

        msgBox.exec();
    }
}

void MainWindow::on_triM_clicked()
{
    QSqlQueryModel* test=Etmp.triparAge();
    QMessageBox msgBox;
    if(test){
        msgBox.setText("tri avec succes");
        ui->tableMariem->setModel(Etmp.triparAge());
    }
    else
        msgBox.setText(("echec"));

    msgBox.exec();
}

void MainWindow::on_employe_currentChanged(int index)
{
    QTextCharFormat f=ui->calendarWidget->weekdayTextFormat(Qt::Saturday);

    Etmp.calendrier(f,ui->calendarWidget);

    Etmp.statistiques(ui->widget_2);
}


//Gestion Parking - Nour
void MainWindow::on_valider_3_clicked()
{
    int num=ui->lineEdit_num_3->text().toInt();
    QString type=ui->comboBox_type_3->currentText();
    QString etat=ui->lineEdit_etat_3->text();
    QString bloc=ui->lineEdit_bloc_3->text();
    int places_A=20;
    int places_B=30;
    int places_C=25;
    int places_D=40;
    int places;
    if(bloc=='A')
    {

        places_A=places_A-1-ptmp.numbre("A");
        places=places_A;
    }
    else if(bloc=='B')
    {
        places_B=places_B-1-ptmp.numbre("B");
        places=places_B;
    }
    else if(bloc=='C')
    {
        places_C=places_C-1-ptmp.numbre("C");
        places=places_C;
    }
    else if(bloc=='D')
    {
        places_D=places_D-1-ptmp.numbre("D");
        places=places_D;
    }

    //
    place p(num,type,etat,bloc,places);
    //
    bool test=p.ajouter ();
    click = new QMediaPlayer();
    click->setMedia(QUrl("C:/Users/Nour Saidi/Desktop/projet QT/projet c++/click.mp3"));
    click->play();
    if (test)
    { ui->tableView_2->setModel(ptmp.afficher());
        QMessageBox :: information (nullptr, QObject ::tr("OK"),
                                    QObject ::tr("Ajout effectué\n"
                                                 "click cancel to exit"),
                                    QMessageBox:: Cancel);
        ui->lineEdit_num_3->clear();
        ui->lineEdit_etat_3->clear();
        ui->lineEdit_bloc_3->clear();
        //ui->places->clear();

    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("not ok"),
                              QObject::tr("try again.\n"
                                          "click cancel to exit."),QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_sup_2_clicked()
{
    QItemSelectionModel *select = ui->tableView_2->selectionModel();
    int num =select->selectedRows(0).value(0).data().toInt();
    bool test=ptmp.supprimer(num);

    click = new QMediaPlayer();
    click->setMedia(QUrl("C:/Users/Nour Saidi/Desktop/projet QT/projet c++/click.mp3"));
    click->play();
    if (test)
    { ui->tableView_2->setModel(ptmp.afficher());
        QMessageBox :: information (nullptr, QObject ::tr("OK"),
                                    QObject ::tr("suppression effectué\n"
                                                 "click cancel to exit"),
                                    QMessageBox:: Cancel);

    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("not ok"),
                              QObject::tr("try again.\n"
                                          "click cancel to exit."),QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_modifier_3_clicked()
{
    int num=ui->num_mod_3->text().toInt();
    QString type =ui->type_mod_5->currentText();
    QString etat=ui->etat_mod_5->text();
    QString bloc=ui->bloc_mod_3->text();
    int places=ui->places_mod_2->text().toInt();

    place p(num,type,etat,bloc,places);
    bool test=p.modifier(num);
    if (test)
    {
        ui->tableView_2->setModel(ptmp.afficher());
        QMessageBox :: information (nullptr, QObject ::tr("OK"),
                                    QObject ::tr("modifier effectué\n"
                                                 "click cancel to exit"),
                                    QMessageBox:: Cancel);
        ui->num_mod_3->clear();
        ui->etat_mod_5->clear();
        ui->bloc_mod_3->clear();
        ui->places_mod_2->clear ();

    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("not ok"),
                              QObject::tr("try again.\n"
                                          "click cancel to exit."),QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_palce_tri_2_clicked()
{
    switch(ui->comboBox_tri_2->currentIndex()){
    case 0:
        ui->tableView_2->setModel(ptmp.tri_places());
        break;
    case 1:
        ui->tableView_2->setModel(ptmp.tri());
        break;
    case 2:
        ui->tableView_2->setModel(ptmp.tri_bloc());
        break;
    default:
        break;
    }
    click = new QMediaPlayer();
    click->setMedia(QUrl("C:/Users/user/Desktop/click.mp3"));
    click->play();
}

void MainWindow::on_tabWidget_4_currentChanged(int index)
{
    // background //
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(234, 234, 234));
    gradient.setColorAt(0.38, QColor(255, 255, 255));
    gradient.setColorAt(1, QColor(216, 216, 216));
    ui->plot_3->setBackground(QBrush(gradient));

    QCPBars *amande = new QCPBars(ui->plot_3->xAxis, ui->plot_3->yAxis);
    amande->setAntialiased(false);
    amande->setStackingGap(1);
    //couleurs
    amande->setName("places");
    amande->setPen(QPen(QColor(170, 0, 127).lighter(130)));
    amande->setBrush(QColor(255, 216, 234));

    //axe des abscisses
    QVector<double> ticks;
    QVector<QString> labels;
    ptmp.statistique(&ticks,&labels);

    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    ui->plot_3->xAxis->setTicker(textTicker);
    ui->plot_3->xAxis->setTickLabelRotation(60);
    ui->plot_3->xAxis->setSubTicks(false);
    ui->plot_3->xAxis->setTickLength(0, 4);
    ui->plot_3->xAxis->setRange(0, 8);
    ui->plot_3->xAxis->setBasePen(QPen(Qt::white));
    ui->plot_3->xAxis->setTickPen(QPen(Qt::white));
    ui->plot_3->xAxis->grid()->setVisible(true);
    ui->plot_3->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui->plot_3->xAxis->setTickLabelColor(Qt::white);
    ui->plot_3->xAxis->setLabelColor(Qt::white);

    // axe des ordonnées
    ui->plot_3->yAxis->setRange(0,10);
    ui->plot_3->yAxis->setPadding(5);
    ui->plot_3->yAxis->setLabel("Statistiques");
    ui->plot_3->yAxis->setBasePen(QPen(Qt::white));
    ui->plot_3->yAxis->setTickPen(QPen(Qt::white));
    ui->plot_3->yAxis->setSubTickPen(QPen(Qt::white));
    ui->plot_3->yAxis->grid()->setSubGridVisible(true);
    ui->plot_3->yAxis->setTickLabelColor(Qt::white);
    ui->plot_3->yAxis->setLabelColor(Qt::white);
    ui->plot_3->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->plot_3->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    // ajout des données  (statistiques de la quantité)//

    QVector<double> PlaceData;
    QSqlQuery q1("select places from GESTION_PLACE_PARKING");
    while (q1.next()) {
        int  nbr_fautee = q1.value(0).toInt();
        PlaceData<< nbr_fautee;
    }
    amande->setData(ticks, PlaceData);

    ui->plot_3->legend->setVisible(true);
    ui->plot_3->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->plot_3->legend->setBrush(QColor(255, 255, 255, 100));
    ui->plot_3->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = font();
    legendFont.setPointSize(5);
    ui->plot_3->legend->setFont(legendFont);
    ui->plot_3->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                    tr("Excel Files (*.xls)"));
    ui->tableView_2->setModel(ptmp.tri());
    ExportExcelObject obj(fileName, "test", ui->tableView_2);
    obj.addField(0, tr("NUM"), "int");
    obj.addField(1, tr("TYPE"), "char(20)");
    obj.addField(2, tr("ETAT"), "char(20)");
    obj.addField(3, tr("BLOC"), "char(20)");
    obj.addField(4, tr("PLACES"), "int");
    obj.export2Excel();
}

void MainWindow::on_pushButton_pdf_2_clicked()
{
    QString strStream;
    QTextStream out(&strStream);
    const int rowCount = ui->tableView_2->model()->rowCount();
    const int columnCount =ui->tableView_2->model()->columnCount();

    out <<  "<html>\n"
            "<head>\n"
            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
         <<  QString("<title>%1</title>\n").arg("eleve")
          <<  "</head>\n"
              "<body bgcolor=#CFC4E1 link=#5000A0>\n"
              "<h1>Liste des COLIS</h1>"

              "<table border=1 cellspacing=0 cellpadding=2>\n";

    // headers
    out << "<thead><tr bgcolor=#f0f0f0>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tableView_2->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tableView_2->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";
    // data table
    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tableView_2->isColumnHidden(column)) {
                QString data = ui->tableView_2->model()->data(ui->tableView_2->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table>\n"
            "</body>\n"
            "</html>\n";

    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);


    //QTextDocument document;
    //document.setHtml(html);
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName("place.pdf");
    document->print(&printer);
}

void MainWindow::on_pushButton_update_2_clicked()
{
    int places;
    QString title, description,bloc;
    QSqlQuery query;

    QSqlQuery q1("SELECT PLACES,BLOC FROM GESTION_PLACE_PARKING");
    while (q1.next())
    {
        places= q1.value(0).toInt();
        bloc= q1.value(1).toString();

        query.exec();
        if(places==0){
            title="places indisponible";
            description="Le bloc "+bloc+" est complet";
            popup->showPopup(title,description);
        }
    }
}

void MainWindow::on_pushButton_place_rechercher_2_clicked()
{
    QSqlQueryModel * test;
    int num;
    QString bloc;
    int places;

    switch(ui->comboBox_rechercher_2->currentIndex()){
    case 0:
        places = ui->lineEdit_recherche_2->text().toInt();;
        test=ptmp.recherche_place(places);
        break;
    case 1:
        num = ui->lineEdit_recherche_2->text().toInt();
        test=ptmp.recherche_place(num);
        break;
    case 2:
        bloc = ui->lineEdit_recherche_2->text();
        test=ptmp.recherche_bloc(bloc);
        break;
    default:
        break;
    }

    click = new QMediaPlayer();
    click->setMedia(QUrl("C:/Users/user/Desktop/click.mp3"));
    click->play();
    if(test != nullptr)
    {
        QMessageBox::information(nullptr, QObject::tr("chercher une place"),
                                 QObject::tr("place trouvé.\n"
                                             "Cliquer ok pour plus d'informations."), QMessageBox::Ok);
        ui->tableView_2->setModel(test);
    }
}
