import csv
import os
import sys
import operator


def main():
    filename = sys.argv[1]
    quantum = int(sys.argv[2])

    data = readCSV(filename)

    fcfs([p.copy() for p in data])
    ps([p.copy() for p in data])
    rr([p.copy() for p in data], quantum)


def readCSV(filename):
    reader = csv.DictReader(open(filename))
    data = [row for row in reader]
    for p in data:
        for key, val in p.items():
            p[key] = int(val)
    return data

#first come first serve
def fcfs(data):
    data.sort(key=lambda x: x['ProcessID'])
    data.sort(key=lambda x: x['Arrival Time'])
    for p in data:
        p['start'] = None
        p['end'] = None
    schedule = []

    #calculate
    time=0
    for p in data:
        if p['Arrival Time'] > time:
            schedule.append(getGanttRow("IDLE", time, p['Arrival Time']))
            time = p['Arrival Time']
        p['start']=time
        p['end'] = time+int(p['Burst Time'])
        time = p['end']
        schedule.append(getGanttRow(p['ProcessID'], p['start'], p['end']))

    infoTable = []
    for p in data:
        infoTable.append({
            "ProcessID": p["ProcessID"],
            "Waiting Time": p['start']-p['Arrival Time'],
            "Turnaround Time": p['end'] - p['Arrival Time']
        })

    printTable("FCFS", infoTable)
    printGantt("FCFS", schedule)
    nonPreWait(infoTable)
    printAverages(infoTable, data)


#priority scheduling
def ps(data):
    for p in data:
        p['arrived'] = False
    data.sort(key=lambda x: x['ProcessID'])
    data.sort(key=lambda x: x['Arrival Time'])
    readyQueue = []
    schedule = []
    time = 0
    global running
    running = None
    maxArrivalTime = data[-1]['Arrival Time']+1
    idleProcess = None
    while time < maxArrivalTime or len(readyQueue) > 0: #loop for processes start
        for p in data:
            if p['Arrival Time'] <= time and p['arrived'] is False:
                readyQueue.append(p)
                p['arrived'] = True
        if len(readyQueue)>0:
            readyQueue.sort(key=lambda x: x['Priority'])
            running = readyQueue.pop(0)
        else:
            running = None
        if running:
            if idleProcess:
                schedule.append(idleProcess)
                idleProcess = None
            schedule.append(getGanttRow(running['ProcessID'], time, time+running['Burst Time']))
            running['start'] = time
            running['end'] = time+running['Burst Time']
            time += running['Burst Time']
            running = None
            for p in data:
                if p['Arrival Time'] <= time and p['arrived'] is False:
                    readyQueue.append(p)
                    p['arrived'] = True
        else:
            if not idleProcess:
                idleProcess = getGanttRow('IDLE', time, time)
            idleProcess['end']+=1
            time += 1

    infoTable = []
    for p in data:
        infoTable.append({
            "ProcessID": p["ProcessID"],
            "Waiting Time": p['start'] - p['Arrival Time'],
            "Turnaround Time": p['end'] - p['Arrival Time']
        })
    printTable("PS", infoTable)
    printGantt("PS", schedule)
    nonPreWait(infoTable)
    printAverages(infoTable, data)

#round robin (this sucks)
def rr(data, quantum):
    for p in data:
        p['arrived'] = False
        p['start'] = None
        p['end'] = None
        p['remainingBurst'] = p['Burst Time']
        p['lastEnd'] = p['Arrival Time']
        p['waitTime'] = 0
    data.sort(key=lambda x: x['ProcessID'])
    data.sort(key=lambda x: x['Arrival Time'])
    queue = []
    schedule = []
    time =0
    maxArrivalTime = data[-1]['Arrival Time']
    global running
    running = False
    idleProcess = False
    while time <= maxArrivalTime or len(queue) > 0:
        
        # get newly arrived processes
        for p in data:
            if p['Arrival Time'] <= time and p['arrived'] is False:
                queue.append(p)
                p['arrived'] = True

        if len(queue)>0:
            running = queue.pop(0)
        else:
            running = None
        if running:
            reAdd = None
            if idleProcess:
                schedule.append(idleProcess)
                idleProcess = None
            runTime = min(running['remainingBurst'], quantum)
            running['remainingBurst'] -= runTime
            print(running['remainingBurst'])
            schedule.append(getGanttRow(running['ProcessID'], time, time+runTime))
            running['waitTime'] += time-running['lastEnd']
            running['lastEnd'] = time+runTime
            if running['start'] is None:
                running['start'] = time
            if running['remainingBurst'] == 0:
                running['end'] = time+runTime
            else:
                reAdd = running

            #get any new processes that might've showed up so loop doesn't end
            time += runTime
            running = None
            for p in data:
                if p['Arrival Time'] <= time and p['arrived'] is False:
                    queue.append(p)
                    p['arrived'] = True
            if reAdd:
                queue.append(reAdd)
        else:
            if not idleProcess:
                idleProcess = getGanttRow('IDLE', time, time)
            idleProcess['end']+=1
            time += 1

    infoTable = []
    for p in data:
        infoTable.append({
            "ProcessID": p["ProcessID"],
            "Waiting Time": p['start'] - p['Arrival Time'],
            "Turnaround Time": p['end'] - p['Arrival Time']
        })


    printTable("Round Robin", infoTable)
    printGantt("Round Robin", schedule)
    yesPreWait(data)
    printAverages(infoTable, data)

def getGanttRow(id, start, end):
    return {
        "ProcessID": id,
        "start": start,
        "end": end
    }

#print our averages
def printAverages(infoTable, data):
    avgTurn = float(sum(p['Turnaround Time'] for p in infoTable)) / len(infoTable)
    throughput = float(len(infoTable)) / data[-1]['end']
    print("Average Turnaround Time:", avgTurn)
    print("Throughput:", throughput)
    #print('\n')
    
#print the gantt chart
def printGantt(name, data):
    print(name, "Gantt chart")
    for p in data:
        print("[{:^4}]--[{:^4}]--[{:^4}]".format(p['start'], p['ProcessID'], p['end']))
    #print('\n')

#print the tables
def printTable(name, tableData):
    print("-"*10, name, "-"*10)
    longest = max([len(name) for name in tableData[0].keys()])
    row_format = "{:^"+str(longest)+"} | "
    row_format *= (len(tableData[0].values()))
    print(row_format.format(*tuple(tableData[0].keys())))
    for process in tableData:
        print(row_format.format(*tuple(process.values())))
    #print('\n')
    
    
def yesPreWait(data):
    print("Average Wait Time:", (sum(p['waitTime'] for p in data)) / len(data))


def nonPreWait(infoTable):
    print("Average Wait Time:", float(sum(p['Waiting Time'] for p in infoTable)) / len(infoTable))


if __name__ == '__main__':
    main()
