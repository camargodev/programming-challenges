def truck_tour(petrol_pumps):
    for i in range(len(petrol_pumps)):
        if can_complete_circle(petrol_pumps, i):
            return i
    return None

def can_complete_circle(petrol_pumps, current):
    cummulated_petrol = 0
    num_of_visited_pumps = 0
    num_of_petrol_pumps = len(petrol_pumps)
    while num_of_visited_pumps < num_of_petrol_pumps:
        pump_available_petrol, distance_to_next = petrol_pumps[current]
        total_gas = cummulated_petrol + pump_available_petrol
        if total_gas < distance_to_next:
            return False
        cummulated_petrol = total_gas - distance_to_next
        num_of_visited_pumps += 1
        current = (current+1)%num_of_petrol_pumps
    return True