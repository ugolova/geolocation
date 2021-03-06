#include "authentication.h"

const char* Authentication::ANONYMOUS_USERNAME = "anonymous";

QString Authentication::currentUser = ANONYMOUS_USERNAME;

const int Authentication::usersCount = 2;

const char* Authentication::usernames[] = {
    "manager1",
    "manager2"
};

const char* Authentication::pswdHashes[] = {
    "a5c297c15e40ac3881db51277613aea3731b673a",
    "d2c9a46b3870e03e3c45c6a6ba0d7a574f50c698"
};

Authentication::Authentication()
{

}

bool Authentication::auth(QString username, QString password)
{
    for (int i = 0; i < usersCount; i++) {
        if (username.toStdString().compare(usernames[i]) == 0) {
            QCryptographicHash md5Generator(QCryptographicHash::Sha1);
            md5Generator.addData(password.toStdString().c_str());
            if (strcmp(pswdHashes[i], md5Generator.result().toHex()) == 0) {
                currentUser = username;
                return true;
            }
            return false;
        }
    }
    return false;
}

QString Authentication::getCurrentUser()
{
    return currentUser;
}

void Authentication::logout()
{
    currentUser = ANONYMOUS_USERNAME;
}
