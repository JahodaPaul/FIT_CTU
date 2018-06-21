Ve velmi vzdálené zemi již několik týdnů panuje vzrušená atmosféra. Blíží se totiž volby a celý národ tak s napětím očekává, že opět po několika letech může přijít změna k lepšímu. Na nohou však nejsou pouze občané, ale také politici, kteří v nejbližších dnech v předvolebních debatách svedou tvrdé souboje o politické body. Zejména těžkou pozici mají členové vlády, kteří by velmi rádi obhájili svůj mandát. U těch se totiž volební přízeň odvíjí zejména od úspěchů či neúspěchů v předešlém funkčním období.

Asi nejtěžší situaci má stávající ministr financí. Není totiž žádným tajemstvím, že jeho působení ve vládě by se dalo shrnout v nejlepším jako tristní. Konkrétně za jeho působení takřka všem klesly příjmy, což spoustu lidí posunulo pod hranici životního minima. S takovými výsledky by v předvolebních debatách ministr jistě neokouzlil, a tak se svými poradci vymyslel záchranný plán. Kdyby přeci mohl v debatách ukazovat nějakou hodnotu, která není vylhaná, vychází z reálných příjmů, nevypadá na první pohled tak zle, ale u které zároveň lidé nerozumí způsobu jejího výpočtu, to by byla výhra! Jako první padla volba na aritmetický průměr, ale průzkum ukázal, že lidé této hodnotě rozumí. Z toho důvodu byl zvolen medián, který se v obecném povědomí vyskytuje výrazně méně. Konkrétně by tak ministr pro úspěch v debatách potřeboval následující - kdykoliv se moderátor či politický oponent zeptají na příjmy v daném finančním rozpětí, ministr odpoví mediánem příjmů všech lidí, kteří v daném rozpětí mají příjem. Situace je však ztížená tím, že příjmy lidí se neustále mění. To znamená, že ze seznamu příjmů všech lidí mohou být některé příjmy odstraněny, a naopak některé příjmy mohou do seznamu přibýt (změna příjmu se dá představit jako kombinace odstranění staré a přibytí nové hodnoty). Je tedy nutné, aby ministr měl rychle k dispozici mediány pro daná rozpětí příjmů v rámci dynamicky se měnícího seznamu příjmů.

Jelikož se jedná o velmi riskantní předvolební pokus, musel být pro efektivní a správné řešení úlohy vybrán ostřílený programátor, který se nebojí zhostit se úkolu takovéto podstaty. Volba padla na vás. Pro zadanou posloupnost přibývání/odstraňování příjmů a rozsahů pro hledání mediánu, musíte vytvořit program, který splní požadavky uvedené výše. Vzhledem k absolutnímu utajení nelze při řešení této úlohy používat takřka žádný cizí kód. Toto opatření se týká i knihovny STL, kterou tak použít nemůžete.

**Formát vstupu a výstupu:**

*   Vstup sestává z určitého počtu řádek na vstupu, kde každá kóduje jeden příkaz, viz níže uvedené příkazy v uvozovkách:

<dl>

<dt><tt>"1 X"</tt></dt>

<dd>kde <tt>X</tt> je přirozené číslo, <tt>1 ≤ X ≤ 10<sup>9</sup></tt>, znamená přidej do seznamu příjmů příjem o hodnotě <tt>X</tt>.</dd>

<dt><tt>"2 X"</tt></dt>

<dd>kde <tt>X</tt> je přirozené číslo, <tt>1 ≤ X ≤ 10<sup>9</sup></tt>, znamená odeber ze seznamu příjmů příjem o hodnotě <tt>X</tt>.</dd>

<dt><tt>"3 X Y"</tt></dt>

<dd>kde <tt>X, Y</tt> jsou přirozená čísla, <tt>1 ≤ X, Y ≤ 10<sup>9</sup></tt>, <tt>X ≤ Y</tt>, znamená nalezni medián (viz definice níže) čísel v rozsahu od <tt>X</tt> do <tt>Y</tt> (včetně) ze stávajícího seznamu příjmů a vypiš jej na samostatný řádek.</dd>

<dt><tt>"4"</tt></dt>

<dd>znamená, že již začaly volby a že žádný další příkaz již následovat nebude; tento příkaz je zaručeně jako poslední na vstupu.</dd>

</dl>

*   Můžete se spolehnout, že vstup je zadán korektně.

*   Medián čísel v rozsahu od <tt>X</tt> do <tt>Y</tt> ze stávajícího seznamu příjmu definujeme takto: je-li ve stávajícím seznamu příjmů <tt>k</tt> příjmů s hodnotou v rozsahu mezi <tt>X</tt> a <tt>Y</tt> (včetně), je medián <tt>⌈<sup>k</sup>⁄<sub>2</sub>⌉</tt>-tý nejmenší z těchto příjmů.
*   Nenachází-li se pro daný rozsah v seznamu příjmů žádný příjem, vypište na výstup řádek s řetězcem <tt>"notfound"</tt> (bez uvozovek).
*   Může se stát, že vzhledem k úřednické chybě dostane váš program požadavek na smazání takového příjmu, který se v seznamu příjmů nevyskytuje. V takovém případě požadavek ignorujte.
*   Naopak se nikdy nestane, že by se v seznamu najednou vyskytovalo (po příslušných požadavcích na přidání) více příjmů o stejné hodnotě. Pokud však bude příjem o určité hodnotě ze seznamu v nějaký moment odebrán, může být později do seznamu znovu přidán.

**Bodové podmínky:**

