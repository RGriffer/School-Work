SELECT 
	e.first_name, e.last_name, s.salary
FROM
	employees e, salaries s
WHERE
	e.emp_no = s.emp_no AND s.to_date = '9999-01-01' AND s.salary > 90000;

SELECT
	e.first_name, e.last_name, d.dept_name
FROM
	employees e, departments d, dept_emp de
WHERE
	e.emp_no = de.emp_no AND de.dept_no = d.dept_no AND d.dept_no IN ('d008','d009') AND de.to_date = '9999-01-01';

SELECT
    e.first_name, e.last_name, t.title
FROM
    employees e, titles t
WHERE
    e.emp_no = t.emp_no AND t.title = 'Technique Leader' AND t.to_date = '9999-01-01' AND e.gender = 'F';
    
SELECT
    e.first_name, e.last_name, s.salary
FROM
    employees e, titles t, salaries s
WHERE
    e.emp_no = t.emp_no AND e.emp_no = s.emp_no AND t.title != 'Senior Engineer' AND s.to_date = '9999-01-01' AND t.to_date = '9999-01-01'
ORDER BY
    s.salary ASC;
    
SELECT
    e.first_name, e.last_name, e.birth_date
FROM
    employees e
ORDER BY
    e.birth_date ASC;
    
SELECT
    e.first_name, e.last_name
FROM
    employees e, titles t
WHERE
    e.emp_no = t.emp_no AND t.to_date = '9999-01-01' AND t.title = 'Manager';
    
SELECT
    e.first_name, e.last_name, d.dept_name
FROM
    employees e, current_dept_emp cde, salaries s, departments d
WHERE
    e.emp_no = s.emp_no AND e.emp_no = cde.emp_no AND cde.dept_no = d.dept_no
ORDER BY s.salary DESC
LIMIT 1;
