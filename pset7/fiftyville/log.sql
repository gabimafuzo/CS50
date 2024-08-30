-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT description
FROM crime_scene_reports
WHERE day = 28
AND year = 2023
AND month = 7
AND street = 'Humphrey Street';

-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.

-- The activity of those who entered and exited the bakery during the robbery
SELECT activity, hour, minute, license_plate
FROM bakery_security_logs
WHERE day = 28
AND year = 2023
AND month = 7
AND hour = 10;

------------+------+--------+---------------+
--| activity | hour | minute | license_plate |
--+----------+------+--------+---------------+
--| entrance | 10   | 8      | R3G7486       |
--| entrance | 10   | 14     | 13FNH73       |
--| exit     | 10   | 16     | 5P2BI95       |
--| exit     | 10   | 18     | 94KL13X       |
--| exit     | 10   | 18     | 6P58WS2       |
--| exit     | 10   | 19     | 4328GD8       |
--| exit     | 10   | 20     | G412CB7       |
--| exit     | 10   | 21     | L93JTIZ       |
--| exit     | 10   | 23     | 322W7JE       |
--| exit     | 10   | 23     | 0NTHK55       |
--| exit     | 10   | 35     | 1106N58       |
--| entrance | 10   | 42     | NRYN856       |
--| entrance | 10   | 44     | WD5M8I6       |
--| entrance | 10   | 55     | V47T75I       |
--+----------+------+--------+---------------+

-- List of license plates associated with the names
SELECT people.license_plate, people.name, people.phone_number, people.passport_number
FROM people
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
WHERE day = 28
AND year = 2023
AND month = 7
AND hour = 10;

--+---------------+---------+----------------+-----------------+
--| license_plate |  name   |  phone_number  | passport_number |
--+---------------+---------+----------------+-----------------+
--| R3G7486       | Brandon | (771) 555-6667 | 7874488539      |
--| 13FNH73       | Sophia  | (027) 555-1068 | 3642612721      |
--| 5P2BI95       | Vanessa | (725) 555-4692 | 2963008352      |
--| 94KL13X       | Bruce   | (367) 555-5533 | 5773159633      |
--| 6P58WS2       | Barry   | (301) 555-4174 | 7526138472      |
--| 4328GD8       | Luca    | (389) 555-5198 | 8496433585      |
--| G412CB7       | Sofia   | (130) 555-0289 | 1695452385      |
--| L93JTIZ       | Iman    | (829) 555-5269 | 7049073643      |
--| 322W7JE       | Diana   | (770) 555-1861 | 3592750733      |
--| 0NTHK55       | Kelsey  | (499) 555-9472 | 8294398571      |
--| 1106N58       | Taylor  | (286) 555-6063 | 1988161715      |
--| NRYN856       | Denise  | (994) 555-3373 | 4001449165      |
--| WD5M8I6       | Thomas  | (286) 555-0131 | 6034823042      |
--| V47T75I       | Jeremy  | (194) 555-5027 | 1207566299      |
--+---------------+---------+----------------+-----------------+

--Select flight data for the people who were at the bakery at the time of the crime, with departure from Fiftyville
SELECT *
FROM flights
JOIN passengers ON flights.id = passengers.flight_id
WHERE passport_number IN (
    SELECT DISTINCT people.passport_number
    FROM people
    JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
    WHERE bakery_security_logs.day = 28
    AND bakery_security_logs.year = 2023
    AND bakery_security_logs.month = 7
    AND bakery_security_logs.hour = 10)
AND origin_airport_id = 8;


