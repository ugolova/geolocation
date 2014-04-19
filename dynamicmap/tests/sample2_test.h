#ifndef SAMPLE2_TEST_H
#define SAMPLE2_TEST_H

#include <QString>
#include <QtTest>

class Sample2Test : public QObject
{
    Q_OBJECT

public:
    explicit Sample2Test(QObject *parent = 0);

private Q_SLOTS:
    void testCase1();
};

#endif // SAMPLE2_TEST_H