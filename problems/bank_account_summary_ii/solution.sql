# Write your MySQL query statement below

# Table: Users
# Table: Transactions

# Report the name and balance of users with a balance higher than
# 10000.  The balance of an account is equal to the sum of the amounts
# of all transactions involving that account.

SELECT
        name,
        # total transaction amounts for balance
        sum(amount) AS balance
    FROM
        # join all transactions to their users
        Users
        LEFT JOIN
            Transactions
            ON Users.account = Transactions.account
    # group by each of the Users' account IDs
    GROUP BY Users.account
    # use HAVING because WHERE clause does not recognize aggregates
    HAVING (balance > 10000)
;
