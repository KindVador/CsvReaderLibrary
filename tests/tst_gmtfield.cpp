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
        auto *gmt = new GmtField();
        QVERIFY(gmt != nullptr);
    }

    void testInitConstructor() {
        auto *gmt = new GmtField(1000000L);
        QVERIFY(gmt != nullptr);
        QCOMPARE(gmt->toTimeStamp(), 1000000L);
    }

    void testEqualityOperators() {
        auto gmt1 = GmtField();
        auto gmt2 = GmtField();
        auto gmt3 = GmtField(10*HOUR_IN_MICRO + 35*MINUTE_IN_MICRO + 49*SEC_IN_MICRO, 2021);
        auto gmt4 = GmtField(10*HOUR_IN_MICRO + 35*MINUTE_IN_MICRO + 49*SEC_IN_MICRO, 2021);
        auto gmt5 = GmtField(10*HOUR_IN_MICRO + 35*MINUTE_IN_MICRO + 49*SEC_IN_MICRO, 1983);

        // equality checks
        QVERIFY(gmt1 == gmt2);
        QVERIFY(gmt2 == gmt1);
        QVERIFY(gmt3 == gmt4);
        QVERIFY(gmt4 == gmt3);
        QCOMPARE(gmt1 == gmt3, false);
        QCOMPARE(gmt4 == gmt2, false);
        QCOMPARE(gmt3 == gmt5, false);

        // non-equality checks
        QCOMPARE(gmt1 != gmt2, false);
        QCOMPARE(gmt2 != gmt1, false);
        QCOMPARE(gmt3 != gmt4, false);
        QCOMPARE(gmt4 != gmt3, false);
        QVERIFY(gmt1 != gmt3);
        QVERIFY(gmt4 != gmt2);
        QVERIFY(gmt3 != gmt5);
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

        auto gmt = GmtField(value);
        QCOMPARE(gmt.toString(), result);
        QCOMPARE(gmt.toStdString(), result.toStdString());
    }

    void testGetYear() {
        auto gmt = GmtField(0);
        QCOMPARE(gmt.getYear(), 1970);
    }

    void testSetYear() {
        auto gmt = GmtField(0);
        QCOMPARE(gmt.getYear(), 1970);
        gmt.setYear(2021);
        QCOMPARE(gmt.getYear(), 2021);
    }

    void testGetDate_data() {
        QTest::addColumn<long long int>("value");
        QTest::addColumn<int>("year");
        QTest::addColumn<QDate>("result");

        QTest::addRow("%d", 0) << (long long int)0 << 1970 << QDate(1970, 1, 1);
        QTest::addRow("%d", 1) << DAY_IN_MICRO << 1970 << QDate(1970, 1, 2);
        QTest::addRow("%d", 2) << 2*DAY_IN_MICRO << 1970 << QDate(1970, 1, 3);
        QTest::addRow("%d", 3) << 31*DAY_IN_MICRO << 2021 << QDate(2021, 2, 1);
        QTest::addRow("%d", 4) << 207*DAY_IN_MICRO << 1983 << QDate(1983, 7, 27);
        QTest::addRow("%d", 5) << 365*DAY_IN_MICRO << 1983 << QDate(1984, 1, 1);
    }

    void testGetDate() {
        QFETCH(long long int, value);
        QFETCH(int, year);
        QFETCH(QDate, result);

        auto gmt = GmtField(value);
        gmt.setYear(year);
        QCOMPARE(gmt.getDate(), result);
    }

    void testGetTime_data() {
        QTest::addColumn<long long int>("value");
        QTest::addColumn<QTime>("result");

        QTest::addRow("%d", 0) << (long long int)0 << QTime(0, 0, 0);
        QTest::addRow("%d", 1) << HOUR_IN_MICRO << QTime(1, 0, 0);
        QTest::addRow("%d", 2) << MINUTE_IN_MICRO << QTime(0, 1, 0);
        QTest::addRow("%d", 3) << SEC_IN_MICRO << QTime(0, 0, 1);
        QTest::addRow("%d", 4) << 13*HOUR_IN_MICRO + 31*MINUTE_IN_MICRO + 55*SEC_IN_MICRO << QTime(13, 31, 55);
        QTest::addRow("%d", 5) << 23*HOUR_IN_MICRO + 59*MINUTE_IN_MICRO + 59*SEC_IN_MICRO << QTime(23, 59, 59);
    }

    void testGetTime() {
        QFETCH(long long int, value);
        QFETCH(QTime, result);

        auto gmt = GmtField(value);
        QCOMPARE(gmt.getTime(), result);
    }

    void testToDateTime_data() {
        QTest::addColumn<long long int>("value");
        QTest::addColumn<int>("year");
        QTest::addColumn<QDate>("date");
        QTest::addColumn<QTime>("time");
        QTest::addColumn<QTimeZone>("tz");

        QTest::addRow("%d", 0) << (long long int)0 << 1970 << QDate(1970, 1, 1) << QTime(0, 0, 0) << QTimeZone::utc();
        QTest::addRow("%d", 1) << DAY_IN_MICRO + HOUR_IN_MICRO << 1970 << QDate(1970, 1, 2) << QTime(1, 0, 0) << QTimeZone::utc();
        QTest::addRow("%d", 2) << 2*DAY_IN_MICRO + MINUTE_IN_MICRO << 1970 << QDate(1970, 1, 3) << QTime(0, 1, 0) << QTimeZone::utc();
        QTest::addRow("%d", 3) << 31*DAY_IN_MICRO + SEC_IN_MICRO << 2021 << QDate(2021, 2, 1) << QTime(0, 0, 1) << QTimeZone::utc();
        QTest::addRow("%d", 4) << 207*DAY_IN_MICRO + 13*HOUR_IN_MICRO + 31*MINUTE_IN_MICRO + 55*SEC_IN_MICRO << 1983 << QDate(1983, 7, 27) << QTime(13, 31, 55) << QTimeZone::utc();
        QTest::addRow("%d", 5) << 365*DAY_IN_MICRO  + 23*HOUR_IN_MICRO + 59*MINUTE_IN_MICRO + 59*SEC_IN_MICRO << 1983 << QDate(1984, 1, 1) << QTime(23, 59, 59) << QTimeZone(3600);
    }

    void testToDateTime() {
        QFETCH(long long int, value);
        QFETCH(int, year);
        QFETCH(QDate, date);
        QFETCH(QTime, time);
        QFETCH(QTimeZone, tz);

        auto gmt = GmtField(value);
        gmt.setYear(year);
        QCOMPARE(gmt.toDateTime(tz), QDateTime(date, time, tz));
    }

    void testFromDateTime_data() {
        QTest::addColumn<long long int>("value");
        QTest::addColumn<int>("year");
        QTest::addColumn<QDate>("date");
        QTest::addColumn<QTime>("time");
        QTest::addColumn<QTimeZone>("tz");

        QTest::addRow("%d", 0) << (long long int)0 << 1970 << QDate(1970, 1, 1) << QTime(0, 0, 0) << QTimeZone::utc();
        QTest::addRow("%d", 1) << DAY_IN_MICRO + HOUR_IN_MICRO << 1970 << QDate(1970, 1, 2) << QTime(1, 0, 0) << QTimeZone::utc();
        QTest::addRow("%d", 2) << 2*DAY_IN_MICRO + MINUTE_IN_MICRO << 1970 << QDate(1970, 1, 3) << QTime(0, 1, 0) << QTimeZone::utc();
        QTest::addRow("%d", 3) << 31*DAY_IN_MICRO + SEC_IN_MICRO << 2021 << QDate(2021, 2, 1) << QTime(0, 0, 1) << QTimeZone::utc();
        QTest::addRow("%d", 4) << 207*DAY_IN_MICRO + 13*HOUR_IN_MICRO + 31*MINUTE_IN_MICRO + 55*SEC_IN_MICRO << 1983 << QDate(1983, 7, 27) << QTime(13, 31, 55) << QTimeZone::utc();
        QTest::addRow("%d", 5) << 23*HOUR_IN_MICRO + 59*MINUTE_IN_MICRO + 59*SEC_IN_MICRO << 1984 << QDate(1984, 1, 1) << QTime(23, 59, 59) << QTimeZone(3600);
    }

    void testFromDateTime() {
        QFETCH(long long int, value);
        QFETCH(int, year);
        QFETCH(QDate, date);
        QFETCH(QTime, time);
        QFETCH(QTimeZone, tz);

        auto inputDateTime = QDateTime(date, time, tz);
        auto gmt = GmtField::fromDateTime(inputDateTime);
        auto outputDateTime = gmt.toDateTime(tz);
        QCOMPARE(outputDateTime, inputDateTime);
        QCOMPARE(gmt.getValue(), value);
    }

    void testFindGmtFormat_data() {
        QTest::addColumn<QString>("input");
        QTest::addColumn<QString>("result");

        QTest::addRow("FORMAT: %%j-%%H:%%M:%%S-%%f.%%f") << "002-10:55:00-000.000" << "%j-%H:%M:%S-%f.%f";
        QTest::addRow("FORMAT: %%j-%%H:%%M:%%S-%%f.%%f") << "083-01:10:20-125.068" << "%j-%H:%M:%S-%f.%f";
        QTest::addRow("FORMAT: %%j-%%H:%%M:%%S-%%f") << "144-14:25:00-062" << "%j-%H:%M:%S-%f";
        QTest::addRow("FORMAT: %%j-%%H:%%M:%%S-%%f") << "099-01:10:20-125" << "%j-%H:%M:%S-%f";
        QTest::addRow("FORMAT: %%j-%%H:%%M:%%S:%%f") << "042-13:55:00:250" << "%j-%H:%M:%S:%f";
        QTest::addRow("FORMAT: %%j-%%H:%%M:%%S") << "002-10:55:00" << "%j-%H:%M:%S";
    }

    void testFindGmtFormat() {
        QFETCH(QString, input);
        QFETCH(QString, result);

        QCOMPARE(findGmtFormat(input), result);
    }

