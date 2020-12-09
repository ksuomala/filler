
<html>
<h1>Filler</h1>
<p>This is a Hive Helsinki project I'm working on for the rest of the year. My player works, but the code still needs to be cleaned up to fit the norm of the school. Right now I am learning to use the SDL library to create a graphical visualizer for the game.</p>
<br />
<br />

<h2>What is Filler?</h2>
<p>Filler is a (very famous) game that is played by two players on an arbitrarily sized rectangular board. The goal of the game is (to humiliate your opponent by) placing more pieces on the board than the other player. The game was provided as a Ruby script called filler_vm. In the beginning of the game the VM creates a board of an arbitrary size. On each turn it generates a randomly sized and shaped token. My task is to create a player algorithm written in C. On each turn the Filler VM writes the board(with all the previously placed pieces on it), and a random token(to be placed on the board) to the players stdin. To place the token on the board the player should write the coordinates on the standard output in the form of: Y X\n. 

As a bonus I want to create a graphical interface for the game using the SDL library.</p>
</html>
