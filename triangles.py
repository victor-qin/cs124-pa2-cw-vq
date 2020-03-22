from random import choices
from strassen_v1 import strassen


def graphGen(dim, p):
    """ Generates graph with dim vertices, edge probability p. """
    matrix = [choices([0, 1], [1-p, p], k=dim)
              for i in range(dim)]
    return matrix


def triangles(dim, p):
    """ Computes number of triangles in a graph using Strassen's algorithm. """
    graph = graphGen(dim, p)
    cubedGraph = strassen(strassen(graph, graph), graph)
    diagSum = 0
    # Add diagonal entries
    for i in range(dim):
        diagSum += cubedGraph[i][i]
    numTriangles = diagSum / 6
    return numTriangles


if __name__ == "__main__":
    # Edit dims, probabilities, numTrials here
    dim = 1024
    probs = [0.01]
    numTrials = 5

    # Compute average number of triangles for given parameters
    for p in probs:
        avg = 0
        for i in range(numTrials):
            avg += triangles(dim, p)
        avg = avg / numTrials
        print("Average number of triangles, probability %f: %f" % (p, avg))
