def noPrefix(words):
    previous_words = set()
    prefixes = set()

    for word in words: 
        if word in prefixes:
            print("BAD SET")
            print(word)
            return
        current_sub_word = ""
        for char in word:
            current_sub_word += char
            prefixes.add(current_sub_word)
            if current_sub_word in previous_words:
                print("BAD SET")
                print(word)
                return
        previous_words.add(word)
            
    print("GOOD SET")