import sys
import heapq
from collections import defaultdict


def file_character_frequencies(file_name):
    # Suggested helper
    with open (file_name, "r") as myfile:
        data=myfile.readlines()
    d = defaultdict(int)
    for c in ''.join(data):
        d[c] += 1
    #print(d)
    return d


class PriorityTuple(tuple):
    """A specialization of tuple that compares only its first item when sorting.
    Create one using double parens e.g. PriorityTuple((x, (y, z))) """
    def __lt__(self, other):
        return self[0] < other[0]

    def __le__(self, other):
        return self[0] <= other[0]

    def __gt__(self, other):
        return self[0] > other[0]

    def __ge__(self, other):
        return self[0] >= other[0]

    def __eq__(self, other):
        return self[0] == other[0]

    def __ne__(self, other):
        x = self.__eq__(other)
        return not x

def huffman_codes_from_frequencies(frequencies):
    # Suggested helper
    tupleList = [(k,v) for v, k in frequencies.items()]
    PTList = list()
    for index, tuple in tupleList:
        PTList.append(PriorityTuple((index, tuple)))
    heapq.heapify(PTList)
    while len(PTList) > 1:
        f1,c1 = heapq.heappop(PTList)
        f2,c2 = heapq.heappop(PTList)
        temp = PriorityTuple((f1+f2, ((c1, c2))))
        heapq.heappush(PTList, temp)
    #print(PTList) #TESTING REMOVE AFTER DONE
    tmp = PTList[0]
    root = tmp[1]
    codes = defaultdict(str)
    prefix = ""
    print(root) #TESTING REMOVE AFTER FINISHED
    trav(root, prefix, codes)
    return codes
    
#recursive traverse function
def trav(node, prefix, codes):
    if isinstance(node, str):
        codes[node] = prefix
    else:
        trav(node[0], prefix + "0", codes)
        trav(node[1], prefix + "1", codes)
    
        

def huffman_letter_codes_from_file_contents(file_name):
    """WE WILL GRADE BASED ON THIS FUNCTION."""
    # Suggested strategy...
    #freqs = file_character_frequencies(file_name)
    #return huffman_codes_from_frequencies(freqs)
    freqs = file_character_frequencies(file_name)
    return huffman_codes_from_frequencies(freqs)


def encode_file_using_codes(file_name, letter_codes):
    """Provided to help you play with your code."""
    contents = ""
    with open(file_name) as f:
        contents = f.read()
    file_name_encoded = file_name + "_encoded"
    with open(file_name_encoded, 'w') as fout:
        for c in contents:
            fout.write(letter_codes[c])
    print("Wrote encoded text to {}".format(file_name_encoded))


def decode_file_using_codes(file_name_encoded, letter_codes):
    """Provided to help you play with your code."""
    contents = ""
    with open(file_name_encoded) as f:
        contents = f.read()
    file_name_encoded_decoded = file_name_encoded + "_decoded"
    codes_to_letters = {v: k for k, v in letter_codes.items()}
    with open(file_name_encoded_decoded, 'w') as fout:
        num_decoded_chars = 0
        partial_code = ""
        while num_decoded_chars < len(contents):
            partial_code += contents[num_decoded_chars]
            num_decoded_chars += 1
            letter = codes_to_letters.get(partial_code)
            if letter:
                fout.write(letter)
                partial_code = ""
    print("Wrote decoded text to {}".format(file_name_encoded_decoded))


def main():
    """Provided to help you play with your code."""
    import pprint
    frequencies = file_character_frequencies(sys.argv[1])
    pprint.pprint(frequencies)
    codes = huffman_codes_from_frequencies(frequencies)
    pprint.pprint(codes)
    #encode_file_using_codes(sys.argv[1], codes)
    decode_file_using_codes("example.txt_encoded" , codes)


if __name__ == '__main__':
    """We are NOT grading you based on main, this is for you to play with."""
    main()
