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
MainWindow::MainWindow(QWidget *parent):
   QMainWindow(parent),
    ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   ui->tableView->setModel(ptmp.afficher());
   ui->lineEdit_num_2->setValidator(new QIntValidator(0,99,this));
   popup = new Popup;



       setGeometry(QStyle::alignedRect(
                       Qt::RightToLeft,
                       Qt::AlignCenter,
                       size(),
                       qApp->desktop()->availableGeometry()));

       setWindowTitle("gestion_place_parking");
}

MainWindow::~MainWindow()
{
   delete ui;
}

void MainWindow::on_valider_2_clicked()
{
   {
       int num=ui->lineEdit_num_2->text().toInt();
       QString type=ui->comboBox_type_2->currentText();
       QString etat=ui->lineEdit_etat_2->text();
       QString bloc=ui->lineEdit_bloc_2->text();
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
       { ui->tableView->setModel(ptmp.afficher());
           QMessageBox :: information (nullptr, QObject ::tr("OK"),
                        QObject ::tr("Ajout effectué\n"
                                     "click cancel to exit"),
                   QMessageBox:: Cancel);
           ui->lineEdit_num_2->clear();
           ui->lineEdit_etat_2->clear();
           ui->lineEdit_bloc_2->clear();
           //ui->places->clear();

   }
       else
       {
           QMessageBox::critical(nullptr,QObject::tr("not ok"),
                                QObject::tr("try again.\n"
                                            "click cancel to exit."),QMessageBox::Cancel);
       }
}}


void MainWindow::on_pushButton_sup_clicked()
{


    QItemSelectionModel *select = ui->tableView->selectionModel();
       int num =select->selectedRows(0).value(0).data().toInt();
  bool test=ptmp.supprimer(num);

   click = new QMediaPlayer();
       click->setMedia(QUrl("C:/Users/Nour Saidi/Desktop/projet QT/projet c++/click.mp3"));
        click->play();
   if (test)
   { ui->tableView->setModel(ptmp.afficher());
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





void MainWindow::on_pushButton_recherche_clicked()
{

   int num = ui->lineEdit_recherche->text().toInt();
       QSqlQueryModel * test=ptmp.recherche_place(num);

           click = new QMediaPlayer();
               click->setMedia(QUrl("C:/Users/user/Desktop/click.mp3"));
                click->play();
           if(test != nullptr)
       {
           QMessageBox::information(nullptr, QObject::tr("chercher une place"),
                       QObject::tr("place trouvé.\n"
                                   "Cliquer ok pour plus d'informations."), QMessageBox::Ok);
               ui->tableView->setModel(test);
       }

}

void MainWindow::on_pushButton_modifier_2_clicked()
{
   int num=ui->num_mod_2->text().toInt();
   QString type =ui->type_mod_2->currentText();
   QString etat=ui->etat_mod_2->text();
   QString bloc=ui->bloc_mod_2->text();
   int places=ui->places_mod->text().toInt();

      place p(num,type,etat,bloc,places);
       bool test=p.modifier(num);
       if (test)
       {
              ui->tableView->setModel(ptmp.afficher());
           QMessageBox :: information (nullptr, QObject ::tr("OK"),
                        QObject ::tr("modifier effectué\n"
                                     "click cancel to exit"),
                   QMessageBox:: Cancel);
           ui->num_mod_2->clear();
           ui->etat_mod_2->clear();
           ui->bloc_mod_2->clear();
           ui->places_mod->clear ();

   }
       else
       {
           QMessageBox::critical(nullptr,QObject::tr("not ok"),
                                QObject::tr("try again.\n"
                                            "click cancel to exit."),QMessageBox::Cancel);
       }
}

void MainWindow::on_pushButton_tri_clicked()
{
   ui->tableView->setModel(ptmp.tri());
   click = new QMediaPlayer();
       click->setMedia(QUrl("C:/Users/user/Desktop/click.mp3"));
        click->play();
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    // background //
              QLinearGradient gradient(0, 0, 0, 400);
              gradient.setColorAt(0, QColor(234, 234, 234));
              gradient.setColorAt(0.38, QColor(255, 255, 255));
              gradient.setColorAt(1, QColor(216, 216, 216));
              ui->plot_2->setBackground(QBrush(gradient));

              QCPBars *amande = new QCPBars(ui->plot_2->xAxis, ui->plot_2->yAxis);
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

              // axe des ordonnées
              ui->plot_2->yAxis->setRange(0,10);
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

              // ajout des données  (statistiques de la quantité)//

              QVector<double> PlaceData;
              QSqlQuery q1("select places from GESTION_PLACE_PARKING");
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

void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                           tr("Excel Files (*.xls)"));
                ui->tableView->setModel(ptmp.tri());
        ExportExcelObject obj(fileName, "test", ui->tableView);
        obj.addField(0, tr("NUM"), "int");
        obj.addField(1, tr("TYPE"), "char(20)");
        obj.addField(2, tr("ETAT"), "char(20)");
        obj.addField(3, tr("BLOC"), "char(20)");
        obj.addField(4, tr("PLACES"), "int");
        obj.export2Excel();

}

void MainWindow::on_pushButton_pdf_clicked()
{
    QString strStream;
                   QTextStream out(&strStream);
                   const int rowCount = ui->tableView->model()->rowCount();
                   const int columnCount =ui->tableView->model()->columnCount();

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
                           if (!ui->tableView->isColumnHidden(column))
                               out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
                       out << "</tr></thead>\n";
                       // data table
                          for (int row = 0; row < rowCount; row++) {
                              out << "<tr>";
                              for (int column = 0; column < columnCount; column++) {
                                  if (!ui->tableView->isColumnHidden(column)) {
                                      QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
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

void MainWindow::on_pushButton_trib_clicked()
{
  ui->tableView->setModel(ptmp.tri_bloc());
  click = new QMediaPlayer();
      click->setMedia(QUrl("C:/Users/user/Desktop/click.mp3"));
       click->play();
}

void MainWindow::on_pushButton_trip_clicked()
{
  ui->tableView->setModel(ptmp.tri_places());
  click = new QMediaPlayer();
      click->setMedia(QUrl("C:/Users/user/Desktop/click.mp3"));
       click->play();
}

void MainWindow::on_pushButton_update_clicked()
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

void MainWindow::on_pushButton_rechercheb_clicked()
{
    QString bloc = ui->lineEdit_recherche->text();
        QSqlQueryModel * test=ptmp.recherche_bloc(bloc);

            click = new QMediaPlayer();
                click->setMedia(QUrl("C:/Users/user/Desktop/click.mp3"));
                 click->play();
            if(test != nullptr)
        {
            QMessageBox::information(nullptr, QObject::tr("chercher une place"),
                        QObject::tr("place trouvé.\n"
                                    "Cliquer ok pour plus d'informations."), QMessageBox::Ok);
                ui->tableView->setModel(test);
        }
}

void MainWindow::on_pushButton_recherchep_clicked()
{
    int places = ui->lineEdit_recherche->text().toInt();
        QSqlQueryModel * test=ptmp.recherche_places(places);

            click = new QMediaPlayer();
                click->setMedia(QUrl("C:/Users/user/Desktop/click.mp3"));
                 click->play();
            if(test != nullptr)
        {
            QMessageBox::information(nullptr, QObject::tr("chercher une place"),
                        QObject::tr("place trouvé.\n"
                                    "Cliquer ok pour plus d'informations."), QMessageBox::Ok);
                ui->tableView->setModel(test);
        }
}
