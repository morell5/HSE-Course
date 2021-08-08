# TypeList

## Task

`TypeList` - the data structure for storing types</br>
Implement operation under TypeList using specializations</br>

There are predefinitions in the `type_list.h`
Implement specializations in the `type_list.h`

You should implement following implementations:
* `Length` : a structure for counting number of types in the list

    Parameters:
    * `TList` : the list of types

    Fields:
    * `length` : the length of the list

    Predefinitions:

    ```c++
    template <typename TList> 
    struct Length;
    ```

* `TypeAt` : the structure to get the type from list by index

    Parameters:
    * `TList` : type list
    * `index` : the type position in the list

    Fields:
    * `TargetType` : the type that you are looking

    Predefinitions:

    ```c++
    template<typename TList, unsigned int index>
    struct TypeAt;
    ```

* `IndexOf` : the structure to get type of the index in the list (if there is no type than it returns -1)

    Parameters:
    * `TList` : type list
    * `TargetType` : the type that you are looking

    Fields:
    * `pos` : the type position in the list

    Predefinitions:

    ```c++
    template<typename TList, typename TargetType>
    struct IndexOf;
    ```

* `Append` : the structure to add types to the list of types

    Parameters:
    * `TList` : the type list
    * `NewType` : the type to add
       
    Fields:
    * `NewTypeList` : new list of types
    
    Predefinitions:

    ```c++
    template<typename TList, typename NewType>
    struct Append;
    ```

* `Erase` : the structure to remove first type entry to the list

    Parameters:
    * `TList` : the type list
    * `TargetType` : the type that you are erasing
    
    Fields:
    * `NewTypeList` : the new type list
    
    Predefinitions:

    ```c++
    template<typename TList, typename TargetType>
    struct Erase;
    ```
      
* `EraseAll` : the structure to remove all type entries to the list

    Parameters:
    * `TList` : the type list
    * `TargetType` : the removal type
    
    Fields:
    * `NewTypeList` : the new type list
    
    Predefinitions:

    ```c++
    template<typename TList, typename TargetType>
    struct EraseAll;
    ```
      
* `NoDuplicates` : the structure to remove duplicates in the list

    Parameters:
    * `TList` : the type list

    Fields:
    * `NewTypeList` : the new type list

    Predefinitions:

    ```c++
    template <typename TList>
    struct NoDuplicates;
    ```
       
* `Replace` : the structure to replace `OldType` with the type `NewType`
    
    Parameters:
    * `TList` : the type list
    * `OldType` : the replacable type
    * `NewType` : new type in the list

    Fields:
    * `NewTypeList` : the new type list

    Predefinitions:

    ```c++
    template <typename TList, typename OldType, typename NewType> 
    struct Replace;
    ```

## Recommended to read

[Modern C++ Design: Generic Programming and Design Patterns Applied](https://drive.google.com/drive/folders/1jeZCxdpFG0cA0PVwRW3kXThitbQnHUSn) 
* **Chapter 3: Typelists** 