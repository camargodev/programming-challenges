PLAYER_1_WINS = 1
PLAYER_2_WINS = 2

def tower_breakers(number_of_towers, tower_height):
    has_possible_moves = tower_height > 1
    has_even_num_of_towers = number_of_towers % 2 == 0 
    if not has_possible_moves:
        return PLAYER_2_WINS
    return PLAYER_2_WINS if has_even_num_of_towers else PLAYER_1_WINS