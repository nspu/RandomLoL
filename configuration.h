#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QWidget>

namespace Ui {
class Configuration;
}

class Configuration : public QWidget
{
    Q_OBJECT
    
public:
    explicit Configuration(QWidget *parent = 0);
    ~Configuration();

    void MaJChamps() ;
    
private slots:

    void on_PB_Parcourir_clicked();

    void on_PB_Enregistrer_clicked();

    void on_PB_Annuler_clicked();

private:
    Ui::Configuration *ui;
    QString sCheminRiotGames ;
    QString sCheminImages ;
};

#endif // CONFIGURATION_H
