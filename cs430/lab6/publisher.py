import csv

with open('pub.csv', newline='') as file:
    reader = csv.reader(file, delimiter=',')
    for row in reader:
        phoneArray = row[2].split(' ')
        numPhone = len(row)
        n = 2
        id = row[0]
        name = row[1][1:]
        print("INSERT INTO Publisher VALUES (" + id + ",\'" + name + "\');")
        while(n < numPhone):
            phoneArray = row[n].split(' ')
            number = phoneArray[1]
            type = phoneArray[2][1:2]
            n += 1
            print("INSERT INTO PublisherPhone VALUES (" + id + ",\'" + number + "\',\'" + type +"\');")
        print()
