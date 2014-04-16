#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <cstring>
#include <QCryptographicHash>
#include <QString>
#include <QDebug>

class Authentication
{
private:
    static const int usersCount;
    static const char* usernames[];
    static const char* pswdHashes[];
public:
    Authentication();
    static bool auth(QString username, QString password);
};

#endif // AUTHENTICATION_H
