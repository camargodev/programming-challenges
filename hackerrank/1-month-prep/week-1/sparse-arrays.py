def build_string_dict(strings):
    string_dict = dict()
    for string in strings:
        if string not in string_dict:
            string_dict[string] = 0
        string_dict[string] += 1
    return string_dict

def get_occurences(string_dict, query):
    if query not in string_dict:
        return 0
    return string_dict[query]

def matching_strings(strings, queries):
    string_dict = build_string_dict(strings)
    return [get_occurences(string_dict, query) for query in queries]