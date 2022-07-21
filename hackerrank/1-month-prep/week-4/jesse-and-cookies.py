def is_larger_than_k(original_cookies, new_cookies, k, original_idx, new_index):
    if len(original_cookies) <= original_idx:
        return new_cookies[new_index] >= k
    
    if len(new_cookies) <= new_index:
        return original_cookies[original_idx] >= k 
    
    return original_cookies[original_idx] >= k and new_cookies[new_index] >= k

def get_lowest_cookie(original_cookies, new_cookies, original_idx, new_index):
    cookie = None
    
    if len(original_cookies) <= original_idx:
        cookie = new_cookies[new_index]
        new_index += 1
    elif len(new_cookies) <= new_index:
        cookie = original_cookies[original_idx]
        original_idx += 1
    else:
        new_cookie = new_cookies[new_index]
        original_cookie = original_cookies[original_idx]
        if new_cookie < original_cookie:
            cookie = new_cookie
            new_index += 1
        else:
            cookie = original_cookie
            original_idx += 1
            
    return cookie, original_idx, new_index

def cookies(k, values):
    original_cookies = sorted(values)
    new_cookies = []
    operations = 0
    orig_idx = 0
    new_idx = 0
    
    while not is_larger_than_k(original_cookies, new_cookies, k, orig_idx, new_idx):
        if ((len(original_cookies)-orig_idx) + (len(new_cookies)-new_idx)) <= 1:
            return -1
        
        lowest, orig_idx, new_idx = get_lowest_cookie(original_cookies, new_cookies, orig_idx, new_idx)
        scnd_lowest, orig_idx, new_idx = get_lowest_cookie(original_cookies, new_cookies, orig_idx, new_idx)
        new_cookie = lowest + 2*scnd_lowest
        new_cookies.append(new_cookie)
        operations += 1
    
    return operations