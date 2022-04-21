# ProducerConsumer

**COMPILATION**
```
make
```
`make` will execute `Makefile` and create an executatble `rideshare`

```
make clean
```
`make clean` will remove all object files from current directory

**EXECUTION**

```
./rideshare
```
run the executable file

**ARGUMENTS**

All arguments are optional, the program has default values

-n N 	Total number of requests of requests (production limit). Default is 120 if not
	specified.

-c N	Specifies the number of milliseconds N that the cost-saving dispatcher (consumer)

-f N	Similar argument for the fast-matching dispatcher.

-h N 	Specifies the number of milliseconds required to produce a ride request for
	a human driver.

-a N 	Specifies the number of milliseconds required to produce a ride request for
	an autonomous car.


**NOTES**

1 / 40 program runs results in random seqmentation fault at consumer::consume() line 58

buffer->consumed[thread_data->id][request_indx]++;


