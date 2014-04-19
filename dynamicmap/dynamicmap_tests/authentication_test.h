#ifndef AUTHENTICATION_TEST_H
#define AUTHENTICATION_TEST_H

#include <QtTest>

#include "../dynamicmap_src/authentication.h"

class AuthenticationTest : public QObject
{
    Q_OBJECT

public:
    explicit AuthenticationTest(QObject *parent = 0);

private Q_SLOTS:
    void testGetCurrentUser();
};

#endif // AUTHENTICATION_TEST_H
