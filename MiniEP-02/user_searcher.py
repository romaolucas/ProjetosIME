import sys

def buscaNome():
    nomes = []
    homonimos = []
    for line in sys.stdin:
        txt = line.split(':')
        if len(txt) != 7:
            raise Exception("Arquivo invalido") 
        try:
            i = nomes.index(txt[4])
        except ValueError:
            nomes.append(txt[4])
            homonimos.append([])
            homonimos[homonimos.index([])].append(txt[0])
        else:
            homonimos[i].append(txt[0])
    for i in range(0, len(nomes)):
        print(nomes[i], homonimos[i])

try:
    opt = sys.argv[1]
    if opt == '-a':
        buscaNome()
    elif opt == '-u':
        print("Busca por UID")
    else:
        raise Exception("Opcao invalida!")
except IndexError:
    print("Uso: \n python3 -u user_searcher.py para buscar por UID \n" +
        " python3 -a user_searcher.py para buscar por nome de usuario")

