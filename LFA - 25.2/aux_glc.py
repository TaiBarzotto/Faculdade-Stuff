#aplicar eliminação de inúteis e de fatoração na GLC;
def definir_glc():
    glc = {}
    with open("glc.txt","r") as glc_file:
        for idx, line in enumerate(glc_file):
            nome_regra = line.split('->')[0].strip()
            if idx == 0:
                inicial = nome_regra
            producoes_raw = line.split('->')[1].split('|')
            producoes=[]
            for prod in producoes_raw:
                aux = prod.replace('\n', "")
                prod= aux.strip()
                producoes.append(prod)

            glc[nome_regra] = producoes
    return glc, inicial


def remover_inalcancaveis(glc, inicio):
    chegou = {inicio}
    proximo = [inicio]
    while proximo:
        cur_state=proximo.pop(0)
        for prod in glc[cur_state]:
            for c in prod:
                if c.isupper() and c!=cur_state and c not in chegou:
                    chegou.add(c)
                    proximo.append(c)
    
    inalcancaveis = set(glc.keys()) - chegou
    if inalcancaveis:
        print("Inalcancaveis: ", inalcancaveis)    
    for i in inalcancaveis:
        del glc[i]
    return glc
        
def remover_improdutivos(glc):
    produtivos = set()
    for key, values in glc.items():
        if key in produtivos:
            continue
        for prod in values:
            for c in prod:
                if c.islower():
                    produtivos.add(key)
                    break
                if c.isupper() and c!=key and c in produtivos:
                    produtivos.add(key)
                    
    improdutivos_direto = list(set(glc.keys()) - produtivos)
    
    for value in improdutivos_direto:
        estados_seguinte = [value]
        mudou = True
        while estados_seguinte and mudou:
            continued = False
            analisado= estados_seguinte[-1]
            for prod in glc[analisado]:
                for c in prod:
                    if continued:
                        break
                    if c !=' ':
                        if c.isupper() and c!=analisado and c in produtivos:
                            produtivos.add(analisado)
                            estados_seguinte.remove(analisado)
                            continued = True
                            continue
                        if c.isupper() and c!=analisado and c not in produtivos:
                            if c in estados_seguinte:
                                mudou = False
                                break
                            estados_seguinte.append(c)
                if not continued:
                    if any(estados_seguinte) in produtivos:
                        produtivos.add(value)
                        estados_seguinte.remove(value)
                      
    improdutivos = set(glc.keys()) - produtivos
    if improdutivos:
        print("Improdutivos: ", improdutivos)    
    for i in improdutivos:
        del glc[i]
    return glc
    
#Construção do conjunto de itens válidos, transições e first/follow
def first(glc):
    first_c = {s: set() for s in glc.keys()}
    for key, values in glc.items():
        for value in values:
            primeiro = value[0]
            if primeiro.islower():
                first_c[key].add(value.split(" ")[0])
                
    mudou = True
    while mudou:
        aux = first_c.copy()
        for key, values in glc.items():
            for value in values:
                primeiro = value[0]
                if primeiro.islower():
                    continue
                else:
                    first_c[key] = first_c[key]|first_c[primeiro]
        if aux == first_c:
            mudou=False
                    
    return(first_c)
                        
def follow(glc, first, inicio):
    c_follow = {s: set() for s in glc.keys()}
    c_follow[inicio].add('$')
    for key, values in glc.items():
        for value in values:
            palavras = value.split(" ")
            for i, c in enumerate(palavras):
                if c.isupper():
                    if i + 1 < len(palavras):
                        proximo = palavras[i+1]
                        if proximo.islower():
                            c_follow[c].add(proximo)
                        else:
                            c_follow[c] = c_follow[c] | first[proximo]
    
    mudou = True
    while mudou:
        aux = c_follow.copy()
        for key, values in glc.items():
            for value in values:
                fim = value[-1]
                if fim.isupper():
                    c_follow[fim] = c_follow[fim] | c_follow[key]
        if aux == c_follow:
            mudou=False
        
def itens_validos(glc, inicio):
    glc_aumentada = {f"{inicio}'": [f"{inicio} $"]}
    inicio_aumentado = f"{inicio}'"
    
glc, inicio = definir_glc()
glc = remover_inalcancaveis(glc, inicio)
glc = remover_improdutivos(glc)
conjunto_first = first(glc)
conjunto_follow = follow(glc, conjunto_first, inicio)


