import os

def lonely_integer(numbers):
    unique_numbers = set(numbers)
    for number in unique_numbers:
        if numbers.count(number) == 1:
            return number

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')
    n = int(input().strip())
    a = list(map(int, input().rstrip().split()))
    result = lonely_integer(a)
    fptr.write(str(result) + '\n')
    fptr.close()
