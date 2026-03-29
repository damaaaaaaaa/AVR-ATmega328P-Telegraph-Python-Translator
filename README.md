# AVR ATmega328P Telegraph & Python Translator

Questo progetto trasforma una board basata su ATmega328P in un telegrafo programmato in C puro (senza librerie standard). Sfrutta Timer e Interrupt hardware per misurare la durata della pressione di un pulsante, invia i segnali Morse via Seriale e utilizza uno script Python per tradurre il file di log in testo leggibile.

## Hardware
* **Pin 2:** Pulsante (Input)
* **Pin 12:** Buzzer (Output)
* **Pin 13:** LED (Output)

## Tempistiche Morse
* **< 300 ms:** Punto (`.`)
* **Fino a 1 sec:** Linea (`-`)
* **Fino a 3 sec:** Spazio tra lettere (` `)
* **Fino a 10 sec:** Slash / Separatore (`/`)
* **Oltre 10 sec:** Ritorno a capo (`\n`)

## Come si usa

### 1. Compilazione e Caricamento
Apri il terminale nella cartella del progetto e usa il Makefile:

```bash
make        # Compila il codice sorgente
make flash  # Carica il programma sul microcontrollore
make clean  # (Opzionale) Pulisce i file di build
```

### 2. Registrazione dei segnali
Usa `screen` per ascoltare la porta seriale a 9600 baud. Sostituisci `/dev/ttyUSB0` con la tua porta reale (es. `/dev/ttyACM0`):

```bash
screen -L /dev/ttyUSB0 9600
```
L'opzione `-L` salverà tutto l'output generato dall'AVR nel file `screenlog.0` all'interno della cartella corrente. Per uscire e chiudere la connessione premi `Ctrl+A` seguito da `K` (conferma con `y`).

### 3. Traduzione con Python
Avvia lo script Python:

```bash
python3 traduttore.py
```

Dal menu dello script potrai:
1. Leggere i segnali da `screenlog.0` e tradurli in lettere all'interno di un nuovo file di output.
2. Pulire/svuotare il file di log originale (`screenlog.0`) per una nuova sessione.
3. Pulire il file di testo con la traduzione.
