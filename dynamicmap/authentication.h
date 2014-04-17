#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <QCryptographicHash>
#include <QString>
#include <QDebug>

class Authentication
{
private:
    static const int usersCount;
    static const char* usernames[];
    static const char* pswdHashes[];
    static const char* ANONYMOUS_USERNAME;
    static QString currentUser;
public:
    Authentication();
    static bool auth(QString username, QString password);
    static QString getCurrentUser();
    static void logout();
};

#endif // AUTHENTICATION_H
