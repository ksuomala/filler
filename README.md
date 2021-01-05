
<html>
<h1>Filler</h1>
<p>This is a Hive Helsinki project I was working on in the end of 2020. I created an algorithm that plays the Filler game, and a visualizer for the game.</p>
<br />
<br />

<h2>What is Filler?</h2>
<p>Filler is a (very famous) game that is played by two players on an arbitrarily sized rectangular board. The goal of the game is (to humiliate your opponent by) placing more pieces on the board than the other player. The game was provided as a Ruby script called filler_vm. In the beginning of the game the VM creates a board of an arbitrary size. On each turn it generates a randomly sized and shaped token. My task is to create a player algorithm written in C. On each turn the Filler VM writes the board(with all the previously placed pieces on it), and a random token(to be placed on the board) to the players stdin. To place the token on the board the player should write the coordinates on the standard output in the form of: Y X\n. 

As a bonus I created a visualizer using the SDL graphics library.</p>


</html>
![Screenshot from 2020-12-24 03-03-53.png](![WORLD-ICE](https://github.com/ksuomala/filler/edit/master/Screenshot from 2020-12-24 03-03-53.png)
