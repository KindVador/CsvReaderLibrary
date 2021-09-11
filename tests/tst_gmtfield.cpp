//
// Created by Florian Contival on 10/09/2021.
//

#include <QtTest>
#include "gmtfield.hpp"

class GmtFieldTest: public QObject
{
Q_OBJECT

private:

private slots:
    void initTestCase() {
        qDebug("Called before everything else.");
    }

    void testDefaultConstructor() {
        GmtField *gmt = new GmtField();
        QVERIFY(gmt != nullptr);
    }

    void testInitConstructor() {
        GmtField *gmt = new GmtField(1000000L);
        QVERIFY(gmt != nullptr);
        QCOMPARE(gmt->toTimeStamp(), 1000000L);
    }

    void testDateTimeParsing_data() {
        QTest::addColumn<QString>("format");
        QTest::addColumn<QString>("value");
        QTest::addColumn<QDateTime>("result");

        QTest::addRow("FORMAT1") << "%j-%H:%M:%S-%f.%f" << "002-10:55:00-000.000" << QDateTime();
        QTest::addRow("FORMAT2") << "%j-%H:%M:%S-%f" << "144-14:25:00-062.500" << QDateTime();
        QTest::addRow("FORMAT3") << "%j-%H:%M:%S:%f" << "042-13:55:00:250" << QDateTime();
        QTest::addRow("FORMAT4") << "%j-%H:%M:%S" << "002-10:55:00" << QDateTime();
    }

    void testDateTimeParsing() {
        QFETCH(QString, format);
        QFETCH(QString, value);
        QFETCH(QDateTime, result);

        GmtField gmt = GmtField();

        QCOMPARE(gmt.toDateTime(), result);
    }

    void cleanupTestCase() {
        qDebug("Called after myFirstTest and mySecondTest.");
    }
};

QTEST_APPLESS_MAIN(GmtFieldTest)   // or QTEST_MAIN(CsvReaderTest) ?

#include "tst_gmtfield.moc"
