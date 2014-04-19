#include "authentication_test.h"

AuthenticationTest::AuthenticationTest(QObject *parent) :
    QObject(parent)
{
}

void AuthenticationTest::testGetCurrentUser()
{
    QCOMPARE(Authentication::getCurrentUser(), Authentication::currentUser);
}

