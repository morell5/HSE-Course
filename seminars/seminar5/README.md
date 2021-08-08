# Seminar

The pattern [Composite](https://refactoring.guru/design-patterns/composite) was studied

"Investment company" problem statement:

You need to implement the following hierarchy:  Managing Director <- Senior VP <- VP <- Banking Associate <- Banking Analyst

Classes have methods:

Banking Analyst:
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