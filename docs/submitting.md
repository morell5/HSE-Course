# Сдача заданий

## Начало работы

1. Сделать `fork` репозитория
2. Склонировать `fork` репозитория

    ```
    git clone https://github.com/<your username>/HSE-Course.git
    ```
3.  Перейти в директорию

    ```
    cd  HSE-Course
    ``` 
4. Синхронизировать `fork` с репозиторием курса

    ```
     git remote add upstream https://github.com/morell5/HSE-Course.git
    ```
4. Вывести `remote`

    ```
    git remote -v
    ```
 
5. Запретить `push` в репозиторий курса

    ```
    git remote set-url --push upstream no_push
    ```

6. Сверить вывод в терминале

    ```
    origin  https://github.com/morell0809/HSE-Course.git (fetch)
    origin  https://github.com/morell0809/HSE-Course.git (push)
    upstream        https://github.com/morell5/HSE-Course.git (fetch)
    upstream        no_push (push)
    ```

## Работа в репозитории
1. Из `master` ветки создать ветку под задачу

    ```
    git checkout -b <название задачи>
    ```
2. Перейти в директорию с задачей

    Пример: `homework/BigInteger`
3. Прочитать условие задачи `task.md`
4. Написать решение задачи в файлах
    * `<имя задачи>.cpp` (реализация)
    * `<имя задачи>.h` (интерфейс)
5. Протестировать решение

    ```
    cmake -G "Unix Makefiles" -B build -S.
    ```

    ```
    cmake --build build
    ```

6. Добавить файлы на удаленный репозиторий

    ```
    git add <имя задачи>.h <имя задачи>.cpp
    git commit -m "ваше сообщение"
    git push
    ```
7. После выполнения задания сделать `PR` в `master`

`Замечание:` ветка с задачей не будет вливаться в `master` ветку

## Подкачивание изменений из основного репозитория

1. В любой папке директории выполнить:

    ```
    git fetch upstream
    ```
2. Перейти в `master` ветку на локали

    ```
    git checkout master
    ```
3. Подкачать измения из `master` ветки репозитория курса

    ```
    git merge upstream/master master
    ```
4. Приступить к решению новой задачи

## Если Вы изменили master в fork

1. Перейти в `master`

    ```
    git checkout master
    ```
2. Подкачать обновления с репозитория курса
    
    ```
    git fetch upstream
    ```
3. Перейти к актуальному `master`
    
    ```
    git reset --hard upstream/master
    ```

4. Переписать изменения в `fork`

    ```
    git push -f
    ```