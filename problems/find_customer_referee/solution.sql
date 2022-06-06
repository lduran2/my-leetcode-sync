# Write your MySQL query statement below

# Table: Customer

# Report the names of the customer that are not referred by the
# customer with id = 2.

SELECT name
    FROM Customer
    WHERE
        # default to allowing NULL referee_ids
        coalesce((referee_id <> 2), TRUE)
;
