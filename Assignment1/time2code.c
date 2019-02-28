// Time2Code
// David Nguyen z5166106
// FINAL VERSION 1.0 - 27/3/18

#include <stdio.h>
#include <assert.h>

// Towns

#define TOWN_ADELAIDE       0
#define TOWN_BRISBANE       1
#define TOWN_BROKEN_HILL    2
#define TOWN_CANBERRA       3
#define TOWN_DARWIN         4
#define TOWN_EUCLA          5
#define TOWN_HOBART         6
#define TOWN_LORD_HOWE_IS   7
#define TOWN_MELBOURNE      8
#define TOWN_PERTH          9
#define TOWN_SYDNEY         10

// New Zealand

#define TOWN_AUCKLAND       11
#define TOWN_CHRISTCHURCH   12
#define TOWN_WELLINGTON     13

// Australia

#define TIMEZONE_AWST_OFFSET  800 // Australian Western Standard Time

#define TIMEZONE_ACWST_OFFSET 845 // Australian Central Western Standard Time

#define TIMEZONE_ACST_OFFSET  930 // Australian Central Standard Time
#define TIMEZONE_ACDT_OFFSET 1030 // Australian Central Daylight Time

#define TIMEZONE_AEST_OFFSET 1000 // Australian Eastern Standard Time
#define TIMEZONE_AEDT_OFFSET 1100 // Australian Eastern Daylight Time

#define TIMEZONE_LHST_OFFSET 1030 // Lord Howe Standard Time
#define TIMEZONE_LHDT_OFFSET 1100 // Lord Howe Daylight Time

// New Zealand
#define TIMEZONE_NZST_OFFSET 1200 // NZ Standard Time
#define TIMEZONE_NZDT_OFFSET 1300 // NZ Daylight Time

// returned by get_local_time
#define INVALID_INPUT (-1)

// Months
#define JANUARY 1
#define FEBRUARY 2
#define MARCH 3
#define APRIL 4
#define MAY 5
#define JUNE 6
#define JULY 7
#define AUGUST 8
#define SEPTEMBER 9
#define OCTOBER 10
#define NOVEMBER 11
#define DECEMBER 12

int get_local_time  (int town, int utc_month, int utc_day, int utc_time);
void run_unit_tests (void);

int get_timezone (int town, int utc_month, int utc_day, int utc_time);
int fix_time     (int utc_time, int result, int timezone, int town);
int time_correction    (int utc_time, int result, int timezone);
int utc_timecorrection (int utc_time);

int main(void) {
    int call_get_local_time = 0;

    printf("Enter 0 to call run_unit_tests()\n");
    printf("Enter 1 to call get_local_time()\n");
    printf("Call which function: ");
    scanf("%d", &call_get_local_time);

    if (!call_get_local_time) {
        printf("calling run_unit_tests()\n");
        run_unit_tests();
        printf("unit tests done\n");
        return 0;
    }

    int town = 0;
    int month = 0;
    int day = 0;
    int time = 0;

    printf("Enter %d for Adelaide\n", TOWN_ADELAIDE);
    printf("Enter %d for Brisbane\n", TOWN_BRISBANE);
    printf("Enter %d for Broken_hill\n", TOWN_BROKEN_HILL);
    printf("Enter %d for Canberra\n", TOWN_CANBERRA);
    printf("Enter %d for Darwin\n", TOWN_DARWIN);
    printf("Enter %d for Eucla\n", TOWN_EUCLA);
    printf("Enter %d for Hobart\n", TOWN_HOBART);
    printf("Enter %d for Lord Howe Island\n", TOWN_LORD_HOWE_IS);
    printf("Enter %d for Melbourne\n", TOWN_MELBOURNE);
    printf("Enter %d for Perth\n", TOWN_PERTH);
    printf("Enter %d for Sydney\n", TOWN_SYDNEY);
    printf("Enter %d for Auckland\n", TOWN_AUCKLAND);
    printf("Enter %d for Christchurch\n", TOWN_CHRISTCHURCH);
    printf("Enter %d for Wellington\n", TOWN_WELLINGTON);

    printf("Which town: ");
    scanf("%d", &town);

    printf("Enter UTC month as integer 1..12: ");
    scanf("%d", &month);

    printf("Enter UTC day as integer 1..31: ");
    scanf("%d", &day);

    printf("Enter UTC time as hour * 100 + minutes\n");
    printf("Enter UTC time as integer [0..2359]: ");
    scanf("%d", &time);

    int local_time = get_local_time(town, month, day, time);

    if (local_time == INVALID_INPUT) {
        printf("invalid input - local time could not be calculated\n");
    } else {
        printf("local_time is %d\n", local_time);
    }

    return 0;
}

