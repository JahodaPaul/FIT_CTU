Prototyp nového modelu auta sice těší designéry a manažery místní automobilky, ale inženýrům zodpovědným za plánování průběhu výroby nepřináší nic než noční můry. Designéři se totiž na novém modelu náležitě vyřádili a ke kompletaci vozu je zapotřebí postupně smontovat velmi vysoké množství dílčích součástek. Navíc mnohdy nastává případ, kdy nelze některou součástku smontovat dříve, než jsou smontovány jiné součástky, na kterých montáž závisí (např. pro smontování dveří je zapotřebí mít připravený zámek a kliku, mechanismus stahování okének, okénko, těsnění, atp.).

Kvůli komplexnosti konstrukce nového modelu auta je tak zapotřebí průběh výroby auta precizně naplánovat. Jinak by totiž hrozilo, že doba potřebná pro kompletaci jednoho vozu bude dlouhodobě nerentabilní. Vzhledem k tomu, že se nejedná o úlohu, kterou by bylo možno vzhledem k objemu součástek vyřešit ručně, byli jste na řešení tohoto problému povoláni vy. Konkrétně je zapotřebí pro daný výrobní plán, určující závislosti součástek při montáži, a pro dané doby nutné pro montáž součástek určit, kdy přesně se ta která součástka má začít montovat tak, aby celková doba potřebná pro sestavení jednoho vozu byla minimální (k sestavení vozu je zapotřebí smontovat všechny součástky uvedené ve výrobním plánu).

K dispozici máte na vstupu počet součástek, časy nutné pro montáž jednotlivých součástek a výrobní plán, který pro každou součástku určuje součástky, které je zapotřebí smontovat před její montáží. Nelze začít montovat konkrétní součástku předtím, než jsou smontovány všechny součástky, na kterých její výroba závisí. Nezáleží-li montáž součástky na montáži žádné jiné součástky, lze ji začít montovat okamžitě. Pokud je součástka smontována v čase <tt>x</tt>, lze jí okamžitě použít pro montáž jiné součástky také v čase <tt>x</tt>. Předpokládejte, že pro montování součástek je vyčleněno neomezené množství dělníků, tj. v jeden okamžik lze montovat libovolné množství součástek. Může nastat situace, kdy designéři při honbě za perfektním návrhem vozu sestaví nevalidní výrobní plán, který z nějakého důvodu nelze realizovat. Takový případ musíte detekovat. Také je možné, že existuje více řešení, které minimalizují dobu pro kompletaci vozu, ale liší se časy pro montáž součástek. V takovém případě vypište libovolné z těchto řešení.

Vzhledem k aféře dieselgate je v automobilkách zakázán veškerý software, který byl použit pro podvody při měření emisí. Toto opatření se týká i knihovny STL a nelze ji tak při řešení této úlohy použít.

**Formát vstupu:**

*   Na prvním řádku je číslo <tt>N</tt> udávající počet součástek nutných ke kompletaci jednoho vozu.
*   Součástky jsou číslovány od nuly, mají tedy čísla <tt>0, 1, ..., N - 1</tt>.
*   Na dalším řádku je <tt>N</tt> čísel <tt>t<sub>0</sub>, t<sub>1</sub>, ..., t<sub>n-1</sub></tt>, <tt>0 < t<sub>i</sub> < 10<sup>9</sup></tt>. <tt>i</tt>-té číslo <tt>t<sub>i</sub></tt> udává čas, který je potřeba pro montáž <tt>i</tt>-té součástky.
*   Poté následuje <tt>N</tt> řádků, postupně pro součástky <tt>0</tt> až <tt>N - 1</tt>. Na začátku řádku je číslo udávající počet součástek potřebných k montáži dané součástky (toto číslo může být i <tt>0</tt>), a následuje mezerami oddělený seznam čísel těchto součástek.
*   Žádná součástka není uvedena ve svém vlastním seznamu závislostí a žádná součástka není uvedena v seznamu závislostí vícekrát.
*   Výrobní plán se vždy skládá z alespoň jedné součástky, ale mezi součástkami nemusí existovat žádná závislost. Z toho vyplývá, že mohou existovat dvojice součástek, které na sobě vzájemně nezávisí (a to ani tranzitivně přes jiné součástky).
*   Můžete předpokládat, že vstup je korektní.

**Formát výstupu:**

