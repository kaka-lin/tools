# First-In-First-Out (FIFO)

`FIFO` (also known as a `pipe`) is one of the methods for inter-process communication. 

In Linux, we can use [mkfifo()](http://man7.org/linux/man-pages/man3/mkfifo.3.html) to make a `FIFO` special file.


## build

```bash
$ make
```
## Run
Open two terminals.

- The first terminal

    ```bash
    $ ./writefifo
    ```

- The second terminal

    ```bash
    $ ./readfifo
    ```
