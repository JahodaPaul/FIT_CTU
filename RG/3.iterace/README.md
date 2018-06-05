# 2. Iterace

## Rozdělení bodů

| jméno              | přerozdělené body |
| ----------------   |:-------------:    |
|  Jakub Drbohlav    |         -5        |
|  Jiří Kasl         |          0        |
|  Pavel Jahoda      |          0        |
|  Petr Pondělík     |          0        |
|  Vanda Hendrychová |          2        |
|  Vojtěch Pejša     |          3        |

## Soubory
- Dodatečné soubory jsou k dispozici na [google disku](https://drive.google.com/drive/u/1/folders/1qCQDIhJG-wts_MB1C-xEC4TojV-LuYBh)
Zde se také nachází již vytvořené pdf ke všem iteracím.

- Tvorba dokumentace probíhala v markdownu (tudíž obsahuje i veškerou historii), LaTeX je pouze finální formátování.

### Vytvoření pdf
Pro ruční vytvoření pdf jsou třeba tyto kroky:

1. Stáhnout adresář [obrazky](https://drive.google.com/drive/u/1/folders/1qCQDIhJG-wts_MB1C-xEC4TojV-LuYBh) z google drivu.
2. Rozbalit tento .zip jako 2.iterace/obrazky
3. Zkompilovat LaTeX do pdf (příkaz pravděpodobně bude potřeba zavolat dvakrát kvůli vygenerovaní obsahu)

 - ``pdflatex navrhova_dokumentace_detailni_design.tex``

## Instalační balíček
K dispozici je instalační balíček pro debian (rg_0.1.0_amd64.deb), který je na google drivu. Test instalace
proběhl na debianu 9.4, na ubuntu 18.04 by také němel být problém. Starší verze těchto distribucí nemusí mít
aktuální verzi potřebných knihoven v repozitářích, instalace tudíž může být obtížnější. Pro nainstalování na 
debian 9.4 stačí stáhnout balíček a nainstalovat pomocí nástroje apt: ``sudo apt install ./rg_0.1.0_amd64.deb``
Hru je mo6n0 spustit z terminálu příkazem RG, nebo z nabídky aplikací v kategorii hry pod názvem RG.
