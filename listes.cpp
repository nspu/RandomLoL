#include "listes.h"
#include "ui_listes.h"
#include <QFileInfo>
#include <QDir>
#include <QDebug>
#include <QStandardItem>
#include <QSettings>
#include <QTime>

Listes::Listes( QWidget *parent ) :
    QWidget( parent ),
    ui(new Ui::Listes)
{
    ui->setupUi(this);
    this->RecupererListePersonnages() ;
    this->MajPerso() ;
    this->MajListe() ;

    if( ui->CBx_Liste->currentText() == "" )
    {
       ui->TV_Liste->setDisabled( true ) ;
       ui->PB_Deselection->setDisabled( true ) ;
       ui->PB_Selection->setDisabled( true ) ;
    }
}

Listes::~Listes()
{
    delete ui;
}

void Listes::on_PB_AjouterListe_clicked()
{
    if(ui->LE_NouvelleListe->text() == "" )
    {
        //ui->L_Erreur->setText( "Liste non créer : Champs vide" ) ;
    }
    else
    {
        QSettings settings( "listes.ini", QSettings::IniFormat ) ;
        settings.beginGroup( ui->LE_NouvelleListe->text() ) ;
        settings.setValue( "perso", "" ) ;
        settings.endGroup() ;
        this->MajListe() ;
        emit( this->SignalListeModifier() ) ;
    }

    if( ui->CBx_Liste->currentText() != "" )
    {
       ui->TV_Liste->setDisabled( false ) ;
       ui->PB_Deselection->setDisabled( false ) ;
       ui->PB_Selection->setDisabled( false ) ;
    }
}

void Listes::on_CBx_Liste_currentIndexChanged(const QString &arg1)
{
    QString sListe ;

    QSettings settings("listes.ini", QSettings::IniFormat) ;
    sListe = settings.value(arg1 + "/perso", "config" ).toString() ;

    for( int i = 0 ; i < ui->TV_Liste->model()->rowCount() ; i++ )
    {
        if( sListe.contains(ui->TV_Liste->model()->data( ui->TV_Liste->model()->index(i ,1)).toString() ) )
        {
            ui->TV_Liste->model()->setData( ui->TV_Liste->model()->index(i ,0), Qt::Checked, Qt::CheckStateRole) ;
        }
        else
        {
            ui->TV_Liste->model()->setData( ui->TV_Liste->model()->index(i ,0), Qt::Unchecked, Qt::CheckStateRole) ;
        }
    }
}

void Listes::on_TV_Liste_clicked(const QModelIndex &index)
{
    this->MajFichierListe() ;
}

void Listes::MajPerso()
{
    QStandardItemModel * modele ;
    QStandardItem * item ;

    //Initialisation de l'objet permettant l'organisation du tableau
    modele = new QStandardItemModel() ;

    ui->TV_Liste->setModel( modele ) ;
    ui->TV_Liste->setEditTriggers( QAbstractItemView::SelectedClicked ) ;
    ui->TV_Liste->setEditTriggers( 0 ) ;

    //Mise en place du tableau
    modele->setColumnCount( 2 ) ;
    modele->setRowCount( this->VecteurNomPerso.size() ) ;
    modele->setHorizontalHeaderItem( 0, new QStandardItem( "" ) ) ;
    modele->setHorizontalHeaderItem( 1, new QStandardItem( "Nom" ) ) ;


    ui->TV_Liste->setColumnWidth( 0, 22 ) ;


    for( int i = 0 ; i < this->VecteurNomPerso.size() ; i++)
    {
        //Permet d'ajout un checkbox Ã  la 1Ã©re case de la ligne
        item = new QStandardItem() ;
        item->setCheckable( true ) ;
        item->setCheckState( Qt::Unchecked ) ;
        modele->setItem( i, 0, item ) ;
        //On remplie le tableau
        modele->setItem( i, 1, new QStandardItem( this->VecteurNomPerso.at(i) ) ) ;
        qDebug() << this->VecteurNomPerso.at( i ) ;
    }

}

void Listes::MajListe()
{
    int i( 0 ) ;
    QString sListe ;
    ui->CBx_Liste->clear() ;

    QSettings settings( "listes.ini", QSettings::IniFormat ) ;
    settings.childGroups() ;
    foreach( sListe, settings.childGroups() )
    {
        qDebug() << sListe ;
        ui->CBx_Liste->insertItem( i, sListe ) ;
        i++ ;
    }
}

void Listes::RecupererListePersonnages()
{
    QSettings settings("config.ini", QSettings::IniFormat) ;
    settings.beginGroup( "path" ) ;
    this->sCheminDuRepertoire = settings.value( "Images" ).toString().replace( "/", "\\" ) ;
    QString sNom ;
    qDebug() << this->sCheminDuRepertoire ;
    QDir Repertoire( this->sCheminDuRepertoire ) ;
    Repertoire.setFilter( QDir::NoDotAndDotDot | QDir::Files ) ;
    Repertoire.setNameFilters( QStringList() << "*quare_0*") ;


    //Parcours ton répertoire
    foreach( QFileInfo FileInfo, Repertoire.entryInfoList() )
    {
        //Ton traitement par fichier, par exemple :
        sNom = FileInfo.baseName().replace( "_Square_0" , "" ) ;
        sNom = sNom.replace( "_square_0" , "" ) ;
        this->VecteurNomPerso.append(sNom) ;
    }
}

void Listes::on_PB_Fermer_clicked()
{
    this->hide();
}

void Listes::on_PB_Supprimer_clicked()
{
    QSettings settings( "listes.ini", QSettings::IniFormat ) ;
    if( ui->CBx_Liste->currentText() != "" || !settings.contains( ui->CBx_Liste->currentText() ) )
    {
        QSettings settings( "listes.ini", QSettings::IniFormat ) ;
        settings.remove( ui->CBx_Liste->currentText() ) ;
    }

    this->MajListe();
    emit(this->SignalListeModifier());

    if( ui->CBx_Liste->currentText() == "" )
    {
       ui->TV_Liste->setDisabled( true ) ;
       ui->PB_Deselection->setDisabled( true ) ;
       ui->PB_Selection->setDisabled( true ) ;
    }
}

void Listes::on_PB_Selection_clicked()
{
    for (register int i (0) ; i < ui->TV_Liste->model()->rowCount() ; i++ )
    {
        ui->TV_Liste->model()->setData( ui->TV_Liste->model()->index( i ,0 ), Qt::Checked, Qt::CheckStateRole ) ;
    }
    this->MajFichierListe() ;
}

void Listes::on_PB_Deselection_clicked()
{
    for (register int i (0) ; i < ui->TV_Liste->model()->rowCount() ; i++ )
    {
        ui->TV_Liste->model()->setData( ui->TV_Liste->model()->index(i ,0), Qt::Unchecked, Qt::CheckStateRole ) ;
    }
    this->MajFichierListe() ;
}

void Listes::MajFichierListe()
{
    QString sListe ;
    for( int i = 0 ; i < ui->TV_Liste->model()->rowCount() ; i++ )
    {
        if( ui->TV_Liste->model()->data( ui->TV_Liste->model()->index( i ,0 ), Qt::CheckStateRole ).toBool() )
        {
            sListe += ui->TV_Liste->model()->data( ui->TV_Liste->model()->index( i, 1 ) ).toString() + ',' ;
            qDebug() << sListe ;
        }
    }

    QSettings settings( "listes.ini", QSettings::IniFormat ) ;
    settings.beginGroup( ui->CBx_Liste->currentText() ) ;
    settings.setValue( "perso", sListe ) ;
    settings.endGroup() ;
}
