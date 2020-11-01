# TypeList

## Задание

`TypeList` - структура данных для хранения типов.</br>
Реализовать операции над TypeList посредством специализаций.</br>

В файле `type_list.h` сделаны предобъявления.
В файле `type_list.h` реализуйте специализации.

Реализовать специализации:
* `Length` : структура для подсчета числа типов в списке

    Параметры:
    * `TList` : список типов

    Поля:
    * `length` : длина списка типов

    Предобъявление:

    ```c++
    template <typename TList> 
    struct Length;
    ```

* `TypeAt` : структура для получения типа по индексу

    Параметры:
    * `TList` : список типов
    * `index` : позиция типа в списке

    Поля:
    * `TargetType` : искомый тип

    Предобъявление:

    ```c++
    template<typename TList, unsigned int index>
    struct TypeAt;
    ```

* `IndexOf` : структура для получения индекса типа в списке (при отсутствии возвращает -1)

    Параметры:
    * `TList` : список типов
    * `TargetType` : искомый тип

    Поля:
    * `pos` : позиция типа в списке

    Предобъявление:

    ```c++
    template<typename TList, typename TargetType>
    struct IndexOf;
    ```

* `Append` : структура для добавления типа в список типов

    Параметры:
    * `TList` : список типов
    * `NewType` : добавляемый тип
       
    Поля:
    * `NewTypeList` : новый список типов
    
    Предобъявление:

    ```c++
    template<typename TList, typename NewType>
    struct Append;
    ```

* `Erase` : структура для удаления первого вхождения типа в список

    Параметры:
    * `TList` : список типов
    * `TargetType` : удаляемый тип
    
    Поля:
    * `NewTypeList` : новый список типов
    
    Предобъявление:

    ```c++
    template<typename TList, typename TargetType>
    struct Erase;
    ```
      
* `EraseAll` : структура для удаления всех вхождений типа в список

    Параметры:
    * `TList` : список типов
    * `TargetType` : удаляемый тип
    
    Поля:
    * `NewTypeList` : новый список типов
    
    Предобъявление:

    ```c++
    template<typename TList, typename TargetType>
    struct EraseAll;
    ```
      
* `NoDuplicates` : структура для удаления типов повторяющихся в списке

    Параметры:
    * `TList` : список типов

    Поля:
    * `NewTypeList` : новый список типов

    Предобъявление:

    ```c++
    template <typename TList>
    struct NoDuplicates;
    ```
       
* `Replace` : структура для замены типа `OldType` типом `NewType`
    
    Параметры:
    * `TList` : список типов
    * `OldType` : заменяемый тип
    * `NewType` : новый тип

    Поля:
    * `NewTypeList` : новый список типов

    Предобъявление:

    ```c++
    template <typename TList, typename OldType, typename NewType> 
    struct Replace;
    ```

## В помощь

[Modern C++ Design: Generic Programming and Design Patterns Applied](https://drive.google.com/drive/folders/1jeZCxdpFG0cA0PVwRW3kXThitbQnHUSn) 
* **Chapter 3: Typelists** 