import heapq

def readNext():
    global infile
    nextNum = int(infile.readline().strip())
    return nextNum

def refreshTop():
    global maxheap, minheap, maxtop, mintop

    maxtop = - heapq.heappop(maxheap)
    heapq.heappush(maxheap, - maxtop)

    mintop = heapq.heappop(minheap)
    heapq.heappush(minheap, mintop)

def nextMedian(nextNum):
    global maxheap, minheap, maxtop, mintop, num

    if nextNum > mintop:
        mintop = heapq.heappushpop(minheap, nextNum)
        heapq.heappush(minheap, mintop)
    else:
        maxtop = - heapq.heappushpop(maxheap, - nextNum)
        heapq.heappush(maxheap, -maxtop)

    if len(maxheap) - len(minheap) == 2:
        bal = - heapq.heappop(maxheap)
        heapq.heappush(minheap, bal)
        refreshTop()
    if len(minheap) - len(maxheap) == 2:
        bal = heapq.heappop(minheap)
        heapq.heappush(maxheap, -bal)
        refreshTop()

    num = num+1

    if num%2 == 0:
        return maxtop
    else:
        if len(maxheap) > len(minheap):
            return maxtop
        else:
            return mintop




if __name__ == "__main__":
    infile = open('Median.txt', 'r')

    minheap = [readNext()]
    maxheap = [-readNext()]

    num = 2


    maxtop = - heapq.heappop(maxheap)
    heapq.heappush(maxheap, - maxtop)

    mintop = heapq.heappop(minheap)
    heapq.heappush(minheap, mintop)
    #print minheap
    #print maxheap

    #new = readNext()

    #print new, nextMedian(new)

    sumMedians = mintop+maxtop

    for i in range(9998):
        sumMedians = sumMedians + nextMedian(readNext())
        #sumMedians = sumMedians%10000

    print sumMedians%10000

    
