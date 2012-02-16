#include "configuration.h"
#include "ui_configuration.h"
#include <QFileDialog>
#include <QDebug>
#include <QSettings>

Configuration::Configuration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Configuration)
{
    ui->setupUi(this);
    this->MaJChamps() ;
}

Configuration::~Configuration()
{
    delete ui;
}

void Configuration::on_PB_Parcourir_clicked()
{   
    QString sDossier ;
    sDossier = QFileDialog::getExistingDirectory( this, tr( "Sélectionner le dossier RiotGames" ), ui->LE_Chemin->text() );
    ui->LE_Chemin->setText(sDossier);
}

void Configuration::on_PB_Enregistrer_clicked()
{
    QDir RepertoireCourant ;
    QDir RepertoireImage ;
    QString sDossier ( ui->LE_Chemin->text() ) ;

    QSettings settings("config.ini", QSettings::IniFormat) ;
    settings.beginGroup("path") ;

    if( ui->RD_CheminDirect->isChecked() )
    {
        settings.setValue("RiotGames", "" ) ;
        settings.setValue( "Images", sDossier + "/" ) ;
    }
    else
    {
        settings.setValue("RiotGames", sDossier ) ;
        settings.setValue( "Images", "" ) ;
        RepertoireCourant.setPath( sDossier ) ;
        RepertoireCourant.setFilter( QDir::Dirs ) ;
        if( RepertoireCourant.exists( "League of Legends" ) )
        {
            sDossier += "/League of Legends/RADS/projects/lol_air_client/releases/" ;
            RepertoireCourant.setPath( sDossier ) ;
            foreach( QFileInfo FileInfo, RepertoireCourant.entryInfoList() )
            {
                RepertoireImage.setPath( sDossier + FileInfo.completeBaseName() + "." + FileInfo.suffix() + "\\" ) ;
                RepertoireImage.setFilter(QDir::Dirs) ;
                qDebug() << RepertoireImage.path() ;
                if( RepertoireImage.exists( "deploy" ) )
                {
                    RepertoireImage.setPath( RepertoireImage.path() + "/deploy/assets/images/champions/" ) ;
                    RepertoireImage.setFilter( QDir::Files ) ;
                    RepertoireImage.setNameFilters( QStringList() << "*quare_0*") ;

                    //Parcours ton répertoire
                    if( !RepertoireImage.entryInfoList().isEmpty() )
                    {
                        this->sCheminRiotGames = ui->LE_Chemin->text() ;
                        this->sCheminImages = RepertoireImage.path().replace( "\\", "/" ) + "/" ;
                        settings.setValue( "Images", this->sCheminImages ) ;
                    }
                }
            }
        }
    }

    this->hide() ;
}

void Configuration::on_PB_Annuler_clicked()
{
    this->hide() ;
    this->MaJChamps() ;
}

void Configuration::MaJChamps()
{
    QSettings settings("config.ini", QSettings::IniFormat) ;
    settings.beginGroup("path");


    if( settings.value("RiotGames").toString() == "" )
    {
        ui->RD_CheminDirect->setChecked( true ) ;
        ui->LE_Chemin->setText( settings.value( "Images" ).toString().replace( "/", "\\" ) ) ;
    }
    else
    {
        ui->RD_RiotGames->setChecked( true ) ;
        ui->LE_Chemin->setText(settings.value("RiotGames").toString()) ;

        this->sCheminRiotGames = settings.value("RiotGames").toString() ;
        this->sCheminImages = settings.value("Images").toString() ;
    }
}
