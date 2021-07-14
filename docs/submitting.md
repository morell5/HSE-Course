# Assignments submitting guide

## Getting started

1. Fork the repo
2. Clone forked repo

    ```
    git clone https://github.com/<your username>/HSE-Course.git
    ```
3.  Go to the directory

    ```
    cd  HSE-Course
    ``` 
4. Syncronize the fork with the course repo

    ```
     git remote add upstream https://github.com/morell5/HSE-Course.git
    ```
4. Print the current `remote`

    ```
    git remote -v
    ```
 
5. Block `push` to the course repository

    ```
    git remote set-url --push upstream no_push
    ```

6. Verify the terminal ouput

    ```
    origin  https://github.com/morell0809/HSE-Course.git (fetch)
    origin  https://github.com/morell0809/HSE-Course.git (push)
    upstream        https://github.com/morell5/HSE-Course.git (fetch)
    upstream        no_push (push)
    ```

## Working in the repo

1. Create a branch for the assignment from `master` branch

    ```
    git checkout -b <task name>
    ```
2. Go to problem's directory

    Example: `homework/BigInteger`
3. Read the problem statement `task.md`
4. Write down the solution in files
    * `<task name>.cpp` (implementation)
    * `<task name>.h` (interface)
5. Run tests

    ```
    cmake -G "Unix Makefiles" -B build -S.
    ```

    ```
    cmake --build build
    ```

6. Push files to remote repo

    ```
    git add <task name>.h <task name>.cpp
    git commit -m "your message"
    git push
    ```
7. **After completing the assignment make a** `PR` **into** `master`

## Fetching updates from course repo

1. Run the following command:

    ```
    git fetch upstream
    ```
2. Go to `master` branch on the local repo

    ```
    git checkout master
    ```
3. Fetching updates from the course's repo `master` branch

    ```
    git merge upstream/master master
    ```
4. Start to solve new assignment

## If you have changed master in the fork

1. Go to `master` branch

    ```
    git checkout master
    ```
2. Fetch updates from course's repo
    
    ```
    git fetch upstream
    ```
3. Go to update `master` branch
    
    ```
    git reset --hard upstream/master
    ```

4. Rewrite update in the `fork`

    ```
    git push -f
    ```