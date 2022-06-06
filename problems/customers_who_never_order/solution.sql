# Write your MySQL query statement below

# Table: Customers

# Table: Orders

# Report all customers who never order anything.

# select the name of those Customers
SELECT name AS Customers
    FROM
    (
        SELECT
                Customers.id,
                name,
                # count the number of Orders per each of the Customers
                #   NULL represent no orders
                sum(Orders.id) AS numOrders
            FROM
                # join Orders to Customers
                Customers
                LEFT JOIN
                    Orders
                    ON Customers.id = Orders.customerId
            GROUP BY Customers.id
            # NULL numOrders represent no orders
            HAVING (numOrders IS NULL)
    ) AS CustomersWithNumOrders
;