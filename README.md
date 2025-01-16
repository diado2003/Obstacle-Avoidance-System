# Obstacle-Avoidance-System

# 1. Diagrama bloc a componentelor proiectului
- 3 LED-URI: verde, rosu, galben
- senzor ultrasonic
- buzzer
- 3 rezistente LED
- microcontroller

# Legături:

- Senzorul ultrasonic -> Microcontroller (măsurare distanță)
- Microcontroller -> LED-uri (semnalizare)
- Microcontroller -> Buzzer (avertizare sonoră)
- Microcontroller -> LCD display (afișare date)

# 2. Schema electrică a proiectului
- Pinii senzorului ultrasonic (trig, echo)
- LED-uri și rezistențe conectate la pini digitali
- Buzzer conectat la un pin digital
- LCD display conectat prin interfață I2C (dacă este adăugat)

# 3. BOM (Bill Of Materials)
- Senzor ultrasonic:	1	
- LED-uri (verde, roșu, galben):	3	
- Buzzer	:1	
- Rezistențe LED:	3	
- LCD display (opțional)	1	

# 4. Descrierea funcționalității hardware
- Senzor ultrasonic: măsoară distanța folosind unde sonore (interfață: pinii digitali pentru trig și echo).
- LED-uri: indică starea drumului (pini digitali).
- Buzzer: emite sunet în caz de pericol (pin digital).
- LCD display: afișează distanța în timp real (I2C).

Functionare:
- masoara distanta pana la obstacol
- verde: the path is clear
- galben: exista un obiect in apropiere
- rosu: risc de coliziune

# 5. Pini utilizați și justificare

Senzor ultrasonic:

- Trig -> D7 (semnal de ieșire)
- Echo -> D8 (semnal de intrare)
-L ED-uri:

- Verde -> D2 (drum liber)
- Galben -> D3 (obiect aproape)
- Roșu -> D4 (risc de coliziune)
- Buzzer: D5 (avertizare sonoră)



# To be decided:
- LCD display pentru a afisa distanta in timp real
- sa mai adaug un senzor ultrasonic astfel incat, daca obiectul apare pe partea stanga,
motorasul de pe acea parte sa se opreasca, iar cel de pe partea dreapta sa ramana pornit pentru a
lua curba fata de obstacol.
