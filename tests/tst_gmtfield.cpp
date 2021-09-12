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

    void testToString_data() {
        QTest::addColumn<long long int>("value");
        QTest::addColumn<QString>("result");

        QTest::addRow("%d", 0) << SEC_IN_MICRO << "001-00:00:01";
        QTest::addRow("%d", 1) << MINUTE_IN_MICRO << "001-00:01:00";
        QTest::addRow("%d", 2) << HOUR_IN_MICRO << "001-01:00:00";
        QTest::addRow("%d", 3) << DAY_IN_MICRO << "002-00:00:00";
        QTest::addRow("%d", 4) << 10*HOUR_IN_MICRO + 35*MINUTE_IN_MICRO + 49*SEC_IN_MICRO << "001-10:35:49";
        QTest::addRow("%d", 5) << 23*HOUR_IN_MICRO + 59*MINUTE_IN_MICRO + 59*SEC_IN_MICRO << "001-23:59:59";
        QTest::addRow("%d", 6) << 28*DAY_IN_MICRO + 10*HOUR_IN_MICRO + 35*MINUTE_IN_MICRO + 49*SEC_IN_MICRO << "029-10:35:49";
        QTest::addRow("%d", 7) << (long long int)0 << "001-00:00:00";
        QTest::addRow("%d", 8) << 364*DAY_IN_MICRO + 23*HOUR_IN_MICRO + 59*MINUTE_IN_MICRO + 59*SEC_IN_MICRO << "365-23:59:59";
        QTest::addRow("%d", 9) << 82*DAY_IN_MICRO + 1*HOUR_IN_MICRO + 10*MINUTE_IN_MICRO + 20*SEC_IN_MICRO + 125*MILLI_IN_MICRO << "083-01:10:20-125";
        QTest::addRow("%d", 10) << 82*DAY_IN_MICRO + 1*HOUR_IN_MICRO + 10*MINUTE_IN_MICRO + 20*SEC_IN_MICRO + 125*MILLI_IN_MICRO + 68<< "083-01:10:20-125.068";
    }

    void testToString() {
        QFETCH(long long int, value);
        QFETCH(QString, result);

        GmtField gmt = GmtField(value);
        qDebug() << "gmt value:" << gmt.toString();
        QCOMPARE(gmt.toString(), result);
        QCOMPARE(gmt.toStdString(), result.toStdString());
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
