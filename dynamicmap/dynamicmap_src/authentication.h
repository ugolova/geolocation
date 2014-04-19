#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <QCryptographicHash>
#include <QString>
#include <QDebug>

class AuthenticationTest;

class Authentication
{
    friend class AuthenticationTest;
private:
    Authentication();
    static const int usersCount;
    static const char* usernames[];
    static const char* pswdHashes[];
    static const char* ANONYMOUS_USERNAME;
    static QString currentUser;
public:
    static bool auth(QString username, QString password);
    static QString getCurrentUser();
    static void logout();
};

#endif // AUTHENTICATION_H
