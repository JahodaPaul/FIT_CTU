Ačkoliv advent začal již před nějakou dobou, v jedné z evropských metropolí přípravu na vánoční šílenství velmi výrazně podcenili. Na pouličním osvětlení k tomuto okamžiku nevisí jediná ozdoba, náměstí zejí prázdnotou a jehličnany po městě jen smutně vzpomínají na loňské Vánoce. To se pochopitelně nezamlouvá široké veřejnosti, neboť jejich oblíbené předvánoční trhy se letos zkrátka nekonají. Místní obyvatelé se tak rozhodli, že záležitost vezmou do svých rukou a že se pokusí alespoň částečně ve městě navodit vánoční atmosféru.

Pro to, aby stav města alespoň trochu odpovídal období adventu, však bude zapotřebí podstoupit dva zásadní kroky: jednak vyzdobit vánoční tématikou dostatečné množství ulic a jednak zahájit adventní trhy na některých náměstích k nim přiléhajícím. A to s vědomím toho, že vše má již mnohadenní zpoždění a že bude zapotřebí náklady uhradit ze společné sbírky. Oba kroky tedy bude zapotřebí zrealizovat úsporně jak na časové, tak finanční frontě. Konkrétně to znamená, že pro první krok zdobení bude zapotřebí vybrat pouze takovou podmnožinu ulic, kde (pro ušetření na ozdobách) bude součet jejich délek co nejmenší, za zachování podmínky, že z každého náměstí se bude dát dostat na libovolné jiné pouze po vyzdobených ulicích. Nikdo totiž nechce o adventu chodit po zachmuřených neozdobených ulicích! Poté, co bude nalezena ideální podmnožina ulic pro výzdobu, přijde na řadu krok druhý. A to výběr náměstí, na kterých bude výhodné spustit adventní trhy. Přirozeně by pro minimalizaci nákladů bylo příhodné, aby se trhy konaly na co nejmenším počtu náměstí. Aby ale nikdo nemusel chodit na trh daleko, je zapotřebí aby každá ozdobená ulice sousedila s nějakým náměstím, na kterém bude probíhat trh..

Jelikož je netriviální již samotné přečtení požadavků výše, vyžádali si občané pro tento úkol vaší pomoc. K dispozici máte na vstupu plán města, který sestává z nákresu náměstí propojených mezi sebou ulicemi, a popisem, která ulice je jak dlouhá. Ulice jsou obousměrné a mají kladnou délku. Žádné dvě ulice nejsou stejně dlouhé. Neexistuje ulice, která by končila na stejném náměstí jako začíná. Mezi dvěma náměstími vždy existuje nejvýše jedna ulice. Z každého náměstí se ulicemi dá dostat do libovolného jiného.

Maličtí trpaslíci ve vašem počítači, kteří obvykle fyzicky interpretují operace knihovny STL, musí na Vánoce pomáhat s balením dárků. Knihovnu STL tudíž ve vašich řešeních použít nemůžete.

**Formát vstupu:**

*   Na prvním řádku jsou dvě čísla <tt>N</tt> a <tt>M</tt>, postupně udávající počet náměstí a počet ulic v plánu.
*   Náměstí i ulice jsou číslovány od nuly, mají tedy čísla <tt>0, 1, ..., N - 1</tt> a <tt>0, 1, ..., M - 1</tt>.
*   Následuje <tt>M</tt> řádků, postupně pro všechny ulice. Na <tt>i</tt>-tém z nich jsou tři mezerami oddělená čísla <tt>x<sub>i</sub></tt>, <tt>y<sub>i</sub></tt> a <tt>k<sub>i</sub></tt>, <tt>0 ≤ x<sub>i</sub>, y<sub>i</sub> < N</tt>, <tt>x<sub>i</sub> ≠ y<sub>i</sub></tt>; <tt>0 < k<sub>i</sub> ≤ 10<sup>9</sup></tt>. Tato čísla uvádějí, že ulice <tt>i</tt> vede mezi náměstími <tt>x<sub>i</sub></tt> a <tt>y<sub>i</sub></tt> a má délku <tt>k<sub>i</sub></tt>.
*   Ve městě jsou vždy alespoň dvě náměstí a tedy vždy alespoň jedna ulice.
*   Můžete předpokládat, že vstup je korektní.

**Formát výstupu:**

