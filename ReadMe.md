**Introduksjon Live proximity web server med esp32 c3**

_Hvordan bruke Code Cell sin esp32 c3 som web server_
1. Følg code cell sin getting started https://microbots.io/pages/learn-codecell å sett opp esp32 etter de parameterene.


2. Copy paste code fra Web_server for kode. Bytt ssid og passord slik at det passer ruter.


3. Det er mulig å låne min private ruter hvis du spør pent !


4. Code cell sin ESP32 C3 har en integrert avstandsmåler. Data fra den sensoren sendes fra MCU til web serveren (som også styres fra mikrokontrolleren).


5. Koble på nettside ved å skrive inn IP-adresse til MCU inn i en nettleser. 
IP-adresse blir printet i terminal etter at den har fått en velykket tilkobling til ruter. 

**DEMO**


![Pomodoro ferdig produkt](https://github.com/RealHaakon/Klokke_introprojekt/blob/main/bilder_og_gifs/LivePoximity-ezgif.com-speed.gif)


**Komponentliste**
| Komponent  | Type          | Kvantitet |
|:-----------|:-------------:|----------:|
| ESP32 C3   | CodeCell      | 1         |
| Wifi ruter | TUF-AX5400    | 1         |


**Ordliste**
| Forkortelse     | Betydning                     | 
|:----------------|:-----------------------------:|
| MCU             | Microcontroller unit          |
| ESP32           | chip fra Espressif Systems    |