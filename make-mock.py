import sys
import random
import networkx as nx

if len(sys.argv) - 1 != 4:
    print("Usage: python3 {} OUTNAMES OUTEDGES VERTEXCOUNT CONNECTEDNESS".format(sys.argv[0]))
    print("OUTNAMES: output filename for generated names, ex: test-names.csv")
    print("OUTEDGES: output filename for generated edgess, ex: test-edges.txt")
    print("VERTEXCOUNT: number of vertices, ex: 10")
    print("CONNECTEDNESS: a decimal from [0, 1.0], ex: 0.3")
    exit(1)
else:
    outnamefile = sys.argv[1]
    outedgefile = sys.argv[2]
    vertexcount = int(sys.argv[3])
    probability = float(sys.argv[4])
    print("Output for graph names:\t{}".format(outnamefile))
    print("Output for graph edges:\t{}".format(outedgefile))
    print("Number of vertices:\t{}".format(vertexcount))
    print("Connectedness:\t{}".format(probability))
    if (input("Is this correct? y/n: ").strip().lower() != 'y'):
        print("Abort.")
        exit(1)

def random_words(count, size):
    vowels = "aeiou"
    consonants = "bcdfghjklmnpqrstvwxyz"
    words = []
    word = random.choice(vowels + consonants)
    while len(words) < count:
        if len(word) == size:
            words.append(word.capitalize())
            word = random.choice(vowels + consonants)
        # explore five at a time
        if word[-1] in vowels:
            word = word + random.choice(consonants)
        else:
            word = word + random.choice(vowels)
    return words

G = nx.gnp_random_graph(10, 0.1, directed=True)
words = random_words(len(G.nodes()), 8)
for i in range(len(G.nodes())):
    G.nodes[i]['page'] = words[i]

nx.write_edgelist(G, outedgefile, data=False)

with open(outnamefile, 'w') as of:
    for i in G.nodes():
        of.write('{},"{}"\n'.format(i, G.nodes[i]['page']))
