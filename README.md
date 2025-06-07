# Dekodery_for_Robert
Dekodery midi 


i inne potrzebne kody do uruchomienia organów 


https://github.com/rommil67/Dekodery_for_Robert/blob/main/Octaw_coppel_for_Robertzwarcie do masy (LOW) poszczególnych pinów włącza połaczenia 

D2 to I - P
D3 to II - P
D4 to II - I
D5 to super II to I
D6 to super I
D7 sub II-I 
D8 super II
D9 super PD10 sub I

Encoder registers and pistons

https://github.com/rommil67/Dekodery_for_Robert/blob/main/Encoder_registers_and_pistons_Robert
Enkoder po zwarciu danego pin to masy (LOW) generuje komunikat midiOn.Pierwsze 40 komunikatów midiOn/Off  (zaczynając od nr 36 ""C ""do nr 75 "es2" włącznie) dotyczy registrów, a następnie dotyczą pistonów i włączają poszczególne funkcje setzera
76 - e2 do 83 włącznie to przyciski od 1 to 8
84 t- kasownik (0) zero
85 - next (+)  >
86 - prev (-)  <
87 - Set
88 - cresc (włączenie)
89 - anulowanie cresc ( można go pominąć bo przyciski 0 - 8 tez powodują anulowanie, jednak po urzyciu tego przycisku setzer wraca na kombinację która była urzyta przed naciśnienciem cresc)
90 - programowanie cresc

Opis działania i obsługi:

Wolne kombinacje od 1 do 8 programuje się w następujący sposób:
ustawić registry
nacisnąć przycisk Set (S) – najczęściej pierwszy po lewej pod klawiaturą i przycisk kombinacji którą chcemy zapamiętać. 

Dwudziesto stopniowe crescendo jest programowane i programuje się je w taki sposób:
Ustawić enkoderem obrotowym Bank nr 1, ustawić registry dla stopnia pierwszego (najczęściej wszystkie wyłączone), i nacisnąć przycisk SET (S) i przycisk Programowanie Crescendo ( ).
Po zapisaniu stopnia pierwszego  Bank zmieni się nr 2, znów  ustawić registry, tym razem dla stopnia drugiego. i znów nacisnąć przycisk SET (S) i Programowanie Crescendo ( ). 
Postępować tak kolejno dla dwudziestu stopni, stopień dziewiętnasty i dwudziesty powinien mieć włączonych najwięcej registrów (prawie wszystkie).
Po zaprogramowaniu wszystkich dwudziestu stopni crescendo nacisnąć przycisk Crescendo (C), dla działania pedału crescenda, albo  Anuluj Crescendo (A) - które spowoduje, że ustawienie organów wróci do ostatnio używanej kombinacji.  

Przyciski next (>) i prev (<) służą do zmiany kombinacji na kolejną do przodu lub do tyłu. Next działa tak, że po 8 kombinacji następuje pierwsza kombinacja następnego banku. podobnie Prev ale w odwrotnym kierunku.
Naciśnięcie SET i jednego z powyżej opisanych przycisków (>) lub (<) zmienia Bank na kolejny, pozostawiając ten sam nr kombinacji.

Kręcenie pokrętłem obok wyświetlacza umożliwia szybką zmianę banku (od 1 do 256) na dalsze pozycje, lecz nowa kombinacja włączy się dopiero po naciśnięciu dodatkowo przycisku kombinacji 1 do 8.

