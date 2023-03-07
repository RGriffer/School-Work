from sys import argv, exit

# provided
#
# Read integers from the given filename.
#
# Return value: list of integers
def read_array(filename):
    try:
        with open(filename) as f:
            return [int(n) for n in f.read().split()]
    except:
        exit("Couldn’t read numbers from file \""+filename+"\"")


# implement
#
# Return the number of inversions in the given list, by doing a merge
# sort and counting the inversions.
#
# Return value: number of inversions
def count_inversions(in_list):
    if(len(in_list) < 2):
        return 0
    
    split = len(in_list) // 2
    l_list = in_list[0:int(split)]
    r_list = in_list[int(split):len(in_list)]
    
    a = count_inversions(l_list)
    b = count_inversions(r_list)
    c = merge_i(l_list, r_list, in_list)
    
    return a + b + c


# implement
#
# Merge the left & right lists into in_list.  in_list already contains
# values--replace those with the merged values.
#
# Return value: inversion count
def merge_i(l_list, r_list, in_list):
    i,j,k,count = 0,0,0,0
    while (i < len(l_list) and j < len(r_list)):
        if (l_list[i] <= r_list[j]):
            in_list[k] = l_list[i]
            i = i + 1
        else:
            in_list[k] = r_list[j]
            count += (len(l_list) - i)
            j = j + 1
        k += 1
            
    while i < len(l_list):
        in_list[k] = l_list[i]
        i += 1
        k += 1
    
    while j < len(r_list):
        in_list[k] = r_list[j]
        j += 1
        k += 1
    return count

#test function
#def merge_i(l_list, r_list, in_list):
#    i, j, k = 0, 0, 0
#    inversions = 0
#    left_len, right_len = len(l_list), len(r_list)
#    while i < left_len and j < right_len:
#        if l_list[i] <= r_list[j]:
#            in_list[k] = l_list[i]
#            i += 1
#        else:
#            in_list[k] = r_list[j]
#            j += 1
#            inversions += left_len - i
#        k += 1
#
#    while i < left_len:
#        in_list[k] = l_list[i]
#        i, k = i+1, k+1
#
#    while j < right_len:
#        in_list[k] = r_list[j]
#        j, k = j+1, k+1
#
#    return inversions



# provided
if __name__ == '__main__':
    if len(argv) != 2:
        exit("usage: python3 "+argv[0]+" datafile")
    in_list = read_array(argv[1])
    print(count_inversions(in_list))
