import os

ALPHABET = 'abcdefghijklmnopqrstuvwxyz'

def caesarCipher(text, num_rotations):
    encrypted_text = ''
    for letter in text:
        if letter.lower() not in ALPHABET:
            encrypted_text += letter
            continue
        is_upper = letter.isupper()
        letter_index = ALPHABET.index(letter.lower())
        encrypted_letter_index = (letter_index+num_rotations)%len(ALPHABET)
        encrypted_letter = ALPHABET[encrypted_letter_index]
        if is_upper:
            encrypted_letter = encrypted_letter.upper()
        encrypted_text += encrypted_letter
    return encrypted_text

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')
    n = int(input().strip())
    s = input()
    k = int(input().strip())
    result = caesarCipher(s, k)
    fptr.write(result + '\n')
    fptr.close()