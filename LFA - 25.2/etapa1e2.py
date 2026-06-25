from al import FITA, ENTRADA, dict_simbolos

inicio = "E'"

# producoes_lista[n] - índice igual ao rN da tabela SLR
producoes_lista = [
    ("E'", "E"),       # r0
    ("E",  "E + T"),   # r1
    ("E",  "T"),       # r2
    ("T",  "T & F"),   # r3
    ("T",  "F"),       # r4
    ("F",  "( E )"),   # r5
    ("F",  "id"),      # r6
]

# FIRST e FOLLOW 
conjunto_first = {
    "E'": {"(", "id"},
    "E":  {"(", "id"},
    "T":  {"(", "id"},
    "F":  {"(", "id"},
}

conjunto_follow = {
    "E'": {"$"},
    "E":  {"$", "+", ")"},
    "T":  {"$", "+", "&", ")"},
    "F":  {"$", "+", "&", ")"},
}

# GOTO 

goto = {
    0:  {"E": 1,  "T": 2,  "F": 3,  "(": 4,  "id": 5},
    1:  {"+": 6},
    2:  {"&": 7},
    4:  {"E": 8,  "T": 2,  "F": 3,  "(": 4,  "id": 5},
    6:  {"T": 9,  "F": 3,  "(": 4,  "id": 5},
    7:  {"F": 10, "(": 4,  "id": 5},
    8:  {")": 11, "+": 6},
    9:  {"&": 7},
}

# TABELA SLR
# "sN" = shift | "rN" = reduce | "acc" = aceite | "" = erro

tabela_slr = {
    0:  {"+": "",    "&": "",    "(": "s4",  ")": "",    "id": "s5",  "$": "",     "E": "1",  "T": "2",  "F": "3"},
    1:  {"+": "s6",  "&": "",    "(": "",    ")": "",    "id": "",    "$": "acc",  "E": "",   "T": "",   "F": ""},
    2:  {"+": "r2",  "&": "s7",  "(": "",    ")": "r2",  "id": "",   "$": "r2",   "E": "",   "T": "",   "F": ""},
    3:  {"+": "r4",  "&": "r4",  "(": "",    ")": "r4",  "id": "",   "$": "r4",   "E": "",   "T": "",   "F": ""},
    4:  {"+": "",    "&": "",    "(": "s4",  ")": "",    "id": "s5",  "$": "",     "E": "8",  "T": "2",  "F": "3"},
    5:  {"+": "r6",  "&": "r6",  "(": "",    ")": "r6",  "id": "",   "$": "r6",   "E": "",   "T": "",   "F": ""},
    6:  {"+": "",    "&": "",    "(": "s4",  ")": "",    "id": "s5",  "$": "",     "E": "",   "T": "9",  "F": "3"},
    7:  {"+": "",    "&": "",    "(": "s4",  ")": "",    "id": "s5",  "$": "",     "E": "",   "T": "",   "F": "10"},
    8:  {"+": "s6",  "&": "",    "(": "",    ")": "s11", "id": "",   "$": "",     "E": "",   "T": "",   "F": ""},
    9:  {"+": "r1",  "&": "s7",  "(": "",    ")": "r1",  "id": "",   "$": "r1",   "E": "",   "T": "",   "F": ""},
    10: {"+": "r3",  "&": "r3",  "(": "",    ")": "r3",  "id": "",   "$": "r3",   "E": "",   "T": "",   "F": ""},
    11: {"+": "r5",  "&": "r5",  "(": "",    ")": "r5",  "id": "",   "$": "r5",   "E": "",   "T": "",   "F": ""},
}


def analise_sitatica(fita, values):
    pilha_semantica = []
    pilha = [0]
    entrada = list(fita) + ['$']
    entrada_value = list(values) + ['$']
    passo = 1
    erro = False
    ts = []
    count_temp=1
    primeira_prod_soma = False
    primeira_reducao = True

    print("\n============================= ANÁLISE SINTÁTICA SLR =============================")
    print("Passo\tPilha\t\t\tEntrada\t\t\tAção")
    print("-" * 81)

    while True:
        estado_topo = pilha[-1]
        simbolo_atual = entrada[0]
        acao = tabela_slr.get(estado_topo, {}).get(simbolo_atual, '')

        print(str(passo) + "\t" + str(pilha) + "\t" + str(entrada) + "\t" + (acao if acao else 'ERRO'))
        passo += 1

        if acao == '':
            print("Erro no estado " + str(estado_topo) + " com simbolo " + simbolo_atual)
            erro = True
            break

        elif acao == 'acc':
            print("Analise Sintática concluida: Cadeia aceita com sucesso!")
            break

        elif acao.startswith('s'):
            prox_estado = int(acao[1:])
            pilha.append(simbolo_atual)
            pilha.append(prox_estado)
            entrada.pop(0)

        elif acao.startswith('r'):
            num_producao = int(acao[1:])
            nao_terminal, corpo = producoes_lista[num_producao]
            tamanho = len(corpo.split(" ")) if corpo != '*' else 0

            for _ in range(tamanho * 2):
                pilha.pop()
            
            if num_producao == 1:
                # ANALISE SEMANTICA - Gramatica não aceita soma como primeira operação
                if primeira_reducao:
                    primeira_prod_soma = True
            
                ts.append(f"T{count_temp} = E.val + T.val")
                count_temp+=1
                
            elif num_producao == 3: 
                ts.append(f"T{count_temp} = T.val & F.val")
                count_temp+=1

            estado_topo_novo = pilha[-1]
            simbolo_atual = entrada[0]
            prox_goto = tabela_slr.get(estado_topo_novo, {}).get(nao_terminal, '')
            if prox_goto == '':
                print("Erro sintatico: goto indefinido para (" + str(estado_topo_novo) + ", " + nao_terminal + ")")
                erro = True
                break

            pilha.append(nao_terminal)
            print(str(passo) + "\t" + str(pilha) + "\t" + str(entrada) + "\t" + (prox_goto if prox_goto else 'ERRO'))
            passo += 1
            pilha.append(int(prox_goto))
            primeira_reducao=False
            
    return erro, primeira_prod_soma, ts

            
    
if __name__ == "__main__":
    print("Fita para parse: ", FITA)
    print("Fita com valores: ", ENTRADA)
    print("Dict", dict_simbolos)
    erro, erro_semantico, ts = analise_sitatica(FITA, ENTRADA)
    if erro_semantico: 
        print("Erro semantico: A gramáticca não aceita somas como primeira operação")
    else:
        print("TS com código intermediário:")
        for i in ts:
            print("\t"+ i)
    
    # Coloca as reduções, guarda a primeira operação, ver se ela é uma soma  efala que na tua gramatica n pode soma 