-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Getting to know which crime was committed on given date and place
SELECT description from crime_scene_reports
WHERE street="Chamberlin Street"
AND year=2020
AND day = 28
AND month = 7;
-- transcripts to read (that day 6 transcripts)
-- Getting the interviews on that day with the 3 witnesses
-- the transcripts mention the courthouse
SELECT transcript from interviews
WHERE year = 2020
AND day = 28
AND month = 7
AND transcript LIKE "%courthouse%";
-- Getting the court logs for 10.15 on 28 July 2020, to know which
-- cars left the buidling in the 10-15 minutes after the theft
SELECT license_plate from courthouse_security_logs
WHERE activity = "exit"
AND year = 2020 AND month = 7 AND day = 28 AND hour = 10
AND minute BETWEEN 15 AND 25;
-- Which persons have those licence plates?
SELECT name FROM people
WHERE license_plate IN (SELECT license_plate from courthouse_security_logs
WHERE activity = "exit"
AND year = 2020 AND month = 7 AND day = 28 AND hour = 10
AND minute BETWEEN 15 AND 25);
-- Before 10.15 he of she withdrew money from the ATM
SELECT account_number FROM atm_transactions
WHERE transaction_type = "withdraw"
AND atm_location = "Fifer Street"
AND year = 2020 AND month = 7 AND day = 28;
-- Get the names behind these bank accounts
SELECT name FROM people
INNER JOIN bank_accounts ON person_id = people.id
WHERE account_number IN
(SELECT account_number FROM atm_transactions
WHERE transaction_type = "withdraw"
AND atm_location = "Fifer Street"
AND year = 2020 AND month = 7 AND day = 28);
-- SUSPECTS AT THIS MOMENT
SELECT name FROM people
WHERE license_plate IN (SELECT license_plate from courthouse_security_logs
WHERE activity = "exit"
AND year = 2020 AND month = 7 AND day = 28 AND hour = 10
AND minute BETWEEN 15 AND 25)
INTERSECT
SELECT name FROM people
INNER JOIN bank_accounts ON person_id = people.id
WHERE account_number IN
(SELECT account_number FROM atm_transactions
WHERE transaction_type = "withdraw"
AND atm_location = "Fifer Street"
AND year = 2020 AND month = 7 AND day = 28);
-- Talked on the phone less than a minute
-- while leaving courthouse
SELECT caller, receiver FROM phone_calls
WHERE year = 2020 AND month = 7 AND day = 28
AND duration < 61;
-- What are their names?
-- Callers
SELECT name, phone_number FROM people
WHERE phone_number IN
(SELECT caller FROM phone_calls
WHERE year = 2020 AND month = 7 AND day = 28
AND duration < 61);
-- Receivers
SELECT name, phone_number FROM people
WHERE phone_number IN
(SELECT receiver FROM phone_calls
WHERE year = 2020 AND month = 7 AND day = 28
AND duration < 61);
-- bought ticket around that time, on the earliest flight
-- from Fiftyville
-- get Fiftyvilles airport id
SELECT * FROM airports
WHERE city="Fiftyville";
-- search for outbound flight
SELECT id, day, hour, minute FROM flights
WHERE origin_airport_id = (SELECT id FROM airports WHERE city="Fiftyville")
AND year = 2020 AND month = 7
AND day = 29
ORDER BY day, hour, minute;
-- who was on this flight?
SELECT name FROM people
INNER JOIN passengers
ON people.passport_number = passengers.passport_number
INNER JOIN flights ON passengers.flight_id = flights.id
WHERE flights.id = (SELECT flights.id FROM flights
INNER JOIN airports ON origin_airport_id = airports.id
WHERE origin_airport_id = (SELECT airports.id FROM airports
WHERE city="Fiftyville")
AND year = 2020 AND month = 7
AND day = 29
ORDER BY day, hour, minute
LIMIT 1);
-- is dit wel de juiste vlucht?
-- where is it flying to?
SELECT city FROM airports
WHERE id =
(SELECT destination_airport_id FROM flights
WHERE id = 36);

-- out: accomplice

-- OTHER CLUES