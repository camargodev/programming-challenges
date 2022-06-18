import os

def counting_sort(numbers):
    ocurrences = [0 for _ in range(100)]
    for number in numbers:
        ocurrences[number] += 1
    return ocurrences

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')
    n = int(input().strip())
    arr = list(map(int, input().rstrip().split()))
    result = counting_sort(arr)
    fptr.write(' '.join(map(str, result)))
    fptr.write('\n')
    fptr.close()