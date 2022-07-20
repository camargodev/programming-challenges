def pairs(exp_difference, values):
    num_pairs = 0
    occurrences = dict()

    for value in values:
        if value not in occurrences:
            occurrences[value] = 0
        occurrences[value] += 1

    for value in values:
        pair_1 = value - exp_difference
        pair_2 = value + exp_difference

        if pair_1 in occurrences:
            num_pairs += occurrences[pair_1]
        if pair_2 in occurrences:
            num_pairs += occurrences[pair_2]

    return num_pairs//2