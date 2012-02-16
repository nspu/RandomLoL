#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include "listes.h"
#include "configuration.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void MajListe() ;
    
private slots:
    void on_PB_AjouterListe_clicked();

    void on_TV_Liste_activated(const QModelIndex &index);

    void on_TV_Liste_clicked(const QModelIndex &index);

    void on_CBx_Liste_currentIndexChanged(const QString &arg1);

    void on_PB_Random_clicked();

    void on_CBx_Liste_activated(const QString &arg1);

    void on_actionListes_triggered();

    void on_MajListe() ;

    void on_actionQuitter_triggered();

    void on_actionOptions_triggered();

private:
    Ui::MainWindow *ui;
    QString DossierImage ;
    Listes * pListes ;
    Configuration * pConfiguration ;
};

#endif // MAINWINDOW_H