--+----+-------------------+------------------------+------+-------+-----+------+--------+-----------+-----------------+------+
--| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute | flight_id | passport_number | seat |
--+----+-------------------+------------------------+------+-------+-----+------+--------+-----------+-----------------+------+
--| 6  | 8                 | 5                      | 2023 | 7     | 28  | 13   | 49     | 6         | 3642612721      | 8A   |
--| 11 | 8                 | 12                     | 2023 | 7     | 30  | 13   | 7      | 11        | 4001449165      | 9C   |
--| 11 | 8                 | 12                     | 2023 | 7     | 30  | 13   | 7      | 11        | 8496433585      | 5D   |
--| 16 | 8                 | 2                      | 2023 | 7     | 26  | 20   | 44     | 16        | 6034823042      | 8D   |
--| 18 | 8                 | 6                      | 2023 | 7     | 29  | 16   | 0      | 18        | 3592750733      | 4C   |
--| 23 | 8                 | 11                     | 2023 | 7     | 29  | 12   | 15     | 23        | 7874488539      | 2C   |
--| 31 | 8                 | 3                      | 2023 | 7     | 30  | 20   | 21     | 31        | 3642612721      | 9B   |
--| 36 | 8                 | 4                      | 2023 | 7     | 29  | 8    | 20     | 36        | 1695452385      | 3B   |
--| 36 | 8                 | 4                      | 2023 | 7     | 29  | 8    | 20     | 36        | 5773159633      | 4A   |
--| 36 | 8                 | 4                      | 2023 | 7     | 29  | 8    | 20     | 36        | 8294398571      | 6C   |
--| 36 | 8                 | 4                      | 2023 | 7     | 29  | 8    | 20     | 36        | 1988161715      | 6D   |
--| 36 | 8                 | 4                      | 2023 | 7     | 29  | 8    | 20     | 36        | 8496433585      | 7B   |
--| 43 | 8                 | 1                      | 2023 | 7     | 29  | 9    | 30     | 43        | 3642612721      | 2C   |
--| 53 | 8                 | 9                      | 2023 | 7     | 29  | 15   | 20     | 53        | 6034823042      | 2C   |
--| 54 | 8                 | 5                      | 2023 | 7     | 30  | 10   | 19     | 54        | 3592750733      | 6C   |
--+----+-------------------+------------------------+------+-------+-----+------+--------+-----------+-----------------+------+

-- Passports of the people who were at the bakery and took a flight departing from Fiftyville.
SELECT passport_number FROM passengers
WHERE flight_id IN (
    SELECT id FROM flights
    WHERE origin_airport_id = 8
    AND passport_number IN (
            SELECT DISTINCT people.passport_number
            FROM people
            JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
            WHERE bakery_security_logs.day = 28
            AND bakery_security_logs.year = 2023
            AND bakery_security_logs.month = 7
            AND bakery_security_logs.hour = 10));

-- Names of the people whose passports match the above condition
SELECT * FROM people
WHERE passport_number IN (
    SELECT passport_number FROM passengers
    WHERE flight_id IN (
    SELECT id FROM flights
    WHERE origin_airport_id = 8
    AND passport_number IN (
            SELECT DISTINCT people.passport_number
            FROM people
            JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
            WHERE bakery_security_logs.day = 28
            AND bakery_security_logs.year = 2023
            AND bakery_security_logs.month = 7
            AND bakery_security_logs.hour = 10)));

--+--------+---------+----------------+-----------------+---------------+
--|   id   |  name   |  phone_number  | passport_number | license_plate |
--+--------+---------+----------------+-----------------+---------------+
--| 325548 | Brandon | (771) 555-6667 | 7874488539      | R3G7486       |
--| 398010 | Sofia   | (130) 555-0289 | 1695452385      | G412CB7       |
--| 449774 | Taylor  | (286) 555-6063 | 1988161715      | 1106N58       |
--| 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
--| 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
--| 560886 | Kelsey  | (499) 555-9472 | 8294398571      | 0NTHK55       |
--| 652412 | Denise  | (994) 555-3373 | 4001449165      | NRYN856       |
--| 660982 | Thomas  | (286) 555-0131 | 6034823042      | WD5M8I6       |
--| 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
--| 745650 | Sophia  | (027) 555-1068 | 3642612721      | 13FNH73       |
--+--------+---------+----------------+-----------------+---------------+

-- Interviewees who mentioned the bakery
SELECT *
FROM interviews
WHERE transcript LIKE '%bakery%';
--+-----+---------+------+-------+-----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
--| id  |  name   | year | month | day |                                                                                                                                                     transcript                                                                                                                                                      |
--+-----+---------+------+-------+-----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
--| 161 | Ruth    | 2023 | 7     | 28  | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
--| 162 | Eugene  | 2023 | 7     | 28  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
--| 163 | Raymond | 2023 | 7     | 28  | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |
--| 192 | Kiana   | 2023 | 5     | 17  | I saw Richard take a bite out of his pastry at the bakery before his pastry was stolen from him.                                                                                                                                                                                                                    |
--+-----+---------+------+-------+-----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+

-- Summary:
-- Spoke on the phone to book a flight on the 29th.
-- The person the thief spoke to on the phone was the same one who purchased the plane ticket.
-- The thief conducted bank transactions earlier on the 28th at the ATM on Leggett Street.
-- The call lasted less than 1 minute

-- Names of the people who took the flight on the 29th and were at the bakery at the time of the crime
SELECT * FROM people
WHERE passport_number IN (
    SELECT passport_number FROM passengers
    WHERE flight_id IN (
    SELECT id FROM flights
    WHERE origin_airport_id = 8
    AND day = 29
    AND passport_number IN (
            SELECT DISTINCT people.passport_number
            FROM people
            JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
            WHERE bakery_security_logs.day = 28
            AND bakery_security_logs.year = 2023
            AND bakery_security_logs.month = 7
            AND bakery_security_logs.hour = 10)));

