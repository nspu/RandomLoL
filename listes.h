#ifndef LISTES_H
#define LISTES_H

#include <QWidget>
#include <QModelIndex>

namespace Ui {
class Listes;
}

class Listes : public QWidget
{
    Q_OBJECT
    
public:
    explicit Listes(QWidget *parent = 0);
    ~Listes();

    void MajPerso() ;

    void MajListe() ;

    void MajFichierListe() ;

    void RecupererListePersonnages() ;

signals:
    void SignalListeModifier() ;
    
private slots:
    void on_PB_AjouterListe_clicked();

    void on_CBx_Liste_currentIndexChanged(const QString &arg1);

    void on_TV_Liste_clicked(const QModelIndex &index);

    void on_PB_Fermer_clicked();

    void on_PB_Supprimer_clicked();

    void on_PB_Selection_clicked();

    void on_PB_Deselection_clicked();

private:
    Ui::Listes *ui;
    QVector<QString> VecteurNomPerso ;
    QString sCheminDuRepertoire ;
};

#endif // LISTES_H
