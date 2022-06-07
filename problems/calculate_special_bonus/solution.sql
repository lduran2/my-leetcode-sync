# Write your MySQL query statement below

# Table: Employees

# Calculate the bonus of each employee.  The bonus of an employee is
# 100% of their salary if the ID of the employee is an odd number and
# the employee name does not start with the character 'M'.  The bonus
# of an employee is 0 otherwise.

SELECT
        employee_id,
        # salary if passes gets_bonus test giving bonus
        IF(gets_bonus, salary, 0) AS bonus
    FROM
    (
        # verify whether an employee gets a bonus
        SELECT
                employee_id,
                salary,
                # use the criterion (odd ID#, name does not start in M)
                # to choose whether the employee gets a bonus
                (
                    ((employee_id & 1) = 1)
                    AND (name NOT LIKE 'M%')
                ) AS gets_bonus
            FROM Employees
    ) AS EmployeesWithGetBonus
;