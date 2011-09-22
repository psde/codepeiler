Anleitung:

 1. Kopieren Sie die Bibliothek "libsysprogSS2011.so" (32 oder 64 Bit)
    in ein Verzeichnis Ihrer Wahl.

        Etwa:  /usr/local/lib


 2. Setzen Sie die Variable "LD_LIBRARY_PATH" entsprechend.
 
        (für bash-Nutzer)
        LD_LIBRARY_PATH=$LD_LIBRARAY_PATH:/usr/local/lib
        export LD_LIBRARY_PATH


 3. Starten Sie nun den Interpreter 

        java –jar interpreter.jar
 
 
 4. Laden Sie die auszuführende Code-Datei über das File-Menü. 
 
