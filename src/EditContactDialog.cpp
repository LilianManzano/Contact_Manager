/**
 * @file EditContactDialog.cpp
 * @brief Fichier cpp de la classe EditContactDialog
 */


#include "EditContactDialog.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QFileDialog>
#include <QString>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QPainter>
#include <QImage>


//------------------------------------------------------------------------------------------------------------------------------
//constructeurs/destructeurs
//------------------------------------------------------------------------------------------------------------------------------
EditContactDialog::EditContactDialog(QWidget *parent)//si on veut créer un contact
    : QDialog(parent)
{
    setModal(true);
    this->currentContact=nullptr;
    setWindowTitle("Créer un contact");
    initUI();
    this->validateButton->setText("Créer");
    initConnect();
}



EditContactDialog::EditContactDialog(Contact * contact, QWidget *parent)//si on veut modifier un contact
    : QDialog(parent)
{
    setModal(true);
    this->currentContact=contact;
    setWindowTitle("Modifier un contact");
    initUI();
    this->validateButton->setText("Modifier");

    this->lastNameEdit->setText(contact->getLastName().c_str());
    this->firstNameEdit->setText(contact->getFirstName().c_str());
    this->companyEdit->setText(contact->getCompany().c_str());
    this->mailEdit->setText(contact->getMail().c_str());
    this->phoneEdit->setText(contact->getPhone().c_str());
    this->pictureEdit->setText(contact->getPathPicture().c_str());


    initConnect();
}

EditContactDialog::~EditContactDialog(){
    delete(this->errorMessage);
    delete(this->lastNameEdit);
    delete(this->firstNameEdit);
    delete(this->companyEdit);
    delete(this->mailEdit);
    delete(this->phoneEdit);
    delete(this->pictureButton);
    delete(this->pictureEdit);
    delete(this->cancelButton);
    delete(this->validateButton);
}


//------------------------------------------------------------------------------------------------------------------------------
//méthodes
//------------------------------------------------------------------------------------------------------------------------------
void EditContactDialog::initUI(){

    this->setWindowIcon(QIcon(":/resources/resourceFiles/logo.png"));
    this->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    this->errorMessage=new MessageLabel("", MessageLabel::NoStyle, true);

    QLabel * lastNameLabel=new QLabel("Nom :",this);
    lastNameLabel->setAlignment(Qt::AlignLeft);
    this->lastNameEdit=new QLineEdit(this);
    QLabel * firstNameLabel=new QLabel("Prénom :", this);
    firstNameLabel->setAlignment(Qt::AlignLeft);
    this->firstNameEdit=new QLineEdit(this);
    QLabel * companyLabel=new QLabel("Entreprise :",this);
    companyLabel->setAlignment(Qt::AlignLeft);
    this->companyEdit=new QLineEdit(this);
    QLabel * mailLabel=new QLabel("Mail :",this);
    mailLabel->setAlignment(Qt::AlignLeft);
    this->mailEdit=new QLineEdit(this);
    QLabel * phoneLabel=new QLabel("Téléphone :",this);
    phoneLabel->setAlignment(Qt::AlignLeft);
    this->phoneEdit=new QLineEdit(this);
    this->pictureButton=new QPushButton("Photo",this);
    this->pictureEdit=new QLineEdit(this);
    this->pictureEdit->setPlaceholderText(".jpg ou .jpeg ou .png");

    this->cancelButton=new QPushButton("Annuler",this);
    this->validateButton=new QPushButton(this);
    this->validateButton->setObjectName("editContactButton");

    QVBoxLayout * mainLayout=new QVBoxLayout(this);
    QVBoxLayout * labelLayout=new QVBoxLayout;
    QVBoxLayout * textEditLayout=new QVBoxLayout;
    QHBoxLayout * formLayout=new QHBoxLayout;
    QHBoxLayout * buttonLayout=new QHBoxLayout;

    labelLayout->addWidget(lastNameLabel);
    textEditLayout->addWidget(this->lastNameEdit);
    labelLayout->addWidget(firstNameLabel);
    textEditLayout->addWidget(this->firstNameEdit);
    labelLayout->addWidget(companyLabel);
    textEditLayout->addWidget(this->companyEdit);
    labelLayout->addWidget(mailLabel);
    textEditLayout->addWidget(this->mailEdit);
    labelLayout->addWidget(phoneLabel);
    textEditLayout->addWidget(this->phoneEdit);
    labelLayout->addWidget(this->pictureButton);
    textEditLayout->addWidget(this->pictureEdit);

    formLayout->addLayout(labelLayout);
    formLayout->addLayout(textEditLayout);
    formLayout->setContentsMargins(5,10,5,20);

    buttonLayout->addWidget(this->cancelButton);
    buttonLayout->addWidget(this->validateButton);

    mainLayout->addWidget(this->errorMessage);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);

    formLayout->setAlignment(Qt::AlignTop);
    buttonLayout->setAlignment(Qt::AlignBottom);

    resize(800,250);
}