// Given an Australian town and a 2018 UTC time
// return the local time in the Australian town
//
// time is returned as hours*100 + minutes
// INVALID_INPUT is return for invalid inputs
//
// utc_month should be 1..12
// utc_day should be 1..31
// utc_time should be 0..2359
// utc_time is hours*100 + minutes
//
// note UTC year is assumed to be 2018
// note UTC seconds is assumed to be zero

int get_local_time(int town, int utc_month, int utc_day, int utc_time) {
	utc_time = utc_timecorrection(utc_time);
    int timezone = get_timezone(town, utc_month, utc_day, utc_time);
    int result = utc_time + timezone;

    if (town < 0 || town > 13 || utc_day > 31 || utc_month > DECEMBER || 
        utc_day < 1 || utc_month < JANUARY || (utc_month == FEBRUARY && 
        utc_day > 28) || (utc_month == APRIL && utc_day == 31)|| 
        (utc_month == JUNE && utc_day == 31) || (utc_month == SEPTEMBER && 
        utc_day == 31)|| (utc_month == NOVEMBER && utc_day == 31) || 
        utc_time >  2400){
    // All these conditions warrant invalid inputs; entering an unspecified town
    // , unspecified day, month and time
        result = INVALID_INPUT;
    } else if (result >= 2400) {
        if(result == 2400) {
        // If the final time is 2400 it is 0
            result = 0;
        } else if (result > 2400) {
        // If the final time is >2400 it is FINAL TIME - 2400
            result = result - 2400;
        }
    }

// Passed into fix_time to correct any times e.g. 1963 -> 2003
    result = fix_time(utc_time, result, timezone, town);

    return result;
}

// To get correct timezone conversions from UTC e.g. daylight saving time
// and standard

int get_timezone(int town, int utc_month, int utc_day, int utc_time) {

    int zone;

    if (town == TOWN_PERTH || town == TOWN_EUCLA) {
    // Perth uses AWST and Eucla uses ACWST
        zone = TIMEZONE_AWST_OFFSET;
        if (town == TOWN_EUCLA) {
            zone = TIMEZONE_ACWST_OFFSET;
        }
    } else if (town == TOWN_ADELAIDE || town == TOWN_BROKEN_HILL || town == 
               TOWN_DARWIN) {
    // These towns use ACST and ACDT (excluding Darwin)
        zone = TIMEZONE_ACST_OFFSET;
        if (((utc_month == OCTOBER && utc_day >= 7 && utc_time >= 200) || 
            (utc_month > OCTOBER) || (utc_month == APRIL && utc_day == 1 && 
            utc_time <  0300) || (utc_month < APRIL)) && town != TOWN_DARWIN) {
        // Darwin does not use daylight saving, if the daylight saving conditions are met
        // then the timezone becomes Daylight Time (DT)
            zone = TIMEZONE_ACDT_OFFSET;
        }
    } else if (town == TOWN_BRISBANE || town == TOWN_CANBERRA || town == 
               TOWN_HOBART || town == TOWN_MELBOURNE || town == TOWN_SYDNEY) {
    // These towns use AEDT and AEST
        if (((utc_month == OCTOBER && utc_day >= 7 && utc_time >= 200) || 
            (utc_month > OCTOBER) || (utc_month == APRIL && utc_day == 1 && 
            utc_time < 300) || utc_month < APRIL) && town != TOWN_BRISBANE) {
    // Brisbane does not use AEDT, but if the daylight saving conditions are met
    // then the other towns must use AEDT
            zone = TIMEZONE_AEDT_OFFSET;
        } else {
            zone = TIMEZONE_AEST_OFFSET; 
        }
    } else if (town == TOWN_AUCKLAND || town == TOWN_CHRISTCHURCH || town == 
               TOWN_WELLINGTON) {
    // These NZ towns use NZST and NZDT
        zone = TIMEZONE_NZST_OFFSET;
        if ((utc_month >= SEPTEMBER && utc_day == 30) || (utc_month > SEPTEMBER 
            ||utc_month < APRIL) ||  (utc_month == APRIL && utc_day == 1 && 
            utc_time < 300)) {
    // If they satisfy the NZ daylight saving dates then the timezone will be 
    // set to NZDT
            zone = TIMEZONE_NZDT_OFFSET;
        }
    } else {
    // Default is LHST 
        zone = TIMEZONE_LHST_OFFSET;
        if ((utc_month == OCTOBER && utc_day >= 7 && utc_time >= 200) || 
            (utc_month > OCTOBER) || (utc_month == APRIL && utc_day == 1 && 
            utc_time < 0300) || utc_month < APRIL) {
    // If daylight saving conditions are met then LHDT is used as timezone
            zone = TIMEZONE_LHDT_OFFSET;
        }
    }

    return zone;
}

