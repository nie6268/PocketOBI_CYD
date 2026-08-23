# PocketOBI CYD – Firmware exportieren & im Browser flashen

Diese Anleitung beschreibt, wie du aus dem Arduino-Sketch eine fertige
`.bin`-Firmware machst und sie ohne Arduino IDE über den Browser auf ein
CYD (ESP32-2432S028) flashst.

## Teil 1: Kompilierte Binärdatei aus der Arduino IDE exportieren

1. Sketch in der Arduino IDE öffnen, Board **"ESP32 Dev Module"** auswählen
   (Werkzeuge → Board).
2. **Wichtig, bevor du kompilierst:** `User_Setup.h` muss in der
   TFT_eSPI-Bibliothek bereits mit `ILI9341_2_DRIVER` und der korrekten
   Pin-Belegung für dieses Board vorliegen – siehe separate
   Projekt-Dokumentation. Ohne das hängt sich das Display beim Start auf.
3. Menü **Sketch → "Kompilierte Binärdatei exportieren"** (bzw. `Strg+Alt+S`).
4. Im Sketch-Ordner erscheint ein Unterordner **`build`**. Darin liegen
   (Dateinamen können leicht abweichen):
   - `<Sketchname>.ino.bootloader.bin`
   - `<Sketchname>.ino.partitions.bin`
   - `<Sketchname>.ino.bin` (die eigentliche Firmware)
   - ggf. `boot_app0.bin`

Diese Dateien gehören zusammen – für einen vollständigen Flash-Vorgang
brauchst du alle.

## Teil 2: Im Browser flashen (Adafruit WebSerial ESPTool)

Kein Terminal, keine Zusatzsoftware nötig. Browser: **Chrome oder Edge**
(Web Serial wird von Firefox/Safari nicht unterstützt).

1. Seite öffnen: **https://adafruit.github.io/Adafruit_WebSerial_ESPTool/**
2. Board per USB anschließen.
3. Oben rechts auf **Connect** klicken, im Popup den passenden COM-/USB-Port
   auswählen.
4. Die Seite zeigt vier Zeilen mit je einem Offset-Feld und einem
   "Choose a file…"-Button. Eintragen:

   | Offset | Datei |
   |---|---|
   | `0x1000` | `<Sketchname>.ino.bootloader.bin` |
   | `0x8000` | `<Sketchname>.ino.partitions.bin` |
   | `0xe000` | `boot_app0.bin` (falls vorhanden) |
   | `0x10000` | `<Sketchname>.ino.bin` |

5. Unten auf **Program** klicken. Ein Fortschrittsbalken erscheint – Board
   während des Vorgangs nicht abstecken.
6. Nach Abschluss: Board einmal aus- und wieder einstecken (oder Reset-Taste),
   damit die neue Firmware startet.

### Falls die Offsets bei dir abweichen

Die Werte oben gelten für den klassischen ESP32 (wie im CYD) mit Standard-
Partitionsschema. Sicherheitshalber prüfen: In der Arduino IDE unter
**Datei → Voreinstellungen** die Option **"Ausführliche Ausgabe während:
Hochladen"** aktivieren, dann einmal ganz normal per Kabel hochladen. Im
Ausgabefenster erscheint der komplette `esptool`-Befehl mit den exakt
verwendeten Adressen für dein Board/Partitionsschema – die kannst du 1:1
übernehmen, falls sie von der Tabelle oben abweichen.
