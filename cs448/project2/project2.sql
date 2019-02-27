--QUERY 1

SELECT EmpName
FROM Employee
WHERE ZipCode = 47906 OR ZipCode = 47907;

--QUERY 2

SELECT ProjName
FROM
	(SELECT ProjId
	FROM ProjectManager
	WHERE EndDate IS NULL) pm JOIN Project p ON pm.ProjId = p.ProjId;

--QUERY 3

SELECT ProjName
FROM Project
ORDER BY ProjName DESC;

--QUERY 4

SELECT UnivName, COUNT(*)
FROM
	(SELECT UnivId
	FROM Graduate) g JOIN University u ON g.UnivId = u.UnivId
GROUP BY UnivName;

--QUERY 5

SELECT EmpName, DeptName, GradYear
FROM
	(SELECT e.EmpId, DeptId, EmpName, GradYear
	FROM
		(SELECT EmpId, DeptId, EmpName
		FROM Employee) e JOIN Graduate g ON e.EmpId = g.EmpId) emp JOIN Department d ON emp.DeptId = d.DeptId;

--QUERY 6

SELECT EmpName
FROM Employee
WHERE DeptId = 1
ORDER BY EmpName ASC;

--QUERY 7

SELECT EmpName, UnivName, GradYear
FROM
	(SELECT EmpName, UnivId, GradYear
	FROM Employee e JOIN Graduate g ON e.EmpId = g.EmpId) emp JOIN University u ON emp.UnivId = u.UnivId
WHERE UnivName = 'Purdue' AND GradYear <= 2005;

--QUERY 8

SELECT ZipCode, COUNT(*)
FROM Employee
GROUP BY ZipCode
ORDER BY ZipCode DESC;

--QUERY 9

SELECT EmpName, GradYear
FROM Employee e JOIN Graduate g ON e.EmpId = g.EmpId
ORDER BY GradYear DESC;

--QUERY 10

SELECT  ProjName, EmpName
FROM
	(SELECT  p.ProjId, EmpId, ProjName
	FROM EmpProject ep JOIN Project p ON ep.ProjId=p.ProjId) epp JOIN Employee e ON epp.EmpId = e.EmpId
ORDER BY ProjName, EmpName;