*   Výstup sestává ze tří řádků. Na prvním řádku program vypíše mezerou oddělený minimální součet délek ulic pro výzdobu a minimální možný počet náměstí, kde se mají otevřít adventní trhy. Na druhém řádku vypište v libovolném pořadí mezerami oddělený seznam čísel ulic, které se mají ozdobit. Na třetím řádku vypište v libovolném pořadí mezerami oddělený seznam náměstí, na kterých se mají spustit adventní trhy.
*   Existuje-li více řešení, vypište libovolné z nich.

**Bodové podmínky:**

1.  Pro splnění povinných testů (test základními a malými daty) je zapotřebí, aby program fungoval korektně pro plány města o nejvýše 10 náměstích a 20 ulicích.
2.  Pro splnění testu středními daty musí program splnit časový a paměťový limit pro plány o nejvýše 100 náměstích a 1 000 ulicích.
3.  Pro splnění testu velkými daty musí program splnit časový a paměťový limit pro plány o nejvýše 100 000 náměstích a 1 000 000 ulicích.

**Ukázka práce programu:**  

* * *

**Příklad vstupu 1:**  

<pre>4 5
1 0 3
3 1 7
0 3 2
0 2 4
2 3 1
</pre>

**Příklad výstupu 1:**  

<pre>6 2
0 2 4
0 3
</pre>

* * *

**Příklad vstupu 2:**  

<pre>7 10
0 4 4
0 3 1
0 2 6
1 3 7
1 2 9
2 3 5
2 5 8
3 4 2
4 5 3
4 6 10
</pre>

**Příklad výstupu 2:**  

<pre>28 2
1 7 8 5 3 9
3 4
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
        *   Max doba běhu: 0.005 s (limit: 1.500 s)
        *   Celková doba běhu: 0.010 s
        *   Využití paměti: 12564 KiB (limit: 32797 KiB)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test malými daty': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Max doba běhu: 0.005 s (limit: 1.500 s)
        *   Celková doba běhu: 0.103 s
        *   Využití paměti: 12564 KiB (limit: 32797 KiB)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test středními daty': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Max doba běhu: 0.006 s (limit: 1.500 s)
        *   Celková doba běhu: 0.115 s
        *   Využití paměti: 12564 KiB (limit: 66977 KiB)
        *   Úspěch v bonusovém testu, hodnocení: 300.00 %
    *   Test 'Test velkými daty': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Max doba běhu: 1.086 s (limit: 5.000 s)
        *   Celková doba běhu: 6.299 s (limit: 30.000 s)
        *   Využití paměti: 58272 KiB (limit: 223227 KiB)
        *   Úspěch v bonusovém testu, hodnocení: 167.00 %
    *   Celkové hodnocení: 501.00 % (= 1.00 * 1.00 * 3.00 * 1.67)
*   Celkové procentní hodnocení: 501.00 %
*   Bonus za včasné odevzdání: 0.50
*   Celkem bodů: 5.01 * ( 2.00 + 0.50 ) = 12.53

**Moje řešení**

*   **Hodnotitel: automat**
    *   Program zkompilován
    *   Test 'Základní test ukázkovými daty': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Max doba běhu: 0.006 s (limit: 1.500 s)
        *   Celková doba běhu: 0.012 s
        *   Využití paměti: 17640 KiB (limit: 32797 KiB)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test malými daty': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Max doba běhu: 0.007 s (limit: 1.500 s)
        *   Celková doba běhu: 0.143 s
        *   Využití paměti: 17640 KiB (limit: 32797 KiB)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test středními daty': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Max doba běhu: 0.009 s (limit: 1.500 s)
        *   Celková doba běhu: 0.166 s
        *   Využití paměti: 17772 KiB (limit: 66977 KiB)
        *   Úspěch v bonusovém testu, hodnocení: 300.00 %
    *   Test 'Test velkými daty': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Max doba běhu: 1.222 s (limit: 5.000 s)
        *   Celková doba běhu: 6.617 s (limit: 30.000 s)
        *   Využití paměti: 129120 KiB (limit: 223227 KiB)
        *   Úspěch v bonusovém testu, hodnocení: 167.00 %
    *   Celkové hodnocení: 501.00 % (= 1.00 * 1.00 * 3.00 * 1.67)
*   Celkové procentní hodnocení: 501.00 %
*   Bonus za včasné odevzdání: 0.50
*   Celkem bodů: 5.01 * ( 2.00 + 0.50 ) = 12.53