1.  Pro splnění povinných testů je zapotřebí, aby program fungoval korektně pro vstupy o nejvýše 1 000 příkazech. Příkazy budou pouze typu 1, 3 a 4.
2.  Pro splnění testu velkými daty #1 musí program splnit časový limit pro vstupy o nejvýše 1 000 000 příkazech. Příkazy budou pouze typu 1, 3 a 4.
3.  Pro splnění testu velkými daty #2 musí program splnit časový limit pro vstupy o nejvýše 1 000 000 příkazech. Příkazy mohou být všech typů.

*   Testy podle ukázky jsou z důvodu omezení typů příkazů na vstupu provedeny ve dvou různých testech. První z nich testuje ukázkové vstupy 1 a 2 a je povinný. Druhý testuje ukázkový vstup 3 a je nepovinný.

**Ukázka práce programu:**  

* * *

**Příklad vstupu 1:**  

<pre>1 13
1 4
1 17
1 6
1 9
1 14
3 4 9
3 3 10
3 14 14
3 1 20
4
</pre>

**Příklad výstupu 1:**  

<pre>6
6
14
9
</pre>

* * *

**Příklad vstupu 2:**  

<pre>1 2
1 3
1 1
3 15 20
3 2 2
3 4 4
4
</pre>

**Příklad výstupu 2:**  

<pre>notfound
2
notfound
</pre>

* * *

**Příklad vstupu 3:**  

<pre>1 4
1 8
1 6
1 12
1 7
2 10
3 10 13
3 8 15
3 1 100
3 2 7
2 6
3 2 7
2 4
3 2 7
2 7
3 2 7
4
</pre>

**Příklad výstupu 3:**  

<pre>12
8
7
6
4
7
notfound
</pre>

</td>

</tr>

</tbody>

</table>

</div>

</div>

<div class="topLayout">

<div class="outBox">

<table id="reftable" width="100%" cellspacing="0" cellpadding="2" border="0">

<tbody>

<tr>

**Referenční řešení**

*   **Hodnotitel: automat**
    *   Program zkompilován
    *   Test 'Základní test ukázkovými daty (vstupy 1, 2)': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Max doba běhu: 0.005 s (limit: 2.000 s)
        *   Celková doba běhu: 0.010 s
        *   Využití paměti: 12564 KiB (limit: 23079 KiB)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test malými daty': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Max doba běhu: 0.006 s (limit: 5.000 s)
        *   Celková doba běhu: 0.192 s
        *   Využití paměti: 12564 KiB (limit: 23079 KiB)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test velkými daty #1 (bez operace 2)': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Max doba běhu: 1.572 s (limit: 7.500 s)
        *   Celková doba běhu: 9.310 s (limit: 30.000 s)
        *   Využití paměti: 74996 KiB (limit: 403938 KiB)
        *   Úspěch v bonusovém testu, hodnocení: 300.00 %
    *   Test 'Základní test ukázkovými daty (vstup 3)': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Max doba běhu: 0.004 s (limit: 2.000 s)
        *   Celková doba běhu: 0.004 s
        *   Využití paměti: 12564 KiB (limit: 23079 KiB)
        *   Úspěch v nepovinném testu, hodnocení: 100.00 %
    *   Test 'Test velkými daty #2 (všechny operace)': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Max doba běhu: 1.105 s (limit: 7.500 s)
        *   Celková doba běhu: 4.596 s (limit: 30.000 s)
        *   Využití paměti: 43716 KiB (limit: 403938 KiB)
        *   Úspěch v bonusovém testu, hodnocení: 167.00 %
    *   Celkové hodnocení: 501.00 % (= 1.00 * 1.00 * 3.00 * 1.00 * 1.67)
*   Celkové procentní hodnocení: 501.00 %
*   Bonus za včasné odevzdání: 0.50
*   Celkem bodů: 5.01 * ( 2.00 + 0.50 ) = 12.53

**Moje řešení**

*   **Hodnotitel: automat**
    *   Program zkompilován
    *   Test 'Základní test ukázkovými daty (vstupy 1, 2)': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Max doba běhu: 0.004 s (limit: 2.000 s)
        *   Celková doba běhu: 0.009 s
        *   Využití paměti: 12568 KiB (limit: 23079 KiB)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test malými daty': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Max doba běhu: 0.006 s (limit: 5.000 s)
        *   Celková doba běhu: 0.181 s
        *   Využití paměti: 12700 KiB (limit: 23079 KiB)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test velkými daty #1 (bez operace 2)': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Max doba běhu: 1.409 s (limit: 7.500 s)
        *   Celková doba běhu: 6.833 s (limit: 30.000 s)
        *   Využití paměti: 59428 KiB (limit: 403938 KiB)
        *   Úspěch v bonusovém testu, hodnocení: 300.00 %
    *   Test 'Základní test ukázkovými daty (vstup 3)': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Max doba běhu: 0.005 s (limit: 2.000 s)
        *   Celková doba běhu: 0.005 s
        *   Využití paměti: 12568 KiB (limit: 23079 KiB)
        *   Úspěch v nepovinném testu, hodnocení: 100.00 %
    *   Test 'Test velkými daty #2 (všechny operace)': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Max doba běhu: 0.853 s (limit: 7.500 s)
        *   Celková doba běhu: 4.219 s (limit: 30.000 s)
        *   Využití paměti: 36060 KiB (limit: 403938 KiB)
        *   Úspěch v bonusovém testu, hodnocení: 167.00 %
    *   Celkové hodnocení: 501.00 % (= 1.00 * 1.00 * 3.00 * 1.00 * 1.67)
*   Celkové procentní hodnocení: 501.00 %
*   Bonus za včasné odevzdání: 0.50
*   Celkem bodů: 5.01 * ( 2.00 + 0.50 ) = 12.53


