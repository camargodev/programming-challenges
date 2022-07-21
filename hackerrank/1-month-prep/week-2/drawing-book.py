def page_count(number_of_pages, target_page):
    flips_from_start = target_page//2
    if number_of_pages % 2 == 0:
        number_of_pages += 1
    flips_from_end = (number_of_pages-target_page)//2
    return min(flips_from_start, flips_from_end)