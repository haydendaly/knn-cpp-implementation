"""
example of euclidean distance formula to emulate with c++ for project going forward
modeled from https://github.com/haydendaly/knn-cpp-imeplentation/blob/master/python_implementation/Hayden_Implementation.ipynb
"""

def euclidean_distance(base, compared):
    distance = 0.0
    for feature in range(len(base)):
        distance += (base[i] - compared[i])**2
    return sqrt(distance)