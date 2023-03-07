import csv

with open('book.csv', newline='') as file:
    reader = csv.reader(file, delimiter=',')
    isbn = None
    for row in reader:
        if(row[0] == 's'):
            numAuth = len(row)
            n = 1
            while(n < numAuth):
                authorId = row[n]
                print("INSERT INTO WrittenBy VALUES (" + authorId + ",\'" + isbn + "\');")
                n += 1
            continue
        isbn = row[0]
        title = row[4]
        pubID = row[5]
        date = row[6]
        #print("INSERT INTO Book VALUES (\'" + isbn + "\',\'" + title + "\',\'" + date + "\'," + pubID + ");")
        print("INSERT INTO PublishedBy VALUES (" + pubID + ",\'" + isbn + "\');")
         #ISBN varchar(100), Pub_ID int, Title varchar(100), Year_Published
