# Please write a DELETE statement and DO NOT write a SELECT statement.
# Write your MySQL query statement below

# Table: Person

# Delete all the duplicate emails, keeping only one unique email with
# the smallest id.

# delete all emails not having the minimum ID of that email
DELETE FROM Person
    WHERE
        (id NOT IN
            (
                # guard against:
                #   You can't specify target table 'Person' for
                #   update in FROM clause
                SELECT min_id FROM
                (
                    # find the minimum IDs
                    # this must be SELECT because DELETE does not have GROUP BY
                    SELECT min(id) AS min_id
                        FROM Person
                        # the minimum ID for each email
                        GROUP BY email
                ) As MinIds
            )
        )
;