import csv

with open('mem.csv', newline='') as file:
    reader = csv.reader(file, delimiter=',')
    id = None
    for row in reader:
        if(row[0] == 's'):
            isbn = row[1]
            out = row[2]
            if(len(row) == 4):
                checkin = row[3]
            else:
                checkin = "NA"
            print("INSERT INTO BorrowedBy VALUES (" + id + ",\'" + isbn + "\',\'" + out + "\',\'" + checkin + "\');");
            #BorrowedBy (MemberID int, ISBN varchar(255), CheckoutDate varchar(255), CheckinDate varchar(255), Primary Key(MemberID, ISBN, CheckoutDate), Foreign Key(MemberID) References Member(MemberID), Foreign Key(ISBN) References Book(ISBN));


            continue
        id = row[0]
        name = row[1].split(" ")
        first = name[0]
        last = name[1]
        date = row[2]
        #print("INSERT INTO Member VALUES (" + id + ',\'' + last + "\',\'" + first + "\',\'" + date + "\');")
