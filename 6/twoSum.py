def readData():
    file = open('2sum.txt', 'r')

    positive = []
    negative = {}

    for line in file:
        num = int(line.strip())
        if num > 0:
            positive.append(num)
        else:
            key = num/20000
            if key in negative:
                negative[key].append(num)
            else:
                negative[key] = [num]
    return positive, negative


if __name__ == "__main__":
    positive, negative = readData()
    #print negative[21123]

    numTargets = 0
    for t in range(-10000, 10001):
        if t%100==0: print str(t) +" "+str(numTargets)
        for pos in positive:
            reqdneg = t - pos
            key = (reqdneg)/20000
            if key in negative:
                if reqdneg in negative[key]:
                    numTargets = numTargets+1
                    break

    print numTargets


    
