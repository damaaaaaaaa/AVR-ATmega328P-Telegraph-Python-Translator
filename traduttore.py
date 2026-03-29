import random

convert = {
    ".-": "a", "-...": "b", "-.-.": "c","-..": "d",  ".": "e", "..-.": "f", "--.": "g",
    "....": "h", "..": "i", ".---": "j", "-.-": "k", ".-..": "l", "--": "m", "-.": "n",
    "---": "o", ".--.": "p", "--.-": "q", ".-.": "r", "...": "s", "-": "t", "..-": "u", 
    "...-": "v", ".--": "w", "-..-": "x", "-.--": "y", "--..": "z", "/": " "
}

def prendi_morse (nomefile):
    f = open (nomefile, "r")
    buffer = []
    try:
        for riga in f:
            riga = riga.strip ('\n')
            lettere = riga.split (' ')
            for parola in lettere:
                buffer.append (parola)
    except Exception as e:
        print ("Qualcosa e' andato storto: ", e)
    finally:
        f.close()
        return buffer

def traduci (nomefile):
    file = nomefile + ".txt"
    buffer = prendi_morse ('screenlog.0')
    f = open (file, 'a')
    try:
        for i, parola in enumerate (buffer):
            if parola in convert:
                f.write (convert[parola])
            else:
                if (random.randint (1, 10) < 2): f.write ('\n')
    except Exception as e:
        print ("errore ", e)
    finally:
        f.close ()


def pulisci (nomefile):
    if nomefile == "screenlog.0":
        open(nomefile, "w").close()
    else:
        nome_file_trad = nomefile + ".txt"
        open(nome_file_trad, "w").close()


def main ():
    while True:
        question = input ("Vuoi tradurre, eliminare un file o annullare?\n([t] per tradurre, [e] per eliminare, altro per annullare)\n")
        if question.upper() == "T":
            nome_file_trad = input ("Inserisci come chiamare il file della traduzione: ")
            traduci (nome_file_trad)
        elif question.upper() == "E":
            quale_elim = input ("Vuoi eliminare il file di log del codice morse o uno di traduzione?\n([t] per pulire il file della traduzione, altro per il file di log)\n")
            if quale_elim.upper() == "T":
                nome_file_elim = input ("Inserisci il nome del file da eliminare: ")
                pulisci (nome_file_elim)
            else:
                pulisci ("screenlog.0")
        else:
            print ("annullamento...")
            break


if __name__ == "__main__":
    main ()
    