void EditContactDialog::initConnect(){
    QObject::connect(this->pictureButton, SIGNAL(clicked()), this, SLOT(openFileDialog()));
    QObject::connect(this->validateButton, SIGNAL(clicked()), this, SLOT(editContact()));
    QObject::connect(this->cancelButton, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(this->pictureEdit, SIGNAL(textChanged(QString)), this, SLOT(checkPathPicture()));
}

bool EditContactDialog::checkData(){
    this->errorMessage->setProperty("",MessageLabel::NoStyle,true);
    bool validData=true;

    if(this->phoneEdit->text().simplified().isEmpty() || this->phoneEdit->text().simplified().length()>50)
      {this->errorMessage->setProperty("Le téléphone n'est pas renseigné",MessageLabel::Red,true);validData=false;}
    if(this->phoneEdit->text().simplified().length()>50)
      {this->errorMessage->setProperty("Le numéro de téléphone est trop long",MessageLabel::Red,true);validData=false;}
    if(this->mailEdit->text().simplified().isEmpty() || this->mailEdit->text().simplified().length()>50)
      {this->errorMessage->setProperty("Le mail n'est pas renseigné",MessageLabel::Red,true);validData=false;}
    if(this->mailEdit->text().simplified().length()>50)
      {this->errorMessage->setProperty("Le mail est trop long",MessageLabel::Red,true);validData=false;}
    if(this->companyEdit->text().simplified().isEmpty() || this->companyEdit->text().simplified().length()>50)
      {this->errorMessage->setProperty("L'entreprise n'est pas renseigné",MessageLabel::Red,true);validData=false;}
    if(this->companyEdit->text().simplified().length()>50)
      {this->errorMessage->setProperty("Le nom de l'entreprise est trop long",MessageLabel::Red,true);validData=false;}
    if(this->firstNameEdit->text().simplified().isEmpty() || this->firstNameEdit->text().simplified().length()>50)
      {this->errorMessage->setProperty("Le prénom n'est pas renseigné",MessageLabel::Red,true);validData=false;}
    if(this->firstNameEdit->text().simplified().length()>50)
      {this->errorMessage->setProperty("Le prénom est trop long",MessageLabel::Red,true);validData=false;}
    if(this->lastNameEdit->text().simplified().isEmpty() || this->lastNameEdit->text().simplified().length()>50)
      {this->errorMessage->setProperty("Le nom n'est pas renseigné",MessageLabel::Red,true);validData=false;}
    if(this->lastNameEdit->text().simplified().length()>50)
      {this->errorMessage->setProperty("Le nom est trop long",MessageLabel::Red,true);validData=false;}

    //Entreprise, numéro et email peuvent être vide ? (Si oui, bdd à modifier)



    return validData;
}

//------------------------------------------------------------------------------------------------------------------------------
//slots
//------------------------------------------------------------------------------------------------------------------------------

void EditContactDialog::openFileDialog(){
    QString pathPicture;
    QFileDialog fileDialog;
    pathPicture=fileDialog.getOpenFileName(this, "Choisir une image (.png ou .jpg ou.jpeg)","","Images (*.png *.jpg *jpeg)");
    this->pictureEdit->setText(pathPicture);
}



void EditContactDialog::editContact(){
    if(this->checkData())
        {

        //verification du chemin d'image et mise à défaut si besoin
        bool errorImg=false;
        QString pathPicture=this->pictureEdit->text().simplified();
        QFileInfo ext(pathPicture);
        if(this->currentContact==nullptr || (this->currentContact!=nullptr && this->currentContact->getPathPicture().c_str()!=pathPicture))
            {
            if(QFile::exists(pathPicture) && (ext.suffix()=="jpg" || ext.suffix()=="jpeg" || ext.suffix()=="png" || ext.suffix()=="JPG" || ext.suffix()=="JPEG" || ext.suffix()=="PNG"))
                {
                QDir directory("img");
                QString newPathPicture="img/img_"+QString::number(directory.count())+".png"; //+ext.suffix();

                QImage image(pathPicture);
                if(image.width()<image.height())
                      {image=image.copy(0,(image.height()-image.width())/2,image.width(),image.width());}
                else
                      {image=image.copy((image.width()-image.height())/2,0,image.height(),image.height());}
                image=image.scaled(1000,1000);
                image.save(newPathPicture, "PNG", 100);
                image.load(newPathPicture);

                QImage out(image.height(), image.height(), QImage::Format_ARGB32);
                out.fill(Qt::transparent);

                QBrush brush(image);
                QPen pen;
                pen.setColor(Qt::darkGray);
                pen.setJoinStyle(Qt::RoundJoin);

                QPainter painter(&out);
                painter.setBrush(brush);
                painter.setPen(Qt::NoPen);
                painter.drawRoundedRect(0, 0, out.width(), out.height(), out.width()/2, out.height()/2);
                out.save(newPathPicture, "PNG", 100);

                pathPicture=newPathPicture;
                }
            else {pathPicture=":/resources/resourceFiles/defaultImg.png";errorImg=true;}
            }


        if(this->currentContact!=nullptr)
            {
            this->currentContact->setLastName(this->lastNameEdit->text().simplified().toStdString());
            this->currentContact->setFirstName(this->firstNameEdit->text().simplified().toStdString());
            this->currentContact->setCompany(this->companyEdit->text().simplified().toStdString());
            this->currentContact->setMail(this->mailEdit->text().simplified().toStdString());
            this->currentContact->setPhone(this->phoneEdit->text().simplified().toStdString());
            this->currentContact->setPathPicture(pathPicture.toStdString());

            emit emitClose(this->currentContact, errorImg);
            }
        if(this->currentContact==nullptr)
            {
            this->currentContact=new Contact(this->lastNameEdit->text().simplified().toStdString(),
                                             this->firstNameEdit->text().simplified().toStdString(),
                                             this->companyEdit->text().simplified().toStdString(),
                                             this->mailEdit->text().simplified().toStdString(),
                                             this->phoneEdit->text().simplified().toStdString(),
                                             pathPicture.toStdString());
            this->currentContact->setId(-1);
            emit emitClose(this->currentContact, errorImg);
            }
        this->close();
        }
}

void EditContactDialog::checkPathPicture(){
    QString pathPicture=this->pictureEdit->text().simplified();
    QFileInfo ext(pathPicture);
    if(QFile::exists(pathPicture) && (ext.suffix()=="jpg" || ext.suffix()=="jpeg" || ext.suffix()=="png" ))
       this->errorMessage->setProperty("",MessageLabel::NoStyle,true);
    else
       this->errorMessage->setProperty("Le lien et/ou l'extension de l'image ne sont pas corrects",MessageLabel::Red,true);

}
