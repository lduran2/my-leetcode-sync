# Write your MySQL query statement below

# Table: Products

# Find the ids of products that are both low fat and recyclable.

SELECT product_id
    FROM Products
    WHERE
        (low_fats = 'Y')
        AND (recyclable = 'Y')
;
