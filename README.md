# RG12-oblici-i-kalupi
Oblici i kalupi

Projekat je igrica u kojoj se oblici ubacuju u odgovarajuce kalupe.

Kako se igra ova igra:
Igrac pritiskom tastera 'g' zapocinje igru i dobija prvi oblik koji treba da smesti u odgovarajuci kalup. Oblik pomera i rotira pomocu tastera 'j', 'k', 'l', 'i', 'y', 'h', 'u' i 'o' (u legendi se moze videti koji taster sta tacno radi). Kada oblik ubaci u kalup, dobija novi oblik i sve tako do isteka vremena. Kada oblik ubaci u kalup osvaja poene. Igrac moze da resetuje igru (tokom igre ili nakon zavrsetka) pritiskom tastera 'r', a zatim opet da je zapocne pritiskom tastera 'g'. Cilj je sakupiti sto vise poena za ograniceno vreme. Kamera moze da se rotira kako bi olaksala igru.

Legenda:
g - igra se pokrece
r - igra se prekida
e - kamera se pomera ulevo
q - kamera se pomera udesno
s - kamera se pomera ka dole
w - kamera se pomera ka gore
u - objekat se rotira ulevo
o - objekat se rotira udesno
i - objekat se translira po x osi unapred
k - objekat se translira po x osi unazad 
j - objekat se translira po y osi unapred
l - objekat se translira po y osi unazad
y - objekat se translira po z osi ka gore
h - objekat se translira po z osi ka dole

Pokretanje programa:
 gcc final.c -lGL -lGLU -lglut -lm
Takodje je koriscena funkcija "glWindowPos2i".
