# Seminar

Разобран паттерн [Composite](https://refactoring.guru/design-patterns/builder)

Код не сохранился

Формулировка задачи:

Иерархия:  Managing Director <- Senior VP <- VP <- Banking Associate <- Banking Analyst

Классы облажают методами:
* Banking Analyst:
* MakePresentation
* GetCompanyIndicator

Banking Associate:
* GatherCompaniesIndicators
* PutCompanyIndicator

VP:
* PreparePitchBook

Senior VP:
* PrepareMeeting

ManagingDir:
* DrinkCoffee
* Deadline: пробрасывает сообщение подчиненным -> вызывает DrinkCoffee