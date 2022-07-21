def hackerland_radio_transmitters(houses, antenna_range):
    houses.sort()
    house_set = set(houses)
    next_uncovered_house = min(houses)
    last_house = max(houses)
    transmitters_count = 0
    
    while next_uncovered_house <= last_house:
        max_placement_house = next_uncovered_house + antenna_range
        while max_placement_house not in house_set:
            max_placement_house -= 1
            
        transmitters_count += 1
        next_uncovered_house = max_placement_house + antenna_range + 1
        while next_uncovered_house <= last_house and next_uncovered_house not in house_set:
            next_uncovered_house += 1
        
    return transmitters_count