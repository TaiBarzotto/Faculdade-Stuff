import os

ESTADO_INICIAL = 0
PROX_ESTADO_LIVRE = 0

def processar_palavra(line, dict_simbolos, afnd):
    global PROX_ESTADO_LIVRE
    eh_simbolo_inicial = 1
    for char in line:
                if char != ' ' and char !="\n":
                    if eh_simbolo_inicial:
                        estado_atual = ESTADO_INICIAL
                    else:
                        estado_atual = PROX_ESTADO_LIVRE

                    if char in dict_simbolos:
                        idx = dict_simbolos[char]
                        if afnd[estado_atual][idx] == "":
                            afnd[estado_atual][idx] = str(PROX_ESTADO_LIVRE + 1)
                        else:
                            afnd[estado_atual][idx] += ", " + str(PROX_ESTADO_LIVRE + 1)

                        PROX_ESTADO_LIVRE += 1

                    eh_simbolo_inicial = False
                

def main():
    if not os.path.exists("tokens.txt"):
        print("Erro ao abrir arquivo de tokens")
        return

    with open("tokens.txt", "r") as tokens:
        simbolos = set()
        for line in tokens:
            for char in line.strip():
                if char != ' ' and char not in {':', '<', '>', '=', '|'} and not char.isupper():
                    simbolos.add(char)

    dict_simbolos = {s: i for i, s in enumerate(simbolos)}

    count_simbolos = sum(len(line.strip()) for line in open("tokens.txt") if ("::" not in line))
    uppercase_letters = {char for line in open("tokens.txt") for char in line.strip() if char.isupper()}
    count_simbolos = count_simbolos + len(uppercase_letters) -1 if count_simbolos !=0 else count_simbolos + len(uppercase_letters)
    dict_estados = {u: -1 for u in uppercase_letters}
    dict_estados["S"] = 0

    afnd = [["" for _ in range(len(simbolos))] for _ in range(count_simbolos)]

    with open("tokens.txt", "r") as tokens:
        for line in tokens:
            if("::" in line):
                line_no_space = line.replace(" ", "").replace("<",'').replace(">",'').strip()
                nome_regra = line_no_space.split("::=")[0]
                producoes = (line_no_space.replace(f"{nome_regra}::=", '')).split("|")
                print(producoes)
                for p in producoes:
                    # Casos do tipo aA
                    if any(c.isupper() for c in p):
                        if dict_estados[p[1]] == -1:
                            dict_estados[p[1]] = PROX_ESTADO_LIVRE + 1
                        if afnd[dict_estados[nome_regra]][dict_simbolos[p[0]]] == "":
                            afnd[dict_estados[nome_regra]][dict_simbolos[p[0]]] = str(dict_estados[p[1]])
                        else:
                            afnd[dict_estados[nome_regra]][dict_simbolos[p[0]]] = ", ",str(dict_estados[p[1]])
                    if "-" in p:
                        print("EPSILON")


                    
            else:
                processar_palavra(line, dict_simbolos, afnd)

    print(dict_estados)

    print("\t" + "\t".join(simbolos))
    for r, row in enumerate(afnd):
        print(f"{r}\t" + "\t".join(cell if cell else "-" for cell in row))

if __name__ == "__main__":
    main()