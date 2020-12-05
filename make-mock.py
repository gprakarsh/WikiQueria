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
    punctuation = ",. "
    vc = vowels + consonants
    pc = punctuation + consonants
    pv = punctuation + vowels
    words = []
    word = random.choice(vc)
    while len(words) < count:
        if len(word) == size:
            words.append(word.capitalize())
            word = random.choice(vc)
        # explore five at a time
        if word[-1] in vowels:
            word = word + random.choice(pc)
        elif word[-1] in punctuation:
            word = word + random.choice(vc)
        else:
            word = word + random.choice(pv)
    return words

def simple_words(count):
    return ["page {}".format(i) for i in range(count)]

if vertexcount > 5000 and probability > 0.3:
    print("Vertexcount and connectedness too high! Please reduce vertexcount to <5000 and connectedness<0.3")
    exit(1)

G = nx.gnp_random_graph(vertexcount, probability, directed=True)
#words = simple_words(len(G.nodes()))
# for i in range(len(G.nodes())):
#     G.nodes[i]['page'] = words[i]
#for i in range(len(G.nodes())):
#    G.nodes[i]['page'] = "Page {}".format(i)
nx.write_edgelist(G, outedgefile, data=False)

# with open(outnamefile, 'w') as of:
#     for i in G.nodes():
#         of.write('{},"{}"\n'.format(i, G.nodes[i]['page']))

# with open(outnamefile, 'w') as of:
#     for i in range(len(G.nodes())):
#         of.write('{},"{}"\n'.format(i, "Page {}".format(i)))

outstr = '\n'.join(['{},"{}"'.format(i, "Page {}".format(i)) for i in range(len(G.nodes()))])
with open(outnamefile, 'w') as of:
    of.write(outstr)