// fix_time is mostly for the timezones that are 9.5 or 10.5 or 845 
// Since these weren't fixed correctly in time_correct

int fix_time(int utc_time, int result, int timezone, int town){

    if (town == TOWN_EUCLA) { 
    // Since Eucla has 845, it's difficult to fix, so by minusing 39 and then 
    // adding 39 after time_correction it correctly fixes the time. 
    // e.g. 059 + 806 -> time_correction(864) -> (905) + 39 -> 943
    // If this result is something like 960 then it gets passed into the 2nd
    // time_correction to fix that result otherwise it is the correct form
        result = result - 39;
        result = time_correction (utc_time, result, timezone) + 39;
        result = time_correction (utc_time, result, timezone);
    } else if (town == TOWN_BROKEN_HILL || town == TOWN_ADELAIDE || town == 
               TOWN_DARWIN ){ 
    // Since these 3 towns are 9.5 or 10.5 timezone, then i have to also 
    // propose a fix. By removing 30 first and plugging it into time_correction
    // and then adding back the 30 it correctly fixes the time. 
    // e.g. 2359 + 900 -> time_correction(859) -> (859) + 30 -> 889
    // This gets passed into the 2nd time_correction to fix it
    // 889 -> 929
        result = result - 30;
        result = time_correction (utc_time, result, timezone) + 30;
        result = time_correction (utc_time, result, timezone);
    // Similar to the previous comments, but for a different town.
    } else if (town == TOWN_LORD_HOWE_IS) {
        result = result - 30;
        result = time_correction (utc_time, result, timezone) + 30;
        result = time_correction (utc_time, result, timezone);
    // The other towns only need to get passed into a normal time_correction
    } else {
        result = time_correction (utc_time, result, timezone);
    }
    return result;
}

// This corrects any final time e.g. 2360 -> 0, 1560 -> 1600
// However doesn,t work for Eucla, Broken Hill and LordHoweIs on its own
// Must be modified (check in fix_time)

int time_correction (int utc_time, int result, int timezone) {

    if ((result >= 060 && result < 100) || (result >= 2360 && result < 2400)) {
    // If the final time is between 060 and 100 it will add 40 -> e.g. 67 = 107
        result = result + 40;
    } else if ((result >= 160 && result < 200) || (result >= 260 && result < 300
                )) {
    // Similar to the previous but from 160 - 200 this time -> e.g. 180 -> 220
        result = result + 40;
    } else if ((result >= 360 && result < 400) || (result >= 460 && result < 500
                )) {
    // Similar to the above ones, but between 360 and 400. e.g. 490 -> 530
        result = result + 40;
    } else if ((result >= 560 && result < 600) || (result >= 660 && result < 700
                )) {
        result = result + 40;
    } else if  ((result >= 760 && result < 800) || (result >= 860 && result < 
                900)) {
        result = result + 40;
    } else if  ((result >= 960 && result < 1000) || (result >= 2060 && result <
                2100)) {
        result = result + 40; 
    } else if ((result >= 1060 && result < 1100) || (result >= 1160 && result <
                1200)) {
        result = result + 40;
    } else if ((result >= 1260 && result < 1300) || (result >= 1360 && result < 
                1400)) {
        result = result + 40;
    } else if ((result >= 1460 && result < 1500) || (result >= 1560 && result < 
                1600)) {
        result = result + 40;
    } else if ((result >= 1660 && result < 1700) || (result >= 1760 && result < 
                1800)) {
        result = result + 40;
    } else if ((result >= 1860 && result < 1900) || (result >= 1960 && result < 
                2000)) {
        result = result + 40;
    } else if ((result >= 2160 && result < 2200) || (result >= 2260 && result < 
                2300)) {
        result = result + 40;
    } 
    return result;
}

// This function corrects input utc_time. (entering 260 = 300)

