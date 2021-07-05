def Newton(n, k):
    Wynik = 1
    for i in range(1, k + 1):
        Wynik = Wynik * (n - i + 1) / i
    return Wynik

omegaB= Newton(36,5)
omegaF = Newton(16,5)

paraB = 9 * Newton(4,2) * Newton(8,3) * (4**3)
paraF = 4 * Newton(4,2) * Newton(3,3) * (4**3)

dwieparyB = Newton(9,2) * (Newton(4,2)**2) * 7 * 4
dwieparyF = Newton(4,2) * (Newton(4,2)**2) * 2 * 4

trojkaB = 9 * Newton(4,3) * Newton(8,2) * (4**2)
trojkaF = 4 * Newton(4,3) * Newton(3,2) * (4**2)

stritB = 5 * (4**5) - 20
stritF = 0

kolorB = Newton(9,5) * 4 - 20
kolorF = 0

fulB = 9 * Newton(4,3) * 8 * Newton(4,2)
fulF = 4 * Newton(4,3) * 3 * Newton(4,2)

karetaB = 9 * 32
karetaF = 4 * 12

pokerB = 20
pokerF = 0

BLOTKARZ = [paraB/omegaB, dwieparyB/omegaB, trojkaB/omegaB, stritB/omegaB, kolorB/omegaB, fulB/omegaB, karetaB/omegaB, pokerB/omegaB]
FIGURANT = [paraF/omegaF, dwieparyF/omegaF, trojkaF/omegaF, stritF/omegaF, kolorF/omegaF, fulF/omegaF, karetaF/omegaF, pokerF/omegaF]

i = 1
blotkarzwin = 0

while i < len(BLOTKARZ):
    for j in range(i):
        blotkarzwin += FIGURANT[j]*BLOTKARZ[i]
    i += 1

print(f'BLOTKARZ WIN : {blotkarzwin*100}%')
