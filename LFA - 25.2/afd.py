import os

ESTADO_INICIAL = 0
PROX_ESTADO_LIVRE = 0

def imprimir_afnd(simbolos, afnd):
    print("\t\t" + "\t\t".join(simbolos))
    for r, row in enumerate(afnd):
        print(f"{r}\t\t" + "\t\t".join(cell if cell else "E" for cell in row))

def imprimir_afd(simbolos, afd:dict):
    print("\t\t" + "\t\t".join(simbolos))
    for key, values in afd.items():
        print(f"{key}\t\t" + "\t\t".join(cell for cell in values))

def processar_palavra(line, dict_simbolos, afnd, estados_finais, tokens_estados):
    global PROX_ESTADO_LIVRE
    eh_simbolo_inicial = True
    for char in line:
                if char != ' ' and char !="\n":
                    if eh_simbolo_inicial:
                        estado_atual = ESTADO_INICIAL
                    else:
                        estado_atual = PROX_ESTADO_LIVRE

                    if char in dict_simbolos:
                        idx = dict_simbolos[char]
                        if afnd[estado_atual][idx] == "" or afnd[estado_atual][idx] == "-":
                            afnd[estado_atual][idx] = str(PROX_ESTADO_LIVRE + 1)
                        else:
                            afnd[estado_atual][idx] += "," + str(PROX_ESTADO_LIVRE + 1)

                        PROX_ESTADO_LIVRE += 1

                    eh_simbolo_inicial = False
                elif char == '\n':
                    estados_finais.add(PROX_ESTADO_LIVRE)

                    nova_linha_estado_final = ['-'] * len(dict_simbolos) 
                    afnd[PROX_ESTADO_LIVRE] = nova_linha_estado_final
                    tokens_estados[PROX_ESTADO_LIVRE] = line.replace("\n","")

    if not line.endswith('\n'):
        tokens_estados[PROX_ESTADO_LIVRE] = line
        estados_finais.add(PROX_ESTADO_LIVRE)
        nova_linha_estado_final = ['-'] * len(dict_simbolos) 
        afnd.append(nova_linha_estado_final)

def processar_gramatica(line, dict_estados, dict_simbolos, afnd, estados_finais):
    global PROX_ESTADO_LIVRE
    line_no_space = line.replace(" ","").replace("<",'').replace(">",'').strip()
    nome_regra = line_no_space.split("::=")[0]
    producoes = (line_no_space.replace(f"{nome_regra}::=", '')).split("|")
    print(producoes)
    for p in producoes:
        # Casos do tipo aA
        if any(c.isupper() for c in p):
            if dict_estados[p[1]] == -1:
                dict_estados[p[1]] = PROX_ESTADO_LIVRE + 1
                PROX_ESTADO_LIVRE = PROX_ESTADO_LIVRE+1
            if afnd[dict_estados[nome_regra]][dict_simbolos[p[0]]] == "" or afnd[dict_estados[nome_regra]][dict_simbolos[p[0]]] == "-":
                afnd[dict_estados[nome_regra]][dict_simbolos[p[0]]] = str(dict_estados[p[1]])
            else:
                afnd[dict_estados[nome_regra]][dict_simbolos[p[0]]] += ","+str(dict_estados[p[1]])
        # Epsilon produção
        elif "*" in p:
            for i, s in enumerate(afnd[dict_estados[nome_regra]]):
                estados_finais.add(dict_estados[nome_regra])
                if s == "":
                    afnd[dict_estados[nome_regra]][i] = "-"
        # Somente um terminal
        else:
            PROX_ESTADO_LIVRE = PROX_ESTADO_LIVRE + 1
            if afnd[dict_estados[nome_regra]][dict_simbolos[p[0]]] == "" or afnd[dict_estados[nome_regra]][dict_simbolos[p[0]]] == "-":
                afnd[dict_estados[nome_regra]][dict_simbolos[p[0]]] = str(PROX_ESTADO_LIVRE)
            else:
                afnd[dict_estados[nome_regra]][dict_simbolos[p[0]]] += ","+ str(PROX_ESTADO_LIVRE)
            estados_finais.add(PROX_ESTADO_LIVRE)
            nova_linha_estado_final = ['-'] * len(dict_simbolos) 
            nova_linha = [''] * len(dict_simbolos) 
            afnd.append(nova_linha)  
            afnd[PROX_ESTADO_LIVRE] = nova_linha_estado_final

