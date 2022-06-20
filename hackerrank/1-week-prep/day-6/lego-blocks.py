MAX_VAL = 1000000007
    
def build_row_formations_by_width(width):
    formations = [0, 1, 2, 4, 8]
    for w in range(5, width+1):
        formations.append((formations[w-1] + formations[w-2] + formations[w-3] + formations[w-4])%MAX_VAL)
    return formations

def lego_blocks(height, width):
    num_row_formations = build_row_formations_by_width(width)
    all_formations = [(num_row**height)%MAX_VAL for num_row in num_row_formations]
    num_valid_formations = [a for a in all_formations]
    for i in range(width+1):
        for j in range(1, i):
            num_valid_formations[i] -= (num_valid_formations[j]*all_formations[i-j])
        num_valid_formations[i] = num_valid_formations[i]%MAX_VAL
    return num_valid_formations[width]
