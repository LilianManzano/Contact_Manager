#ifndef LISTCONTACT_H
#define LISTCONTACT_H

/**
 * @file ListContact.h
 * @brief Fichier header de la classe ListContact
 */


#include <string>
#include "Contact.h"

/**
 * @class ListContact
 * @brief classe représentant une liste de pointeurs vers des objets 'Contact'
 */
class ListContact
{
    private:
        std::list<Contact*> listContact; /**< liste de pointeurs sur des objets 'Contact' */

    public:
        ListContact();
        ~ListContact();

        /**
         * @brief Permet de récupérer l'attribut de liste.
         * @return std::list<Contact*>
         */
        std::list<Contact*> getListContact() const;
        /**
         * @brief Permet de définir l'attribut de liste.
         * @param Le paramètre doit être un std::list<Contact*>
         */
        void setListContact(const std::list<Contact*> &);

        /**
         * @brief Permet d'ajouter un contact à la liste.
         * @param Le paramètre doit être un pointeur sur un objet Contact
         */
        void addContact(Contact* const);
        /**
         * @brief Permet d'enlever un contact de la liste en fonction de son identifiant.
         * @param Le paramètre doit être un entier représentant l'identifiant
         */
        void removeContactById(const int);
        /**
         * @brief Permet de récupérer un contact de la liste en fonction de son identifiant.
         * @param Le paramètre doit être un entier représentant l'identifiant
         * @return pointeur vers objet Contact
         */
        Contact* getContactById(const int) const;
        /**
         * @brief Permet de récupérer un contact de la liste en fonction de son index dans celle-ci.
         * @param Le paramètre doit être un entier représentant l'index
         * @return pointeur vers objet Contact
         */
        Contact* getContactByIndex(const int) const;
        /**
         * @brief Permet de récupérer la taille de la liste.
         * @return entier
         */
        int getSize() const;

        /**
         * @brief Permet de vider tous les contacts de la liste.
         */
        void removeAllContacts();

        /**
         * @brief Permet de trier la liste de contacts par ordre alphabétique (avec le nom du contact).
         */
        void sortByAlphabet();
        /**
         * @brief Permet de trier la liste de contacts par ordre inverse alphabétique (avec le nom du contact).
         */
        void sortByReverseAlphabet();
        /**
         * @brief Permet de trier la liste de contacts par date de création.
         */
        void sortByCreateDate();


        /**
         * @brief Permet d'obtenir une chaine de caractères avec les informations de l'objet
         * @return std::string sous la forme 'contact.toString\\n\\ncontact.toString\\n\\ncontact.toString'
         */
        std::string toString() const;
};

#endif // LISTCONTACT_H
