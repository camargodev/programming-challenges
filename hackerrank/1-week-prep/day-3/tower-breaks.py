def tower_breakers(n, m):
    if m == 1:
        return 2
    return 2 if n % 2 == 0 else 1