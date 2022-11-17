/**
 * @file MainWindow.cpp
 * @brief Fichier cpp de la classe MainWindow
 */


#include "MainWindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QStringList>
#include <QDebug>
#include <QAbstractItemView>


MainWindow::MainWindow(ContactCRUD * contactCRUD, QWidget *parent)
    : QWidget(parent)
{
    //lien avec BDD
    this->contactCRUD=contactCRUD;
    contactCRUD->getAllContacts(&this->listContact);
    initUI();
    initConnect();
    fillTable();
}

MainWindow::~MainWindow(){}




void MainWindow::initUI(){
    resize(1600, 800);


    //selection de filtre
    this->filtersCombobox = new QComboBox(this);
    this->filtersCombobox->setObjectName("filtersCombobox");
    this->filtersCombobox->addItem("Pas de filtre");
    this->filtersCombobox->addItem("Nom");
    this->filtersCombobox->addItem("Prénom");
    this->filtersCombobox->addItem("Entreprise");
    this->filtersCombobox->addItem("Mail");
    this->filtersCombobox->addItem("Telephone");

    //barre de recherche
    this->searchLineEdit = new QLineEdit(this);
    this->searchLineEdit->setPlaceholderText("nom, prénom, mail, ...");
    this->searchLineEdit->setObjectName("searchLineEdit");
    //bouton de recherche
    this->searchButton = new QPushButton("Rechercher", this);
    this->searchButton->setObjectName("searchButton");

    //selecteur de date
    QLabel * dateSelectorLabel1=new QLabel("Contacts crées entre le ");
    this->dateSelectorButton1 = new QPushButton(this);
    this->dateSelectorButton1->setMinimumWidth(100);
    QLabel * dateSelectorLabel2=new QLabel("et le ");
    this->dateSelectorButton2 = new QPushButton(this);
    this->dateSelectorButton2->setMinimumWidth(100);

    //bouton pour réinitialiser les filtres
    this->resetFiltersButton=new QPushButton("Réinitialiser les filtres");



    //selection de tri
    this->sortCombobox=new QComboBox(this);
    this->sortCombobox->setObjectName("sortCombobox");
    this->sortCombobox->addItem("Trier par date de création");
    this->sortCombobox->addItem("Trier par ordre A->Z");
    this->sortCombobox->addItem("Trier par ordre Z->A");

    //tableau des contacts
    this->contactsTable = new QTableWidget(this);
    this->contactsTable->setObjectName("contactsTable");
    this->contactsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->contactsTable->setColumnCount(6);
    QStringList hlabels; hlabels <<"Nom"<<"Prénom"<<"Entreprise"<<"mail"<<"Téléphone"<<"Date de création";
    this->contactsTable->setHorizontalHeaderLabels(hlabels);
    this->contactsTable->verticalHeader()->setVisible(false);
    this->contactsTable->horizontalHeader()->setSelectionMode(QAbstractItemView::NoSelection);
    this->contactsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->contactsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->contactsTable->setSelectionMode(QAbstractItemView::SingleSelection);

    //Layout verticaux puis horizontaux
    QVBoxLayout * mainLayout = new QVBoxLayout(this);

    QHBoxLayout * searchBarLayout = new QHBoxLayout();
    QHBoxLayout * dateAndResetLayout = new QHBoxLayout();
    QHBoxLayout * dateSelectorLayout = new QHBoxLayout();
    QHBoxLayout * resetFiltersButtonLayout = new QHBoxLayout();
    QHBoxLayout * showContactsLayout = new QHBoxLayout();
    showContactsLayout->setContentsMargins(0,20,0,0);

    //ajouts des widget dans chaque layout
    searchBarLayout->addWidget(this->filtersCombobox);
    searchBarLayout->addWidget(this->searchLineEdit);
    searchBarLayout->addWidget(this->searchButton);


    dateSelectorLayout->addWidget(dateSelectorLabel1);
    dateSelectorLayout->addWidget(this->dateSelectorButton1);
    dateSelectorLayout->addWidget(dateSelectorLabel2);
    dateSelectorLayout->addWidget(this->dateSelectorButton2);

    resetFiltersButtonLayout->addWidget(this->resetFiltersButton);

    dateAndResetLayout->addLayout(dateSelectorLayout);
    dateAndResetLayout->addLayout(resetFiltersButtonLayout);


    showContactsLayout->addWidget(this->sortCombobox);
    showContactsLayout->addWidget(this->contactsTable);

    //ajout des layout (attention à l'ordre)
    mainLayout->addLayout(searchBarLayout);
    mainLayout->addLayout(dateAndResetLayout);
    mainLayout->addLayout(showContactsLayout);


    //propriétés d'alignement sur les layout et widget
    dateAndResetLayout->setAlignment(dateSelectorLayout,Qt::AlignLeft );
    dateAndResetLayout->setAlignment(resetFiltersButtonLayout,Qt::AlignRight );

    showContactsLayout->setAlignment(this->sortCombobox, Qt::AlignTop);
}

void MainWindow::initConnect(){
    QObject::connect(this->dateSelectorButton1, SIGNAL(clicked()),this,SLOT(openCalendarDialog()));
    QObject::connect(this->sortCombobox, SIGNAL(currentIndexChanged(int)),this,SLOT(updateTable()));
}

void MainWindow::fillTable(){
    if(this->sortCombobox->currentIndex()==0)
        this->listContact.sortByCreateDate();
    if(this->sortCombobox->currentIndex()==1)
        this->listContact.sortByAlphabet();
    if(this->sortCombobox->currentIndex()==2)
        this->listContact.sortByReverseAlphabet();

    this->contactsTable->setRowCount(0);

    for(int i=0; i<this->listContact.getSize(); i++)
        {
        this->contactsTable->insertRow(i);

        this->contactsTable->setItem(i,0,new QTableWidgetItem(this->listContact.getContactByIndex(i)->getLastName().c_str()));
        this->contactsTable->setItem(i,1,new QTableWidgetItem(this->listContact.getContactByIndex(i)->getFirstName().c_str()));
        this->contactsTable->setItem(i,2,new QTableWidgetItem(this->listContact.getContactByIndex(i)->getCompany().c_str()));
        this->contactsTable->setItem(i,3,new QTableWidgetItem(this->listContact.getContactByIndex(i)->getMail().c_str()));
        this->contactsTable->setItem(i,4,new QTableWidgetItem(this->listContact.getContactByIndex(i)->getPhone().c_str()));
        this->contactsTable->setItem(i,5,new QTableWidgetItem(this->listContact.getContactByIndex(i)->getDateCreation()->toString().c_str()));
        }
}




void MainWindow::openCalendarDialog(){
    this ->calendarDialog=new CalendarDialog();
    this->calendarDialog->show();
}

void MainWindow::updateTable(){fillTable();}