--+--------+---------+----------------+-----------------+---------------+
--|   id   |  name   |  phone_number  | passport_number | license_plate |
--+--------+---------+----------------+-----------------+---------------+
--| 325548 | Brandon | (771) 555-6667 | 7874488539      | R3G7486       |
--| 398010 | Sofia   | (130) 555-0289 | 1695452385      | G412CB7       |
--| 449774 | Taylor  | (286) 555-6063 | 1988161715      | 1106N58       |
--| 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
--| 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
--| 560886 | Kelsey  | (499) 555-9472 | 8294398571      | 0NTHK55       |
--| 660982 | Thomas  | (286) 555-0131 | 6034823042      | WD5M8I6       |
--| 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
--| 745650 | Sophia  | (027) 555-1068 | 3642612721      | 13FNH73       |
--+--------+---------+----------------+-----------------+---------------+

-- Phone calls lasting less than 65 seconds on the 28th
SELECT *
FROM phone_calls
WHERE year = 2023
AND month= 07
AND day =28
AND duration <= 65;

--+-----+----------------+----------------+------+-------+-----+----------+
--| id  |     caller     |    receiver    | year | month | day | duration |
--+-----+----------------+----------------+------+-------+-----+----------+
--| 221 | (130) 555-0289 | (996) 555-8899 | 2023 | 7     | 28  | 51       |
--| 224 | (499) 555-9472 | (892) 555-8872 | 2023 | 7     | 28  | 36       |
--| 233 | (367) 555-5533 | (375) 555-8161 | 2023 | 7     | 28  | 45       |
--| 234 | (609) 555-5876 | (389) 555-5198 | 2023 | 7     | 28  | 60       |
--| 251 | (499) 555-9472 | (717) 555-1342 | 2023 | 7     | 28  | 50       |
--| 254 | (286) 555-6063 | (676) 555-6554 | 2023 | 7     | 28  | 43       |
--| 255 | (770) 555-1861 | (725) 555-3243 | 2023 | 7     | 28  | 49       |
--| 261 | (031) 555-6622 | (910) 555-3251 | 2023 | 7     | 28  | 38       |
--| 271 | (751) 555-6567 | (594) 555-6254 | 2023 | 7     | 28  | 61       |
--| 279 | (826) 555-1652 | (066) 555-9701 | 2023 | 7     | 28  | 55       |
--| 281 | (338) 555-6650 | (704) 555-2131 | 2023 | 7     | 28  | 54       |
--+-----+----------------+----------------+------+-------+-----+----------+

-- Combining all the information gathered so far
SELECT *
FROM phone_calls
JOIN people ON people.phone_number = phone_calls.caller
WHERE people.passport_number IN (
    SELECT passport_number FROM passengers
    WHERE flight_id IN (
    SELECT id FROM flights
    WHERE origin_airport_id = 8
    AND day = 29
    AND passport_number IN (
            SELECT DISTINCT people.passport_number
            FROM people
            JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
            WHERE bakery_security_logs.day = 28
            AND bakery_security_logs.year = 2023
            AND bakery_security_logs.month = 7
            AND bakery_security_logs.hour = 10)))
AND phone_calls.duration <= 65
AND phone_calls.day = 28;

-- Main suspects
--+-----+----------------+----------------+------+-------+-----+----------+--------+--------+----------------+-----------------+---------------+
--| id  |     caller     |    receiver    | year | month | day | duration |   id   |  name  |  phone_number  | passport_number | license_plate |
--+-----+----------------+----------------+------+-------+-----+----------+--------+--------+----------------+-----------------+---------------+
--| 221 | (130) 555-0289 | (996) 555-8899 | 2023 | 7     | 28  | 51       | 398010 | Sofia  | (130) 555-0289 | 1695452385      | G412CB7       |
--| 224 | (499) 555-9472 | (892) 555-8872 | 2023 | 7     | 28  | 36       | 560886 | Kelsey | (499) 555-9472 | 8294398571      | 0NTHK55       |
--| 233 | (367) 555-5533 | (375) 555-8161 | 2023 | 7     | 28  | 45       | 686048 | Bruce  | (367) 555-5533 | 5773159633      | 94KL13X       |
--| 251 | (499) 555-9472 | (717) 555-1342 | 2023 | 7     | 28  | 50       | 560886 | Kelsey | (499) 555-9472 | 8294398571      | 0NTHK55       |
--| 254 | (286) 555-6063 | (676) 555-6554 | 2023 | 7     | 28  | 43       | 449774 | Taylor | (286) 555-6063 | 1988161715      | 1106N58       |
--| 255 | (770) 555-1861 | (725) 555-3243 | 2023 | 7     | 28  | 49       | 514354 | Diana  | (770) 555-1861 | 3592750733      | 322W7JE       |
--+-----+----------------+----------------+------+-------+-----+----------+--------+--------+----------------+-----------------+---------------+

