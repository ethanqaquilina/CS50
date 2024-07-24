-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Check crime reports on day of crime
SELECT description
FROM crime_scene_reports
WHERE day = 28
AND year = 2023
AND month = 7
AND street = 'Humphrey Street';

-- Check security logs of the robbery in 10 min time frame
SELECT *
FROM bakery_security_logs
JOIN people ON bakery_security_logs.license_plate = people.license_plate
WHERE bakery_security_logs.day = 28
AND bakery_security_logs.year = 2023
AND bakery_security_logs.month = 7
AND bakery_security_logs.hour = 10
AND bakery_security_logs.minute >= 15
AND bakery_security_logs.minute <= 25

-- Check interviews of that day
SELECT name, transcript
FROM interviews
WHERE day = 28
AND year = 2023
AND month = 7

-- Check who made transactions on that morning legget street
SELECT *
FROM atm_transactions
JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
JOIN people ON bank_accounts.person_id = people.id
WHERE year = 2023
AND month = 7
AND day = 28
AND atm_location = 'Leggett Street'

-- Check phone calls that day
SELECT people.name
FROM phone_calls
JOIN people ON phone_calls.caller = people.phone_number
WHERE year = 2023
AND month = 7
AND day = 28
AND duration < 60

-- Check who Diana and Bruce called
SELECT people.name
FROM phone_calls
JOIN people ON phone_calls.receiver = people.phone_number
WHERE year = 2023
AND month = 7
AND day = 28
AND duration < 60
AND phone_calls.caller = (
    SELECT phone_number
    FROM people
    WHERE name = 'Diana'
)


-- View flights on July 29th
SELECT *
FROM flights
WHERE year = 2023
AND month = 7
AND day = 29
ORDER BY hour ASC, minute ASC

-- View Passengers on flight 36
SELECT name
FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
WHERE passengers.flight_id = 36

-- View flight 36 Destination
SELECT city
FROM airports
WHERE id = (
    SELECT destination_airport_id
    FROM flights
    WHERE id = 36
)
