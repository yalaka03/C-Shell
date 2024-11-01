## C-Shell
Simulates what a shell does
./a.out to run it(bash and gcc)


## The following is a guide to what files implement what part:

- The name usually implies the command that the file implements.
- Non_user files implement the background and foreground processes.
- Repeat is implemented in main itself. 


## Limits

- Only a maximum of 10 background processes are stored and hence supported, any more will work but no information about pid might be given.
- For any command only 10 space seperated arguments are supported including the command name.
- Paths are assumed to be atmost 100 characters.
- All names(files,directories) are assumed to be less than 30 characters.
- Export documents as Markdown, HTML and PDF

## Assumptions
- Spaces are expected in input output redirection and I/O.
- For cat if more than one file is input with input redirection all the files are displayed.
- In ls -l 6 months is same day 6 months ago.
- In job queue, after a job is completed all the other job IDs reduce their numbers to fit the sequence.

Virtual Memory size is in bytes.
Commands fg and bg require a job number or else do not work

Only one input output redirection works.
Commands work in Output redirection only if it is the last segment of command.
```sh
ls | sort > a.txt (works)
ls > a.txt | sort (does not work)
ls > a.txt > b.txt (prints ls in a.txt but not b.txt)
```
# Pipes
Any number of pipes are allowed.
eg:
```sh
cat a.txt | sort | wc | wc
```

# Signals
- All signals have the expected behaviour.




