#include <QString>
#include <QtTest>

class UntitledTest : public QObject
{
    Q_OBJECT

public:
    UntitledTest();

private Q_SLOTS:
    void testCase1();
};

UntitledTest::UntitledTest()
{
}

void UntitledTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(UntitledTest)

#include "tst_untitledtest.moc"
