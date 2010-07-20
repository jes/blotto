# Colonel Blotto

Colonel Blotto is a game in which a number of colonels are to arrange their
soldiers over a number of battlefields. Each colonel has equally many soldiers
and the number of battlefields is the same for each battle.

There is a git repository at [github](http://github.com/jes/blotto).

  1. The game
  2. Compiling
  3. Usage of blotto
  4. Usage of genteam
  5. Elastic tabstops
  6. Contact

## 1. The game

A rather excellent description of the game can be found on Jonathan Partington's
[site](http://www.amsta.leeds.ac.uk/~pmt6jrp/personal/blotto.html).

For the common configuration of the game, in which there are 10 battlefields and
100 soldiers, each colonel assigns a number of soldiers to each battlefield. For
example, consider a game between Alice and Bob, who assign their soldiers as
follows:  
  `Alice: 10 10 10 10 10 10 10 10 10 10`  
  `Bob:   12  8 12  8 12  8 12  8 12  8`  
We can see that Bob wins on the first battlefield by having 12 soldiers against
Alice's 10. On the second field, Alice wins by having 10 against Bob's 8. In
all, the two colonels draw the game because each wins on 5 battlefields.

## 2. Compiling

Compiling the programs is very simple, just run  
  `$ make`  
and the files `blotto` and `genteam` will be created. You can use these programs
where they are if you wish, or you can install them with  
  `$ make install`  

If you wish to install in to a different prefix, use, for example:  
  `$ make PREFIX=/usr/local install`  

You can also set DESTDIR, for example to install somewhere under /opt.

## 3. Usage of blotto

The `blotto` program runs a round-robin tournament between a number of colonels,
and outputs a nice table of results at the end. The program assigns 2 points for
a win and 1 for a draw.

Running the game described above between Alice and Bob could go as follows.  
  `$ blotto 10 100`  
to start the program with 10 battlefields and 100 soldiers per colonel. Next,
instructions to the operator will be printed because stdin is an interactive
terminal. The armies would be input, as  
  `alice 10 10 10 10 10 10 10 10 10 10`  
and  
  `bob 12 8 12 8 12 8 12 8 12 8`  
After the armies are input, the user must generate an EOF, which is usually
achieved by typing Ctrl-D.

`blotto` will run the tournament (which for two armies involves only one game),
and then print out a nicely-formatted table of results.

## 4. Usage of genteam

The `genteam` program generates a number of randomly-generated teams and outputs
in a format suitable for piping directly to the input of `blotto`.

To generate one random team for the usual 10/100 configuration, run  
  `$ genteam 10 100`  
and you will get something like  
  `team1 10 9 11 13 11 13 4 14 8 7`  

If you want a lot more teams, append the number of teams you want to the command
line arguments, for example  
  `$ genteam 10 100 5`  
would generate 5 random teams.

If you want to run a tournament between 5 teams, you can run  
  `$ genteam 10 100 5 | blotto 10 100`

## 5. Elastic tabstops

If you read some of the source code for these programs you may notice that the
indentation looks very strange in your editor. This is because I use
[elastic tabstops](http://nickgravgaard.com/elastictabstops/) to have blocks of
related code automatically align. There is a nice java applet demonstrating the
system in the page linked.

## 6. Contact

If you find a bug or just want to contact me for any reason, send an email to  
  James Stanley <james@incoherency.co.uk>  
or find me on IRC as the user `jamesstanley` on `irc.freenode.net`. I am
usually in the channel `#maximilian`, so you'll probably find me in there.
