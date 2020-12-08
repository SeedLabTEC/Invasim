# Invasim

Manycore architecture simulator using the paradigm Invasive computing

## Intructions

Open a terminal in the program folder and run the next commands:

1- Compile the program running the makefile:
  ```console
  user@Computer:~$ make

  ```

2- The binary is stored in **$PROGRAM_DIR/bin**, it takes three parameters 
    
    2.1- Processor cores (x and y).
    2.2- Amount of cycles to run.
    2.3- Using Artificial Intelligence for resource allocation: this is a boolean value (1 or 0)
  ```console
  user@Computer:~$ ./bin/invasive_simulator x_dimesion y_dimension cycles with_AI?

  ```

Note: In bin you must keep the structure of the analyzerResults.
