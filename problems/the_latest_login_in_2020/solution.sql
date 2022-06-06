# Write your MySQL query statement below

# Table: Logins

# Report the latest login for all users in the year 2020.

# group by user, year, and filter out 2020
SELECT
        user_id,
        max(time_stamp) AS last_stamp
    FROM
    (
        # extract the year from the time stamp
        SELECT
                user_id,
                time_stamp,
                extract(YEAR FROM time_stamp) AS year
            FROM Logins
    ) AS YearedLogins
    WHERE (year = 2020)
    # collect logins by user, year to find the max time_stamp
    GROUP BY user_id, year
;