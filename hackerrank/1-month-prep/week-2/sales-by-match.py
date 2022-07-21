def sock_merchant(n, socks):
    socks_dict = dict()
    for sock in socks:
        if sock not in socks_dict:
            socks_dict[sock] = 0
        socks_dict[sock] += 1
    total_pairs = 0
    for sock in socks_dict.keys():
        total_pairs += socks_dict[sock]//2
    return total_pairs