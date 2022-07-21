PLAYER_1 = "Louise"
PLAYER_2 = "Richard"

def find_power_of_2_lower_than(number):
    power_of_2 = 1
    while power_of_2 < number:
        power_of_2 = 2*power_of_2
    return power_of_2//2

def is_power_of_two(number):
    while number > 1 and number % 2 == 0:
        number = number//2
    return number == 1

def execute_play(counter):
    if is_power_of_two(counter):
        return counter/2
    return counter - find_power_of_2_lower_than(counter)

def switch_player(player):
    if player is None:
        return PLAYER_1
    return PLAYER_2 if player == PLAYER_1 else PLAYER_1

def counter_game(counter):
    last_player = None
    while counter > 1:
        counter = execute_play(counter)
        last_player = switch_player(last_player)
    return last_player