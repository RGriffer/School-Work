drop table BorrowedBy, WrittenBy, AuthorPhone, PublisherPhone, PublishedBy, LocatedAt;

drop table Book, Author, Member, Publisher, Library;

CREATE TABLE Member ( MemberID int, LastName varchar(255), FirstName varchar(255), DOB varchar(255), Primary Key(MemberID));

CREATE TABLE Publisher ( PubID int, PubName varchar(255), Primary Key(PubID));

CREATE TABLE Book ( ISBN varchar(255), Title varchar(255), YearPub varchar(255), PubID int, Primary Key(ISBN), Foreign Key(PubID) References Publisher(PubID));

CREATE TABLE Author ( AuthorID int, LastName varchar(255), FirstName varchar(255), Primary Key(AuthorID));

CREATE TABLE Library ( LibraryName varchar(255), Street varchar(255), City varchar(255), State varchar(255), Primary Key(LibraryName));


CREATE TABLE BorrowedBy (MemberID int, ISBN varchar(255), CheckoutDate varchar(255), CheckinDate varchar(255), LibraryName varchar(255), Primary Key(MemberID, ISBN, CheckoutDate, LibraryName), Foreign Key(MemberID) References Member(MemberID), Foreign Key(ISBN) References Book(ISBN), Foreign Key(LibraryName) References Library(LibraryName));

CREATE TABLE WrittenBy (AuthorID int, ISBN varchar(255), Primary Key(AuthorID, ISBN), Foreign Key(AuthorID) References Author(AuthorID), Foreign Key(ISBN) References Book(ISBN));

CREATE TABLE AuthorPhone (AuthorID int, PNumber varchar(255), Type varchar(255), Foreign Key(AuthorID) References Author(AuthorID), Primary Key(AuthorID, PNumber));

CREATE TABLE PublisherPhone (PubID int, PNumber varchar(255), Type varchar(255), Foreign Key(PubID) References Publisher(PubID), Primary Key(PubID, PNumber));

CREATE TABLE PublishedBy (PubID int, ISBN varchar(255), Primary Key(PubID, ISBN), Foreign Key(PubID) References Publisher(PubID), Foreign Key(ISBN) References Book(ISBN));

CREATE TABLE LocatedAt (TotalCopies int, Available int, Shelf int, FloorNumber int, LibraryName varchar(255), ISBN varchar(255), Primary Key(LibraryName, ISBN), Foreign Key(LibraryName) References Library(LibraryName), Foreign Key(ISBN) References Book(ISBN));
