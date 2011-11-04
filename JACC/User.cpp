
#include "User.h"
#include <string.h>
#include <iostream>

User::User(char *nick, char psw[41], char *SDate, char *bDate, char *img, char *phra, char *internetP)
{

    nickname = new char[strlen(nick)+1];
    strcpy(nickname, nick);
    
    strcpy(password, psw);
    
    signDate = new char[strlen(SDate)+1];
    strcpy(signDate, SDate);
    
    if(bDate)
    {
        birthDate = new char[strlen(bDate)+1];
        strcpy(birthDate, bDate);
    }
    else
        birthDate = NULL;
        
    if(img)
    {
        image = new char[strlen(img)+1];
        strcpy(image, img);
    }
    else
        image = NULL;
        
    if(phra)
    {
        phrase = new char[strlen(phra)+1];
        strcpy(phrase, phra);
    }
    else
        phrase = NULL;
    
    ip = new char[strlen(internetP)+1];
    strcpy(ip, internetP);
    //ip = "192.168.0.102";    
    status = "Disponibile";    // Default status
}

User::User(User *U)
{
   
    this->nickname = new char[strlen(U->nickname)+1];
    strcpy(this->nickname, U->nickname);    
    
    strcpy(this->password, U->password); 
    
    this->signDate = new char[strlen(U->signDate)+1];
    strcpy(this->signDate, U->signDate);
    
    if(U->birthDate)
    {
        this->birthDate = new char[strlen(U->birthDate)+1];
        strcpy(this->birthDate, U->birthDate);
    }
    else
        this->birthDate = NULL;
        
    if(U->image)
    {
        this->image = new char[strlen(U->image)+1];
        strcpy(this->image, U->image);
    }
    else
        this->image = NULL;
        
    if(U->phrase)
    {
        this->phrase = new char[strlen(U->phrase)+1];
        strcpy(this->phrase, U->phrase);
    }
    else
        this->phrase = NULL;
     
    this->status = new char[strlen(U->status)+1];
    strcpy(this->status, U->status);
    
    this->ip = new char[strlen(U->ip)+1];
    strcpy(this->ip, U->ip);

}

User::~User()
{
    delete [] nickname;
    strcpy(password, "\0");
    delete [] signDate;
    if(birthDate) delete [] birthDate;
    if(image) delete [] image;
    if(phrase) delete [] phrase;
    delete [] status;
    delete [] ip;
}


