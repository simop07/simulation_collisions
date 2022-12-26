# Simulation

[This project](#simulation) show an approximated simulation of elementay particles colliding.\
The code I developed is used for physics course [Laboratorio di Elettromagnetismo e 
Ottica](https://www.unibo.it/it/didattica/insegnamenti/insegnamento/2022/434322) during 2021-2022 academic year.

## Download and usage

The project is written in [C++](https://isocpp.org/) language, and it is supported by 
[ROOT](https://root.cern.ch/) analysis framework. It can be compiled with [GCC](https://gcc.gnu.org/).

## Note

- **Aggiungere commenti**, ma non troppi tanto c'è già la relazione di supporto
- Scrivere che è normale ottenere dei memory leak, basta verificarlo con fSanitize..., e spiegare perché non si può agire con una delete per risolverli (poiché altrimenti gli oggetti muoiono non appena il programma finisce e non viene visualizzato nulla, un po' come il DrawCopy).
- Aggiungere indirizzo di Github nella relazione, assieme a tutto ciò che riguarda:

    - Istruzioni di dowload
    - Istruzioni di compilazione
    - Istruzioni di testing
    - Tutto quello che richiede l'Arcelli nel pdf
    - Aggiunta di verifica indipendenza generazione angolo polare e azimutale

- Per compilare il file script.sh: "chmod +x script.sh"
- Dai un'occhiata al file .txt di appunti presente nella cartella