int utc_timecorrection (int utc_time){

	if ((utc_time >= 060 && utc_time < 100) || (utc_time >= 2360 && utc_time < 2400)) {
    // If utc_time is between 60 and 100 it will add 40 -> e.g. 67 = 107
        utc_time = utc_time + 40;
    } else if ((utc_time >= 160 && utc_time < 200) || (utc_time >= 260 && utc_time < 300
                )) {
    // Similar to the previous but from 160 - 200 this time -> e.g. 180 -> 220
        utc_time = utc_time + 40;
    } else if ((utc_time >= 360 && utc_time < 400) || (utc_time >= 460 && utc_time < 500
                )) {
    // Similar to the above ones, but between 360 and 400. e.g. 490 -> 530
        utc_time = utc_time + 40;
    } else if ((utc_time >= 560 && utc_time < 600) || (utc_time >= 660 && utc_time < 700
                )) {
        utc_time = utc_time + 40;
    } else if  ((utc_time >= 760 && utc_time < 800) || (utc_time >= 860 && utc_time < 
                900)) {
        utc_time = utc_time + 40;
    } else if  ((utc_time >= 960 && utc_time < 1000) || (utc_time >= 2060 && utc_time <
                2100)) {
        utc_time = utc_time + 40; 
    } else if ((utc_time >= 1060 && utc_time < 1100) || (utc_time >= 1160 && utc_time <
                1200)) {
        utc_time = utc_time + 40;
    } else if ((utc_time >= 1260 && utc_time < 1300) || (utc_time >= 1360 && utc_time < 
                1400)) {
        utc_time = utc_time + 40;
    } else if ((utc_time >= 1460 && utc_time < 1500) || (utc_time >= 1560 && utc_time < 
                1600)) {
        utc_time = utc_time + 40;
    } else if ((utc_time >= 1660 && utc_time < 1700) || (utc_time >= 1760 && utc_time < 
                1800)) {
        utc_time = utc_time + 40;
    } else if ((utc_time >= 1860 && utc_time < 1900) || (utc_time >= 1960 && utc_time < 
                2000)) {
        utc_time = utc_time + 40;
    } else if ((utc_time >= 2160 && utc_time < 2200) || (utc_time >= 2260 && utc_time < 
                2300)) {
        utc_time = utc_time + 40;
    } 

	return utc_time;
}

// Firstly, i made sure that some days, months and times returned invalid. 
// Then i proceed to convert the entered UTC time into local time with timezone additions
// In the fixtime function; it fixes any time that is similar to ??60 or above to the nearest hour
// This includes entered UTC and the RESULT.

// run unit tests for get_local_time

