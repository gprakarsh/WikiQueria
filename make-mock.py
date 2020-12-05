import sys
import random
import networkx as nx

if len(sys.argv) - 1 != 5:
    print("Usage: python3 {} OUTNAMES OUTEDGES VERTEXCOUNT CONNECTEDNESS".format(sys.argv[0]))
    print("OUTNAMES: output filename for generated names, ex: test-names.csv")
    print("OUTEDGES: output filename for generated edges, ex: test-edges.txt")
    print("OUTSCC: output filename for strongly connected component mapping, ex: test-scc.txt")
    print("VERTEXCOUNT: number of vertices, ex: 10")
    print("CONNECTEDNESS: a decimal from [0, 1.0], ex: 0.3")
    exit(1)
else:
    outnamefile = sys.argv[1]
    outedgefile = sys.argv[2]
    outsccfile = sys.argv[3]
    vertexcount = int(sys.argv[4])
    probability = float(sys.argv[5])
    print("Output for graph names:\t{}".format(outnamefile))
    print("Output for graph edges:\t{}".format(outedgefile))
    print("Output for SCCs:\t{}".format(outsccfile))
    print("Number of vertices:\t{}".format(vertexcount))
    print("Connectedness:\t{}".format(probability))
    print("The expected number of edges is:", vertexcount * (vertexcount - 1) / 2 * probability)
    if (input("Is this correct? y/n: ").strip().lower() != 'y'):
        print("Abort.")
        exit(1)

def random_words(count, size):
    vowels = "aeiou"
    consonants = "bcdfghjklmnpqrstvwxyz"
    punctuation = ",. "
    vc = vowels + consonants
    pc = punctuation + consonants
    pv = punctuation + vowels*5
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

if vertexcount >= 5000 and probability >= 0.05:
    print("Vertexcount and connectedness too high! Please reduce vertexcount to <5000 and connectedness<0.3")
    exit(1)


G = nx.gnp_random_graph(vertexcount, probability, directed=True)
sccs = list(nx.strongly_connected_components(G))

# counter = 0
# while len(sccs) >= len(G.nodes()) - 10 or len(sccs) <= len(G.nodes()) - 50:
#     G = nx.gnp_random_graph(vertexcount, probability, directed=True)
#     list(nx.strongly_connected_components(G))
#     counter += 1
#     if counter > 100:
#         print("Too many steps taken to create SCCs graph that's reasonable! Aborting.")
#         break
# for i in range(len(G.nodes())):
#     G.nodes[i]['page'] = words[i]
#for i in range(len(G.nodes())):
#    G.nodes[i]['page'] = "Page {}".format(i)

outscc = "\n".join(["{} {}".format(min(scc), " ".join([str(x) for x in scc])) for scc in sccs])

nx.write_edgelist(G, outedgefile, data=False)

# with open(outnamefile, 'w') as of:
#     for i in G.nodes():
#         of.write('{},"{}"\n'.format(i, G.nodes[i]['page']))

# with open(outnamefile, 'w') as of:
#     for i in range(len(G.nodes())):
#         of.write('{},"{}"\n'.format(i, "Page {}".format(i)))

words = random_words(vertexcount, 12)
outnames = '\n'.join(['{},"{}"'.format(i, word) for i, word in enumerate(words)])
with open(outnamefile, 'w') as of:
    of.write(outnames)
with open(outsccfile, 'w') as of:
    of.write(outscc)
