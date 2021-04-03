import random as rd

nVerts = rd.randint(1, 7)
while (True):
    nEdges = rd.randint(1, 7)
    if (nEdges > nVerts): break

print("{} {}".format(nVerts, nEdges))

while(True):
    nServ = rd.randint(1, 4)
    nMoni = rd.randint(0, 4)
    nCli  = rd.randint(1, 4)
    if ((nServ + nMoni + nCli) < nVerts): break

print("{} {} {}".format(nServ, nMoni, nCli))



vertexs = list(range(nVerts))

for count in range(nServ):
    serv = vertexs.pop(rd.randint(0, len(vertexs)-1))
    print(serv)
for count in range(nMoni):
    moni = vertexs.pop(rd.randint(0, len(vertexs)-1))
    print(moni)
for count in range(nCli):
    cli = vertexs.pop(rd.randint(0, len(vertexs)-1))
    print(cli)


for edges in range(nEdges):
    print(rd.randint(0, nVerts-1), rd.randint(0, nVerts-1), rd.randint(1, 30))

