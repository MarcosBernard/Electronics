#---------------------------------------
# Calculo de tiempo TMR0 - PIC16F877A
#---------------------------------------
# Temporización = 4*(1/F.Oscilador)*(256-ValorTMR0)*Prescaler

#Variables independientes:
F_Osc = 4000000
ValorTMR0 = 0
Prescaler = 256

#Variable dependiente
Temporizacion = 4*(1/F_Osc)*(256-ValorTMR0)*Prescaler

print(Temporizacion)
