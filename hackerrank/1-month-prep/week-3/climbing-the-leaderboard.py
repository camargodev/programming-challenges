def climbing_leaderboard(previous_ranks, new_pontuations):
    previous_ranks = sorted(set(previous_ranks))
    last_rank = len(previous_ranks)+1
    current_index = 0
    
    new_ranks = []
    for new_pontuation in new_pontuations:
        while current_index < len(previous_ranks) and new_pontuation >= previous_ranks[current_index]:
            current_index += 1
        rank = last_rank-current_index
        new_ranks.append(rank)
    
    return new_ranks