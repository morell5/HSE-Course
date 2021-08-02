# Seminar

The [Builder](https://refactoring.guru/design-patterns/builder) pattern was studied.

**"Moscow trains"** problem statement:

You need to track on the map train locations. More concreate you track the head car.</br>
The train consist of 8 cars.</br>
You work in a local coordinate system and assume that the earth is a surface.</br>
Ostankino television tower is taken as the origin.

Each Builder overrides the following methods:
* create a seat
* create a window
* create a roof
* create a wheel

Cars hierarchy:
* head
* ordinary

Implementation notes:
* A train stores a list of cars and coordinates of the head car
* The Builder pattern performs a step by step construction of the car
* After the construction the car is added to the train
