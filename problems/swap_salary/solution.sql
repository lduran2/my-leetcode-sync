# Write your MySQL query statement below

# Table: Salary

# Swap all 'f' and 'm' values (i.e., change all 'f' values to 'm' and
# vice versa) with a single update statement and no intermediate
# temporary tables.

# Note that you must write a single update statement, do not write any
# select statement for this problem.

UPDATE Salary
    SET sex =
    (
        # given a sex, return the opposite
        # return NULL if illegal value
        CASE
            WHEN sex = 'm' THEN 'f'
            WHEN sex = 'f' THEN 'm'
            ELSE NULL
        END
    )
;