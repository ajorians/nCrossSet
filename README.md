# nCrossSet
A port of Cross Set for the TI-NSpire Graphing Calculator

About:
This is a game for the TI-nSpire!  This is a clone of the game Cross Set.  It works on the TI-NSpire (CX) with ndless 3.1 and higher.

It is played where you make the active number in each row and column unique from the other numbers in the row and column.  You do this be shifting through the available numbers the cell contains.  For convenience you can lock a cells value.  This is useful when you are sure you have it correct.

How to put on calculator:
Start up TI-NSpire Student Software or whatever you use to put it on the calculator.  Then just drag-n-srop the nCrossSet-sdl.prg.tns file into the application to transfer it to your calculator.  You have to have ndless 3.1 or higher on your calculator in order to run it!

Also included is an external level.  You can add that to your calculator as well.  Once you start the main game it will register the .crs extension; then you can run the level to play it.

How to play:
Every cell has an active number.  That number is in the white font.  That number must be different than the active number for the other cells in that row and column.  You can switch the active number with a different active number that the cell contains.

You use the arrow keys to move around as well as the 2,4,6,8 keys.  Use the Ctrl key to change the active number for the cell.  Use the Shift key to lock a cell.  Locking of a cell prevent you from accidently changing the active value.

Keep playing until you beat the level.

If you do find yourself stuck and unsure how to proceed I added such that the 'a' key will use an algorithm to find a value for you.  This is meant from a starting position but does work mid-game.  But it requires you not to lock a cell unless it is accurate.

Source:
I included my source.  I programmed with C and used nSDL as well as the ndless Software Development Kit.

Contact Me:
A.J. Orians
E-mail: ajorians@gmail.com
