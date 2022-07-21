def process_query(query):
    return int(query[0]), int(query[1]), int(query[2])

def dynamic_array(length, queries):
    answers = []
    array = []
    for _ in range(length):
        array.append([])
    last_answer = 0
    for query in queries:
        action, x, y = process_query(query)
        index_x = ((x ^ last_answer) % length)
        if action == 1:
            array[index_x].append(y)
        else:
            index_y = y % len(array[index_x])
            last_answer = array[index_x][index_y]
            answers.append(last_answer)
    return answers