-- Filtering by the transaction location
SELECT * FROM people
WHERE id IN (
    SELECT person_id FROM bank_accounts
    JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
    WHERE atm_location LIKE '%Leggett Street%'
    AND day = 28
    AND year = 2023
    AND month = 7);

--+--------+---------+----------------+-----------------+---------------+
--|   id   |  name   |  phone_number  | passport_number | license_plate |
--+--------+---------+----------------+-----------------+---------------+
--| 395717 | Kenny   | (826) 555-1652 | 9878712108      | 30G67EN       |
--| 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
--| 438727 | Benista | (338) 555-6650 | 9586786673      | 8X428L0       |
--| 449774 | Taylor  | (286) 555-6063 | 1988161715      | 1106N58       |
--| 458378 | Brooke  | (122) 555-4581 | 4408372428      | QX4YZN3       |
--| 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
--| 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
--| 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
--| 948985 | Kaelyn  | (098) 555-1164 | 8304650265      | I449449       |
--+--------+---------+----------------+-----------------+---------------+

-- Combining transaction data with phone calls, flight details, and bakery footage
SELECT name FROM people
WHERE id IN (
    SELECT person_id FROM bank_accounts
    JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
    WHERE atm_location LIKE '%Leggett Street%'
    AND day = 28
    AND year = 2023
    AND month = 7)
INTERSECT
SELECT name
FROM phone_calls
JOIN people ON people.phone_number = phone_calls.caller
WHERE people.passport_number IN (
    SELECT passport_number FROM passengers
    WHERE flight_id IN (
    SELECT id FROM flights
    WHERE origin_airport_id = 8
    AND day = 29
    AND passport_number IN (
            SELECT DISTINCT people.passport_number
            FROM people
            JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
            WHERE bakery_security_logs.day = 28
            AND bakery_security_logs.year = 2023
            AND bakery_security_logs.month = 7
            AND bakery_security_logs.hour = 10
            AND bakery_security_logs.minute BETWEEN 15 and 26
            AND bakery_security_logs.activity = 'exit')))
AND phone_calls.duration <= 65
AND phone_calls.day = 28;

-- Two main suspects
--+-------+
--| name  |
--+-------+
--| Bruce |
--| Diana |
--+-------+

-- Phone numbers of the main suspects
SELECT * FROM people
WHERE name = 'Bruce'
or name = 'Diana';

--+--------+-------+----------------+-----------------+---------------+
--|   id   | name  |  phone_number  | passport_number | license_plate |
--+--------+-------+----------------+-----------------+---------------+
--| 514354 | Diana | (770) 555-1861 | 3592750733      | 322W7JE       |
--| 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
--+--------+-------+----------------+-----------------+---------------+

-- Flights taken by the main suspects
Select * from flights
JOIN passengers on passengers.flight_id = flights.id
JOIN people on passengers.passport_number = people.passport_number
WHERE  flights.day = 29
AND people.name = 'Diana'
or people.name = 'Bruce';


--+----+-------------------+------------------------+------+-------+-----+------+--------+-----------+-----------------+------+--------+-------+----------------+-----------------+---------------+
--| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute | flight_id | passport_number | seat |   id   | name  |  phone_number  | passport_number | license_plate |
--+----+-------------------+------------------------+------+-------+-----+------+--------+-----------+-----------------+------+--------+-------+----------------+-----------------+---------------+
--| 18 | 8                 | 6                      | 2023 | 7     | 29  | 16   | 0      | 18        | 3592750733      | 4C   | 514354 | Diana | (770) 555-1861 | 3592750733      | 322W7JE       | Boston
--| 36 | 8                 | 4                      | 2023 | 7     | 29  | 8    | 20     | 36        | 5773159633      | 4A   | 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       | New York City
--+----+-------------------+------------------------+------+-------+-----+------+--------+-----------+-----------------+------+--------+-------+----------------+-----------------+---------------+


-- Thief: Bruce, because the witness said they would be on the earlier flight on the 29th
-- Who received Bruce's call? (375) 555-8161

SELECT * FROM people
Where phone_number = '(375) 555-8161';

--Accomplice: Robin
--+--------+-------+----------------+-----------------+---------------+
--|   id   | name  |  phone_number  | passport_number | license_plate |
--+--------+-------+----------------+-----------------+---------------+
--| 864400 | Robin | (375) 555-8161 | NULL            | 4V16VO0       |
--+--------+-------+----------------+-----------------+---------------+