def afd_nova(afd,afnd, estados):
    if estados == []: return
    novos_estados = []
    for estado in estados:
            for novo_estado in afd[estado]:
                if novo_estado != '-' and novo_estado!='':
                    if novo_estado not in afd.keys():
                        novos_estados.append(novo_estado)
                        if "," in novo_estado:
                            transicoes = [''] * len(afd[estado]) 
                            for c in novo_estado.split(","):
                                    for i, estado_t in enumerate(afnd[int(c)]):
                                        if estado_t != '' and estado_t != '-':
                                            if transicoes[i] == '':
                                                transicoes[i] = estado_t
                                            else:
                                                transicoes[i] += ","+estado_t
                            afd[novo_estado] = transicoes
                        else:
                            if novo_estado not in afd:
                                afd[novo_estado] = afnd[int(novo_estado)]
            afd_nova(afd, afnd,novos_estados)

def gerar_afnd():
    global PROX_ESTADO_LIVRE
    if not os.path.exists("tokens.txt"):
        print("Erro ao abrir arquivo de tokens")
        return

    with open("tokens.txt","r") as tokens:
        simbolos = set()
        for line in tokens:
            for char in line.strip():
                if char != ' ' and char not in {':', '<', '>', '=', '|', '*', '\n'} and not char.isupper():
                    simbolos.add(char)
    simbolos = sorted(simbolos)
    dict_simbolos = {s: i for i, s in enumerate(simbolos)}

    count_simbolos = sum(len(line.strip()) for line in open("tokens.txt") if ("::" not in line))
    uppercase_letters = {char for line in open("tokens.txt") for char in line.strip() if char.isupper()}
    count_simbolos = count_simbolos + len(uppercase_letters) -1 if count_simbolos !=0 else count_simbolos + len(uppercase_letters)
    dict_estados = {u: -1 for u in uppercase_letters}
    dict_estados["S"] = 0
    estados_finais = set()
    tokens_estado = {}

    print(f"Simbolos: {simbolos}")
    afnd = [["" for _ in range(len(simbolos))] for _ in range(count_simbolos)]

    with open("tokens.txt","r") as tokens:
        for line in tokens:
            if("::" in line):
                processar_gramatica(line, dict_estados, dict_simbolos, afnd, estados_finais)
            else:
                processar_palavra(line, dict_simbolos, afnd, estados_finais, tokens_estado)

    print(f"Estados-Inteiro (Vindos das Gramaticas): {dict_estados}")
    print(f"Final dos tokens: {tokens_estado}")
    

    afd = {}
    afd['0'] = [cell for cell in afnd[0]]
    i = 0
    afd_nova(afd, afnd, list(afd.keys()))

    novos_estados_finais = []
    for estados in afd.keys():
        if "," in estados:
            for estado in estados.split(","):
                if int(estado) in estados_finais:
                    novos_estados_finais.append(estados)
                    break
        else:
            if int(estados) in estados_finais:
                novos_estados_finais.append(estados)
                   
    for estado_final in novos_estados_finais:
        if "" in afd[estado_final]:
            for i, elemento in enumerate(afd[estado_final]):
                if elemento == '':
                    afd[estado_final][i] = "-"
    print(f"Estados finais: {estados_finais}")
    print(f"Novos estados finais: {novos_estados_finais}")

    mapa_final_estados = {str(v): k for k, v in dict_estados.items()}
    ultimo_estado = list(dict_estados.keys())
    ultimo_estado.remove('S')
    ultimo_estado.sort()
    proxima_letra = ord(ultimo_estado[-1]) 
    for num_linha, linha in enumerate(afnd):
        if str(num_linha) not in mapa_final_estados.keys():
            while chr(proxima_letra) in dict_estados:
                proxima_letra += 1
            
            mapa_final_estados[str(num_linha)] = chr(proxima_letra)
            proxima_letra += 1

    for valor in afd.values():
        for i,cell in enumerate(valor):
            if cell != '' and cell !='-':
                if "," in cell:
                    estados_novos = cell.split(",")
                    new_name = "["
                    for e in estados_novos:
                        if new_name == "[":
                            new_name += mapa_final_estados[e]
                            continue
                        new_name+=","+mapa_final_estados[e]
                    new_name+=']'
                    valor[i]= new_name
                else:
                    valor[i]= mapa_final_estados[cell]
    chaves_antigas = list(afd.keys())
    for chave in chaves_antigas:
        if "," in chave:
            estados_novos = chave.split(",")
            new_name = "["
            for e in estados_novos:
                if new_name == "[":
                    new_name += mapa_final_estados[e]
                    continue
                new_name+=","+mapa_final_estados[e]
            new_name+=']'
            afd[new_name] = afd.pop(chave)
        else:
           afd[mapa_final_estados[chave]] = afd.pop(chave)
    estado_de_erro = ['~'] * len(simbolos)
    afd['Er'] = estado_de_erro
    for key, values in afd.items():
       for i, cell in enumerate(values):
            values[i] = cell if cell else "Er" 
    imprimir_afd(simbolos, afd)
if __name__ == "__main__":
    gerar_afnd()
