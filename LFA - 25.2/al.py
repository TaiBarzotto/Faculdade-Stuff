from afd import gerar_afd

afd, simbolos, dict_simbolos, estados_finais = gerar_afd()
ESTADO_ATUAL_AL = '0'
FITA = []
TOKEN = ''
TS = []
#print(afd)
#print(simbolos, dict_simbolos, estados_finais)
PALAVRAS_RESERVADAS = {}
ENTRADA = []
with open('tokens.txt', 'r') as f:
    for line in f:
        palavra = line.strip()
        if '::' not in line and palavra:  # ignora as regras da GR
            PALAVRAS_RESERVADAS[palavra] = palavra
print(PALAVRAS_RESERVADAS)

with open('entrada.txt', 'r') as file:
    erro = False
    for num_linha, line in enumerate(file):
        for char in line:
            if char != ' ' and char != '\n':
                if char not in simbolos:
                    ESTADO_ATUAL_AL = '~'
                    TOKEN+=char
                else:
                    posicao = dict_simbolos[char]
                    aux = afd[ESTADO_ATUAL_AL][posicao]
                    ESTADO_ATUAL_AL = aux
                    TOKEN+=char
            else:
                if ESTADO_ATUAL_AL in estados_finais:
                    if TOKEN != ' ' and TOKEN != '\n' and TOKEN != '':
                        ts_token = {
                            'token': TOKEN,
                            'tipo': PALAVRAS_RESERVADAS.get(TOKEN.lower(), "id"),
                            'tipo_dado': type(TOKEN),
                            'linha': num_linha,
                            'status': 'aceito'
                        }
                        FITA.append(PALAVRAS_RESERVADAS.get(TOKEN.lower(), "id"))
                        ENTRADA.append(TOKEN)
                        TS.append(ts_token)
                    TOKEN = ''
                elif ESTADO_ATUAL_AL == '~':
                    erro = True
                    ts_token = {
                        'token': TOKEN,
                        'linha': num_linha,
                        'status': 'ERRO'
                    }
                    TS.append(ts_token)
                    TOKEN = ''
                    #print("TOKEN NÃO RECONHECIDO")
                ESTADO_ATUAL_AL = '0'
    if erro:
        for item in TS:
            if item.get('status') == "ERRO":
                print(f"Erro léxico no token {item.get('token')} na linha {item.get('linha')}")
    else:
        print("Analise léxica concluida com sucesso\nTabela de Simbolos: ", TS)
        print("Fita de Estados: ", FITA)  
      
                    
                    
                    

