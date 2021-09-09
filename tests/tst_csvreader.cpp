#include <QtTest>
#include "csvreader.hpp"

class CsvReaderTest: public QObject
{
    Q_OBJECT

private:
    bool myCondition()
    {
        return true;
    }

private slots:
    void initTestCase() {
        qDebug("Called before everything else.");
    }

    void testFile1() {

    }

    void myFirstTest() {
        QVERIFY(true);      // check that a condition is satisfied
        QCOMPARE(1, 1);     // compare two values
    }

    void mySecondTest() {
        QVERIFY(myCondition());
        QVERIFY(1 != 2);
    }

    void cleanupTestCase() {
        qDebug("Called after myFirstTest and mySecondTest.");
    }
};

QTEST_APPLESS_MAIN(CsvReaderTest)

#include "tst_csvreader.moc"
