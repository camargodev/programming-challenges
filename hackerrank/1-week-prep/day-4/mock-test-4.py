def truckTour(petrol_pumps):
    for i in range(len(petrol_pumps)):
        if can_complete_circle(petrol_pumps, i):
            return i
    return None

def can_complete_circle(petrol_pumps, current, cummulated_petrol=0, visited_pumps=0):
    num_of_petrol_pumps = len(petrol_pumps)
    while visited_pumps < num_of_petrol_pumps:
        petrol_pump = petrol_pumps[current]
        if petrol_pump[0] + cummulated_petrol < petrol_pump[1]:
            return False
        cummulated_petrol = cummulated_petrol + petrol_pump[0] - petrol_pump[1]
        visited_pumps += 1
        current = (current+1)%num_of_petrol_pumps
    return True