#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileInfo>
#include <QDir>
#include <QDebug>
#include <QStandardItem>
#include <QSettings>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->MajListe();

    this->pListes = new Listes ;
    this->pListes->setWindowTitle("Gestion Listes");
    this->pListes->setWindowModality(Qt::ApplicationModal);

    this->pConfiguration = new Configuration ;
    this->pConfiguration->setWindowTitle("Configuration");
    this->pConfiguration->setWindowModality(Qt::ApplicationModal);

    connect( this->pListes, SIGNAL( SignalListeModifier() ), this, SLOT( on_MajListe() ) ) ;

    QDir Chemin ;
   // QPixmap pixmap_img(Chemin.currentPath() + "/images/fond.png");
   // ui->L_Fond->setPixmap(pixmap_img);
    ui->PB_Random->setUpdatesEnabled( false ) ;

    ui->CBx_Liste->setUpdatesEnabled( true );

    QPixmap pixmapPrincipale(Chemin.currentPath() + "/curseur/normal.png");
    QCursor CurseurPrincipale(pixmapPrincipale) ;
    ui->PB_Random->setCursor(CurseurPrincipale) ;

    ui->CBx_Liste->setStyleSheet("QComboBox {"
                                 "gridline-color: rgb(0, 0, 0);"
                                 "font: 75 italic 11pt \"Corbel\";"
                                 "background:qlineargradient(spread:pad, x1:0, y1:0, x2:0.874, y2:0, stop:1 rgba(255, 255, 255, 0));"
                                 "selection-background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0.874, y2:0.232955, stop:1 rgba(255, 255, 255, 0));"
                                 "selection-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0.874, y2:0.232955, stop:1 rgba(255, 255, 255, 0));}"
                                 "border-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0.874, y2:0.232955, stop:1 rgba(255, 255, 255, 0));");

}

MainWindow::~MainWindow()
{
    delete this->pListes ;
    delete ui;
}

void MainWindow::MajListe()
{
    int i( 0 ) ;
    QString sListe ;
    ui->CBx_Liste->clear() ;

    QSettings settings( "listes.ini", QSettings::IniFormat ) ;
    settings.childGroups() ;
    foreach( sListe, settings.childGroups() )
    {
        ui->CBx_Liste->insertItem( i, sListe ) ;
        i++ ;
    }
}

void MainWindow::on_PB_AjouterListe_clicked()
{
}

void MainWindow::on_TV_Liste_activated( const QModelIndex &index )
{

}

void MainWindow::on_TV_Liste_clicked( const QModelIndex &index )
{


}

void MainWindow::on_CBx_Liste_currentIndexChanged( const QString &arg1 )
{

}

void MainWindow::on_PB_Random_clicked()
{
    QString sListe ;
    QString sNom ;
    int nRand( 0 ) ;
    int nDebut( 0 );
    int nFin( 0 ) ;
    int nDeplacement ( 0 ) ;

    QSettings settings("listes.ini", QSettings::IniFormat) ;
    sListe = settings.value(ui->CBx_Liste->currentText() + "/perso", "config" ).toString() ;
    if( sListe.count(',') != 0 )
    {
        qsrand(QTime::currentTime().msec());

        nRand =  ( qrand() % sListe.count( ',' )  ) ;

        while( nDeplacement != nRand )
        {
            if( sListe[nDebut] == ',' )
            {
                nDeplacement++ ;
            }
            nDebut++ ;
        }



        nFin = nDebut + 1 ;

        while( sListe[nFin] != ',' )
        {

            nFin++ ;
        }

        sNom = sListe.mid( nDebut, nFin - nDebut ) ;

        ui->L_Perso->setText( sNom ) ;

        QSettings settings("config.ini", QSettings::IniFormat) ;
        settings.beginGroup("path");

        QPixmap pixmap( settings.value( "Images" ).toString() + sNom + "_Square_0.png") ;
        ui->L_Icone->setPixmap(pixmap) ;
        qDebug() << settings.value( "Images" ).toString().replace( "/" ,"\\" ) + sNom + "_Square_0.png" ;
    }
}

void MainWindow::on_CBx_Liste_activated(const QString &arg1)
{
}

void MainWindow::on_actionListes_triggered()
{
    this->pListes->show();
}

void MainWindow::on_MajListe()
{
    this->MajListe();
}

void MainWindow::on_actionQuitter_triggered()
{
    this->close() ;
}


void MainWindow::on_actionOptions_triggered()
{
    this->pConfiguration->show();
}
