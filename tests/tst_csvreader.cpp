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

    void testDefaultConstructor() {
        CsvReader *reader = new CsvReader();
        QVERIFY(reader != nullptr);
        QCOMPARE(reader->separator(), QChar());
        QCOMPARE(reader->comments(), QChar());
    }

    void testInitConstructor() {
        QString testFilePath = QString("");
        CsvReader *reader = new CsvReader(testFilePath, QChar(';'), QChar('#'));
        QVERIFY(reader != nullptr);
        QCOMPARE(reader->separator(), QChar(';'));
        QCOMPARE(reader->comments(), QChar('#'));
    }

    void cleanupTestCase() {
        qDebug("Called after myFirstTest and mySecondTest.");
    }
};

QTEST_APPLESS_MAIN(CsvReaderTest)   // or QTEST_MAIN(CsvReaderTest) ?

#include "tst_csvreader.moc"
