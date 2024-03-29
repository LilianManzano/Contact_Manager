#ifndef CALENDARDIALOG_H
#define CALENDARDIALOG_H

/**
 * @file CalendarDialog.h
 * @brief Fichier header de la classe CalendarDialog
 */


#include <QDialog>
#include <QPushButton>
#include <QCalendarWidget>
#include <QObject>
#include <QDate>

/**
 * @class CalendarDialog
 * @brief classe représentant l'interface de la boîte de dialogue demandant une date
 * @details La classe hérite de la classe QDialog.
 */
class CalendarDialog : public QDialog
{
    Q_OBJECT


    private:
        QCalendarWidget * calendar;/**< calendrier */
        QPushButton * cancelButton;/**< bouton annuler */
        QPushButton * validateButton;/**< bouton valider */

        /**
         * @brief Permet d'initialiser les éléments d'interfaces (Layout, taille, calendrier, boutons, et autres propriétés).
         */
        void initUI();
        /**
         * @brief Permet d'initialiser les connect.
         */
        void initConnect();


    public:
        /**
         * @brief Constructeur.
         * @details
         * Défini la boîte de dialogue en mode bloquante, puis appel les méthodes 'initUI' et 'initConnect'.
         */
        CalendarDialog(QWidget *parent = 0);
        ~CalendarDialog();
        /**
         * @brief Permet de récupérer le QCalendarWidget, notamment pour fixer des propriétés suivant le contexte de la fenêtre.
         * @return pointeur sur objet QCalendarWidget
         */
        QCalendarWidget * getCalendar();


    public slots:
        /**
         * @brief slot emmetant le signal 'emitClose', avec en paramêtre la date sélectionnée.
         * @details
         * Dans notre programme le signal est envoyé à la fenêtre principal pour récupérer la date et fermer la boîte de dialogue.
         */
        void validateCloseDialog();
        /**
         * @brief slot emmetant le signal 'emitClose', avec en paramêtre un pointeur nullptr.
         * @details
         * Dans notre programme le signal est envoyé à la fenêtre principal pour récupérer le pointeur et ainsi savoir que l'opération à été annulé puis fermer la boîte de dialogue.
         */
        void cancelCloseDialog();


    signals:
        /**
         * @brief signal.
         * @param pointeur vers un objet QDate
         * @details
         * Dans notre programme le signal est envoyé à la fenêtre principal pour récupérer le pointeur et ainsi savoir que l'opération à été annulé puis fermer la boîte de dialogue.
         */
        void emitClose(QDate *);
};

#endif // CALENDARDIALOG_H
