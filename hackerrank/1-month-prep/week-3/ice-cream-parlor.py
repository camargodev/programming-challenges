def ice_cream_parlor(price, flavors):
    flavor_map = dict()
    for i in range(len(flavors)):
        flavor_map[flavors[i]] = i
    for i in range(len(flavors)):
        pair = price - flavors[i]
        if pair in flavor_map and flavor_map[pair] != i:
            return [i+1, flavor_map[pair]+1]
    return []