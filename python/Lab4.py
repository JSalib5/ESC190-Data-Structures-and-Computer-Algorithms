def find(L, e):
    low = 0
    high = len(L) - 1
    mid = 0
    while low <= high:
        if L[mid] != e:
            mid = int((high+low)//2)
            if L[mid]<e:
                low = mid + 1
            if L[mid]>e:
                high = mid - 1
        if L[mid] == e:
            if L[mid - 1] == e:
                mid = mid - 1 
            if L[mid - 1] != e:
                return mid
    return -1


def find_higher(L, e):
    low = 0
    high = len(L) - 1
    mid = 0
    while low <= high:
        if L[mid] != e:
            mid = int((high+low)//2)
            if L[mid]<e:
                low = mid + 1
            if L[mid]>e:
                high = mid - 1
        if L[mid] == e:
            if L[mid + 1] == e:
                mid = mid + 1 
            if L[mid + 1] != e:
                return mid
    return -1


  


if __name__ == "__main__":
    L = [1, 2, 3, 4, 6, 13, 13, 13, 13, 15]
    e = 13

    print(find(L, e)) # should return 5
    print(find_higher(L, e)) #should return 9
