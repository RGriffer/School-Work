SELECT * FROM Library ORDER BY LibraryName;

SELECT * FROM LocatedAt ORDER BY ISBN;

SELECT DISTINCT Title, la1.TotalCopies, la1.LibraryName FROM Library l, Book b, LocatedAt la1, LocatedAt la2 WHERE la1.ISBN = la2.ISBN AND la1.LibraryName != la2.LibraryName AND b.ISBN = la1.ISBN ORDER BY Title;

SELECT DISTINCT LibraryName, COUNT(DISTINCT ISBN) FROM LocatedAt WHERE LibraryName = 'Main' UNION SELECT DISTINCT LibraryName, COUNT(DISTINCT ISBN) FROM LocatedAt WHERE LibraryName = 'South Park';

CREATE SQL SECURITY INVOKER VIEW book_view AS select distinct b.Title, Group_Concat(distinct a.FirstName,' ', a.LastName), Group_Concat(l.LibraryName) from LocatedAt l, Book b, Author a, WrittenBy wb where b.ISBN=wb.ISBN AND wb.AuthorID=a.AuthorID AND b.ISBN=l.ISBN GROUP BY b.Title;

SELECT * FROM book_view;