//    void testDateTimeParsing_data() {
//        QTest::addColumn<QString>("format");
//        QTest::addColumn<QString>("value");
//        QTest::addColumn<QDateTime>("result");
//
//        QTest::addRow("FORMAT1") << "%j-%H:%M:%S-%f.%f" << "002-10:55:00-000.000" << QDateTime();
//        QTest::addRow("FORMAT2") << "%j-%H:%M:%S-%f" << "144-14:25:00-062.500" << QDateTime();
//        QTest::addRow("FORMAT3") << "%j-%H:%M:%S:%f" << "042-13:55:00:250" << QDateTime();
//        QTest::addRow("FORMAT4") << "%j-%H:%M:%S" << "002-10:55:00" << QDateTime();
//    }
//
//    void testDateTimeParsing() {
//        QFETCH(QString, format);
//        QFETCH(QString, value);
//        QFETCH(QDateTime, result);
//
//        GmtField gmt = GmtField();
//
//        QCOMPARE(gmt.toDateTime(), result);
//    }

    void cleanupTestCase() {
        qDebug("Called after myFirstTest and mySecondTest.");
    }
};

QTEST_APPLESS_MAIN(GmtFieldTest)   // or QTEST_MAIN(CsvReaderTest) ?

#include "tst_gmtfield.moc"
