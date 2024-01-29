-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Recommended to start by exploring the crime_scenes_reports table
.schema crime_scene_reports;

-- Get the id'S and descriptions of all the crime scene reports from the time and place
SELECT id, description
        FROM crime_scene_reports
       WHERE year = 2021
         AND month = 7
         AND day = 28
         AND street = "Humphrey Street";
-- From this I now know that the mystery's id is 295 and the theft took place at 10:15am at the Humphrey Street bakery.

-- I should look closer on the interviews table
SELECT id, name, transcript
        FROM interviews
       WHERE year = 2021
         AND month = 7
         AND day = 28;

-- Ruth (161) the thief leaving withing ten minutes of the theft
-- I should look closer into the bakery_security_logs table:
SELECT id, activity, license_plate, hour, minute
        FROM bakery_security_logs
       WHERE year = 2021
         AND month = 7
         AND day = 28
         AND hour = 10
         AND minute BETWEEN 15 AND 25;
    -- From this I know that it's one of the 8 cars exiting within that time range. But I need more i formation about the time fram before I know which one.


-- Eugene (162) the thief withdrew some money earlier that morning at the ATM om Leggett Street.
-- I should look closer into that security footage:
SELECT id, account_number, transaction_type, amount
        FROM atm_transactions
       WHERE year = 2021
         AND month = 7
         AND day = 28
         AND atm_location = "Leggett Street";
    -- From this I know that the thief's card number is in one of the 9 transactions.


-- Raymond (163) the thief called someone (less then 1 min) while leaving bakery. Thief is planning on taking the earliest flight out of fiftyville tomorrow. Thief asked person to purchase flight ticket.
-- I should look closer into the phone_calls table
SELECT id, caller, receiver, duration
        FROM phone_calls
       WHERE year = 2021
         AND month = 7
         AND day = 28
         AND duration < 60;
    -- From this I know that the thief's number is in one of the 9 calls.


-- Look further into the flights leaving from Fiftyville tomorrow morning (29/7)
SELECT id, abbreviation, full_name
        FROM airports
       WHERE city = "Fiftyville";
-- I now know that the id of the airport is 8 and the abbreviation is CSF.

-- Look further into the flights departing from the relevant airport
SELECT id, hour, minute
        FROM flights
       WHERE origin_airport_id = 8
         AND year = 2021
         AND month = 7
         AND day = 29;
-- I know that it's the first flight tomorrow (from the phone call) so it must be the 8.20 flight with id 36.

--Look further into the destinations
SELECT destination_airport_id
        FROM flights
       WHERE id = 36;
-- From the above I know that the airport destination is 4. Try and find out the name of the airport.

SELECT full_name, abbreviation, city
        FROM airports
       WHERE id = 4;
-- The flight is going to LaGuardia Airport (LGA) in New York City.

-- Look further into the passenger's list for the flight
SELECT passport_number, seat
        FROM passengers
       WHERE flight_id = 36;

-- Look further into the bank accouts to try and find a name.
SELECT person_id
        FROM bank_accounts
       WHERE account_number IN
            (SELECT account_number
               FROM atm_transactions
              WHERE year = 2021
                AND month = 7
                AND day = 28
                AND atm_location = "Leggett Street");


-- Finding out who the thief is by connecting all the relevant information from the queries above.
SELECT name, id, phone_number
        FROM people
       WHERE passport_number IN
            (SELECT passport_number
               FROM passengers
              WHERE flight_id = 36)
        AND license_plate IN
            (SELECT license_plate
               FROM bakery_security_logs
              WHERE year = 2021
                AND month = 7
                AND day = 28
                AND hour = 10
                AND minute BETWEEN 15 AND 25)
        AND phone_number IN
            (SELECT caller
               FROM phone_calls
              WHERE year = 2021
                AND month = 7
                AND day = 28
                AND duration < 60)
        AND id IN
            (SELECT person_id
               FROM bank_accounts
              WHERE account_number IN
                    (SELECT account_number
                       FROM atm_transactions
                       WHERE year = 2021
                       AND month = 7
                       AND day = 28
                       AND atm_location = "Leggett Street"));
-- Executing the above leads us to the thief - Bruce!


-- Finding out who the accomplice is by looking further into Bruce's phone call:
SELECT name, id
        FROM people
       WHERE phone_number IN
             (SELECT receiver
                FROM phone_calls
               WHERE year = 2021
                 AND month = 7
                 AND day = 28
                 AND duration < 60
                 AND caller = "(367) 555-5533");


-- As per earlier, finding out what city the thief escaped to:
SELECT destination_airport_id
        FROM flights
       WHERE id = 36;