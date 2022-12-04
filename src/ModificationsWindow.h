#ifndef MODIFICATIONSWINDOW_H
#define MODIFICATIONSWINDOW_H

/**
 * @file ModificationsWindow.h
 * @brief Fichier header de la classe ModificationsWindow
 */

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QDialog>
#include <QWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QVBoxLayout>

/**
 * @class ModificationWindow
 * @brief classe représentant l'affichage des modifications
 * @details La classe hérite de la classe QWidget.
 */
class ModificationsWindow : public QDialog
{
    Q_OBJECT

    private:
        QSqlDatabase * database;/**< base de données */
        QTableWidget * modificationsTable;/**< tableau affichant les modifications */

    public:
        /**
         * @brief Constructeur.
         */
        ModificationsWindow(QSqlDatabase *, QWidget *parent = 0);
        ~ModificationsWindow();

        /**
         * @brief Permet d'initialiser les éléments d'interfaces (Layout, taille, et autres propriétés).
         */
        void initUI();

        /**
         * @brief Permet d'initialiser de remplir le tableau avec les modifications contenues dans la base de données.
         */
        void fillModificationsTable();

};

#endif // MODIFICATIONSWINDOW_H