void run_unit_tests(void) {
    // (1) UTC midnight on 20th March -> time in Sydney: 11am AEDT
    assert(get_local_time(TOWN_SYDNEY, 3, 20, 0) == 1100);

    // (2) Testing for invalid months (42 is not valid)
    assert(get_local_time(TOWN_CANBERRA, 42, 0, 0) == INVALID_INPUT);

    // (3) Testing for invalid days (41 is not valid)
    assert(get_local_time(TOWN_EUCLA, 4, 41, 0) == INVALID_INPUT);

    // (4) Sydney - Test if limit is 2400 = (0)
    assert(get_local_time(TOWN_SYDNEY, 3, 20, 1300) == 0);

    // (5) Sydney - Test if daylight saving time is adjusted
    assert(get_local_time(TOWN_SYDNEY, 4, 1, 100) == 1200);

    // (6) Sydney - Test if standard time is working for Sydney
    assert(get_local_time(TOWN_SYDNEY, 4, 20, 1500) == 100);

    // (7) Darwin - Test if Darwin only uses Standard Time
    assert(get_local_time(TOWN_DARWIN, 3, 15, 200) == 1130);

    // (8) Darwin - Test if hours are correct (1460 = 1500)
    assert(get_local_time(TOWN_DARWIN, 4, 12, 1560) == 130);

    // (9) Darwin - Test if conversions are correct (2359 == 929)
    assert(get_local_time(TOWN_DARWIN, 12, 23, 2359) == 929);

    // (10) Adelaide - Test if daylight saving works 
    assert(get_local_time(TOWN_ADELAIDE, 3, 14, 500) == 1530);

    // (11) Adelaide - Test if standard time works
    assert(get_local_time(TOWN_ADELAIDE, 6, 23, 359) == 1329);

    // (12) Adelaide - Test if conversions work (1260 = 1300)
    assert(get_local_time(TOWN_ADELAIDE, 9, 30, 260) == 1230);

    // (13) February should not have more than 28 days
    assert(get_local_time(TOWN_WELLINGTON, 2, 29, 0) == INVALID_INPUT);

    // (14) April should not have more than 30 days
    assert(get_local_time(TOWN_CANBERRA, 4, 31, 0) == INVALID_INPUT);

    // (15) June should not have more than 30 days
    assert(get_local_time(TOWN_BRISBANE, 6, 31, 0) == INVALID_INPUT);

    // (16) September should not have more than 30 days
    assert(get_local_time(TOWN_HOBART, 9, 31, 0) == INVALID_INPUT);

    // (17) November should not have more than 30 days 
    assert(get_local_time(TOWN_LORD_HOWE_IS, 11, 31, 0) == INVALID_INPUT);

    // (18) Time should not be over 2400 
    assert(get_local_time(TOWN_CHRISTCHURCH, 12, 24, 2934) == INVALID_INPUT);

    // (19) Lord Howe Island - Test if standard time works
    assert(get_local_time(TOWN_LORD_HOWE_IS, 5, 21, 330) == 1400);

    // (20) Lord Howe Island - Test if daylight saving works
    assert(get_local_time(TOWN_LORD_HOWE_IS, 3, 12, 559) == 1659);

    // (21) Lord Howe Island - Test if conversions are working correctly
    assert(get_local_time(TOWN_LORD_HOWE_IS, 5, 23, 660) == 1730);

    // (22) Auckland - Test if standard time is working correctly
    assert(get_local_time(TOWN_AUCKLAND, 6, 12, 439) == 1639);

    // (23) Auckland - Test if daylight saving is working correctly
    assert(get_local_time(TOWN_AUCKLAND, 2, 5, 330) == 1630);

    // (24) Auckland - Test if conversions are working correctly
    assert(get_local_time(TOWN_AUCKLAND, 9, 23, 763) == 2003);

    // (25) Town must not be larger than 13
    assert(get_local_time(15, 1, 2, 0) == INVALID_INPUT);

    // (26) Town must not be lower than 0
    assert(get_local_time(-3, 4, 3, 1200) == INVALID_INPUT);

    // (27) Perth - has no daylight saving 
    assert(get_local_time(TOWN_PERTH, 3, 2, 0) == 800);

    // (28) Perth - Testing conversion accuracy
    assert(get_local_time(TOWN_PERTH, 6, 21, 990) == 1830);

    // (29) Eucla - Has no daylight saving 
    assert(get_local_time(TOWN_EUCLA, 2, 12, 500) == 1345);

    // (30) Eucla - Testing conversion accuracy
    assert(get_local_time(TOWN_EUCLA, 5, 11, 2159) == 644);

    // (31) Eucla - Testing conversion accuracy
    assert(get_local_time(TOWN_EUCLA, 11, 30, 59) == 944);

    // (32) Eucla - Testing conversion accuracy again
    assert(get_local_time(TOWN_EUCLA, 3, 4, 183) == 1108);

    // (33) Conversion Accuracy 
    assert(get_local_time(TOWN_AUCKLAND, 2, 13, 198) == 1538);

    // (34) Conversion Accuracy 
    assert(get_local_time(TOWN_SYDNEY, 1, 12, 294) == 1434);

    // (35) Broken Hill - Test if daylight saving is working
    assert(get_local_time(TOWN_BROKEN_HILL, 1, 14, 0) == 1030);
 
    // (36) Broken Hill - Test if standard time is correct
    assert(get_local_time(TOWN_BROKEN_HILL, 5, 11, 0) == 930);

    // (37) Broken Hill - Conversion accuracy (193 UTC convereted to ACST)
    assert(get_local_time(TOWN_BROKEN_HILL, 8, 12, 193) == 1203);

    // (38) Broken Hill - Conversion accuracy (daylight saving)
    assert(get_local_time(TOWN_BROKEN_HILL, 11, 30, 598) == 1708);

    // (39) Conversion Accuracy (Daylight Saving)
    assert(get_local_time(TOWN_SYDNEY, 11, 12, 698) == 1838);

    // (40) Conversion Accuracy (Standard) 
    assert(get_local_time(TOWN_LORD_HOWE_IS, 5, 6, 798) == 1908);

    // (41) Testing for Daylight saving after 200
    assert(get_local_time(TOWN_SYDNEY, 4, 1, 300) == 1300);

    // (42) Adelaide - Conversion accuracy (193 UTC convereted)
    assert(get_local_time(TOWN_ADELAIDE, 8, 12, 193) == 1203);
}
