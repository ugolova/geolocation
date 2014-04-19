#ifndef SAMPLE_TEST_H
#define SAMPLE_TEST_H

#include <QString>
#include <QtTest>

class SampleTest : public QObject
{
    Q_OBJECT

public:
    explicit SampleTest(QObject *parent = 0);

private Q_SLOTS:
    void testCase1();
};

#endif // SAMPLE_TEST_H
