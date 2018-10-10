# Algoritmisk musik och digital syntes
## Projektdokumentation - Utkast
Vi planerar att genomföra ett avancerat projekt
## Mål
Målet med detta projekt är att utveckla en digital synt på en inbäddad plattform som med hjälp av ett antal algoritmer ska klara av att spela ett stycke musik med eller utan yttre påverkan.
Minimikraven för detta projekt är som följer:
* Synten ska vara kapabel till att spela både harmonier och melodier.
* Melodierna och harmonierna ska genereras algoritmiskt och melodierna ska passa till harmonierna.
* Möjligheten att interagera med genereringen av melodier och harmonier i form av justering av modus, tonmaterial, tempo eller effekter via knapparna och switcharna på IO-skölden ska finnas.
## Planerad lösning
Projektet ska utföras med enkortsdatorn ChipKIT Uno32 och den tillhörande Basic I/O-skölden och koden ska skrivas i C. För att generera melodier och harmonier planerar vi att använda tekniker för algoritmisk komposition, framförallt markovkedjor och olika typer av viktade slumpförhållanden. För att generera tänker vi använda ChipKITets inbyggda D/A-konverterare och en extern högtalare med inbyggd förstärkare och aux-ingång.
## Planerad verifikation
Verifiering av det musikaliska resultatet är svårt att genomföra då bedömningen är baserad på subjektivitet men för att verifiera att programmet genererar det förväntade resultatet planerar vi att genomföra enhetstester på stora delar av koden.
