#1 Návrh Architektury
Architektura aplikace bude fungovat jako MVC(Model-View-Controler). Vybrali jsme tuto architekturu protože rozděluje aplikaci do tří komponent.
-Model( správa data)
-View(uživatelské rozhraní)
-Controller(řídící logika)
Hlavní výhodou architektury MVC je, že všechny tři komponenty jsou na sobě co nejméně závislé a díky tomu je jednoduché v případě potřeby jednu z nich vyměnit aniž by to narušilo funkčnost zbývajících dvou komponent. To navíc velmi zjednodušuje paralelní vývoj aplikace, protože každý člen týmu může pracovat na jiné části.
Navíc vývojář nemusí přemýšlet kam svůj kód umístit.

Použíté knihovny a frameworky:
- Grafická knihovna -> sfml
- Grafické uživatelské rozhraní -> Imgui
- Fyzika a kolize -> Box2D
- Správa buildů -> Cmake

Pro lepší představu je architektura MVC znázorněna na následujícím obrázku.


## 1.1 Prezentační vrstva - View
View je komponenta, která dostává data z modelu a zobrazuje je uživateli. Je rozdělěna prozatím na dvě části, "Game_Scene" a "Menu_Scene". V budoucnu možná nějaké ještě přibudou. View odchytává stisky kláves a pohyb myši. Na základě aktuální stavu a odchytnuté klávesnici View odešle potřebné informace Contoleru. Důvodem, že jinak bude reagovat na stisk šipky ve hře, což například bude pohyb postavičky. A jinak bude reagovat v hlavním menu.

## 1.2 Datová vrstva - Model
Model obsahuje definice datových objektů a jsou v něm uložena všechna data, která aplikace používá. Stará se o persistenci dat. Ukládání a načítání hry. Přijímá příkazy od controleru a na základě nich pracuje s daty. Například je pošle View, aby je View mohlo zobrazit uživateli.

## 1.3 Controler
Contoler je mezičlánkem mezi prezenční a datovou vrstvou. Dostává informace od View vyhodnotí je a pošle potřebný příkaz Modelu. Například jestliže dostane od View příkaz jdi dopředu tak controler zjistí, že hráč šlápl na pas a ztratil poslední život a pošle modelu, že má poslat do View "dead screen", protože hra skončila.



