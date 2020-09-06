def is_signature_valid(orig, act):
    diff = 0
    for i in range(len(orig)):
        if i >= len(act) or orig[i] != act[i]:
            diff += 1
        if diff > 1:
            return False
    return True

def signatures(num):
    signature_dict = {}
    index = 0
    while index < num:
        stream = input()
        teststream = stream
        if len(teststream.replace(' ', '')) > 0:
            streams = stream.split(' ')
            name = ''
            signature = ''
            if len(streams) == 2:
                name = str(streams[0])
                signature = str(streams[1])
            signature_dict[name] = signature
            index += 1
    # ßprint(signature_dict)
    num_studs = input()
    if num_studs.replace(' ', '') == '':
        num_studs = input()
    num_studs = int(num_studs)
    count = 0
    index = 0
    while index < num_studs:
        stream = input()
        teststream = stream
        if len(teststream.replace(' ', '')) > 0:
            streams = stream.split(' ')
            name = ''
            signature = ''
            if len(streams) == 2:
                name = str(streams[0])
                signature = str(streams[1])
            # print(name, signature)
            # print(signature_dict)
            if len(name) > 0 and len(signature) > 0:
                if not is_signature_valid(signature_dict[name], signature):
                    count += 1
            index += 1
    return count


while True:
    num = input()
    if len(num.replace(' ', '')) > 0:
        num = int(num)
        if num == 0:
            break
        fakes = signatures(num)
        print(fakes)