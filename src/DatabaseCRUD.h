#ifndef DATABASECRUD_H
#define DATABASECRUD_H

/**
 * @file DatabaseCRUD.h
 * @brief Fichier header de la classe DatabaseCRUD
 */


#include "ListContact.h"

#include <QSqlDatabase>
#include <QString>

/**
 * @class DatabaseCRUD
 * @brief classe représentant le gestionnaire de la BDD
 * @details
 * La classe permet de faire les requètes sur les contact, interactions, todos, et modifications à la BDD. \n
 * 'CRUD' pour Create, Read, Update, Delete.
 */
class DatabaseCRUD
{
    private:
        QSqlDatabase * database;/**< base de données */

    public:
        /**
         * @brief Constructeur.
         * @param pointeur vers un objet QSqlDatabase
         * @details Le paramêtre doit être la base de données ouverte par la classe DatabaseManagement
         */
        DatabaseCRUD(QSqlDatabase *);

        /**
         * @brief Permet de remplir une liste de contact avec tous les contacts contenus dans la BDD en attribut.
         * @param pointeur vers un objet ListContact
         * @details
         * Aucune liste n'est retourné, c'est la liste de contact passée en paramêtre qui est remplie. \n
         * La méthode fait une requête à la BDD.
         */
        void getAllContacts(ListContact *);

        /**
         * @brief Permet de supprimer un contact de la BDD en fonction de son identifiant.
         * @param entier
         * @details La méthode fait une requête à la BDD.
         */
        void deleteContactBDD(const int & id);

        /**
         * @brief Permet d'ajouter un contact à la BDD.
         * @param pointeur vers un objet Contact
         * @details La méthode fait une requête à la BDD.
         */
        void addContactBDD(Contact *);

        /**
         * @brief Permet de modifier un contact de la BDD.
         * @param pointeur vers un objet Contact
         * @details La méthode fait une requête à la BDD.
         */
        void modifyContactBDD(Contact *);

        /**
         * @brief Permet de remplir une liste de contact avec les contacts contenus dans la BDD respectant les filtres de recherches.
         * @param pointeur vers un objet ListContact
         * @param QString, dans notre programme c'est le contenu de la barre de recherche qui est récupéré
         * @param entier, dans notre programme c'est l'index courant du sélecteur de filtres
         * @param pointeur vers un objet Date, dans notre programme c'est la date de début des filtres
         * @param pointeur vers un objet Date, dans notre programme c'est la date de fin des filtres
         * @details
         * Aucune liste n'est retourné, c'est la liste de contact passée en paramêtre qui est remplie. \n
         * Pour filtrer, la méthode fait une requête à la BDD, et applique des méthodes de la classe date.
         */
        void searchByFilters(ListContact *, QString, int, Date *, Date *);
};

#endif // DATABASECRUD_H
