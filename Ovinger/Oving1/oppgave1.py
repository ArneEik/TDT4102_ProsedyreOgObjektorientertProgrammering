# oppgave1.py
print("Kjorer Oppgave 1 i Python")
# Din kode for oppgave 1 her

def isFibonacciNumber(n):
    a, b = 0,1
    while b<n:
        temp = b
        b +=a
        a = temp
    return b==n

print(isFibonacciNumber(2))