Naciśnięcie przycisku SET i jednego z ośmiu  przycisków kombinacji powoduje zapisanie aktualnego ustawienia registrów do danej kombinacji w aktualnie wyświetlanym banku.Wolne kombinacje od 1 do 8 programuje się w następujący sposób:ustawić registrynacisnąć przycisk Set (S) – pierwszy po lewej pod klawiaturą i przycisk kombinacji którą chcemy zapamiętać. Dwudziesto stopniowe crescendo jest programowane i programuje się je w taki sposób:Ustawić enkoderem obrotowym Bank nr 1, ustawić registry dla stopnia pierwszego (najczęściej wszystkie wyłączone), i nacisnąć przycisk SET (S) i przycisk Programowanie Crescendo ( ).Po zapisaniu stopnia pierwszego Bank zmieni się nr 2, znów ustawić registry, tym razem dla stopnia drugiego. i znów nacisnąć przycisk SET (S) i Programowanie Crescendo ( ). Postępować tak kolejno dla dwudziestu stopni, stopień dziewiętnasty i dwudziesty powinien mieć włączonych najwięcej registrów (prawie wszystkie).Po zaprogramowaniu wszystkich dwudziestu stopni crescendo nacisnąć przycisk Crescendo (C), dla działania pedału crescenda, albo Anuluj Crescendo (A) - które spowoduje, że ustawienie organów wróci do ostatnio używanej kombinacji. Przyciski next (>) i prev (<) służą do zmiany kombinacji na kolejną do przodu lub do tyłu. Next działa tak, że po 8 kombinacji następuje pierwsza kombinacja następnego banku. podobnie Prev ale w odwrotnym kierunku.Naciśnięcie SET i jednego z powyżej opisanych przycisków (>) lub (<) zmienia Bank na kolejny, pozostawiając ten sam nr kombinacji.Kręcenie pokrętłem obok wyświetlacza umożliwia szybką zmianę banku (od 1 do 256) na dalsze pozycje, lecz nowa kombinacja włączy się dopiero po naciśnięciu dodatkowo przycisku kombinacji 1 do 8.Naciśnięcie przycisku SET i jednego z ośmiu przycisków kombinacji powoduje zapisanie aktualnego ustawienia registrów do danej kombinacji w aktualnie wyświetlanym banku.

Wolne kombinacje od 1 do 8 programuje się w następujący sposób:ustawić registrynacisnąć przycisk Set (S) – pierwszy po lewej pod klawiaturą i przycisk kombinacji którą chcemy zapamiętać. Dwudziesto stopniowe crescendo jest programowane i programuje się je w taki sposób:Ustawić enkoderem obrotowym Bank nr 1, ustawić registry dla stopnia pierwszego (najczęściej wszystkie wyłączone), i nacisnąć przycisk SET (S) i przycisk Programowanie Crescendo ( ).Po zapisaniu stopnia pierwszego Bank zmieni się nr 2, znów ustawić registry, tym razem dla stopnia drugiego. i znów nacisnąć przycisk SET (S) i Programowanie Crescendo ( ). Postępować tak kolejno dla dwudziestu stopni, stopień dziewiętnasty i dwudziesty powinien mieć włączonych najwięcej registrów (prawie wszystkie).Po zaprogramowaniu wszystkich dwudziestu stopni crescendo nacisnąć przycisk Crescendo (C), dla działania pedału crescenda, albo Anuluj Crescendo (A) - które spowoduje, że ustawienie organów wróci do ostatnio używanej kombinacji. Przyciski next (>) i prev (<) służą do zmiany kombinacji na kolejną do przodu lub do tyłu. Next działa tak, że po 8 kombinacji następuje pierwsza kombinacja następnego banku. podobnie Prev ale w odwrotnym kierunku.Naciśnięcie SET i jednego z powyżej opisanych przycisków (>) lub (<) zmienia Bank na kolejny, pozostawiając ten sam nr kombinacji.Kręcenie pokrętłem obok wyświetlacza umożliwia szybką zmianę banku (od 1 do 256) na dalsze pozycje, lecz nowa kombinacja włączy się dopiero po naciśnięciu dodatkowo przycisku kombinacji 1 do 8.Naciśnięcie przycisku SET i jednego z ośmiu przycisków kombinacji powoduje zapisanie aktualnego ustawienia registrów do danej kombinacji w aktualnie wyświetlanym banku.
