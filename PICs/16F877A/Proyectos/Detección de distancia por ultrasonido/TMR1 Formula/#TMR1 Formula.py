#TMR1 Formula
'''
Desborde_Timer1 = (4/(Frecuencia_Oscilador))*Preescaler*(65536-TMR1)

Paso_Contador = 4/FrecuenciaOscilación
'''
print("Frecuencia del Oscilador (MHz):")
Freq=int(input())

print("Prescaler:")
Prescaler=int(input())

print("TMR1:")
TMR1=int(input())

DesbordeTMR1=float((4/(Freq*1000000))*Prescaler*(65536-TMR1))
print(DesbordeTMR1)