ALPHABET = 'abcdefghijklmnopqrstuvwxyz'

def caesar_cipher(text, num_rotations):
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