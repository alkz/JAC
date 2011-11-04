#ifndef USER_CLASS
#define USER_CLASS

class User
{
    friend class JACCMain;
    friend class JACCFrm;
    friend class JACCConv;
    
    public:
        User(char *, char [41], char *, char *, char *, char *, char *);
        User(User *);
        ~User();
    private:
        char *nickname;
        char password[41];
        char *signDate;
        char *birthDate;
        char *image;
        char *phrase;
        
        char *status;
        char *ip;
};

#endif
