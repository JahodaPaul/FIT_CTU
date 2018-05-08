# 2. Iterace

## Rozdělení bodů

| jméno              | přerozdělené body |
| ----------------   |:-------------:    |
|  Jakub Drbohlav    |         -5        |
|  Jiří Kasl         |         +1        |
|  Pavel Jahoda      |         +1        |
|  Petr Pondělík     |         +1        |
|  Vanda Hendrychová |         +1        |
|  Vojtěch Pejša     |         +1        |

## Soubory
- Dodatečné soubory jsou k dispozici na [google disku](https://drive.google.com/drive/u/1/folders/1qCQDIhJG-wts_MB1C-xEC4TojV-LuYBh)
Zde se také nachází již vytvořené pdf s dokumentací (složka dokumentace).

- Tvorba dokumentace probíhala v markdownu (tudíž obsahuje i veškerou historii), LaTeX je pouze finální formátování.

### Vytvoření pdf
Pro ruční vytvoření pdf jsou třeba tyto kroky:

1. Stáhnout adresář [obrazky](https://drive.google.com/drive/u/1/folders/1qCQDIhJG-wts_MB1C-xEC4TojV-LuYBh) z google drivu.
2. Rozbalit tento .zip jako 1.iterace/obrazky
3. Zkompilovat LaTeX do pdf (příkaz pravděpodobně bude potřeba zavolat dvakrát kvůli vygenerovaní obsahu)

 - ```pdflatex analyticka_dokumentace.tex```

## Instalační balíček
K dispozici je instalační balíček pro debian ( rg_0.0.2_amd64.deb ) který je na google drivu. Test instalace
proběhl na debianu 9.4, na ubuntu 18.04 by také němel být problém. Starší verze těchto distribucí nemusí mít
aktuální verzi potřebných knihoven v repozitářích, instalace tudíž může být optážnější. Pro nainstalování na 
debian 9.4 stačí použít st8hnout bal84ek a pu69t ``sudo apt install ./tg_0.0.2_amd64.deb``
