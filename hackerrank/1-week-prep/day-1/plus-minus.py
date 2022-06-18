def plus_minus(values):
    negatives = 0
    positives = 0
    zeros = 0
    for value in values:
        if value < 0:
            negatives += 1
        elif value > 0:
            positives += 1
        else:
            zeros += 1
    
    total = len(values)
    print(format_number(positives/total))
    print(format_number(negatives/total))
    print(format_number(zeros/total))
    
def format_number(number):
    return "{:.6f}".format(number)