*   Pokud nelze sestavit výrobní plán pro zadané závislosti součástek, program má vypsat na samostatný řádek řetězec "No solution." (bez uvozovek).
*   Pokud řešení existuje, výstup sestává ze dvou řádků. Na prvním řádku program vypíše minimální dobu potřebnou pro smontování všech součástek auta. Na druhém řádku následuje <tt>N</tt> mezerami oddělených čísel, kde <tt>i</tt>-té z nich udává čas, kdy se má začít montovat <tt>i</tt>-tá součástka.

**Bodové podmínky:**

1.  Pro splnění povinných testů (test základními a malými daty) je zapotřebí, aby program fungoval korektně pro výrobní plány o nejvýše 10 součástkách a 20 závislostech.
2.  Pro splnění testu středními daty musí program splnit časový a paměťový limit pro plány o nejvýše 100 součástkách a 1 000 závislostech.
3.  Pro splnění testu velkými daty musí program splnit časový a paměťový limit pro plány o nejvýše 100 000 součástkách a 1 000 000 závislostech.

**Ukázka práce programu:**  

* * *

**Příklad vstupu 1:**  

<pre>6             
3 5 7 2 2 4 
0           
0           
2 0 1       
2 2 1       
0           
1 4 
</pre>

**Příklad výstupu 1:**  

<pre>14
0 0 5 12 0 2
</pre>

* * *

**Příklad vstupu 2:**  

<pre>4
6 3 5 4
0
2 0 3
1 1
1 2
</pre>

**Příklad výstupu 2:**  

<pre>No solution.
</pre>

</td>

</tr>

</tbody>

</table>

</div>

</div>


**Referenční řešení**


*   **Hodnotitel: automat**
    *   Program zkompilován
    *   Test 'Základní test ukázkovými daty': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Max doba běhu: 0.007 s (limit: 1.500 s)
        *   Celková doba běhu: 0.012 s
        *   Využití paměti: 17636 KiB (limit: 32797 KiB)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test malými daty': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Max doba běhu: 0.006 s (limit: 1.500 s)
        *   Celková doba běhu: 0.261 s
        *   Využití paměti: 17636 KiB (limit: 32797 KiB)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test středními daty': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Max doba běhu: 0.006 s (limit: 1.500 s)
        *   Celková doba běhu: 0.277 s (limit: 15.000 s)
        *   Využití paměti: 17636 KiB (limit: 66977 KiB)
        *   Úspěch v bonusovém testu, hodnocení: 167.00 %
    *   Test 'Test velkými daty': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Max doba běhu: 0.260 s (limit: 2.000 s)
        *   Celková doba běhu: 3.646 s (limit: 20.000 s)
        *   Využití paměti: 28588 KiB (limit: 208626 KiB)
        *   Úspěch v bonusovém testu, hodnocení: 200.00 %
    *   Celkové hodnocení: 334.00 % (= 1.00 * 1.00 * 1.67 * 2.00)
*   Celkové procentní hodnocení: 334.00 %
*   Bonus za včasné odevzdání: 0.75
*   Celkem bodů: 3.34 * ( 3.00 + 0.75 ) = 12.53

**Moje řešení**

*   **Hodnotitel: automat**
    *   Program zkompilován
    *   Test 'Základní test ukázkovými daty': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Max doba běhu: 0.005 s (limit: 1.500 s)
        *   Celková doba běhu: 0.009 s
        *   Využití paměti: 12560 KiB (limit: 32797 KiB)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test malými daty': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Max doba běhu: 0.005 s (limit: 1.500 s)
        *   Celková doba běhu: 0.205 s
        *   Využití paměti: 12560 KiB (limit: 32797 KiB)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test středními daty': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Max doba běhu: 0.006 s (limit: 1.500 s)
        *   Celková doba běhu: 0.243 s (limit: 15.000 s)
        *   Využití paměti: 12560 KiB (limit: 66977 KiB)
        *   Úspěch v bonusovém testu, hodnocení: 167.00 %
    *   Test 'Test velkými daty': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Max doba běhu: 0.583 s (limit: 2.000 s)
        *   Celková doba běhu: 7.178 s (limit: 20.000 s)
        *   Využití paměti: 25320 KiB (limit: 208626 KiB)
        *   Úspěch v bonusovém testu, hodnocení: 200.00 %
    *   Celkové hodnocení: 334.00 % (= 1.00 * 1.00 * 1.67 * 2.00)
*   Celkové procentní hodnocení: 334.00 %
*   Bonus za včasné odevzdání: 0.75
*   Celkem bodů: 3.34 * ( 3.00 + 0.75 ) = 12.53

