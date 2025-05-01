import math

def bisseccao(funcao, a, b, erro=0.1, max_iter=1000):
    """
    Implementa o método da bissecção para encontrar uma raiz de uma função
    contínua em um intervalo [a,b] onde f(a) e f(b) têm sinais opostos.
    
    Args:
        funcao: A função para a qual estamos buscando a raiz
        a, b: Limites do intervalo inicial
        erro: Tolerância máxima para o comprimento do intervalo (padrão: 0.1)
        max_iter: Número máximo de iterações (prevenção de loop infinito)
    
    Returns:
        tuple: (intervalo_a, intervalo_b, mensagem) onde intervalo_a e intervalo_b
               são os limites do intervalo final que contém a raiz
    """
    # Verificando se f(a) e f(b) têm sinais opostos
    fa = funcao(a)
    fb = funcao(b)
    
    if fa * fb >= 0:
        return (None, None, "não é possível afirmar que existe solução neste intervalo, tente outros dois números")
    
    iteracao = 0
    
    while (b - a) > erro and iteracao < max_iter:
        iteracao += 1
        
        # Calculando o ponto médio do intervalo
        c = (a + b) / 2
        fc = funcao(c)
        
        # Se f(c) = 0, encontramos a raiz exata
        if abs(fc) < 1e-10:
            return (c, c, "a equação tem pelo menos uma solução neste intervalo")
        
        # Atualizando o intervalo
        if fa * fc < 0:
            b = c
            fb = fc
        else:
            a = c
            fa = fc
    
    return (a, b, "a equação tem pelo menos uma solução neste intervalo")

# Função 1: x⁴ + √x = 2x + 4  →  x⁴ + √x - 2x - 4 = 0
def funcao1(x):
    if x <= 0:  # Garantir que a função está definida (√x requer x >= 0)
        return float('inf')  # Retornar um valor grande para x <= 0
    return x**4 + math.sqrt(x) - 2*x - 4

# Função 2: e²ˣ + x² = 3  →  e²ˣ + x² - 3 = 0
def funcao2(x):
    return math.exp(2*x) + x**2 - 3

# Função 3: 2cosx + 4 = x - 2  →  2cosx - x + 6 = 0
def funcao3(x):
    return 2*math.cos(x) - x + 6

def resolver_equacao(equacao_numero, a, b):
    """
    Resolve uma das equações usando o método da bissecção com entrada do usuário.
    
    Args:
        equacao_numero: Número da equação a ser resolvida (1, 2 ou 3)
        a, b: Limites do intervalo inicial fornecidos pelo usuário
    """
    if equacao_numero == 1:
        funcao = funcao1
        eq_texto = "x⁴ + √x = 2x + 4"
    elif equacao_numero == 2:
        funcao = funcao2
        eq_texto = "e²ˣ + x² = 3"
    elif equacao_numero == 3:
        funcao = funcao3
        eq_texto = "2cosx + 4 = x - 2"
    else:
        print("Número de equação inválido")
        return
    
    print(f"Resolvendo a equação {equacao_numero}: {eq_texto}")
    
    a_final, b_final, mensagem = bisseccao(funcao, a, b)
    
    print(f"Resultado: {mensagem}")
    if a_final is not None:
        print(f"Intervalo da solução: [{a_final:.6f}, {b_final:.6f}]")
        print(f"Comprimento do intervalo: {b_final - a_final:.6f}")
        print(f"Valor estimado da raiz: {(a_final + b_final)/2:.6f}")
        if b_final - a_final <= 0.1:
            print("O erro da aproximação é menor ou igual a 0.1, condição satisfeita!")
        else:
            print("O erro da aproximação ainda é maior que 0.1, mais iterações seriam necessárias.")

def main():
    # Receber a escolha da equação
    print("Escolha uma equação:")
    print("1. x⁴ + √x = 2x + 4")
    print("2. e²ˣ + x² = 3")
    print("3. 2cosx + 4 = x - 2")
    
    try:
        equacao = int(input("Digite o número da equação (1, 2 ou 3): "))
        if equacao not in [1, 2, 3]:
            print("Opção inválida. Por favor, escolha 1, 2 ou 3.")
            return
        
        # Receber o intervalo do usuário
        a = float(input("Digite o limite inferior do intervalo: "))
        b = float(input("Digite o limite superior do intervalo: "))
        
        if a >= b:
            print("O limite inferior deve ser menor que o limite superior.")
            return
        
        resolver_equacao(equacao, a, b)
        
    except ValueError:
        print("Entrada inválida. Por favor, digite números válidos.")

if __name__ == "__main__":
    main()