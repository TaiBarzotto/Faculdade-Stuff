import math

def bissecao(f, a, b, precisao=0.1, max_iter=1000000):
    if f(a) == 0:
        return f"a equação tem pelo menos uma solução neste intervalo: ({a:.4f}, {a:.4f})\nIterações = {i+1}"
    if f(b) == 0:
        return f"a equação tem pelo menos uma solução neste intervalo: ({b:.4f}, {b:.4f})\nIterações = {i+1}"

    if f(a) * f(b) > 0:
        return "não é possível afirmar que existe solução neste intervalo, tente outros dois números"

    for i in range(max_iter):
        c = (a + b) / 2
        fc = f(c)
        if (b - a) <= precisao:
            return f"a equação tem pelo menos uma solução neste intervalo: ({a:.4f}, {b:.4f})\nIterações = {i+1}"
        if f(a) * fc < 0:
            b = c
        else:
            a = c
    return f"a equação tem pelo menos uma solução neste intervalo: ({a:.4f}, {b:.4f})\nIterações = {i+1}"

# === Equação ii: x^4 + sqrt(x) - 2x - 4 ===
def f2(x):
    return math.exp(2*x) + x**2 - 3

# === Equação iii: 2cos(x) + 6 - x ===
def f3(x):
    return 2 * math.cos(x) + 6 - x

# === Entrada do usuário ===
print("Escolha a equação:")
print("1 - e^(2x) + x^2 = 3")
print("2 - 2cos(x) + 4 = x - 2")
escolha = input("Digite 1 ou 2: ")

a = float(input("Digite o valor de a: "))
b = float(input("Digite o valor de b: "))

if escolha == "1":
    print(bissecao(f2, a, b))
elif escolha == "2":
    print(bissecao(f3, a, b))
else:
    print("Escolha inválida.")
