INSERT INTO Book VALUES ('96-42013-10510','Growing your own Weeds','06/24/2012',10000);
INSERT INTO PublishedBy VALUES (10000,'96-42013-10510');
INSERT INTO LocatedAt VALUES (1,1,8,2,'Main','96-42013-10510');

UPDATE LocatedAt SET TotalCopies=8 WHERE ISBN='96-42013-10907' AND LibraryName = 'Main';

DELETE Author FROM Author WHERE Author.FirstName='Grace' AND Author.LastName='Slick';

Insert into Author values (305, 'Adams', 'Commander');
Insert into AuthorPhone values (305, '970-555-5555', 'o');

INSERT INTO LocatedAt VALUES (1,1,8,3,'South Park','96-42013-10510');

DELETE LocatedAt FROM LocatedAt INNER JOIN Book on LocatedAt.ISBN=Book.ISBN where LocatedAt.LibraryName='Main' AND Book.Title="Missing Tomorrow";

UPDATE LocatedAt SET TotalCopies=TotalCopies + 2 WHERE LibraryName='South Park' AND ISBN='96-42103-11604';

INSERT INTO Book VALUES ('96-42013-10513','Growing your own Weeds','06/24/2012',90000);
