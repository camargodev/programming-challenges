def minimum_bribes(positions):
    again = True
    num_of_bribes = 0
    moves_by_person = [0]*len(positions)
    
    while again:
        again = False
        for i in range(0, len(positions)-1):
            if positions[i] > positions[i+1]:
                moves_by_person[positions[i]-1] += 1
                if moves_by_person[positions[i]-1] > 2:
                    print("Too chaotic")
                    return
                positions[i], positions[i+1] = positions[i+1], positions[i]
                num_of_bribes += 1
                again = True
    print(num_of_bribes)
        
if __name__ == '__main__':
    t = int(input().strip())

    for t_itr in range(t):
        n = int(input().strip())
        q = list(map(int, input().rstrip().split()))
        minimum_bribes(q)